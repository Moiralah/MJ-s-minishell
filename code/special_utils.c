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

char	*str_remove_q(char *str)
{
	long int	q;
	int			i;

	i = -1;
	while (str[++i] != '\0')
	{
		q = -1;
		if ((str[i] == '"') | (str[i] == 39))
			q = ft_strchr(str + i + 1, str[i]) - str;
		if (q < 0)
			continue ;
		str = strnrplc(str, NULL, q, 1);
		str = strnrplc(str, NULL, i, 1);
		i = q - 1;
	}
	return (str);
}

char	*exp_correct_key(char *str)
{
	char		*key;
	long int	i;
	int			q;

	i = ft_strchr(str, '=') - str;
	q = 0;
	while ((i < 0) && (str[q] != '\0') && ft_isalpha(str[q]))
		q++;
	if ((i <= 0) && (str[q] != '\0'))
		return (perr("bash: export: %s: not a valid identifier\n", str), NULL);
	if (i < 0)
		return (ft_strdup(str));
	if (str[i + 1] == '=')
		i += 1;
	key = ft_substr(str, 0, i);
	i = 0;
	while ((key[i] != '\0') && ft_isalpha(key[i]) && (key[i] != ' '))
		i++;
	if (key[i] == '\0')
		return (key);
	perr("bash: export: |||%s: not a valid identifier\n", str);
	free(key);
	return (NULL);
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
