#include "minishell.h"

char	*fnames_to_nodes(t_node cur_node, char *comm, char ch)
{
	char	*fname;
	char	*start;
	int		word_s;
	int		i;

	i = 0;
	word_s = 0;
	start = ft_strchr(comm, ch);
	while (start[++i] != '\0')
	{
		if (word_s)
		{
			i = word_end(start + word_s, " <>", 1);
			fname = ft_substr(start, word_s, i - word_s);
			if (start[0] == start[1])
				cur_node->next = create_redir_node(ch + 1, fname);
			else
				cur_node->next = create_redir_node(ch, fname);
			comm = strnrplc(comm, NULL, comm - start, i - word_s);
		}
		else if (ft_isprint(start[i]) || (start[i] != ' ') || (start[i] != ch))
			word_s = i;
	}
	return (comm);
}

t_node	linking(t_node cur_node, char **envp, char *comm)
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
	cur_node->next = function_matching(comm, envp);
	return (cur_node->next);
}

void	executing(t_node start_node)
{
	t_node	cur_node;
	pid_t	pid;
	int		fd[2];

	cur_node = start_node->next;
	pipe(fd);
	while (cur_node != NULL)
	{
		dup2(fd[0], stdout);
		dup2(fd[1], stdin);
		pid = fork();
		if (pid < 0)
			error_exit(strerror(errno));
		else if (pid == 0)
		{
			close(fd[0]);
			close(fd[1]);
			cur_node->run(cur_node->params);
		}
		else
		{
			waitpid(pid, NULL, 0);
			cur_node = cur_node->next;
		}
	}
}

void	listening(char **envp)
{
	t_node	*nodes[2];
	char	**comms;
	char	*line;
	int		i;

	i = -1;
	line = readline(getcwd(NULL, 0));
	add_history(line);
	comms = ft_split(line, '|');
	free (line);
	nodes[1] = create_generic_node();
	nodes[0] = nodes[1];
	while (comms[++i] != '\0')
		nodes[1] = linking(nodes[1], comms[i]);
	free(comms);
	executing(nodes[0]);
	// free envp list here
	while (nodes[0] != NULL)
	{
		nodes[1] = nodes[0];
		nodes[0] = nodes[0]->next;
		free(nodes[1]);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int	running;

	running = 1;
	while (running)
		listening(envp);
	return (0);
}
