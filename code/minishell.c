/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:08 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:03:08 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executing(t_head *head, t_exit *ex)
{
	t_node	*cur;
	int		i;

	cur = head->start;
	while (cur != NULL)
	{
		change_io(cur, head);
		i = cur->run(cur->params, head);
		if (i == -1)
		{
			free(head->input);
			head->input = strjoin_n_gnl(head->ori_fd[1]);
		}
		ex->code = 0;
		if (i > 0)
			ex->code = i;
		cur = cur->next;
	}
	change_io(cur, head);
	pipe_handling(&head->fd, head->ori_fd, head->com_amnt);
	i = 0;
	while (i != -1)
		i = waitpid(-1, NULL, 0);
	add_history(head->input);
}

void	linking(t_head *head, t_exit *ex, char *comm, int index)
{
	t_node	*temp;

	if (!head->start)
		head->start = create_redir_node(0, NULL);
	temp = head->start;
	while (temp->next != NULL)
		temp = temp->next;
	comm = expansion(head->envp, ex, comm, 0);
	comm = fnames_to_nodes(temp, comm, '<');
	while (temp->next != NULL)
		temp = temp->next;
	comm = fnames_to_nodes(temp, comm, '>');
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = function_matching(comm);
	temp->next->to_pipe = index + 1;
	if (head->start->params[0][0] == 0)
	{
		temp = head->start;
		head->start = temp->next;
		free2d(temp->params);
		free(temp);
	}
}

void	initialising(t_list **envp, t_exit *ex, char **comms, char *line)
{
	t_head	*head;
	int		i;

	i = -1;
	head = create_head_node(*envp, line, strlist_len(comms));
	while (comms[++i] != NULL)
		linking(head, ex, comms[i], i);
	free(comms);
	executing(head, ex);
	*envp = head->envp;
	free_exec_list(head);
}

char	*listening(int i, int q)
{
	char	*line;

	line = readline("MJ > ");
	if (line == NULL)
		(printf("exit\n"), exit(0));
	while (line[i] != '\0')
	{
		q = 0;
		if ((line[i] == '"') && ft_strchr(line + i + 1, '"'))
			i = ft_strchr(line + i + 1, '"') - line;
		else if ((line[i] == '"') && !ft_strchr(line + i + 1, '"'))
			q = 1;
		else if ((line[i] == 39) && ft_strchr(line + i + 1, 39))
			i = ft_strchr(line + i + 1, 39) - line;
		else if ((line[i] == 39) && !ft_strchr(line + i + 1, 39))
			q = 1;
		if (q)
		{
			line = ft_strjoin(line, ft_strdup("\n"));
			line = ft_strjoin(line, readline("> "));
		}
		else
			i++;
	}
	return (line);
}

int	main(int argc, char **argv, char **local_envp)
{
	t_list	*envp;
	t_exit	*ex;
	char	*input;
	int		running;

	running = -1;
	if ((argc > 1) && (argv != NULL))
		return (printf("Don't give any args"), -1);
	ex = ft_calloc(1, sizeof(t_exit));
	ex->code = 0;
	envp = init_envp(local_envp);
	while (running)
	{
		init_signal();
		input = listening(0, 0);
		initialising(&envp, ex, ft_splitmj(input, '|'), input);
	}
	while (envp != NULL)
		remove_link(&envp, envp, NULL);
	return (0);
}
