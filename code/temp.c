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
	new_node->envp = NULL;
	new_node->params = NULL;
	new_node->run = run_heredoc;
	new_node->built = 1;
	new_node->to_pipe = 1;
	new_node->next = NULL;
	return (new_node);
}

char	*expand_error_code(t_exit *ex, char *str, int *i, int *q)
{
	char	*exit_code;

	if (*q == -2)
		return (str);
	if (str[*q + 1] != '?')
		return (str);
	exit_code = ft_itoa(ex->code);
	str = strnrplc(str, exit_code, *q + 1, 1);
	*i = -1;
	*q = -2;
	return (str);
}

int	run_non_built_in(t_node *start, t_node *cur, t_exit **ex, char **input)
{
	int	i;

	i = cur->run(cur->params, start, cur);
	if (i)
		ex[0]->code = i;
	free(*input);
	*input = strjoin_n_gnl(STDOUT_FILENO);
	return (i);
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

t_node	**resetting(t_node *start, char *input, int **fd, int com_amnt)
{
	t_node	**nodes;
	int		i;

	i = 0;
	if (!fd)
	{
		nodes = ft_calloc(2, sizeof(t_node));
		nodes[0] = start;
		nodes[1] = start->next;
		pipe_handling(start, fd, com_amnt);
		return (nodes);
	}
	pipe_handling(start, fd, com_amnt);
	while (i != -1)
		i = waitpid(-1, NULL, 0);
	add_history(input);
	free(input);
	return (NULL);
}
