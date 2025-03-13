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
	int		i;

	i = -1;
	while (path[++i] != NULL)
		path[i] = str_remove_q(path[i]);
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
	int		i;

	i = -1;
	while (to_print[++i] != NULL)
		to_print[i] = str_remove_q(to_print[i]);
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
	int		i;

	i = -1;
	while (to_set[++i] != NULL)
		to_set[i] = str_remove_q(to_set[i]);
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
	int		i;

	i = -1;
	while (to_unset[++i] != NULL)
		to_unset[i] = str_remove_q(to_unset[i]);
	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = to_unset;
	new_node->run = run_unset;
	new_node->to_pipe = 0;
	new_node->next = NULL;
	return (new_node);
}
