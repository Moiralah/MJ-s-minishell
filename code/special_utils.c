/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:08 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:03:08 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "minishell.h"

t_node	*create_heredoc_node(char **delimiter)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = delimiter;
	new_node->run = run_heredoc;
	new_node->to_pipe = 1;
	new_node->next = NULL;
	return (new_node);
}

t_node	*create_pipe_node(int index)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = ft_calloc(2, sizeof(char *));
	new_node->params[0] = ft_itoa(index + 1);
	new_node->params[1] = NULL;
	new_node->run = run_pipe;
	new_node->next = NULL;
	return (new_node);
}

char	*str_remove_set(char *str, char *set)
{
	char		**chs;
	char		*start;
	long int	q;
	int			i;

	i = -1;
	chs = ft_split(set, '|');
	while (chs[++i] != NULL)
	{
		q = 1;
		while (q > 0)
		{
			start = ft_strchr(str, ft_atoi(chs[i]));
			if (start == NULL)
				break ;
			q = start - str;
			if (q == (long int) ft_strlen(str))
				break ;
			str = strnrplc(str, NULL, q, 0);
		}
	}
	free2d(chs);
	return (str);
}

void	finish_heredoc(t_head *head, char **str, int *fds)
{
	dup2(fds[0], STDIN_FILENO);
	dup2(fds[2], STDOUT_FILENO);
	close(fds[0]);
	close(fds[1]);
	close(fds[2]);
	if (!str[0])
	{
		free(str[1]);
		return ;
	}
	free(str[0]);
	head->input = ft_strjoin(head->input, ft_strdup("\n"));
	head->input = ft_strjoin(head->input, str[1]);
}
