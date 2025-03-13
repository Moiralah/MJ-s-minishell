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

int	run_cd(char **params, t_head *head)
{
	char	*new_path;
	char	*home;

	if (strlist_len(params) > 2)
		return (printf("bash: cd : too many arguments\n"), 1);
	home = ft_getenv("HOME", head->envp);
	if (!params[1] || !ft_strcmp(params[1], home) || params[1][0] == '~')
		new_path = home;
	else if (params[1] && (params[1][0] == '-'))
		new_path = ft_strdup(ft_getenv("OLDPWD", head->envp));
	else
		new_path = params[1];
	ft_setenv(&(head->envp), "OLDPWD", getcwd(NULL, 0), 1);
	if (chdir(new_path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", new_path);
		return (1);
	}
	ft_setenv(&(head->envp), "PWD", getcwd(NULL, 0), 1);
	if (params[1] && (params[1][0] == '-'))
		free(new_path);
	return (0);
}

int	run_echo(char **params, t_head *head)
{
	int	i;

	(void) head;
	i = 1;
	while (params[i] && (ft_strncmp(params[i], "-n", 2) == 0))
		i++;
	while ((params[i]) && (params[i + 1]))
	{
		printf("%s ", params[i]);
		i++;
	}
	if (params[i])
		printf("%s", params[i]);
	if (ft_strcmp(params[1], "-n") != 0)
		printf("\n");
	return (0);
}

int	run_pwd(char **params, t_head *head)
{
	char	*cwd;

	(void) params;
	(void) head;
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (errno);
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

int	run_export(char **params, t_head *head)
{
	char		*s[2];
	int			i[3];

	i = 0;
	e = 0;
	if (!params[1])
		return (run_env(params, head));
	while (params[++i])
	{
		q = ft_strchr(params[i], '=') - params[i];
		if ((q == 0) || ft_isdigit(params[i][0]))
			printf("bash: export: %s: not a valid identifier\n", params[i]);
		if ((q == 0) || ft_isdigit(params[i][0]))
			e = 1;
		if ((q <= 0) || ft_isdigit(params[i][0]))
			continue ;
		s[0] = ft_substr(params[i], 0, q);
		s[1] = ft_substr(params[i], q + 1, ft_strlen(params[i]) - q - 1);
		ft_setenv(&(head->envp), key, val, 1);
	}
	return (e);
}

int	run_unset(char **params, t_head *head)
{
	t_list	*list[2];
	int		i;

	i = 0;
	while (params[++i] != NULL)
	{
		list[0] = head->envp;
		list[1] = NULL;
		while (list[0] != NULL)
		{
			if (!ft_strcmp(list[0]->key, params[i]))
			{
				remove_link(&head->envp, list[0], list[1]);
				break ;
			}
			list[1] = list[0];
			list[0] = list[0]->next;
		}
	}
	return (0);
}
