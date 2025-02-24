#include "minishell.h"

char	*expansion(char *str, t_list *envp)
{
	char	*start;
	char	*var_name;
	char	*var_val;
	int		i;

	i = 0;
	start = ft_strchr(str, '$');
	while ((start) && (start[++i] != '\0'))
	{
		var_name = NULL;
		if (start[i] == '?')
			printf("Exit Status Code: 1\n");
		else if ((start[i] == ' ') || (start[i] == '$'))
			var_name = ft_substr(start, 1, i - 1);
		if (!var_name)
			continue ;
		var_val = ft_getenv(var_name, envp);
		free(var_name);
		strnrplc(str, var_val, str - start, i - 1);
		start = ft_strchr(str, '$');
		i = 0;
	}
	return (str);
}

char	*strnrplc(char *str, char *replace, int start, int len)
{
	char	*before;
	char	*after;

	before = ft_substr(str, 0, start);
	after = ft_substr(str, start + len, ft_strlen(str) - start - len);
	str = ft_strjoin(before, replace);
	str = ft_strjoin(str, after);
	return (str);
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
