#include "minishell.h"

t_node	create_generic_node(void)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = NULL;
	new_node->run = NULL;
	return (new_node);
}

t_node	create_exec_node(char *command, char **envp)
{
	t_node	new_node;
	char	**params;
	char	*trimmed_command;

	trimmed_command = ft_strtrim(command, " ");
	free(command);
	params = strlist_join(ft_split(trimmed_command, ' '), envp, -1);
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = params;
	new_node->run = run_EXEC;
	return (new_node);
}

t_node	create_exit_node(void)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = NULL;
	new_node->run = run_EXIT;
	return (new_node);
}

t_node	create_env_node(char **envp)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = envp;
	new_node->run = run_ENV;
	return (new_node);
}

t_node	create_redir_node(char *ch, char *filename, int *pid)
{
	t_node	new_node;
	char	*params[4];

	params[0] = ch;
	params[1] = filename;
	params[2] = (char *)pid;
	params[3] = "\0";
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = params;
	new_node->run = run_REDIR;
	return (new_node);
}
