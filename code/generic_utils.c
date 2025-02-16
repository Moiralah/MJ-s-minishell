#include "minishell.h"

char	*remove(char *str, int start, int end)
{
	char	*before_start;
	char	*after_end;
	char	*new_str;

	before_start = ft_substr(comm, 0, start - 0);
	after_end = ft_substr(comm, end, ft_strlen(str) - end);
	new_str = ft_strjoin(before_start, after_end);
	free(before_start);
	free(after_end);
	free(str);
	return (new_str);
}

void	error_exit(int errno)
{
	printf("Error: %s\n", strerror(errno));
	exit(-1);
}
