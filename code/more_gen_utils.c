/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_gen_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:23 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:03:24 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expansion(char *str, t_list *envp, t_exit *ex, int i)
{
	char	*var[2];
	int		q;

	q = -2;
	while (str[++i] != '\0')
	{
		var[0] = NULL;
		if (str[i] == 39)
			i = ft_strchr(str + i + 1, 39) - str + 1;
		if (str[i] == '$')
			q = i;
		str = expand_error_code(ex, str, &i, &q);
		if (verify_ch(str[i + 1], "0|9|10|32|34|36"))
			var[0] = ft_substr(str, q + 1, i - q);
		if (!var[0])
			continue ;
		var[1] = ft_strdup(ft_getenv(var[0], envp));
		free(var[0]);
		str = strnrplc(str, var[1], q, i - q);
		i = -1;
		q = -2;
	}
	return (str);
}

char	*find_path(char *params, t_list *envp)
{
	char	**path_list;
	char	*path;
	int		i;

	path = ft_getenv("PATH", envp);
	path_list = ft_split(path, ':');
	if (access(params, F_OK) == 0)
		return (params);
	i = -1;
	while (path_list[++i] != NULL)
	{
		path = ft_strjoin(ft_strdup("/"), ft_strdup(params));
		path = ft_strjoin(ft_strdup(path_list[i]), path);
		if (access(path, F_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free2d(path_list);
	return (path);
}

int	legitnum(char *str)
{
	if (!str || !*str)
		return (0);
	if (str[0] == '-' || str[0] == '+')
		str++;
	if (!*str)
		return (0);
	while (*str)
	{
		if (!ft_isdigit(*str))
			return (0);
		str++;
	}
	return (1);
}

void	change_io(t_node **n, pid_t pid, int *fd, int com_amnt)
{
	if ((n[1] && !n[1]->to_pipe) || (com_amnt == 1))
		return ;
	if ((pid > 0) && n[1] && (n[1]->to_pipe == com_amnt))
		dup2(n[0]->ori_fd[0], STDIN_FILENO);
	if ((pid > 0) && n[1] && (n[1]->to_pipe == com_amnt))
		dup2(n[0]->ori_fd[1], STDOUT_FILENO);
	if (pid > 0)
		return ;
	if (!n[1] && !dup2(n[0]->ori_fd[0], STDIN_FILENO))
		return ;
	if (n[1]->to_pipe == 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (n[1]->to_pipe == com_amnt)
	{
		dup2(fd[(n[1]->to_pipe * 2) - 4], STDIN_FILENO);
		dup2(n[0]->ori_fd[1], STDOUT_FILENO);
	}
	else
	{
		dup2(fd[(n[1]->to_pipe * 2) - 4], STDIN_FILENO);
		dup2(fd[(n[1]->to_pipe * 2) - 1], STDOUT_FILENO);
	}
}

int	run_heredoc(char **params, t_node *start, t_node *self)
{
	char	*line;

	(void) start;
	(void) self;
	line = readline(">");
	while (ft_strncmp(line, params[0], ft_strlen(line) + 1) != 0)
	{
		free(line);
		line = readline(">");
	}
	return (0);
}
