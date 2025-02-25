#include "minishell.h"

char	*expansion(char *str, t_list *envp)
{
	char	*start;
	char	*var_name;
	char	*var_val;
	int		i;

	i = 0;
	start = ft_strchr(str, '$');
	while ((start) && (start[++i] != '\0'))
	{
		var_name = NULL;
		if (start[i] == '?')
			printf("Exit Status Code: 1\n");
		else if ((start[i] == ' ') || (start[i] == '$'))
			var_name = ft_substr(start, 1, i - 1);
		if (!var_name)
			continue ;
		var_val = ft_getenv(var_name, envp);
		free(var_name);
		strnrplc(str, var_val, str - start, i - 1);
		start = ft_strchr(str, '$');
		i = 0;
	}
	return (str);
}

char	find_path(charparams, t_list *envp)
{
	char	**path_list;
	char	*right_path;
	char	*path;
	int		i;

	path = ft_strdup(ft_getenv("PATH", envp));
	path_list = ft_split(path, ':');
	free(path);
	i = -1;
	if (access(params, F_OK) == 0)
		return (params);
	while (path_list[++i] != NULL)
	{
		right_path = ft_strjoin("/", ft_strdup(params));
		right_path = ft_strjoin(path_list[i], right_path);
		if (access(right_path, F_OK) == 0)
			break ;
		free(right_path);
		right_path = NULL;
	}
	free2d(path_list);
	return (right_path);
}

void	change_io(pid_t pid, int *fd, int com_amnt, int q)
{
	if ((pid == 0) && (com_amnt != 1) && (q == 1))
		dup2(fd[1], STDOUT_FILENO);
	else if ((pid == 0) && (com_amnt != 1) && (q == i))
		dup2(fd[(q * 2) - 4], STDIN_FILENO);
	else if ((pid == 0) && (com_amnt != 1))
	{
		dup2(fd[(2 * q) - 4], STDIN_FILENO);
		dup2(fd[(2 * q) - 1], STDOUT_FILENO);
	}
}

void	run_node(pid_t pid, t_node *start, t_node cur, char *input)
{
	char	**comm;

	comm = ft_calloc(3, sizof(char *));
	comm[0] = ft_strdup("echo");
	comm[1] = ft_strdup("-n");
	comm[2] = NULL;
	if (pid == 0)
	{
		pipe_handling(&fd, (i - 1) * 2);
		if (cur->run(cur->params, start, cur) == 1)
		{
			free(input);
			input = strjoin_n_gnl(STDOUT_FILENO);
		}
		run_exec(comm, start, cur);
	}
	free2d(comm);
}

void	heredoc(char *str)
{
	char	*line;

	line = readline(">");
	while (ft_strncmp(line, str, ft_strlen(str)) != 0)
	{
		free(line);
		line = readline(">");
	}
}
