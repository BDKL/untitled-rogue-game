import git
import sys
import subprocess
import os

def compile_and_push_or_commit(repo_path, commit_message):
    try:
        # Check if the argument is 'compile'
        if commit_message.lower() == 'compile':
            # Run scons command in the current directory
            subprocess.run(['scons', 'platform=windows'])
            print("Compilation completed.")
        else:
            # Open the repository
            repo = git.Repo(repo_path)

            # Add all files
            repo.git.add('--all')

            # Commit changes
            repo.index.commit(commit_message)

            # Push changes to the remote repository
            origin = repo.remote(name='origin')
            origin.push()

            print("Changes committed and pushed successfully.")

    except git.exc.GitCommandError as e:
        print(f"Error occurred: {e}")

# Provide the path to your local repository
repository_path = os.getcwd()

# Get the commit message from command line arguments or use a default message
if len(sys.argv) > 1:
    commit_msg = ' '.join(sys.argv[1:])
else:
    commit_msg = 'Default commit message'

# Check if the argument is 'compile' or perform commit and push
if commit_msg.lower() == 'compile':
    # Run scons command in the current directory
    current_directory = os.getcwd()
    subprocess.run(['scons', 'platform=windows'], cwd=current_directory)
    print("Compilation completed.")
else:
    compile_and_push_or_commit(repository_path, commit_msg)