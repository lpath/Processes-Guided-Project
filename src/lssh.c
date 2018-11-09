/**
 * lssh: Lambda School Shell
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define MAX_COMMANDLINE_LEN 8192
#define MAX_COMMANDLINE_ARGS 128

/**
 * Break up a command line string into an array of char*s.
 *
 * ls -la /
 *
 * becomes:
 *
 * exec_commands[0] == "ls"
 * exec_commands[1] == "-la"
 * exec_commands[2] == "/"
 * exec_commands[3] == NULL
 */
void parse_commandline(char *commandline, char *exec_commands[], int max_count)
{
	char *sep = " \r\n\t"; // whitespace separators
	char *token;
	char *str = commandline;
	int i = 0;
	
	// Read individual tokens and store them in exec_commands
	while ((token = strtok(str, sep)) != NULL && i < max_count) {
		str = NULL; // pass NULL for all subsequent calls to strtok

		exec_commands[i++] = token;
	}

	// Add NULL terminator for execv
	exec_commands[i] = NULL;
}

/**
 * Main
 */
int main(void)
{
	char commandline[MAX_COMMANDLINE_LEN];
	char *exec_commands[MAX_COMMANDLINE_ARGS];

	while (printf("$ "), fgets(commandline, sizeof commandline, stdin) != NULL) {

		// -1 to leave room for NULL terminator
		parse_commandline(commandline, exec_commands, MAX_COMMANDLINE_ARGS-1);

		// Handle empty command
		if (exec_commands[0] == NULL) {
			continue;
		}

		// Handle built-ins
		if (strcmp(exec_commands[0], "exit") == 0) {
			// Exit
			exit(0);

		} else if (strcmp(exec_commands[0], "cd") == 0) {
			// Chdir

			// Check for correct usage
			if (exec_commands[1] == NULL || exec_commands[2] != NULL) {
				fprintf(stderr, "usage: cd dirname\n");
				continue;
			}

			// Change directory
			if (chdir(exec_commands[1]) == -1) {
				perror("chdir");
			}
			
			continue;
		}

		// Try to fork and exec the requested process
		pid_t pid = fork();

		if (pid == 0) {
			execvp(exec_commands[0], exec_commands);
			perror("exec");
			exit(1);
		} else {
			wait(NULL);
		}
	}

	return 0;
}
