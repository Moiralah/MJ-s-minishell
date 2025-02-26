/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:56 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:03:56 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*strjoin_n_gnl(int fd)
{
	char	*line;
	char	*temp;

	line = ft_calloc(1, sizeof(char));
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		line = ft_strjoin(line, temp);
		temp = get_next_line(fd);
	}
	return (line);
}

char	*strnrplc(char *str, char *replace, int start, int len)
{
	char	*before;
	char	*after;

	before = ft_substr(str, 0, start);
	after = ft_substr(str, start + len + 1, ft_strlen(str) - start - len);
	if (replace)
	{
		free(str);
		str = ft_strjoin(before, replace);
		return (ft_strjoin(str, after));
	}
	free(str);
	return (ft_strjoin(before, after));
}

int	strlist_len(char **strlist)
{
	int	i;

	i = 0;
	while (strlist[i] != NULL)
		i++;
	return (i);
}

int	word_end(char *word, char *end_set, int print)
{
	int	i;
	int	q;

	i = -1;
	q = 0;
	if (word[++i] == '"')
		return (ft_strchr(word, '"') - word);
	while (word[i] != '\0')
	{
		if (print && (!ft_isprint(word[i])))
			return (i);
		while ((end_set[q] != '\0') && (end_set[q] != word[i]))
			q++;
		if (end_set[q] == word[i])
			return (i);
		i++;
	}
	return (i);
}

void	free_strlist(char **strlist, int index)
{
	int	i;

	i = -1;
	while (strlist[++i] != NULL)
	{
		if (i == index)
			break ;
		free(strlist[i]);
	}
	if (index < 0)
		free(strlist);
}

int	ft_lstsize(t_list *lst)
{
	int		i;
	t_list	*temp;

	i = 0;
	temp = lst;
	while (temp != NULL)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}
