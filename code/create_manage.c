#include "minishell.h"

t_node	create_pipe_node(void)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = NULL;
	new_node->run = run_pipe(void);
	return (new_node);
}

t_node	create_exec_node(char **comm_n_flags)
{
	t_node	new_node;
	char	**params;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = comm_n_flags;
	new_node->run = run_EXEC;
	return (new_node);
}

t_node	create_exit_node(char **code)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = code;
	new_node->run = run_EXIT;
	return (new_node);
}

t_node	create_env_node(char **var)
{
	t_node	new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = var;
	new_node->run = run_ENV;
	return (new_node);
}

t_node	create_redir_node(char *ch, char *filename)
{
	t_node	new_node;
	char	*params[3];

	params[0] = ch;
	params[1] = filename;
	params[2] = "\0";
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = params;
	new_node->run = run_REDIR;
	return (new_node);
}
