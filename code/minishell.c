#include "minishell.h"

void	error_exit(const char *msg)
{
	perror(msg);
	exit(1);
}

/* t_nodes	linking(t_node cur_node, char *comm, int *pid)
{
	t_nodes	*rd_node;
	char	*command;
	char	ch;

	ch = '\0';
	if (ft_strch(comm, '<') >= 0)
		ch = '<';
	else if (ft_strch(comm, '>') >= 0)
		ch = '>';
	if (!ch)
		return (match_node(command));
	command = ft_substr(comm, 0, ft_strch(comm, ch), len);
	redir_node->type->filename = ft_substr(comm, ft_strrch(comm, ch) + 1, len, len);
	if (ft_strch(comm, ch) == 0)
	{
		command = ft_substr(comm, ft_strrch(comm, ' ') + 1, len, len);
		redir_node->type->filename = ft_substr(comm, ft_strrch(comm, ch) + 1, ft_strrch(comm, ' '), len);
	}
	redir_node->type->pid = pid;
	current_node->next->next = func_match(command);
	return (current_node->next->next);
} */

void	listening(void)
{
	t_node	*nodes[2];
	char	**comms;
	char	*line;
	int		pid[2];
	int		i;

	i = -1;
	line = readline(getcwd());
	add_history(line);
	comms = ft_split(line, '|');
	nodes[1] = create_generic_node();
	nodes[0] = nodes[1];
	while (comms[++i] != '\0')
	{
		dup2(pid[0], stdout);
		dup2(pid[1], stdin);
		write(1, 'Hi', 3);
		//nodes[1] = linking(nodes[1], comms[i], pid);
	}
	executing(nodes[0]);
}

int	main(void)
{
	int	running;

	running = 1;
	while (running)
		listening();
	return (0);
}
