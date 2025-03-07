/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_splitmj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 16:27:18 by huidris           #+#    #+#             */
/*   Updated: 2024/03/16 21:06:47 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	in_quote(char const *s)
{
	if (*s == '"')
		return (ft_strchr(s + 1, '"') - s);
	else if (*s == 39)
		return (ft_strchr(s + 1, 39) - s);
	else
		return (-1);
}

static int	numwords(char const *s, char c)
{
	int	i;
	int	words_count;

	i = 0;
	words_count = 0;
	while (s[i])
	{
		if (s[i] == '"' || s[i] == 39)
			i += in_quote(s + i);
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == 0))
			words_count++;
		i++;
	}
	return (words_count);
}

static void	word2d(char **res, char const *s, int start, int end)
{
	res[0] = (char *)malloc((end - start + 2) * sizeof(char));
	if (!res[0])
		return ;
	ft_strlcpy(res[0], (s + start), (end - start + 2));
}

static int	split_words(char **result, char const *s, char c, int word)
{
	int	i_start;
	int	i_end;

	i_end = 0;
	i_start = 0;
	while (s[i_end])
	{
		if (s[i_end] == '"' || s[i_end] == 39)
			i_end += in_quote(s + i_end);
		else if (s[i_end] == c)
			i_start = i_end + 1;
		if (s[i_end] != c && (s[i_end + 1] == c || s[i_end + 1] == 0))
		{
			word2d(&result[word], s, i_start, i_end);
			if (!result[word])
				return (free2d(result), 0);
			word++;
		}
		i_end++;
	}
	result[word] = 0;
	return (1);
}

char	**ft_splitmj(char const *s, char c)
{
	char	**result;

	if (!s)
		return (NULL);
	result = ft_calloc(numwords(s, c) + 1, sizeof(char *));
	if (!result)
		return (NULL);
	if (!split_words(result, s, c, 0))
		return (NULL);
	return (result);
}
