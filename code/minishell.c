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

void	executing(t_node *start, int *fd, int com_amnt, char *input)
{
	t_node	*cur;
	pid_t	pid;

	pid = -2;
	cur = start->next;
	pipe_handling(&fd, com_amnt);
	while (cur != NULL)
	{
		if (!cur->built)
			pid = fork();
		change_io(cur, pid, fd, com_amnt);
		if (pid == -1)
			error_exit(strerror(errno), start, cur);
		if ((pid == -2) && (cur->run(cur->params, start, cur) == 1))
			(free(input), input = strjoin_n_gnl(STDOUT_FILENO));
		else if ((pid == 0) && (pipe_handling(&fd, com_amnt)))
			cur->run(cur->params, start, cur);
		cur = cur->next;
	}
	pipe_handling(&fd, com_amnt);
	waitpid(-1, NULL, 0);
	add_history(input);
	free(input);
}

t_node	*linking(t_node *start_node, t_node *cur_node, char *comm)
{
	comm = expansion(comm, start_node->envp, 0);
	comm = fnames_to_nodes(&cur_node, comm, '<');
	comm = fnames_to_nodes(&cur_node, comm, '>');
	cur_node->next = function_matching(comm);
	return (cur_node->next);
}

void	initialising(t_list **envp, char **comms, char *line)
{
	t_node	*nodes[2];
	int		i;

	i = -1;
	nodes[0] = create_generic_node();
	nodes[0]->envp = envp[0];
	nodes[1] = nodes[0];
	while (comms[++i] != NULL)
	{
		nodes[1] = linking(nodes[0], nodes[1], comms[i]);
		nodes[1]->to_pipe = i + 1;
	}
	free(comms);
	nodes[1] = nodes[0];
	executing(nodes[1], NULL, i, line);
	envp[0] = nodes[0]->envp;
	while (nodes[0] != NULL)
	{
		nodes[1] = nodes[0];
		nodes[0] = nodes[0]->next;
		free(nodes[1]);
	}
}

char	*listening(int i, int q)
{
	char	*line;

	line = readline("MJ > ");
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
	char	*input;
	int		running;

	running = -1;
	if ((argc > 1) && (argv != NULL))
		return (printf("Don't give any args"), -1);
	envp = init_envp(local_envp);
	while (running)
	{
		init_signal();
		input = listening(0, 0);
		initialising(&envp, ft_split(input, '|'), input);
	}
	while (envp != NULL)
		remove_link(&envp, envp, NULL);
	return (0);
}
