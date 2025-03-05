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

// var[0] = var_name
// var[1] = var_value
char	*expansion(char *str, t_list *envp, int i)
{
	char	*s;
	char	*var[2];

	s = ft_strchr(str, '$');
	if (s && ft_strchr(s, 39) != NULL)
		return (str);
	while ((s) && (s[++i] != '\0'))
	{
		var[0] = NULL;
		if (s[i] == '?')
			printf("Exit Status Code: 1\n");
		else if ((s[i + 1] == ' ') || (s[i + 1] == '$') || (s[i + 1] == '\0'))
			var[0] = ft_substr(s, 1, i);
		if (!var[0])
			continue ;
		var[1] = ft_getenv(var[0], envp);
		free(var[0]);
		if (!var[1] || *var[1] == '\0')
			var[1] = NULL;
		var[1] = ft_strdup(var[1]);
		str = strnrplc(str, var[1], s - str, i);
		s = ft_strchr(str, '$');
		i = -1;
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

void	change_io(t_node *cur, pid_t pid, int *fd, int com_amnt, int *ori, int fix)
{
	if (fix)
	{
		dup2(ori[1], STDOUT_FILENO);
		dup2(ori[0], STDIN_FILENO);
	}
	if ((!cur->to_pipe) || (com_amnt == 1))
		return ;
	if (pid > 0)
		return ;
	if (cur->to_pipe == 1)
		dup2(fd[1], STDOUT_FILENO);
	else if (cur->to_pipe == com_amnt)
		dup2(fd[(cur->to_pipe * 2) - 4], STDIN_FILENO);
	else
	{
		dup2(fd[(cur->to_pipe * 2) - 4], STDIN_FILENO);
		dup2(fd[(cur->to_pipe * 2) - 1], STDOUT_FILENO);
	}
}

void	heredoc(char *str)
{
	char	*line;

	line = readline(">");
	while (ft_strcmp(line, str) != 0)
	{
		free(line);
		line = readline(">");
	}
}
