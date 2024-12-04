
async function downloadArtifact(ARTIFACT_ID, JOB_PATH, PR_NUMBER, context, github) {
    if (!ARTIFACT_ID) {
        console.log("Send the comment to PR and exit the job");
        // Create a comment
        const comment = `Failed to create a report:\n Job logs: ${JOB_PATH}`;

        // Post the comment to the pull request
        let prcomment = await github.rest.issues.createComment({
            owner: context.repo.owner,
            repo: context.repo.repo,
            issue_number: PR_NUMBER,
            body: comment,
        });

        process.exit(1);
    } else {
        // Download report.json
        let download = await github.rest.actions.downloadArtifact({
            owner: context.repo.owner,
            repo: context.repo.repo,
            artifact_id: ARTIFACT_ID,
            archive_format: 'zip',
        });

        let fs = require('fs');
        fs.writeFileSync(`${process.env.GITHUB_WORKSPACE}/report.zip`, Buffer.from(download.data));

        console.log("Artifact downloaded successfully.");
    }
}

async function createComment(github, context) {
    const { issue_number, Passes, Failures, Pending, Skipped, ARTIFACT_URL, JOB_PATH } = process.env;

    const body = `
        Core SDK - MFOS standalone sanity report:
        Passes - ${Passes} Failures - ${Failures} Pending - ${Pending} Skipped - ${Skipped}
        Report JSON/HTML Files: ${ARTIFACT_URL}
        Job Logs: ${JOB_PATH}
    `;

    const response = await github.rest.issues.createComment({
        owner: context.repo.owner,
        repo: context.repo.repo,
        issue_number: issue_number,
        body: body.trim()
    });

    console.log('Comment updated successfully.');
}

module.exports = { downloadArtifact, createComment };