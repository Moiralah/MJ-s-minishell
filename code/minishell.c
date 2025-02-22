#include "minishell.h"

void	executing(t_node start_node, int i)
{
	t_node	cur_node;
	pid_t	pid;
	int		*fd;
	int		q;

	cur_node = start_node;
	fd = ft_calloc((i - 1) * 2, sizeof(int));
	q = -1;
	while (++q < (i - 1))
		pipe(fd + (2 * q));
	q = 0;
	while ((cur_node != NULL) && (++q))
	{
		pid = fork();
		if (pid < 0)
			error_exit(strerror(errno));
		else if ((pid == 0) && (q == 1))
			dup2(fd[1], STDOUT_FILENO);
		else if ((pid == 0) && (q == i))
			dup2(fd[(q * 2) - 4], STDIN_FILENO);
		else if (pid == 0)
		{
			dup2(fd[(2 * q) - 4], STDIN_FILENO);
			dup2(fd[(2 * q) - 1], STDOUT_FILENO);
		}
		if (pid == 0)
		{
			close_pipe(fd, (i - 1) * 2);
			cur_node->run(cur_node->params);
			break;
		}
		cur_node = cur_node->next;
	}
	close_pipe(fd, (i - 1) * 2);
	waitpid(-1, NULL, 0);
}

t_node	linking(t_node cur_node, char *comm)
{
	char	*input;

	comm = fnames_to_node(cur_node, comm, '<');
	while (cur_node->next != NULL)
		cur_node = cur_node->next;
	input = cur_node->params[1];
	comm = fnames_to_list(cur_node, comm, '>');
	while (cur_node->next != NULL)
		cur_node = cur_node->next;
	if (ft_strncmp(input, cur_node->params[1], ft_strlen(input)) == 0)
		error_exit(-1);
	cur_node->next = function_matching(comm);
	return (cur_node->next);
}

void	initialising(chra **comms, char **envp)
{
	t_node	*nodes[2];
	char	**comms;
	int		i;

	i = -1;
	while (comms[++i] != '\0')
	{
		nodes[1] = linking(nodes[1], comms[i]);
		if (i == 0)
			nodes[0] = nodes[1];
	}
	free(comms);
	nodes[0]->envp = init_envp(envp);
	executing(nodes[0], i);
	while (nodes[0]->envp != NULL)
		remove_link(nodes[0]->envp, nodes[0]->envp, NULL);
	while (nodes[0] != NULL)
	{
		nodes[1] = nodes[0];
		nodes[0] = nodes[0]->next;
		free(nodes[1]);
	}
}

char	*listening(int i, int q)
{
	char	*line;

	line = readline("MJ > ");
	while (line[i] != "\0")
	{
		q = 0;
		if ((line[i] == '"') && ft_strchr(line + i + 1, '"'))
			i = ft_strchr(line + i + 1, '"') - line;
		else if ((line[i] == '"') && !ft_strchr(line + i + 1, '"'))
			q = 1;
		else if ((line[i] == ''') && ft_strchr(line + i + 1, '''))
			i = ft_strchr(line + i + 1, 39) - line;
		else if ((line[i] == ''') && !ft_strchr(line + i + 1, '''))
			q = 1;
		if (q)
		{
			line = ft_strjoin(line, "\n");
			line = ft_strjoin(line, readline("> "));
		}
		else
			i++;
	}
	return (line);
}

int	main(int argc, char **argv, char **envp)
{
	int	running;

	running = 1;
	if ((argc > 1) && (argv != NULL))
		return (printf("Don't give any args"), -1);
	while (running)
		initialising(ft_split(listening(0, 0), '|'), envp);
	return (0);
}
