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

int	run_pipe(char **params, t_head *head, t_exit *ex)
{
	int	index;

	if (ex->code < 0)
		return (ex->code);
	if ((head->com_amnt <= 1) || (params[0][0] == '-'))
		return (0);
	index = ft_atoi(params[0]);
	head->cur_pipe = index - 1;
	if (index == 1)
		dup2(head->fd[1], STDOUT_FILENO);
	else if (index == head->com_amnt)
	{
		dup2(head->fd[(index * 2) - 4], STDIN_FILENO);
		dup2(head->ori_fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(head->fd[(index * 2) - 4], STDIN_FILENO);
		dup2(head->fd[(index * 2) - 1], STDOUT_FILENO);
	}
	return (0);
}

int	run_redir(char **params, t_head *head, t_exit *ex)
{
	int	fd;

	if (ex->code < 0)
		return (ex->code);
	(void) head;
	if (params[0][0] == '<')
		fd = open(params[1], O_RDONLY, 0666);
	else if (params[0][0] == '>')
		fd = open(params[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (params[0][0] == '?')
		fd = open(params[1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
	{
		perr("bash: open: The file doesn't exists or can't be accessed\n");
		return (2);
	}
	if (params[0][0] == '<')
		dup2(fd, STDIN_FILENO);
	else if ((params[0][0] == '>') || (params[0][0] == '?'))
		dup2(fd, STDOUT_FILENO);
	return (close(fd), 0);
}

int	run_env(char **params, t_head *head, t_exit *ex)
{
	t_list	*temp;
	t_list	*to_remove;

	if (ex->code < 0)
		return (1);
	if (strlist_len(params) != 1)
		return (perr("env: %s: No such file or directory\n", params[1]), 127);
	temp = head->envp;
	if (!ft_strcmp(params[0], "export"))
	{
		temp = dup_env(head->envp);
		ft_sortenv(&temp);
		to_remove = temp;
	}
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->key, temp->val);
		temp = temp->next;
	}
	if (!ft_strcmp(params[0], "export"))
		remove_link(&to_remove, to_remove, NULL);
	return (0);
}

int	run_exec(char **params, t_head *head, t_exit *ex)
{
	struct stat	st;
	pid_t		pid;
	char		**arr_envp;
	char		*path;

	if (ex->code < 0)
		return (1);
	arr_e = linklist_to_strlist(head->envp);
	path = find_path(params[0], head->envp);
	pid = fork();
	if (pid == -1)
		return (perr("bash: error: fork failed\n"), errno);
	if (pid == 0)
	{
		pipe_handling(&head->fd, (head->com_amnt - 1) * 2);
		(close(head->ori_fd[0]), close(head->ori_fd[1]));
		stat(path, &st);
		if (S_ISDIR(st.st_mode))
			exit(126);
		execve(path, params, arr_envp);
		free_exec_list(head);
		if (access(path, F_OK) != 0)
			exit(127);
		exit(errno + 113);
	}
	return (0);
}

int	run_exit(char **params, t_head *head, t_exit *ex)
{
	long long int	exit_code;

	if (ex->code < 0)
		return (1);
	if (strlist_len(params) == 1)
	{
		free_exec_list(head);
		exit(0);
	}
	else if (strlist_len(params) == 2)
	{
		if (!legitnum(params[1]))
		{
			perr("exit: %s: numeric argument required\n", params[1]);
			free_exec_list(head);
			exit(2);
		}
		exit_code = ft_atoll(params[1]);
		free_exec_list(head);
		exit((unsigned char) exit_code);
	}
	else if (strlist_len(params) > 2)
		return (perr("exit: too many arguments\n"), 1);
	return (0);
}
