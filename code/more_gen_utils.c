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

char	*expansion(char *str, t_list *envp, int i)
{
	char	*s;
	char	*var_name;
	char	*var_val;

	s = ft_strchr(str, '$');
	while ((s) && (s[++i] != '\0'))
	{
		var_name = NULL;
		if (s[i] == '?')
			printf("Exit Status Code: 1\n");
		else if ((s[i + 1] == ' ') || (s[i + 1] == '$') || (s[i + 1] == '\0'))
			var_name = ft_substr(s, 1, i);
		if (!var_name)
			continue ;
		var_val = ft_getenv(var_name, envp);
		free(var_name);
		if (*var_val == '\0')
			var_val = NULL;
		var_val = ft_strdup(var_val);
		str = strnrplc(str, var_val, s - str, i);
		s = ft_strchr(str, '$');
		i = 0;
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

int	change_io(int *fd, int com_amnt, int q, int to_pipe)
{
	if ((!to_pipe) || (com_amnt == 1))
		return (q);
	q++;
	if (q == 1)
	{
		printf("To STDOUT\n");
		dup2(fd[1], STDOUT_FILENO);
	}
	else if (q == com_amnt)
		dup2(fd[(q * 2) - 4], STDIN_FILENO);
	else
	{
		dup2(fd[(q * 2) - 4], STDIN_FILENO);
		dup2(fd[(q * 2) - 1], STDOUT_FILENO);
	}
	return (q);
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
