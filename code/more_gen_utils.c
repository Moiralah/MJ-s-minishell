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

char	*expansion(t_list *envp, t_exit *ex, char *str, int i)
{
	char	*var[2];
	int		q;

	while (str[++i] != '\0')
	{
		if ((str[i] == 39) && ft_strchr(str + i + 1, 39))
			i = ft_strchr(str + i + 1, 39) - str;
		if ((str[i] != '$') || (!ft_isalpha(str[i + 1]) && (str[i + 1] != '?')))
			continue ;
		q = i + 1;
		i = get_end(str + q, "0|9|10|32|34|36|63", 1) + q;
		if (!(i - q))
			i++;
		var[0] = ft_substr(str, q, i - q);
		var[1] = ft_strdup(ft_getenv(var[0], envp));
		if (var[0][0] == '?')
			free(var[1]);
		if (var[0][0] == '?')
			var[1] = ft_itoa(ex->code);
		free(var[0]);
		str = strnrplc(str, var[1], q - 1, i - q + 1);
		i = -1;
	}
	return (str);
}

char	*find_path(char *params, t_list *envp)
{
	char	**path_list;
	char	*path;
	int		i;

	if (ft_strchr(params, '/'))
		return (params);
	path = ft_getenv("PATH", envp);
	path_list = ft_split(path, ':');
	i = -1;
	while (path_list[++i] != NULL)
	{
		path = ft_strjoin(ft_strdup("/"), ft_strdup(params));
		path = ft_strjoin(ft_strdup(path_list[i]), path);
		if (access(path, X_OK) == 0)
			break ;
		free(path);
		path = NULL;
	}
	free2d(path_list);
	return (path);
}

int	run_heredoc(char **params, t_head *head)
{
	char	*s[2];
	int		fds[3];

	if (pipe(fds) == -1)
		return (printerror("Error: failed to create pipe\n"), 1);
	s[1] = NULL;
	fds[2] = dup(STDOUT_FILENO);
	dup2(head->ori_fd[1], STDOUT_FILENO);
	while (1)
	{
		s[0] = readline(">");
		if (!s[0] || !ft_strcmp(s[0], params[1]))
			break ;
		s[0] = ft_strjoin(s[0], ft_strdup("\n"));
		s[1] = ft_strjoin(s[1], ft_strdup(s[0]));
		write(fds[1], s[0], ft_strlen(s[0]));
		free(s[0]);
	}
	return (finish_heredoc(head, s, fds), 0);
}

int	get_end(char *str, char *set, int set_at_end)
{
	char	**chs;
	int		i;
	int		q;

	i = 0;
	chs = ft_split(set, '|');
	while ((size_t)i <= ft_strlen(str))
	{
		q = 0;
		while ((chs[q] != NULL) && (str[i] != ft_atoi(chs[q])))
			q++;
		if ((chs[q] != NULL) && (set_at_end))
			return (i);
		else if ((chs[q] == NULL) && (!set_at_end))
			return (i);
		i++;
	}
	return (-1);
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
