#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

void	pipe_handling(int **fd, int len)
{
	int	i;

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
	while (++i < len)
		close(fd[0][i]);
}

void	change_io(int *fd, int com_amnt, int q)
{
	if ((com_amnt != 1) && (q == 1))
		dup2(fd[1], STDOUT_FILENO);
	else if ((com_amnt != 1) && (q == com_amnt))
		dup2(fd[(q * 2) - 4], STDIN_FILENO);
	else if (com_amnt != 1)
	{
		dup2(fd[(2 * q) - 4], STDIN_FILENO);
		dup2(fd[(2 * q) - 1], STDOUT_FILENO);
	}
}

int	main(void)
{
	pid_t	pid;
	int		*fd;
	int		i;
	int		q;

	i = 0;
	fd = malloc(2 * sizeof(int));
	// pipe_handling(&fd, 2);
	while (++i < 2)
	{
		change_io(fd, 2, i);
		pid = fork();
		if ((pid == 0) && (i == 0))
		{
			printf("Hi\n");
			q = -1;
			while (++q < 2)
				close(fd[q]);
			execlp("ls", "ls", NULL);
		}
		else if ((pid == 0) && (i == 1))
		{
			printf("Bye\n");
			q = -1;
			while (++q < 2)
				close(fd[q]);
			execlp("grep", "grep", "mini", NULL);
		}
	}
	q = -1;
	while (++q < 2)
		close(fd[q]);
	waitpid(-1, NULL, 0);
}
