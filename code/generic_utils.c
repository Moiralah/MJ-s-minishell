#include "minishell.h"

t_node	function_matching(char *str, char **envp)
{
	char	**comm_n_flags;
	char	*comm;

	comm_n_flags = ft_split(str, ' ');
	comm = comm_n_flags[0];
	if (strncmp("cd", comm, ft_strlen(comm)))
		return (create_cd_node(comm_n_flags));
	else if (strncmp("echo", comm, ft_strlen(comm)))
		return (create_echo_node(comm_n_flags));
	else if (strncmp("pwd", comm, ft_strlen(comm)))
		return (create_pwd_node(comm_n_flags));
	else if (strncmp("export", comm, ft_strlen(comm)))
		return (create_export_node(comm_n_flags));
	else if (strncmp("unset", comm, ft_strlen(comm)))
		return (create_unset_node(comm_n_flags));
	else if (strncmp("env", comm, ft_strlen(comm)))
		return (create_env_node(comm_n_flags));
	else if (strncmp("exit", comm, ft_strlen(comm)))
		return (create_exit_node(comm_n_flags));
	return (create_exec_node(comm_n_flags, envp));
}

char	*expansion(char *str)
{
	char	*start;
	char	*var_name;
	char	*var_val;
	int		i;

	i = 0;
	start = ft_strchr(str, '$');
	while (start[++i] != '\0')
	{
		var_name = NULL;
		if (start[i] == '?')
			printf("Exit Status Code: 1\n");
		else if ((start[i] == ' ') || (start[i] == '$'))
			var_name = ft_substr(start, 1, i - 1);
		if (!var_name)
			continue ;
		var_val = ft_getenv(var_name);
		free(var_name);
		strnrplc(str, var_val, str - start, i - 1);
		start = ft_strchr(str, '$');
		i = 0;
	}
}

char	*strnrplc(char *str, char *replace, int start, int len)
{
	char	*before;
	char	*after;

	before = ft_substr(str, 0, start);
	after = ft_substr(str, start + len, ft_strlen(str) - start - len);
	str = ft_strjoin(before, replace);
	str = ft_strjoin(str, after);
	return (str);
}

int	heredoc(char *str)
{
	char	*line;
	char	*input;
	int		fd;

	line = readline();
	input = ft_strjoin(input, line);
	while (ft_strncmp(line, str, ft_strlen(str)) != 0)
	{
		line = readline();
		input = ft_strjoin(input, line);
	}
	free(str);
	fd = open("temp.txt", O_CREATE, O_WRONLY);
	write(fd, input, ft_strlen(input));
	return (fd);
}

void	error_exit(int errno)
{
	printf("Error: %s\n", strerror(errno));
	exit(-1);
}
