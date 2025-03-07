/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_manage.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:38 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:03:38 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_redir(char **params, t_node *start_node, t_node *self)
{
	int	fd;

	if (params[0][0] == '<')
		fd = open(params[1], O_RDONLY, 0666);
	else if (params[0][0] == '>')
		fd = open(params[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (params[0][0] == '?')
		fd = open(params[1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
	{
		printf("File can't be accessed\n");
		return (error_exit(start_node, self), 127);
	}
	if (params[0][0] == '<')
		dup2(fd, STDIN_FILENO);
	else if ((params[0][0] == '>') || (params[0][0] == '?'))
		dup2(fd, STDOUT_FILENO);
	return (free2d(params), close(fd), 0);
}

int	run_env(char **params, t_node *start_node, t_node *self)
{
	t_list	*temp;
	t_list	*copy;

	(void) self;
	if (strlist_len(params) != 1)
	{
		printf("Env should be run without any arguments\n");
		return (error_exit(start_node, self), 1);
	}
	temp = start_node->envp;
	if (!ft_strcmp(params[0], "export"))
	{
		temp = dup_env(start_node->envp);
		ft_sortenv(&temp);
		copy = temp;
	}
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->val);
		temp = temp->next;
	}
	if (!ft_strcmp(params[0], "export"))
		remove_link(&copy, copy, NULL);
	free2d(params);
	return (0);
}

int	run_exec(char **params, t_node *start_node, t_node *self)
{
	t_list	*temp;
	char	**arr_e;
	char	*line;
	int		len;

	len = 0;
	temp = start_node->envp;
	while ((temp != NULL) && (++len))
		temp = temp->next;
	arr_e = ft_calloc(len + 1, sizeof(char *));
	arr_e[len] = NULL;
	temp = start_node->envp;
	while (strlist_len(arr_e) < len)
	{
		line = ft_strjoin(ft_strdup(temp->key), ft_strdup("="));
		arr_e[strlist_len(arr_e)] = ft_strjoin(line, ft_strdup(temp->val));
		temp = temp->next;
	}
	line = find_path(params[0], start_node->envp);
	execve(line, params, arr_e);
	free2d(arr_e);
	if (*line != '\0')
		free(line);
	return (error_exit(start_node, self), 127);
}

int	run_exit(char **params, t_node *start_node, t_node *self)
{
	long long	exit_status;

	(void) self;
	(void) start_node;
	if (strlist_len(params) == 1)
		exit(0);
	if (strlist_len(params) >= 2 && legitnum(params[1]))
	{
		exit_status = ft_atoll(params[1]);
		if (strlist_len(params) > 2)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return (0);
		}
		exit((unsigned char)exit_status);
	}
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(params[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(2);
	}
	free2d(params);
	return (0);
}
