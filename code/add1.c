#include "minishell.h"

void error_exit(const char *msg)
{
	perror(msg);
	exit(1);
}

t_node *func_match(char *comm)
{
	t_node	*new_node;
	char	**comm_flags;

	comm = ft_strtrim(comm, ' ');
	comm_flags = ft_split(comm, ' ');
	if (ft_strcmp(comm_flags[0], "cd"))
		new_node = create_CD_node(comm_flags[1]);
	else if (ft_strcmp(comm_flags[0], "echo"))
		new_node = create_ECHO_node();
	else if (ft_strcmp(comm_flags[0], "pwd"))
		new_node = create_PWD_node();
	else if (ft_strcmp(comm_flags[0], "export"))
		new_node = create_EXPORT_node;
	else if (ft_strcmp(comm_flags[0], "unset"))
		new_node = create_UNSET_node;
	else if (ft_strcmp(comm_flags[0], "env"))
		new_node = create_ENV_node();
	else if (ft_strcmp(comm_flags[0], "exit"))
		new_node = create_EXIT_node();
	else
		new_node = create_EXEC_node(comm_flags);
	free2d(comm_flags);
	return (new_node);
}

t_node *get_next_nodes(t_node *current_node, char *comm, int *pid)
{
	t_node *redir_node;
	char *command;
	char *filename;
	char ch;
	int ch_pos;

	ch = '\0';
	command = NULL;
	filename = NULL;

	if ((ch_pos = ft_strchr(comm, '<')) >= 0)
		ch = '<';
	else if ((ch_pos = ft_strchr(comm, '>')) >= 0)
		ch = '>';
	if (!ch)
		return (NULL);
	redir_node = malloc(sizeof(t_node));
	if(!redir_node)
		error_exit("malloc failed");
	redir_node->type.redir = malloc(sizeof(t_redir_node));
	if (!redir_node->type.redir)
		error_exit("malloc failed");
	redir_node->next = NULL;
	current_node->next = redir_node;
	if ((ch_pos = ft_strchr(comm, ch)) != NULL)
		ch_pos += 1;
	redir_node->type.redir->ch = ch;
	if (ch_pos == 0)
	{
		command = NULL;
		filename = ft_strtrim(ft_substr(comm, ch_pos + 1, ft_strlen(comm) - ch_pos - 1), ' ');
	}
	else
	{
		command = ft_strtrim(ft_substr(comm, 0, ch_pos), ' ');
		filename = ft_strtrim(ft_substr(comm, ch_pos + 1, ft_strlen(comm) - ch_pos - 1), ' ');
	}
	redir_node->type.redir->filename = filename;
	redir_node->type.redir->pid = pid;
	redir_node->next = func_match(command);
	free(command);
	return (redir_node->next);
}
