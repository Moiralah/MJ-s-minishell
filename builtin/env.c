/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 14:52:02 by huidris           #+#    #+#             */
/*   Updated: 2025/02/19 00:16:05 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

t_env_node	*init_env(char **envp)
{
	int			i;
	int			j;
	t_env_node	*head;
	t_env_node	*cur;
	t_env_node	*new;

	head = NULL;
	cur = NULL;
	new = NULL;
	i = -1;
	while (envp[++i])
	{
		new = mallocy(sizeof(t_env_node));
		j = ft_strchr(envp[i], '=') - envp[i];
		new->key = ft_substr(envp[i], 0, j);
		new->value = ft_substr(envp[i], j + 1, ft_strlen(envp[i]) - j - 1);
		new->next = NULL;
		if (!head)
			head = new;
		else
			cur->next = new;
		cur = new;
	}
	return (head);
}

void	free_env_node(char *key, char *val)
{
	free(key);
	free(val);
}

char	*ft_getenv(char *key, t_node *node)
{
	t_env_node	*temp;

	temp = node->env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
			return (temp->value);
		temp = temp->next;
	}
	return (NULL);
}

void	ft_setenv(t_node *node, char *key, char *val, int overwrite)
{
	t_env_node	*temp;
	t_env_node	*new;

	temp = node->env;
	while (temp)
	{
		if (ft_strncmp(temp->key, key, ft_strlen(key)) == 0)
		{
			if (overwrite)
			{
				free(temp->value);
				temp->value = val;
			}
			return ;
		}
		temp = temp->next;
	}
	new = mallocy(sizeof(t_env_node));
	new->key = ft_strdup(key);
	new->value = ft_strdup(val);
	new->next = NULL;
	temp = node->env;
	while (temp->next)
		temp = temp->next;
	temp->next = new;
}

//run_env may take in temporary input
void	run_env(t_env_node	*env)
{
	while (env)
	{
		printf("%s=%s\n", env->key, env->value);
		env = env->next;
	}
}
