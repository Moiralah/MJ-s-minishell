/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_built_in.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:02:22 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:02:22 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*create_cd_node(char **path)
{
	t_node	*new_node;
	char	*trimmed;
	char	to_trim[3];
	int		i;

	i = -1;
	to_trim[0] = '"';
	to_trim[1] = 39;
	to_trim[2] = '\0';
	while (path[++i] != NULL)
	{
		trimmed = ft_strtrim(path[i], to_trim);
		free(path[i]);
		path[i] = trimmed;
	}
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = path;
	new_node->run = run_cd;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}

t_node	*create_echo_node(char **to_print)
{
	t_node	*new_node;
	char	*trimmed;
	char	to_trim[3];
	int		i;

	i = -1;
	to_trim[0] = '"';
	to_trim[1] = 39;
	to_trim[2] = '\0';
	while (to_print[++i] != NULL)
	{
		trimmed = ft_strtrim(to_print[i], to_trim);
		free(to_print[i]);
		to_print[i] = trimmed;
	}
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = to_print;
	new_node->run = run_echo;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}

t_node	*create_pwd_node(char **params_to_verify)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = params_to_verify;
	new_node->run = run_pwd;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}

t_node	*create_export_node(char **to_set)
{
	t_node	*new_node;
	char	*trimmed;
	char	to_trim[3];
	int		i;

	i = -1;
	to_trim[0] = '"';
	to_trim[1] = 39;
	to_trim[2] = '\0';
	while (to_set[++i] != NULL)
	{
		trimmed = ft_strtrim(to_set[i], to_trim);
		free(to_set[i]);
		to_set[i] = trimmed;
	}
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = to_set;
	new_node->run = run_export;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}

t_node	*create_unset_node(char **to_unset)
{
	t_node	*new_node;
	char	*trimmed;
	char	to_trim[3];
	int		i;

	i = -1;
	to_trim[0] = '"';
	to_trim[1] = 39;
	to_trim[2] = '\0';
	while (to_unset[++i] != NULL)
	{
		trimmed = ft_strtrim(to_unset[i], to_trim);
		free(to_unset[i]);
		to_unset[i] = trimmed;
	}
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = to_unset;
	new_node->run = run_unset;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}
