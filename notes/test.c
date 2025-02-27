#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void	pipe_handling(int **fd, int len)
{
	int     i;

	i = -1;
	if (len == 0)
		return ;
	if (fd[0] == NULL)
	{
		if (len <= 1)
			fd[0] = calloc(2, sizeof(int));
		else
			fd[0] = calloc((len - 1) * 2, sizeof(int));
		if (len <= 1)
			len = 2;
		while (++i < (len - 1))
			pipe(fd[0] + (2 * i));
		return ;
	}
	while (++i < (len - 1) * 2)
		close(fd[0][i]);
	free(fd[0]);
}

int	main()
{
	pid_t	pid;
	int	*fd;
	int	limit;
	int	i;

	fd = NULL;
	limit = 3;
	pipe_handling(&fd, limit);
	i = -1;
	while (++i < limit)
	{
		/* if (i == 0)
			dup2(fd[1], STDOUT_FILENO);
		else if (i == 1)
		{
			dup2(fd[0], STDIN_FILENO);
			dup2(fd[3], STDOUT_FILENO);
		}
		else
			dup2(fd[2], STDIN_FILENO); */
		pid = fork();
		if (pid == 0)
		{
			if (i == 0)
				dup2(fd[1], STDOUT_FILENO);
			else if (i == 1)
			{
				dup2(fd[0], STDIN_FILENO);
				dup2(fd[3], STDOUT_FILENO);
			}
			else
				dup2(fd[2], STDIN_FILENO);
			if (i == 0)
			{
				// dup2(fd[1], STDOUT_FILENO);
				pipe_handling(&fd, limit);
				/* int	q = -1;
				while (++q < 4)
					close(fd[q]); */
				execlp("ls", "ls", NULL);
			}
			else if (i == 1)
			{
				/* dup2(fd[0], STDIN_FILENO);
				dup2(fd[3], STDOUT_FILENO); */
				pipe_handling(&fd, limit);
				/* int	q = -1;
				while (++q < 4)
					close(fd[q]); */
				execlp("grep", "grep", ".c", NULL);
			}
			else if (i == 2)
			{
				// dup2(fd[2], STDIN_FILENO);
				pipe_handling(&fd, limit);
				/* int	q = -1;
				while (++q < 4)
					close(fd[q]); */
				execlp("wc", "wc", "-l", NULL);
			}
		}
	}
	pipe_handling(&fd, limit);
	/* int	q = -1;
	while (++q < 4)
		close(fd[q]); */
	waitpid(-1, NULL, 0);
}
