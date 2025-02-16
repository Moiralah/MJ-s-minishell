#include "minishell.h"

char	*fnames_to_list(char *comm, char ch, int start)
{
	char	**fnames;
	int		word_s;
	int		i;
	int		q;

	fnames = ft_calloc(count_ch(comm, ch) + 2, sizeof(char *));
	word_s = -1;
	i = 0;
	q = -1;
	while (start >= 0)
	{
		if (word_s > 0)
		{
			i = get_end(comm, word_s);
			fnames[++q] = ft_substr(comm, word_s, i - 1 - word_s);
			comm = remove(comm, start, i);
			start = ft_strchr(comm, ch);
			word_s = -1;
			i = 0;
		}
		else if (ft_isprint(comm[start + (++i)]) || (comm[start + i] != ' '))
			word_s = start + i;
	}
	fnames[++q] = comm;
	return (fnames);
}

t_node	linking(t_node cur_node, char **envp, char *comm, int *pid)
{
	char	**in;
	char	**out;
	char	*final_command;
	int		i;

	in = fnames_to_list(comm, '<', ft_strchr(comm, '<'));
	i = -1;
	while (++i < (strlist_len(in) - 1))
	{
		cur_node->next = create_redir_node("<", in[i], pid);
		cur_node = cur_node->next;
	}
	out = fnames_to_list(in[strlist_len(in) - 1], '>', ft_strchr(comm, '>'));
	free(in);
	i = -1;
	while (++i < (strlist_len(out) - 1))
	{
		cur_node->next = create_redir_node(">", out[i], pid);
		cur_node = cur_node->next;
	}
	final_command = out[strlist_len(out) - 1];
	free(out);
	cur_node->next = create_exec_node(final_command, envp);
	return (cur_node->next);
}

void	executing(t_node start_node)
{
	t_node	cur_node;
	pid_t	pid;

	cur_node = start_node->next;
	while (cur_node != NULL)
	{
		pid = fork();
		if (pid < 0)
			error_exit(strerror(errno));
		else if (pid == 0)
			cur_node->run(cur_node->params);
		else
		{
			if (wait() < 0)
				error_exit(strerror(errno));
			cur_node = cur_node->next;
		}
	}
	while (start_node != NULL)
	{
		cur_node = start_node;
		start_node = start_node->next;
		free(cur_node);
	}
}

void	listening(char **envp)
{
	t_node	*nodes[2];
	char	**comms;
	char	*line;
	int		pid[2];
	int		i;

	i = -1;
	line = readline(getcwd(NULL, 0));
	add_history(line);
	pipe(pid, O_CLOEXEC);
	comms = ft_split(line, '|');
	free (line);
	nodes[1] = create_generic_node();
	nodes[0] = nodes[1];
	while (comms[++i] != '\0')
	{
		dup2(pid[0], stdout);
		dup2(pid[1], stdin);
		nodes[1] = linking(nodes[1], comms[i], pid);
	}
	free(comms);
	executing(nodes[0]);
}

int	main(int argc, char **argv, char **envp)
{
	int	running;

	running = 1;
	while (running)
		listening(envp);
	return (0);
}
