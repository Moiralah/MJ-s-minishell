#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main()
{
	pid_t	pid;
	//int	new_fd[2];
	int	fd[4];
	int	i;

	i = -1;
	while (++i < 2)
		pipe(fd + 2 * i);
	i = -1;
	while (++i < 3)
	{
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
			{
				dup2(fd[1], STDOUT_FILENO);
				int	q = -1;
				while (++q < 4)
					close(fd[q]);
				execlp("ls", "ls", NULL);
			}
			else if (i == 1)
			{
				dup2(fd[0], STDIN_FILENO);
				dup2(fd[3], STDOUT_FILENO);
				int	q = -1;
				while (++q < 4)
					close(fd[q]);
				execlp("grep", "grep", ".c", NULL);
			}
			else if (i == 2)
			{
				dup2(fd[2], STDIN_FILENO);
				int	q = -1;
				while (++q < 4)
					close(fd[q]);
				execlp("wc", "wc", "-l", NULL);
			}
		}
	}
	i  = -1;
	while (++i < 4)
		close(fd[i]);
	waitpid(-1, NULL, 0);
}
