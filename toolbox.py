import git
import sys
import subprocess
import os

def update_repo(repo_path):
    try:
        # Open the repository
        repo = git.Repo(repo_path)

        # Fetch changes from the remote repository
        origin = repo.remote(name='origin')
        origin.fetch()

        # Merge changes
        repo.git.merge('origin/master') 

        print("Repository updated successfully.")

    except git.exc.GitCommandError as e:
        print(f"Error occurred: {e}")

def compile_and_push_or_commit(repo_path, commit_message):
    try:
        
        if commit_message.lower() == 'compile':
            # Run scons command in the current directory
            subprocess.run(['scons', 'platform=windows'])
            print("Compilation completed.")
        else:
            update_repo(repo_path)
            repo = git.Repo(repo_path)

            # Add all files
            repo.git.add('--all')

            # Commit changes
            repo.index.commit(commit_message)

            # Push changes to the repo
            origin = repo.remote(name='origin')
            origin.push()

            print("Changes committed and pushed successfully.")

    except git.exc.GitCommandError as e:
        print(f"Error occurred: {e}")

repository_path = os.getcwd()

if len(sys.argv) > 1:
    commit_msg = ' '.join(sys.argv[1:])
else:
    commit_msg = 'Default commit message'


if commit_msg.lower() == 'compile':
    # Run scons command in the current directory
    current_directory = os.getcwd()
    subprocess.run(['scons', 'platform=windows'], cwd=current_directory)
    print("Compilation completed.")
elif commit_msg.lower() == 'update':
    update_repo(repository_path)
else:
    compile_and_push_or_commit(repository_path, commit_msg)
