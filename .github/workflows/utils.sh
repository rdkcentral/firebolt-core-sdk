#!/bin/bash
set -o pipefail

# function runTests(){
#   MODULE="$1" # Pass the module name (core, manage, discovery)

#   echo "Clone firebolt-apis repo with pr branch"
#   PR_BRANCH=$(echo "$EVENT_NAME" | tr '[:upper:]' '[:lower:]')
#   if [ "${PR_BRANCH}" == "pull_request" ]; then
#     PR_BRANCH=$PR_HEAD_REF
#   elif [ "${PR_BRANCH}" == "push" ]; then
#     PR_BRANCH=$GITHUB_REF
#     PR_BRANCH="${PR_BRANCH#refs/heads/}"
#   else
#     echo "Unsupported event: $EVENT_NAME"
#     exit 1
#   fi

#   git clone --branch ${PR_BRANCH} https://github.com/rdkcentral/firebolt-apis.git
#   echo "cd to firebolt-apis repo and compile firebolt-open-rpc.json"
#   cd firebolt-apis
#   npm i
#   npm run compile
#   npm run dist
#   cd ..

#   echo "clone mfos repo and start it in the background"
#   git clone https://github.com/rdkcentral/mock-firebolt.git
#   cd mock-firebolt/server
#   cp ../../firebolt-apis/dist/firebolt-open-rpc.json ../../mock-firebolt/server/src/firebolt-open-rpc.json
#   jq 'del(.supportedOpenRPCs[] | select(.name == "core"))' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
#   jq '.supportedOpenRPCs += [{"name": "core","cliFlag": null,"cliShortFlag": null,"fileName": "firebolt-open-rpc.json","enabled": true}]' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
#   cp src/.mf.config.SAMPLE.json src/.mf.config.json
#   npm install
#   npm start &
#   cd ..//..

#   echo "clone fca repo and start it in the background"
#   git clone --branch main https://github.com/rdkcentral/firebolt-certification-app.git
#   cd firebolt-certification-app
  
#   if [ "$MODULE" == "manage" ]; then
#     echo "Updating dependency to Manage SDK"
#     jq '.dependencies["@firebolt-js/sdk"] = "file:../firebolt-apis/src/sdks/manage"' package.json > package.json.tmp && mv package.json.tmp package.json
#   elif [ "$MODULE" == "discovery" ]; then
#     echo "Updating dependency to Discovery SDK"
#     jq '.dependencies["@firebolt-js/sdk"] = "file:../firebolt-apis/src/sdks/discovery"' package.json > package.json.tmp && mv package.json.tmp package.json
#   else
#     echo "Running Core by default"
#     jq '.dependencies["@firebolt-js/sdk"] = "file:../firebolt-apis/src/sdks/core"' package.json > package.json.tmp && mv package.json.tmp package.json
#   fi

#   npm install
#   npm start &
#   sleep 5s
#   cd ..

#   echo "curl request with runTest install on initialization"
#   response=$(curl -X POST -H "Content-Type: application/json" -d "$INTENT" http://localhost:3333/api/v1/state/method/parameters.initialization/result)

#   echo "run mfos tests in a headless browser"
#   npm install puppeteer
#   echo "Start xvfb"
#   Xvfb :99 -screen 0 1024x768x24 > /dev/null 2>&1 &
#   export DISPLAY=:99

#   echo "Run headless browser script with puppeteer"
#   node -e '
#     const puppeteer = require("puppeteer");
#     const fs = require("fs");
#     (async () => {
#       const browser = await puppeteer.launch({ headless: true, args: ["--no-sandbox", "--disable-gpu"] });
#       const page = await browser.newPage();

#       // Enable console logging
#       page.on("console", (msg) => {
#       let logMessage="";
#       if (msg.type().includes("log")) {
#        logMessage = `${msg.text()}`;
#        console.log(logMessage);
#       }
#      if (logMessage.includes("Response String:")) {
#         const jsonStringMatch = logMessage.match(/Response String:(.*)/);
#         if (jsonStringMatch && jsonStringMatch[1]) {
#           try {
#             const jsonString = jsonStringMatch[1].trim();
#             const responseString = JSON.parse(jsonString);
#             console.log("Parsed JSON:", responseString);
#             const filePath="report.json"
#             fs.writeFileSync(filePath, JSON.stringify(responseString), "utf-8");
#             console.log(`Parsed JSON written to ${filePath}`);
#             // Exit the Node.js script
#             process.exit(0);

#           } catch (error) {
#             console.error("Error parsing JSON:", error);
#           }
#         }
#       }
#     });
#       // Navigate to the URL
#       await page.goto("http://localhost:8081/?mf=ws://localhost:9998/12345&standalone=true");

#      // Sleep for 80 seconds (80,000 milliseconds)
#      await new Promise(resolve => setTimeout(resolve, 80000));

#       // Close the browser
#       await browser.close();
#     })();
#   '
#   echo "Create HTML and JSON assets for ${MODULE}"
#   npm i mochawesome-report-generator
#   echo $MODULE
#   echo "report/$MODULE"
#   echo "report/${MODULE}"
#   mkdir -p report/$MODULE
#   # Move the report.json to the correct location
#     if [ -f report.json ]; then
#       mv report.json report/$MODULE/
#     else
#       echo "report.json not found for $MODULE"
#       exit 1
#     fi

#      # Check if the module directory exists
#   if [ ! -d report/$MODULE ]; then
#     echo "Module directory report/$MODULE does not exist."
#     exit 1
#   fi

#   # Debugging output to see the directory contents
#   ls -ltr report/$MODULE/
  
#   # Process report.json
#   echo "HELLO"
#   # Check if the module directory exists
#   echo "Checking if directory report/${MODULE} exists"
#   if [ ! -d report/${MODULE} ]; then
#       echo "Module directory report/${MODULE} does not exist."
#       exit 1
#   fi

#   # Now check for the report.json file in the correct directory
#   echo "Checking for report.json at report/${MODULE}/report.json"
#   if [ -f report/${MODULE}/report.json ]; then
#       echo "Found report.json"
#       jq -r '.' report/${MODULE}/report.json > tmp.json && mv tmp.json report/${MODULE}/report.json
#       jq '.report' report/${MODULE}/report.json > tmp.json && mv tmp.json report/${MODULE}/report.json
#   else
#       echo "report.json not found at report/${MODULE}/report.json"
#       exit 1
#   fi
#   echo "Checking for report generator"

#   node -e "
#   const marge = require('mochawesome-report-generator/bin/cli-main');
#   marge({
#     _: ['report/${MODULE}/report.json'],
#     reportFileName: 'report.json',
#     reportTitle: 'FireboltCertificationTestReport',
#     reportPageTitle: 'FireboltCertificationTestReport',
#     reportDir: './report/${MODULE}',
#   });
# "
# }

function check_port() {
  local PORT=$1
  # Check if port is in use
  if lsof -i :$PORT > /dev/null; then
    echo "Port $PORT is already in use"
    # Kill the process using the port
    PID=$(lsof -t -i :$PORT)
    if [ ! -z "$PID" ]; then
      echo "Killing process $PID using port $PORT"
      kill -9 $PID
      echo "Port $PORT is now free"
    fi
  else
    echo "Port $PORT is available"
  fi
}

function runTests(){
  MODULE="$1" # Pass the module name 

  # Clone firebolt-apis repo if it doesn't already exist
 # if [ ! -d "firebolt-apis" ]; then
    echo "Clone firebolt-apis repo with PR branch"
    PR_BRANCH=$(echo "$EVENT_NAME" | tr '[:upper:]' '[:lower:]')
    if [ "${PR_BRANCH}" == "pull_request" ]; then
      PR_BRANCH=$PR_HEAD_REF
    elif [ "${PR_BRANCH}" == "push" ]; then
      PR_BRANCH=$GITHUB_REF
      PR_BRANCH="${PR_BRANCH#refs/heads/}"
    else
      echo "Unsupported event: $EVENT_NAME"
      exit 1
    fi

    git clone --branch ${PR_BRANCH} https://github.com/rdkcentral/firebolt-apis.git
    echo "cd to firebolt-apis repo and compile firebolt-open-rpc.json"
    cd firebolt-apis
    npm i
    npm run compile
    npm run dist
    cd ..
 # else
 #   echo "firebolt-apis repo already exists. Skipping clone."
  # fi

  # Clone mock-firebolt repo if it doesn't already exist
 # if [ ! -d "mock-firebolt" ]; then
    echo "Cloning mfos repo and start it in the background"
    git clone https://github.com/rdkcentral/mock-firebolt.git
    cd mock-firebolt/server
    cp ../../firebolt-apis/dist/firebolt-open-rpc.json ../../mock-firebolt/server/src/firebolt-open-rpc.json
    jq --arg MODULE "$MODULE" 'del(.supportedOpenRPCs[] | select(.name == $MODULE))' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
    jq --arg MODULE "$MODULE" '.supportedOpenRPCs += [{"name": $MODULE, "cliFlag": null, "cliShortFlag": null, "fileName": "firebolt-open-rpc.json", "enabled": true}]' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
   # jq 'del(.supportedOpenRPCs[] | select(.name == "core"))' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
   # jq '.supportedOpenRPCs += [{"name": "core","cliFlag": null,"cliShortFlag": null,"fileName": "firebolt-open-rpc.json","enabled": true}]' src/.mf.config.SAMPLE.json > src/.mf.config.SAMPLE.json.tmp && mv src/.mf.config.SAMPLE.json.tmp src/.mf.config.SAMPLE.json
    cp src/.mf.config.SAMPLE.json src/.mf.config.json
    npm install
    npm start &
    cd ../..
 # else
 #   echo "mock-firebolt repo already exists. Skipping clone."
  # fi

  # Clone Firebolt Certification App (FCA) if it doesn't exist
 # if [ ! -d "firebolt-certification-app" ]; then
    echo "Clone FCA repo"
    git clone --branch main https://github.com/rdkcentral/firebolt-certification-app.git
 # fi

  echo "Updating dependency for ${MODULE} in FCA"
  cd firebolt-certification-app

  check_port 8081
  
  if [ "$MODULE" == "manage" ]; then
    echo "Updating dependency to Manage SDK"
    jq '.dependencies["@firebolt-js/manage-sdk"] = "file:../firebolt-apis/src/sdks/manage"' package.json > package.json.tmp && mv package.json.tmp package.json
  elif [ "$MODULE" == "discovery" ]; then
    echo "Updating dependency to Discovery SDK"
    jq '.dependencies["@firebolt-js/discovery-sdk"] = "file:../firebolt-apis/src/sdks/discovery"' package.json > package.json.tmp && mv package.json.tmp package.json
  else
    echo "Running Core by default"
    jq '.dependencies["@firebolt-js/sdk"] = "file:../firebolt-apis/src/sdks/core"' package.json > package.json.tmp && mv package.json.tmp package.json
  fi

  npm install
  npm start &
  sleep 5s
  cd ..

  
  echo "curl request with runTest install on initialization"
  response=$(curl -X POST -H "Content-Type: application/json" -d "$INTENT" http://localhost:3333/api/v1/state/method/parameters.initialization/result)
  # response=$(curl -X POST -H "Content-Type: application/json" -d "MANAGE" http://localhost:3333/api/v1/state/method/parameters.initialization/result)
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

  echo "Create HTML and JSON assets for ${MODULE}"
  npm i mochawesome-report-generator
  echo $MODULE
  echo "report/$MODULE"
  echo "report/${MODULE}"
  mkdir -p report/$MODULE
  # Move the report.json to the correct location
  if [ -f report.json ]; then
    mv report.json report/$MODULE/
  else
    echo "report.json not found for $MODULE"
    exit 1
  fi

  # Check if the module directory exists
  if [ ! -d report/$MODULE ]; then
    echo "Module directory report/$MODULE does not exist."
    exit 1
  fi

  # Debugging output to see the directory contents
  ls -ltr report/$MODULE/
  
  # Process report.json
  echo "HELLO"
  # Check if the module directory exists
  echo "Checking if directory report/${MODULE} exists"
  if [ ! -d report/${MODULE} ]; then
    echo "Module directory report/${MODULE} does not exist."
    exit 1
  fi

  # Now check for the report.json file in the correct directory
  echo "Checking for report.json at report/${MODULE}/report.json"
  if [ -f report/${MODULE}/report.json ]; then
    echo "Found report.json"
    jq -r '.' report/${MODULE}/report.json > tmp.json && mv tmp.json report/${MODULE}/report.json
    jq '.report' report/${MODULE}/report.json > tmp.json && mv tmp.json report/${MODULE}/report.json
  else
    echo "report.json not found at report/${MODULE}/report.json"
    exit 1
  fi
  echo "Checking for report generator"

  node -e "
  const marge = require('mochawesome-report-generator/bin/cli-main');
  marge({
    _: ['report/${MODULE}/report.json'],
    reportFileName: 'report.json',
    reportTitle: 'FireboltCertificationTestReport',
    reportPageTitle: 'FireboltCertificationTestReport',
    reportDir: './report/${MODULE}',
  });
"
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

# Check argument and call corresponding function
if [ "$1" == "runTests" ]; then
    runTests "$2"
elif [ "$1" == "getResults" ]; then
    getResults
elif [ "$1" == "getArtifactData" ]; then
    getArtifactData
elif [ "$1" == "unzipArtifact" ]; then
    unzipArtifact
else
    echo "Invalid function specified."
    exit 1
fi