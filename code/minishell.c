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
	t_node	*nodes[2];

	nodes[0] = start;
	nodes[1] = start->next;
	while (nodes[1] != NULL)
	{











		run_node(nodes, &input, fd, com_amnt);
		nodes[1] = nodes[1]->next;
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

void	initialising(t_list **envp, char **comms, char *line, int *fd)
{
	t_node	*nodes[2];
	int		i;

	i = -1;
	pipe_handling(&fd, strlist_len(comms));
	// nodes[0] = create_pipe_node(fd, 0, strlist_len(comms));
	nodes[0] = create_generic_node();
	nodes[0]->envp = envp[0];
	nodes[1] = nodes[0];
	while (comms[++i] != NULL)
	{
		nodes[1] = linking(nodes[0], nodes[1], comms[i]);
		// nodes[1]->next = create_pipe_node(fd, i, strlist_len(comms));
		nodes[1] = nodes[1]->next;
	}
	free(comms);
	nodes[1] = nodes[0];
	executing(nodes[1], fd, i, line);
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
		initialising(&envp, ft_split(input, '|'), input, NULL);
	}
	while (envp != NULL)
		remove_link(&envp, envp, NULL);
	return (0);
}
