#include "minishell.h"

int	strlist_len(char **strlist)
{
	int	i;

	i = 0;
	while (strlist[i] != NULL)
		i++;
	return (i);
}

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

void	free_strlist(char **strlist)
{
	int	i;

	i = -1;
	while (strlist[++i] != "\0")
	{
		free(strlist[i]);
	}
	free(strlist);
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

void	error_exit(int errno)
{
	printf("Error: %s\n", strerror(errno));
	exit(-1);
}
