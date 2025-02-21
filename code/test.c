#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/wait.h>

int	main(void)
{
	int	new_fd[2];
	int	old_fd[2];
	int	pid;
	int	limit;
	int	i;

	i = -1;
	limit = 2;
	while (++i < limit)
	{
		if(i == 0)
			pipe(old_fd);
		else if (i == 1)
			pipe(new_fd);
		printf("Running\n");
		pid = fork();
		if (pid == 0)
		{
			printf("In Pipe |");
			printf(" Process %d\n", i);
			if (i != 0)
				dup2(old_fd[0], STDIN_FILENO);
			if (i != limit - 1)
				dup2(old_fd[1], STDOUT_FILENO);
			if (i == 0)
			{
				close(old_fd[0]);
				close(old_fd[1]);
				execlp("ls", "ls", NULL);
			}
			else if (i == (limit - 1))
			{
				close(new_fd[0]);
				close(new_fd[1]);
				execlp("grep", "grep", "mini", NULL);
			}
		}
		if (pid != 0)
		{
			if (i == 0)
			{
				close(old_fd[0]);
				close(old_fd[1]);
			}
			else if (i == 1)
			{
				close(new_fd[0]);
				close(new_fd[1]);
			}
			waitpid(pid, NULL, 0);
		}
	}
	return (0);
}
