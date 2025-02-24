#include "minishell.h"

void	executing(t_node *start, char *line, int i)
{
	pid_t	pid;
	int		*fd;
	int		q;

	fd = ft_calloc((i - 1) * 2, sizeof(int));
	q = -1;
	while (++q < (i - 1))
		pipe(fd + (2 * q));
	q = 0;
	while ((start != NULL) && (++q))
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
			if (start->run(start->params, start->envp) == 1)
			{
				free(line);
				line = strjoin_n_gnl(STDOUT_FILENO);
			}
			kill(0, SIGKILL);
		}
		start = start->next;
	}
	close_pipe(fd, (i - 1) * 2);
	waitpid(-1, NULL, 0);
	add_history(line);
	free(line);
}

t_node	*linking(t_node *cur_node, char *comm)
{
	char	*input;

	input = NULL;
	comm = fnames_to_nodes(&cur_node, comm, '<');
	if ((cur_node) && (cur_node->params))
		input = cur_node->params[1];
	comm = fnames_to_nodes(&cur_node, comm, '>');
	if (input && !ft_strncmp(input, cur_node->params[1], ft_strlen(input)))
		error_exit("grep: (standard input): input file is also the output");
	cur_node->next = function_matching(comm);
	return (cur_node->next);
}

void	initialising(t_list *envp, char **comms, char *line)
{
	t_node	*nodes[2];
	int		i;

	i = -1;
	nodes[0] = create_generic_node();
	nodes[1] = nodes[0];
	while (comms[++i] != NULL)
	{
		comms[i] = expansion(comms[i], envp);
		nodes[1] = linking(nodes[1], comms[i]);
	}
	nodes[0]->envp = envp;
	nodes[1] = nodes[0];
	executing(nodes[1], line, i);
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
	while (line[i] != '\0')
	{
		q = 0;
		if ((line[i] == '"') && ft_strchr(line + i + 1, '"'))
			i = ft_strchr(line + i + 1, '"') - line;
		else if ((line[i] == '"') && !ft_strchr(line + i + 1, '"'))
			q = 1;
		else if ((line[i] == 39) && ft_strchr(line + i + 1, 39))
			i = ft_strchr(line + i + 1, 39) - line;
		else if ((line[i] == 39) && !ft_strchr(line + i + 1, 39))
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
	char	*input;
	int		running;

	running = -1;
	if ((argc > 1) && (argv != NULL))
		return (printf("Don't give any args"), -1);
	while (running)
	{
		input = listening(0, 0);
		initialising(init_envp(envp), ft_split(input, '|'), input);
	}
	return (0);
}
