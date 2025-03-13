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

int	run_pipe(char **params, t_head *head)
{
	int	index;

	if ((head->com_amnt <= 1) || (params[0][0] == '-'))
		return (0);
	index = ft_atoi(params[0]);
	head->cur_pipe = index - 1;
	if (index == 1)
		dup2(head->fd[1], STDOUT_FILENO);
	else if (index == head->com_amnt)
	{
		// head->cur_pipe = index - 1;
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

int	run_redir(char **params, t_head *head)
{
	int	fd;

	(void) head;
	if (params[0][0] == '<')
		fd = open(params[1], O_RDONLY, 0666);
	else if (params[0][0] == '>')
		fd = open(params[1], O_CREAT | O_WRONLY | O_TRUNC, 0666);
	else if (params[0][0] == '?')
		fd = open(params[1], O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (fd == -1)
	{
		printerror("bash: open: The file doesn't exists or can't be accessed\n");
		return (2);
	}
	if (params[0][0] == '<')
		dup2(fd, STDIN_FILENO);
	else if ((params[0][0] == '>') || (params[0][0] == '?'))
		dup2(fd, STDOUT_FILENO);
	return (close(fd), 0);
}

int	run_env(char **params, t_head *head)
{
	t_list	*temp;
	t_list	*to_remove;

	if (strlist_len(params) != 1)
	{
		printerror("env: %s: No such file or directory\n", params[1]);
		return (127);
	}
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

int	run_exec(char **params, t_head *head)
{
	pid_t	pid;
	char	**arr_envp;
	char	*path;
	int		status;

	arr_envp = linklist_to_strlist(head->envp);
	path = find_path(params[0], head->envp);
	pid = fork();
	if (pid == -1)
		return (printerror("bash: error: fork failed\n"), errno);
	if (pid == 0)
	{
		pipe_handling(&head->fd, (head->com_amnt - 1) * 2);
		(close(head->ori_fd[0]), close(head->ori_fd[1]));
		execve(path, params, arr_envp);
		free_exec_list(head);
		exit(errno + 113);
	}
	if (head->cur_pipe != 0)
		close(head->fd[(head->cur_pipe * 2) - 1]);
	waitpid(-1, &status, 0);
	if (WEXITSTATUS(status) != 127)
		return (WEXITSTATUS(status));
	dup2(head->ori_fd[1], STDOUT_FILENO);
	return (printerror("%s: command not found\n", params[0]), WEXITSTATUS(status));
}

int	run_exit(char **params, t_head *head)
{
	long long int	exit_code;

	if (strlist_len(params) == 1)
	{
		free_exec_list(head);
		exit(0);
	}
	else if (strlist_len(params) == 2)// && legitnum(params[1]))
	{
		if ((params[1][0] == '-' || params[1][0] == '+')
			&& (params[1][1] == '"' || params[1][1] == 39))
			params[1] = str_remove_q(params[1]);
		else if (!legitnum(params[1]))
		{
			printerror("exit: %s: numeric argument required\n", params[1]);
			free_exec_list(head);
			exit(2);
		}
		exit_code = ft_atoll(params[1]);
		free_exec_list(head);
		exit((unsigned char) exit_code);
	}
	else if (strlist_len(params) > 2)
		return (printerror("exit: too many arguments\n"), 1);
	return (0);
}
