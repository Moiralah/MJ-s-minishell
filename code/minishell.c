#include "minishell.h"

void	executing(t_node start_node)
{
	t_node	cur_node;
	pid_t	pid[2];
	int		fd[2];

	cur_node = start_node;
	pipe(fd);
	while (cur_node != NULL)
	{
		dup2(fd[0], stdout);
		dup2(fd[1], stdin);
		pid[0] = fork();
		if (pid[0] < 0)
			error_exit(strerror(errno));
		else if (pid[0] == 0)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			cur_node->run(cur_node->params);
		}
		pid[1] = fork();
		if (pid[1] < 0)
			error_exit(strerror(errno));
		else if (pid[1] == 0)
		{
			cur_node = cur_node->next;
			dup2(fd[0], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			cur_node->run(cur_node->params);
		}
		if ((pid[0] != 0) && (pid[1] != 0))
		{
			waitpid(pid[0], NULL, 0);
			waitpid(pid[1], NULL, 0);
			cur_node = cur_node->next->next;
		}
	}
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
	executing(nodes[0]);
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
