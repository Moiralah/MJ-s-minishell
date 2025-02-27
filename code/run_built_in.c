/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_built_in.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:29 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:03:29 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_cd(char **params, t_node *start_node, t_node *self)
{
	char	*new_path;
	char	*home;

	if (strlist_len(params) > 2)
		error_exit(NULL, start_node, self);
	home = ft_getenv("HOME", start_node->envp);
	if (!params[1] || !ft_strcmp(params[1], home) || params[1][0] == '~')
		new_path = home;
	else if (params[1] && (params[1][0] == '-'))
		new_path = ft_strdup(ft_getenv("OLDPWD", start_node->envp));
	else
		new_path = params[1];
	if (*new_path == '\0')
		return (-1);
	ft_setenv(&(start_node->envp), "OLDPWD", getcwd(NULL, 0), 1);
	if (chdir(new_path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", new_path);
		error_exit(NULL, start_node, self);
	}
	ft_setenv(&(start_node->envp), "PWD", getcwd(NULL, 0), 1);
	if (params[1] && (params[1][0] == '-'))
		free(new_path);
	return (free2d(params), 0);
}

int	run_echo(char **params, t_node *start_node, t_node *self)
{
	int	i;

	(void) start_node;
	(void) self;
	i = 1;
	while (params[i] && (ft_strncmp(params[i], "-n", 2) == 0))
		i++;
	while (params[i + 1])
	{
		printf("%s ", params[i]);
		i++;
	}
	printf("%s", params[i]);
	if (ft_strncmp(params[1], "-n", 2) != 0)
		printf("\n");
	free2d(params);
	return (0);
}

int	run_pwd(char **params, t_node *start_node, t_node *self)
{
	char	*cwd;

	(void) start_node;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		error_exit(strerror(errno), start_node, self);
	printf("%s\n", cwd);
	free(cwd);
	free2d(params);
	return (0);
}

int	run_export(char **params, t_node *start_node, t_node *self)
{
	char	*key;
	char	*val;
	int		q;
	int		i;

	i = 0;
	if (!params[1])
		return (run_env(params, start_node, self), 0);
	while (params[++i])
	{
		if (!ft_strchr(params[i], '='))
			continue ;
		q = ft_strchr(params[i], '=') - params[i];
		if (q == 0)
		{
			printf("bash: export: %s: not a valid identifier\n", params[i]);
			error_exit(NULL, start_node, self);
		}
		key = ft_substr(params[i], 0, q);
		val = ft_substr(params[i], q + 1, ft_strlen(params[i]) - q - 1);
		ft_setenv(&(start_node->envp), key, val, 1);
	}
	free2d(params);
	return (0);
}

int	run_unset(char **params, t_node *start_node, t_node *self)
{
	t_list	*list[2];
	int		i;

	(void) self;
	if (strlist_len(params) == 1)
		printf("bash: unset: not enough arguments\n");
	i = 0;
	while (params[++i] != NULL)
	{
		list[0] = start_node->envp;
		list[1] = NULL;
		while (list[0] != NULL)
		{
			if (!ft_strcmp(list[0]->key, params[i]))
			{
				remove_link(&start_node->envp, list[0], list[1]);
				break ;
			}
			list[1] = list[0];
			list[0] = list[0]->next;
		}
	}
	return (free2d(params), 0);
}
