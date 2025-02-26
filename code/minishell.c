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

void	executing(t_node *start, char *input, int com_amnt, int q)
{
	t_node	*nodes[2];
	int		*fd;

	fd = NULL;
	nodes[0] = start->next;
	nodes[1] = start;
	pipe_handling(&fd, com_amnt);
	while ((nodes[0] != NULL) && (++q))
	{
		change_io(fd, com_amnt, q);
		run_node(nodes, &input, fd, com_amnt);
		nodes[0] = nodes[0]->next;
	}
	pipe_handling(&fd, com_amnt);
	waitpid(-1, NULL, 0);
	add_history(input);
	free(input);
}

t_node	*linking(t_node *start_node, t_node *cur_node, char *comm)
{
	char	*input;
	char	*err_line;

	input = NULL;
	err_line = "grep: (standard input): input file is also the output";
	comm = fnames_to_nodes(&cur_node, comm, '<');
	if ((cur_node) && (cur_node->params))
		input = cur_node->params[1];
	comm = fnames_to_nodes(&cur_node, comm, '>');
	if (input && !ft_strcmp(input, cur_node->params[1]))
		error_exit(err_line, start_node, cur_node);
	cur_node->next = function_matching(comm);
	return (cur_node->next);
}

void	initialising(t_list *envp, char **comms, char *line)
{
	t_node	*nodes[2];
	int		i;

	i = -1;
	nodes[0] = create_generic_node();
	nodes[1] = nodes[0];
	while (comms[++i] != NULL)
	{
		comms[i] = expansion(comms[i], envp, 0);
		nodes[1] = linking(nodes[0], nodes[1], comms[i]);
	}
	free(comms);
	nodes[0]->envp = envp;
	nodes[1] = nodes[0];
	executing(nodes[1], line, i, 0);
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
		initialising(envp, ft_split(input, '|'), input);
	}
	while (envp != NULL)
		remove_link(&envp, envp, NULL);
	return (0);
}
