#include "minishell.h"

t_node	*function_matching(char *str)
{
	char	**comm_n_flags;
	char	*comm;

	comm_n_flags = ft_split(str, ' ');
	comm = comm_n_flags[0];
	if (ft_strncmp("cd", comm, ft_strlen(comm)))
		return (create_cd_node(comm_n_flags));
	else if (ft_strncmp("echo", comm, ft_strlen(comm)))
		return (create_echo_node(comm_n_flags));
	else if (ft_strncmp("pwd", comm, ft_strlen(comm)))
		return (create_pwd_node(comm_n_flags));
	else if (ft_strncmp("export", comm, ft_strlen(comm)))
		return (create_export_node(comm_n_flags));
	else if (ft_strncmp("unset", comm, ft_strlen(comm)))
		return (create_unset_node(comm_n_flags));
	else if (ft_strncmp("env", comm, ft_strlen(comm)))
		return (create_env_node(comm_n_flags));
	else if (ft_strncmp("exit", comm, ft_strlen(comm)))
		return (create_exit_node(comm_n_flags));
	return (create_exec_node(comm_n_flags));
}

char	*fnames_to_nodes(t_node *cur_node, char *comm, char ch)
{
	char	*fname;
	char	*start;
	int		word_s;
	int		i;

	i = 0;
	word_s = 0;
	start = ft_strchr(comm, ch);
	while (start[++i] != '\0')
	{
		if (word_s)
		{
			i = word_end(start + word_s, " <>", 1);
			fname = ft_substr(start, word_s, i - word_s);
			if (start[0] == start[1])
				cur_node->next = create_redir_node(ch + 1, fname);
			else
				cur_node->next = create_redir_node(ch, fname);
			cur_node = cur_node->next;
			comm = strnrplc(comm, NULL, comm - start, i - word_s);
		}
		else if (ft_isprint(start[i]) || (start[i] != ' ') || (start[i] != ch))
			word_s = i;
	}
	return (comm);
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

void	remove_link(t_list *head, t_list *cur, t_list *prev)
{
	free(cur->key);
	free(cur->val);
	if (cur == head)
		head = head->next;
	else
		prev->next = cur->next;
	free(cur);
}

void	error_exit(char *error_str)
{
	printf("Error: %s\n", error_str);
	exit(-1);
}
