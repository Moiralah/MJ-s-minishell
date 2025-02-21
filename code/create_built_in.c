#include "minishell.h"

t_node	create_cd_node(char **path)
{
	t_node	new_node;

	if (strlist_len(path) > 2)
		error_exit(1);
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = path;
	new_node->run = run_CD;
	return (new_node);
}

t_node	create_echo_node(char **to_print)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = to_print;
	new_node->run = run_ECHO;
	return (new_node);
}

t_node	create_pwd_node(char **params_to_verify)
{
	t_node	new_node;

	free_strlist(params_to_verify, -1);
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = NULL;
	new_node->run = run_PWD;
	return (new_node);
}

t_node	create_export_node(char **to_set)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = to_set;
	new_node->run = run_EXPORT;
	return (new_node);
}

t_node	create_unset_node(char **to_unset)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = to_unset;
	new_node->run = run_UNSET;
	return (new_node);
}
