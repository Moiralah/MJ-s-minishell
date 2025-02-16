#include "minishell.h"

t_node	create_cd_node(char *path)
{
	t_node	new_node;
	char	*params[2];

	params[0] = path;
	params[1] = "\0";
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = params;
	new_node->run = run_CD;
	return (new_node);
}

t_node	create_echo_node(char *str)
{
	t_node	new_node;
	char	*params[2];

	params[0] = str;
	params[1] = "\0";
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = params;
	new_node->run = run_ECHO;
	return (new_node);
}

t_node	create_pwd_node(void)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = NULL;
	new_node->run = run_PWD;
	return (new_node);
}

t_node	create_export_node(char *var, char *val)
{
	t_node	new_node;
	char	*params[3];

	params[0] = var;
	params[1] = val;
	params[2] = "\0";
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = params;
	new_node->run = run_EXPORT;
	return (new_node);
}

t_node	create_unset_node(char *var)
{
	t_node	new_node;
	char	*params[2];

	params[0] = var;
	params[1] = "\0";
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = params;
	new_node->run = run_UNSET;
	return (new_node);
}
