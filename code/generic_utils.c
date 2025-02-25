/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   generic_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:00 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:03:00 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*function_matching(char *str)
{
	char	**comm_n_flags;

	comm_n_flags = ft_split(str, ' ');
	free(str);
	if (!ft_strncmp("cd", comm_n_flags[0], ft_strlen(comm_n_flags[0])))
		return (create_cd_node(comm_n_flags));
	else if (!ft_strncmp("echo", comm_n_flags[0], ft_strlen(comm_n_flags[0])))
		return (create_echo_node(comm_n_flags));
	else if (!ft_strncmp("pwd", comm_n_flags[0], ft_strlen(comm_n_flags[0])))
		return (create_pwd_node(comm_n_flags));
	else if (!ft_strncmp("export", comm_n_flags[0], ft_strlen(comm_n_flags[0])))
		return (create_export_node(comm_n_flags));
	else if (!ft_strncmp("unset", comm_n_flags[0], ft_strlen(comm_n_flags[0])))
		return (create_unset_node(comm_n_flags));
	else if (!ft_strncmp("env", comm_n_flags[0], ft_strlen(comm_n_flags[0])))
		return (create_env_node(comm_n_flags));
	else if (!ft_strncmp("exit", comm_n_flags[0], ft_strlen(comm_n_flags[0])))
		return (create_exit_node(comm_n_flags));
	return (create_exec_node(comm_n_flags));
}

char	*fnames_to_nodes(t_node **cur_node, char *comm, char ch)
{
	char	*fname;
	char	*start;
	int		word_s;
	int		i;

	i = 0;
	word_s = 0;
	start = ft_strchr(comm, ch);
	while ((start) && (start[++i] != '\0'))
	{
		if (word_s)
		{
			i = word_end(start + word_s, " <>", 1);
			fname = ft_substr(start, word_s, i - word_s);
			if (start[0] == start[1])
				cur_node[0]->next = create_redir_node(ch + 1, fname);
			else
				cur_node[0]->next = create_redir_node(ch, fname);
			cur_node[0] = cur_node[0]->next;
			comm = strnrplc(comm, NULL, comm - start, i - word_s);
		}
		else if (ft_isprint(start[i]) || (start[i] != ' ') || (start[i] != ch))
			word_s = i;
	}
	return (comm);
}

void	pipe_handling(int **fd, int len)
{
	int	i;

	i = -1;
	if (len == 0)
		return ;
	if (fd[0] == NULL)
	{
		if (len <= 1)
			fd[0] = ft_calloc(2, sizeof(int));
		else
			fd[0] = ft_calloc((len - 1) * 2, sizeof(int));
		if (len <= 1)
			len = 2;
		while (++i < (len - 1))
			pipe(fd[0] + (2 * i));
		return ;
	}
	while (++i < len)
		close(fd[0][i]);
}

void	remove_link(t_list **head, t_list *cur, t_list *prev)
{
	free(cur->key);
	free(cur->val);
	if (cur == head[0])
		head[0] = head[0]->next;
	else
		prev->next = cur->next;
	free(cur);
}

void	error_exit(char *error_str, t_node *start, t_node *cur)
{
	t_node	*temp;
	int		to_free;

	printf("Error: %s\n", error_str);
	to_free = 0;
	while (start->envp != NULL)
		remove_link(&(start->envp), start->envp, NULL);
	temp = start;
	start = start->next;
	free(temp);
	while (start != NULL)
	{
		temp = start;
		start = start->next;
		if (start == cur)
			to_free = 1;
		if (to_free)
			free2d(start->params);
		free(start);
	}
	exit(1);
}
