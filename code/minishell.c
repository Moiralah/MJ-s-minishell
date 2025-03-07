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

void	executing(t_node *start, t_exit *ex, int com_amnt, char *input)
{
	t_node	**n;
	pid_t	pid;
	int		*fd;

	fd = NULL;
	n = resetting(start, input, &fd, com_amnt);
	while (n[1] != NULL)
	{
		pid = -2;
		if (!n[1]->built)
			pid = fork();
		change_io(n, pid, fd, com_amnt);
		if (pid == -1)
			(error_exit(n[0], n[1]), ex->code = errno);
		if (pid == -1)
			return ;
		if ((pid == -2) && run_non_built_in(n[0], n[1], &ex, &input))
			return ;
		else if ((pid == 0) && pipe_handling(n[0], &fd, com_amnt))
			(restore_signal(), n[1]->run(n[1]->params, n[0], n[1]));
		signal_ignore();
		n[1] = n[1]->next;
	}
	change_io(n, pid, fd, com_amnt);
	resetting(n[0], input, &fd, com_amnt);
}

t_node	*linking(t_node *start_node, t_node *cur_node, t_exit *ex, char *comm)
{
	comm = expansion(comm, start_node->envp, ex, 0);
	comm = fnames_to_nodes(&cur_node, comm, '<');
	comm = fnames_to_nodes(&cur_node, comm, '>');
	cur_node->next = function_matching(comm);
	if (cur_node->next)
		return (cur_node->next);
	return (cur_node);
}

void	initialising(t_list **envp, t_exit *ex, char **comms, char *line)
{
	t_node	*nodes[2];
	int		i;

	i = -1;
	nodes[0] = create_generic_node(envp[0]);
	nodes[1] = nodes[0];
	while (comms[++i] != NULL)
	{
		nodes[1] = linking(nodes[0], nodes[1], ex, comms[i]);
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
