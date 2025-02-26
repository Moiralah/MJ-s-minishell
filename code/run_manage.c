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

int	run_pipe(char **params, t_node *start_node, t_node *self)
{
	int	*fd;
	int	q;
	int	l;

	(void) start_node;
	(void) self;
	fd = (int *)params[0];
	q = ft_atoi(params[1]);
	l = ft_atoi(params[2]);
	if (q == l)
		return (-1);
	if (q == 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (q == (l - 1))
		dup2(fd[(q * 2) - 4], STDIN_FILENO);
	else
	{
		dup2(fd[(q * 2) - 4], STDIN_FILENO);
		dup2(fd[(q * 2) - 1], STDOUT_FILENO);
	}
	return (0);
}

int	run_redir(char **params, t_node *start_node, t_node *self)
{
	int	fd;

	if (params[0][0] == '<')
		fd = open(params[1], O_CREAT | O_RDONLY, 0666);
	else if (params[0][0] == '=')
		heredoc(params[1]);
	else if (params[0][0] == '>')
		fd = open(params[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (params[0][0] == '?')
		fd = open(params[1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
		error_exit(strerror(errno), start_node, self);
	if (params[0][0] == '<')
		dup2(fd, STDIN_FILENO);
	else if ((params[0][0] == '>') || (params[0][0] == '?'))
		dup2(fd, STDOUT_FILENO);
	else
		dup2(STDIN_FILENO, STDIN_FILENO);
	if (params[0][0] != '=')
		return (free2d(params), close(fd), 0);
	return (free2d(params), 1);
}

int	run_env(char **params, t_node *start_node, t_node *self)
{
	t_list	*temp;

	(void) self;
	if (strlist_len(params) != 1)
		error_exit("Env with too many args\n", start_node, self);
	temp = start_node->envp;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->val);
		temp = temp->next;
	}
	free2d(params);
	return (0);
}

int	run_exec(char **params, t_node *start_node, t_node *self)
{
	t_list	*temp;
	char	**arr_e;
	char	*line;
	int		len;

	temp = start_node->envp;
	while ((temp != NULL) && (len++))
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
	free(line);
	return (error_exit(strerror(errno), start_node, self), 0);
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
