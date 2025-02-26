/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:02:48 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:02:48 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
		ft_setenv(&start, str[0], str[1], 0);
	}
	return (start);
}

char	*ft_getenv(char *key, t_list *envp)
{
	t_list	*temp;

	temp = envp;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
			return (temp->val);
		temp = temp->next;
	}
	return ("\0");
}

void	ft_setenv(t_list **envp, char *key, char *val, int overwrite)
{
	t_list	*node[2];

	node[0] = *envp;
	while (node[0])
	{
		if (ft_strcmp(node[0]->key, key) == 0)
		{
			if (overwrite)
				free(node[0]->val);
			node[0]->val = val;
			return ;
		}
		node[0] = node[0]->next;
	}
	node[1] = malloc(sizeof(t_list));
	node[1]->key = key;
	node[1]->val = val;
	node[1]->next = NULL;
	node[0] = *envp;
	while ((node[0]) && (node[0]->next))
		node[0] = node[0]->next;
	if (!node[0])
		*envp = node[1];
	else
		node[0]->next = node[1];
}
