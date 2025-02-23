#include "minishell.h"

t_list	*init_envp(char **envp)
{
	t_list	*start;
	char	*str[2];
	int		i;
	int		q;

	i = -1;
	start = NULL;
	while (envp[++i] != NULL)
	{
		q = ft_strchr(envp[i], '=') - envp[i];
		str[0] = ft_substr(envp[i], 0, q);
		str[1] = ft_substr(envp[i], q + 1, ft_strlen(envp[i]) - q - 1);
		ft_setenv(start, str[0], str[1], 0);
	}
	return (start);
}

char	*ft_getenv(char *key, t_list *envp)
{
	t_list	*temp;

	temp = envp;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (temp->val);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_setenv(t_list *envp, char *key, char *val, int overwrite)
{
	t_list	*temp;
	t_list	*new;

	temp = envp;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
		{
			if (overwrite)
				free(temp->val);
			temp->val = val;
			return ;
		}
		temp = temp->next;
	}
	new = malloc(sizeof(t_list));
	new->key = ft_strdup(key);
	new->val = ft_strdup(val);
	new->next = NULL;
	temp->next = new;
}

void	close_pipe(int *pipe, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		close(pipe[i]);
}

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
