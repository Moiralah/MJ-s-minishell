#include "minishell.h"

t_list	*init_env(char **envp)
{
	t_list	*start;
	char	*str[2];
	int		i;
	int		q;

	i = -1;
	while (envp[++i] != NULL)
	{
		q = ft_strchr(envp[i], '=') - envp[i];
		str[0] = ft_substr(envp[i], 0, q);
		str[1] = ft_substr(envp[i], q + 1, ft_strlen(envp[i]) - q - 1);
		ft_setenv(start, str[0], str[1], 0);
	}
	return (start);
}

char	*ft_getenv(t_list *envp, char *key)
{
	t_list	*temp;

	temp = envp;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (temp->value);
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
				free(temp->value);
			temp->value = val;
			return ;
		}
		temp = temp->next;
	}
	new = malloc(sizeof(t_list));
	new->key = ft_strdup(key);
	new->value = ft_strdup(val);
	new->next = NULL;
	temp->next = new;
}
