#include "minishell.h"

t_node	*create_cd_node(char **path)
{
	t_node	*new_node;

	if (strlist_len(path) > 2)
		error_exit(strerror(errno));
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = path;
	new_node->run = run_cd;
	return (new_node);
}

t_node	*create_echo_node(char **to_print)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = to_print;
	new_node->run = run_echo;
	return (new_node);
}

t_node	*create_pwd_node(char **params_to_verify)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node	*));
	new_node->envp = NULL;
	new_node->params = params_to_verify;
	new_node->run = run_pwd;
	return (new_node);
}

t_node	*create_export_node(char **to_set)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = to_set;
	new_node->run = run_export;
	return (new_node);
}

t_node	*create_unset_node(char **to_unset)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = to_unset;
	new_node->run = run_unset;
	return (new_node);
}
