#include "minishell.h"

void	run_node(t_node **n, char **input, int *fd, int com_amnt)
{
	pid_t	pid;

	pid = -2;
	if (!n[1]->built)
		pid = fork();
	change_io(n[0], n[1], pid, fd, com_amnt);
	if (pid == -1)
		error_exit(strerror(errno), n[0], n[1]);
	if ((pid == -2) && (n[1]->run(n[1]->params, n[0], n[1]) == 1))
	{
		free(*input);
		*input = strjoin_n_gnl(STDOUT_FILENO);
	}
	else if (pid == 0)
	{
		pipe_handling(n[0], &fd, com_amnt);
		restore_signal();
		n[1]->run(n[1]->params, n[0], n[1]);
	}
	else
		signal_ignore();
}
