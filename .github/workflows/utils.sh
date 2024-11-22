#!/bin/bash
set -o pipefail

current_apis_dir=$(pwd)

cd ..
current_dir=$(pwd)
cd $current_apis_dir

# Function to check if a branch exists in the remote repository
function branch_exists() {
    local branch=$1
    git ls-remote --heads https://github.com/rdkcentral/firebolt-apis.git "$branch" | grep -q "$branch"
}

function runTests(){
  echo "Determine the branch to checkout"
  # Convert event name to lowercase
  PR_BRANCH=$(echo "$EVENT_NAME" | tr '[:upper:]' '[:lower:]')

  # Check if OPENRPC_PR_BRANCH is not empty and the event is repository_dispatch
  if [ -n "$OPENRPC_PR_BRANCH" ] && [ "$PR_BRANCH" == "repository_dispatch" ]; then
      # Check if the branch exists in firebolt-apis
      if branch_exists "$OPENRPC_PR_BRANCH"; then
          PR_BRANCH=$OPENRPC_PR_BRANCH
          echo "Using branch from OPENRPC_PR_BRANCH: $OPENRPC_PR_BRANCH"
      else
          echo "Branch '$OPENRPC_PR_BRANCH' does not exist in firebolt-apis. Defaulting to 'next'."
          PR_BRANCH="next"
      fi
  elif [ "$PR_BRANCH" == "pull_request" ]; then
      # If it's a pull request event, use the PR branch
      PR_BRANCH=$PR_HEAD_REF
  elif [ "$PR_BRANCH" == "push" ]; then
      # For push events, extract the branch name
      PR_BRANCH=$GITHUB_REF
      PR_BRANCH="${PR_BRANCH#refs/heads/}"
  else
      echo "Unsupported event: $EVENT_NAME"
      exit 1
  fi

  echo "Cloning firebolt-apis repo with branch: $PR_BRANCH"
  git clone --branch ${PR_BRANCH} https://github.com/rdkcentral/firebolt-apis.git
  echo "cd to firebolt-apis repo and compile firebolt-open-rpc.json"
  cd firebolt-apis
  if [ "$EVENT_NAME" == "repository_dispatch" ]; then
  # If OPENRPC_PR_BRANCH is set and is not 'next'
    if [ -n "$OPENRPC_PR_BRANCH" ] && [ "$OPENRPC_PR_BRANCH" != "next" ]; then
      echo "Updating OpenRPC dependency to branch: $OPENRPC_PR_BRANCH"
      jq ".dependencies[\"@firebolt-js/openrpc\"] = \"file:../firebolt-openrpc#$OPENRPC_PR_BRANCH\"" package.json > package.json.tmp && mv package.json.tmp package.json
    fi
  fi
  npm i
  npm run compile
  npm run dist
  cd ..

  echo "clone mfos repo and start it in the background"
  git clone https://github.com/rdkcentral/mock-firebolt.git
  cd mock-firebolt/server
  cp ../../firebolt-apis/dist/firebolt-open-rpc.json ../../mock-firebolt/server/src/firebolt-open-rpc.json
  jq 'del(.supportedOpenRPCs[] | select(.name == "core"))' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
  jq '.supportedOpenRPCs += [{"name": "core","cliFlag": null,"cliShortFlag": null,"fileName": "firebolt-open-rpc.json","enabled": true}]' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
  cp src/.mf.config.SAMPLE.json src/.mf.config.json
  npm install
  npm start &
  cd ..//..

  echo "clone fca repo and start it in the background"
  git clone --branch main https://github.com/rdkcentral/firebolt-certification-app.git
  cd firebolt-certification-app
  jq '.dependencies["@firebolt-js/sdk"] = "file:../firebolt-apis/src/sdks/core"' package.json > package.json.tmp && mv package.json.tmp package.json
  npm install
  npm start &
  sleep 5s
  cd ..

  echo "curl request with runTest install on initialization"
  response=$(curl -X POST -H "Content-Type: application/json" -d "$INTENT" http://localhost:3333/api/v1/state/method/parameters.initialization/result)

  echo "run mfos tests in a headless browser"
  npm install puppeteer
  echo "Start xvfb"
  Xvfb :99 -screen 0 1024x768x24 > /dev/null 2>&1 &
  export DISPLAY=:99

  echo "Run headless browser script with puppeteer"
  node -e '
    const puppeteer = require("puppeteer");
    const fs = require("fs");
    (async () => {
      const browser = await puppeteer.launch({ headless: true, args: ["--no-sandbox", "--disable-gpu"] });
      const page = await browser.newPage(); 

      // Enable console logging
      page.on("console", (msg) => {
      let logMessage="";
      if (msg.type().includes("log")) {
       logMessage = `${msg.text()}`;
       console.log(logMessage);
      }
     if (logMessage.includes("Response String:")) {
        const jsonStringMatch = logMessage.match(/Response String:(.*)/);
        if (jsonStringMatch && jsonStringMatch[1]) {
          try {
            const jsonString = jsonStringMatch[1].trim();
            const responseString = JSON.parse(jsonString);
            console.log("Parsed JSON:", responseString);
            const filePath="report.json"
            fs.writeFileSync(filePath, JSON.stringify(responseString), "utf-8");
            console.log(`Parsed JSON written to ${filePath}`);
            // Exit the Node.js script
            process.exit(0);

          } catch (error) {
            console.error("Error parsing JSON:", error);
          }
        }
      }
    });
      // Navigate to the URL
      await page.goto("http://localhost:8081/?mf=ws://localhost:9998/12345&standalone=true");

     // Sleep for 80 seconds (80,000 milliseconds)
     await new Promise(resolve => setTimeout(resolve, 80000));

      // Close the browser
      await browser.close();
    })();
  '
  echo "create html and json assets"
  npm i mochawesome-report-generator
  mkdir report
  mv report.json report/
  jq -r '.' report/report.json > tmp.json && mv tmp.json report/report.json
  jq '.report' report/report.json > tmp.json && mv tmp.json report/report.json
  node -e '
  const marge = require("mochawesome-report-generator/bin/cli-main");
  marge({
    _: ["report/report.json"],
    reportFileName: "report.json",
    reportTitle: "FireboltCertificationTestReport",
    reportPageTitle: "FireboltCertificationTestReport",
    reportDir: "./report",
  });
  '
}

function getResults(){
  failures=$(cat report/report.json | jq -r '.stats.failures')
  echo "If failures more than 0, fail the job"
  echo "Failures=$failures"
  if [ "$failures" -eq 0 ]; then
    echo "No failures detected."
  else
    exit 1
  fi
}

function getArtifactData(){
  PREVIOUS_JOB_ID=$(jq -r '.id' <<< "$WORKFLOW_RUN_EVENT_OBJ") && echo "PREVIOUS_JOB_ID=$PREVIOUS_JOB_ID" >> "$GITHUB_ENV"
  SUITE_ID=$(jq -r '.check_suite_id' <<< "$WORKFLOW_RUN_EVENT_OBJ") && echo "SUITE_ID=$SUITE_ID" >> "$GITHUB_ENV"
  ARTIFACT_ID=$(gh api "/repos/$OWNER/$REPO/actions/artifacts" --jq ".artifacts[] | select(.workflow_run.id==$PREVIOUS_JOB_ID and .expired==false) | .id") && echo "ARTIFACT_ID=$ARTIFACT_ID" >> "$GITHUB_ENV"
  PR_NUMBER=$(jq -r '.pull_requests[0].number' <<< "$WORKFLOW_RUN_EVENT_OBJ") && echo "PR_NUMBER=$PR_NUMBER" >> "$GITHUB_ENV"
  ARTIFACT_URL="$SERVER_URL/$GITHUB_REPO/suites/$SUITE_ID/artifacts/$ARTIFACT_ID" && echo "ARTIFACT_URL=$ARTIFACT_URL" >> "$GITHUB_ENV"
  JOB_PATH="$SERVER_URL/$GITHUB_REPO/actions/runs/$PREVIOUS_JOB_ID" && echo "JOB_PATH=$JOB_PATH" >> "$GITHUB_ENV"
}

function unzipArtifact(){
  unzip report.zip
  # Extract values from report.json
  report=$(cat report.json | jq -r '.')
  passes=$(echo "$report" | jq -r '.stats.passes')
  failures=$(echo "$report" | jq -r '.stats.failures')
  pending=$(echo "$report" | jq -r '.stats.pending')
  skipped=$(echo "$report" | jq -r '.stats.skipped')
  echo "Skipped=$skipped" >> "$GITHUB_ENV"
  echo "Pending=$pending" >> "$GITHUB_ENV"
  echo "Passes=$passes" >> "$GITHUB_ENV"
  echo "Failures=$failures" >> "$GITHUB_ENV"
}

function cloneAndInstallThunder() {
  cd ..

  git clone https://github.com/rdkcentral/Thunder.git

  cd Thunder

  git checkout 283b3d54334010403d85a4e69b3835de23e42331

  cd ..

  git clone https://github.com/rdkcentral/ThunderTools.git

  cd ThunderTools

  git checkout 64b72b5ed491436b0e6bc2327d8a7b0e75ee2870

  cd ..

  echo "current_dir is $current_dir"

  mkdir -p $current_dir/data

  if [ ! -d "$(pwd)/Thunder" ] 
  then
      echo "Directory Thunder DOES NOT exist." 
      exit 9999
  fi

  if [ ! -d "$(pwd)/ThunderTools" ]
  then
      echo "Directory ThunderTools DOES NOT exist."
      exit 9999
  fi

  if [ ! -d "$current_dir/firebolt-apis" ]
  then
      echo "Directory $current_dir/firebolt-apis DOES NOT exist."
      exit 9999
  fi

  cd $current_dir

  [ -d "$current_dir/build" ] && rm -rf $current_dir/build

  echo "Building Thunder";

  cmake -G Ninja -S ThunderTools -B build/ThunderTools -DCMAKE_INSTALL_PREFIX="install/usr" && echo "Tools Setup" || exit 9999

  cmake --build build/ThunderTools --target install && echo "Thunder Tools Build succeeded" || exit 9999

  #-G Ninja is the "Build system generator"
  #-S is the source path
  #-B is the output directory
  cmake -G Ninja -S Thunder -B build/Thunder \
  -DBUILD_SHARED_LIBS=ON \
  -DBINDING="127.0.0.1" \
  -DCMAKE_BUILD_TYPE="Debug" \
  -DCMAKE_INSTALL_PREFIX="install/usr" \
  -DCMAKE_MODULE_PATH="${PWD}/install/usr/include/WPEFramework/Modules" \
  -DDATA_PATH="${PWD}/install/usr/share/WPEFramework" \
  -DPERSISTENT_PATH="${PWD}/install/var/wpeframework" \
  -DPORT="55555" \
  -DPROXYSTUB_PATH="${PWD}/install/usr/lib/wpeframework/proxystubs" \
  -DSYSTEM_PATH="${PWD}/install/usr/lib/wpeframework/plugins" \
  -DVOLATILE_PATH="tmp" && echo "Thunder configure succeeded" || exit 9999

  cmake --build build/Thunder --target install && echo "Thunder Build succeeded" || exit 9999
}


function generate_cpp_sdk_source_code(){
  local sdk_name=$1

  echo " ************ Genrate Source Code for ${sdk_name^} CPP SDK ************"

  cd src/sdks/${sdk_name}
  npm run cpp
}

function build_cpp_sdk() {
  
  FIREBOLT_VERSION=$(node -p "require('./package.json').version")
  echo "The version from package.json is $FIREBOLT_VERSION"
  local sdk_name=$1
  
  echo " ************ Build ${sdk_name^} CPP SDK ************"

  cd /__w/firebolt-apis/firebolt-apis/src/sdks/${sdk_name}/build/cpp/src/firebolt-${sdk_name}-native-sdk-${FIREBOLT_VERSION}/
  chmod +x ./build.sh

  ./build.sh -s "/__w/thunder/install/" || exit 9999
}

# Check argument and call corresponding function
case "$1" in 
  runTests) runTests ;;
  getResults) getResults ;;
  getArtifactData) getArtifactData ;;
  unzipArtifact) unzipArtifact ;;
  generate_cpp_core_sdk_source_code) generate_cpp_sdk_source_code "core"  ;;
  generate_cpp_manage_sdk_source_code) generate_cpp_sdk_source_code "manage"  ;;
  generate_cpp_discovery_sdk_source_code) generate_cpp_sdk_source_code "discovery"  ;;
  cloneAndInstallThunder) cloneAndInstallThunder ;;
  build_core_cpp_sdk) build_cpp_sdk "core" ;;
  build_manage_cpp_sdk) build_cpp_sdk "manage" ;;
  build_discovery_cpp_sdk) build_cpp_sdk "discovery" ;;
  *)
    echo "Invalid function specified."
    exit 1
    ;;
esac
