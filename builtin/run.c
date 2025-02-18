/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/16 18:55:16 by huidris           #+#    #+#             */
/*   Updated: 2025/02/18 22:48:03 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

void	run_echo(char **argv)
{
	int	i;

	i = 1;
	while (argv[i] && (ft_strncmp(argv[i], "-n", 2) == 0))
		i++;
	while (argv[i + 1])
	{
		printf("%s ", argv[i]);
		i++;
	}
	printf("%s", argv[i]);
	if (ft_strncmp(argv[1], "-n", 2) != 0)
		printf("\n");
}

void	run_cd(int argc, char **argv, t_node *node)
{
	char	*new_path;

	if (argc == 1
		|| !ft_strncmp(argv[1], ft_getenv("HOME", node), ft_strlen(argv[1])))
		new_path = ft_getenv("HOME", node);
	else if ((argc == 2) && (argv[1][0] == '-'))
	{
		new_path = ft_strdup(ft_getenv("OLDPWD", node));
		printf("%s\n", new_path);
	}
	else
		new_path = argv[1];
	ft_setenv(node, "OLDPWD", getcwd(NULL, 0), 1);
	if (chdir(new_path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", new_path);
		error_exit(NULL);
	}
	ft_setenv(node, "PWD", getcwd(NULL, 0), 1);
	if ((argc == 2) && (argv[1][0] == '-'))
		free(new_path);
}

void	run_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}

void	run_export(char **argv, t_node *node)
{
	int		i;
	int		j;
	char	*key;
	char	*val;

	i = 0;
	while (argv[++i])
	{
		j = 0;
		while (argv[i][j] && argv[i][j] != '=')
			j++;
		if (!argv[i][j])
			continue ;
		key = ft_substr(argv[i], 0, j);
		val = ft_substr(argv[i], j + 1, ft_strlen(argv[i]) - j - 1);
		ft_setenv(node, key, val, 1);
	}
}

void	run_unset(char **argv, t_node *node)
{
	t_env_node	*temp;
	t_env_node	*prev;
	int			i;

	i = 0;
	while (argv[++i])
	{
		temp = node->env;
		while (temp)
		{
			if ((ft_strlen(argv[i]) - ft_strlen(temp->key)) == 0
				&& (ft_strncmp(argv[i], temp->key, ft_strlen(argv[i])) == 0))
			{
				if (temp == node->env)
					node->env = temp->next;
				else
					prev->next = temp->next;
				free_env_node(temp->key, temp->value);
				free(temp);
				break ;
			}
			prev = temp;
			temp = temp->next;
		}
	}
}
