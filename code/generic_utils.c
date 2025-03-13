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

	comm_n_flags = ft_splitmj(str, ' ');
	free(str);
	if (!comm_n_flags[0])
		return (NULL);
	if (!ft_strcmp("cd", comm_n_flags[0]))
		return (create_cd_node(comm_n_flags));
	else if (!ft_strcmp("echo", comm_n_flags[0]))
		return (create_echo_node(comm_n_flags));
	else if (!ft_strcmp("pwd", comm_n_flags[0]))
		return (create_pwd_node(comm_n_flags));
	else if (!ft_strcmp("export", comm_n_flags[0]))
		return (create_export_node(comm_n_flags));
	else if (!ft_strcmp("unset", comm_n_flags[0]))
		return (create_unset_node(comm_n_flags));
	else if (!ft_strcmp("env", comm_n_flags[0]))
		return (create_env_node(comm_n_flags));
	else if (!ft_strcmp("exit", comm_n_flags[0]))
		return (create_exit_node(comm_n_flags));
	return (create_exec_node(comm_n_flags));
}

char	*fnames_to_nodes(t_node *cur_node, char *comm, char ch)
{
	char	*fname;
	int		i;

	i = -1;
	while (comm[++i] != '\0')
	{
		if (comm[i] == '"')
			i = ft_strchr(comm + i + 1, '"') - comm;
		else if (comm[i] == 39)
			i = ft_strchr(comm + i + 1, 39) - comm;
		if (comm[i] != ch)
			continue ;
		fname = ft_substr(comm, i, fname_len(comm + i, " <>"));
		if (comm[i + 1] == ch)
			cur_node->next = create_redir_node(ch + 1, fname);
		else
			cur_node->next = create_redir_node(ch, fname);
		cur_node = cur_node->next;
		comm = strnrplc(comm, NULL, i, ft_strlen(fname));
		free(fname);
		i = 0;
	}
	return (comm);
}

int	pipe_handling(int **fd, int len)
{
	int	i;

	i = -1;
	restore_signal();
	if (fd[0] == NULL)
	{
		fd[0] = ft_calloc((len - 1) * 2, sizeof(int));
		while (++i < (len  - 1))
			pipe(fd[0] + (2 * i));
		return (0);
	}
	while (++i < len)
		close(fd[0][i]);
	return (1);
}

void	free_exec_list(t_head *head)
{
	t_node	*temp;

	while (head->start != NULL)
	{
		temp = head->start;
		head->start = head->start->next;
		free2d(temp->params);
		free(temp);
	}
	free(head->input);
	free(head->ori_fd);
	free(head->fd);
	free(head);
}

void	remove_link(t_list **head, t_list *cur, t_list *prev)
{
	if (cur == head[0])
		head[0] = head[0]->next;
	else
		prev->next = cur->next;
	free(cur->key);
	free(cur->val);
	free(cur);
}
