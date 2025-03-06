/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_manage.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:02:35 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:02:35 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_generic_node(t_list *envp)
{
	t_node	*new_node;
	int	fd[2];

	fd[0] = dup(STDIN_FILENO);
	fd[1] = dup(STDOUT_FILENO);
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = envp;
	new_node->params = NULL;
	new_node->run = NULL;
	new_node->ori_fd = fd;
	new_node->built = 1;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}

t_node	*create_exec_node(char **comm_n_flags)
{
	t_node	*new_node;
	char	*trimmed;
	char	to_trim[3];
	int		i;

	i = -1;
	to_trim[0] = '"';
	to_trim[1] = 39;
	to_trim[2] = '\0';
	while (comm_n_flags[++i] != NULL)
	{
		trimmed = ft_strtrim(comm_n_flags[i], to_trim);
		free(comm_n_flags[i]);
		comm_n_flags[i] = trimmed;
	}
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = comm_n_flags;
	new_node->run = run_exec;
	new_node->ori_fd = NULL;
	new_node->built = 0;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}

t_node	*create_exit_node(char **code)
{
	t_node	*new_node;
	char	*trimmed;
	char	to_trim[3];
	int		i;

	i = -1;
	to_trim[0] = '"';
	to_trim[1] = 39;
	to_trim[2] = '\0';
	while (code[++i] != NULL)
	{
		trimmed = ft_strtrim(code[i], to_trim);
		free(code[i]);
		code[i] = trimmed;
	}
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = code;
	new_node->run = run_exit;
	new_node->ori_fd = NULL;
	new_node->built = 1;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}

t_node	*create_env_node(char **var)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = var;
	new_node->run = run_env;
	new_node->ori_fd = NULL;
	new_node->built = 1;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}

t_node	*create_redir_node(char ch, char *filename)
{
	t_node	*new_node;
	char	str_ch[2];
	char	to_trim[3];

	str_ch[0] = ch;
	str_ch[1] = '\0';
	to_trim[0] = '"';
	to_trim[1] = 39;
	to_trim[2] = '\0';
	filename = ft_strtrim(filename, to_trim);
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->envp = NULL;
	new_node->params = ft_calloc(3, sizeof(char));
	new_node->params[0] = ft_strdup(str_ch);
	new_node->params[1] = ft_strtrim(filename, " <>");
	new_node->params[2] = NULL;
	new_node->run = run_redir;
	new_node->ori_fd = NULL;
	new_node->built = 1;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	free (filename);
	return (new_node);
}
