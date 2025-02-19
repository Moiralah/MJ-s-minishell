#include "minishell.h"

char	**strlist_join(char **list, char **list_to_join, int marker, int free)
{
	char	**new_list;
	int		i;
	int		q;

	i = strlist_len(list);
	if (marker)
		i += 1;
	q = strlist_len(list_to_join);
	new_list = malloc(sizeof(char *) * (i + q + 1));
	new_list[i + q] = "\0";
	while ((i + q) > 0)
	{
		if (q > 0)
			new_list[i + q] = list_to_join[--q];
		else if ((q == 0) && (marker--))
			new_list[--i] = "\0";
		else if (i > 0)
			new_list[i] = strlist[--i];
	}
	if (free == 1)
		free (list_to_join);
	if (free == -1)
		free (list);
	return (new_list);
}

int	strlist_len(char **strlist)
{
	int	i;

	i = 0;
	while (strlist[i] != NULL)
		i++;
	return (i);
}

int	count_ch(char *str, char ch)
{
	int	cnt;
	int	i;

	cnt = 0;
	i = -1;
	while (str[++i] != "\0")
	{
		if (str[i] == ch)
			cnt++;
	}
	return (cnt);
}

int	word_end(char *word, char *end_set, int print)
{
	int	i;
	int	q;

	i = -1;
	q = 0;
	if (word[++i] == '"')
		return (ft_strchr(word, '"') - word);
	while (word[i] != "\0")
	{
		if (print) && (!ft_isprint(word[i]))
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
	while (strlist[++i] != "\0")
	{
		if (i == index)
			break ;
		free(strlist[i]);
	}
	if (index < 0)
		free(strlist);
}
