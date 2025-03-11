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

t_node	*create_heredoc_node(void)
{
	t_node	*new_node;

	new_node = ft_calloc(1, sizeof(t_node));
	new_node->params = NULL;
	new_node->run = run_heredoc;
	new_node->to_pipe = 1;
	new_node->next = NULL;
	return (new_node);
}

char	**linklist_to_strlist(t_list *linklist)
{
	t_list	*temp;
	char	**strlist;
	char	*line;
	int		len;

	len = 0;
	temp = linklist;
	while (temp != NULL)
	{
		len++;
		temp = temp->next;
	}
	strlist = ft_calloc(len + 1, sizeof(char *));
	temp = linklist;
	while (temp != NULL)
	{
		line = ft_strjoin(ft_strdup(temp->key), ft_strdup("="));
		line = ft_strjoin(line, ft_strdup(temp->val));
		strlist[strlist_len(strlist)] = line;
		temp = temp->next;
	}
	return (strlist);
}

int	verify_ch(char ch, char *set)
{
	char	**chs;
	int		i;

	i = -1;
	chs = ft_split(set, '|');
	while (chs[++i] != NULL)
	{
		if (ch == ft_atoi(chs[i]))
		{
			free2d(chs);
			return (1);
		}
	}
	free2d(chs);
	return (0);
}

void	free_exec_list(t_head *head)
{
	t_node	*temp;

	while (head->start != NULL)
	{
		temp = head->start;
		head->start = head->start->next;
		free2d(temp->params);
		free(temp);
	}
	free(head->input);
	free(head->ori_fd);
	free(head->fd);
	free(head);
}
/* char	*expand_error_code(t_exit *ex, char *str, int *i, int *q)
{
	char	*exit_code;

	if (*q == -2)
		return (str);
	if (str[*q + 1] != '?')
		return (str);
	exit_code = ft_itoa(ex->code);
	str = strnrplc(str, exit_code, *q, 1);
	*i = -1;
	*q = -2;
	return (str);
} */

/* int	run_node(t_node *start, t_node *cur, char *input, )
{
	int	i;

	i = n[1]->run(n[1]->params, n[0]);
	ex[0]->code = 0;
	if (i > 0)
		ex[0]->code = i;
	if (i != -1)
		return (i);
	free(*input);
	*input = strjoin_n_gnl(STDOUT_FILENO);
	return (i);
} */
