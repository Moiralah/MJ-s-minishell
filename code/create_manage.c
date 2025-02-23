#include "minishell.h"

t_node	*create_exec_node(char **comm_n_flags)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = comm_n_flags;
	new_node->run = run_exec;
	return (new_node);
}

t_node	*create_exit_node(char **code)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = code;
	new_node->run = run_exit;
	return (new_node);
}

t_node	*create_env_node(char **var)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = var;
	new_node->run = run_env;
	return (new_node);
}

t_node	*create_redir_node(char ch, char *filename)
{
	t_node	*new_node;
	char	*params[3];
	char	str_ch[2];

	str_ch[0] = ch;
	str_ch[1] = '\0';
	params[0] = str_ch;
	params[1] = filename;
	params[2] = "\0";
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = params;
	new_node->run = run_redir;
	return (new_node);
}
