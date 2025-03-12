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
	if (after == NULL)
		after = ft_strdup("");
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

int	fname_len(char *word, char *ig_set)
{
	int	n[4];

	n[0] = -1;
	n[2] = 0;
	n[3] = 0;
	while ((word[++n[0]] != '\0') && (!(n[2] && n[3])))
	{
		if (word[n[0]] == '"')
			n[0] = ft_strchr(word + n[0] + 1, '"') - word;
		else if (word[n[0]] == 39)
			n[0] = ft_strchr(word + n[0] + 1, 39) - word;
		n[1] = 0;
		while ((ig_set[n[1]] != '\0') && (ig_set[n[1]] != word[n[0]]))
			n[1]++;
		if (!n[2] && (ig_set[n[1]] == '\0'))
			n[2] = n[0];
		if (n[2] && (ig_set[n[1]] != '\0'))
			n[3] = n[0];
	}
	if (!n[3])
		n[3] = n[0];
	return (n[3]);
}
