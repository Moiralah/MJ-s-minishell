/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:10:19 by huidris           #+#    #+#             */
/*   Updated: 2025/01/16 23:06:29 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

// https://man7.org/linux/man-pages/man3/errno.3.html
void error_exit(const char *msg, int errnum)
{
	errno = errnum;
	perror(msg);
	exit(0);
}

void run_CD(char *new_path)
{
	chdir(new_path);
}

	// This function represents a kind of constructor. Other create_XX_node functions behave in a similar manner
	// by assigning the type of node the new node is and the function to be run with that new node. It should be
	// noted that necessary information required for the node to run properly are to be assigned at this stage too
	// Eg. the file path user wants to cd to is assigned now
t_node *create_CD_node(char *path)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->CD = malloc(sizeof(CD_node));
	new_node->CD->new_path = path;
	new_node->CD->run = run_CD;
	return (new_node);
}

t_node *func_match(char *comm)
{
	t_node	*new_node;
	char	**comm_flags;

	comm = ft_strtrim(comm, ' ');
	comm_flags = ft_split(comm, ' ');
	if (ft_strcmp(comm_flags[0], "cd"))
		new_node = create_CD_node(comm_flags[1]);
	else if (ft_strcmp(comm_flags[0], "echo"))
		new_node = create_ECHO_node();
	else if (ft_strcmp(comm_flags[0], "pwd"))
		new_node = create_PWD_node();
	else if (ft_strcmp(comm_flags[0], "export"))
		new_node = create_EXPT_node();
	else if (ft_strcmp(comm_flags[0], "unset"))
		new_node = create_UNST_node();
	else if (ft_strcmp(comm_flags[0], "env"))
		new_node = create_ENV_node();
	else if (ft_strcmp(comm_flags[0], "exit"))
		new_node = create_EXIT_node();
	else
		new_node = create_EXEC_node(comm_flags);
	return (new_node);
}

t_node *get_next_nodes(t_node *current_node, char *comm, int *pid)
{
	t_node *redir_node;
	char *command;
	char ch;

	ch = '\0';
	if (ft_strch(comm, '<') >= 0)
		ch = '<';
	else if (ft_strch(comm, '>') >= 0)
		ch = '>';
	if (!ch)
		return (NULL);
	redir_node = malloc(sizeof(t_node));
	redir_node->REDIR = malloc(sizeof(redir_node));
	redir_node->next = NULL;
	current_node->next = redir_node;
	if (comm[ft_strch(ch) + 1] == ch);
		ch += 1;
	redir_node->type->ch = ch;
	command = ft_substr(comm, 0, ft_strch(comm, ch), len);
	redir_node->type->filename = ft_substr(comm, ft_strrch(comm, ch) + 1, len, len);
	if (ft_strch(comm, ch) == 0)
	{
		command = ft_substr(comm, ft_strrch(comm, ' ') + 1, len, len);
		redir_node->type->filename = ft_substr(comm, ft_strrch(comm, ch) + 1, ft_strrch(comm, ' '), len);
	}
	redir_node->type->pid = pid;
	current_node->next->next = func_match(command) return (current_node->next->next);
}

void run_list(t_node *start)
{
	t_node *current;
	pid_t pid;

	current = start->next;
	while (current != NULL)
	{
		pid = fork();
		if (pid == 0)
			current->type->run(current->type->params);
		waitpid(0);
		current = current->next;
	}
}

int main(int argc, char **argv, char **envp)
{
	t_node *current_node;
	t_node *start_node;
	char **comms;
	char *input;
	int pid[2];
	int i;

	while (1)
	{
		i = -1;
		input = readline("\nminishell>");
		add_history(input);
		comms = ft_split(input, '|');
		current_node = (t_node *){0};
		start_node = current_node;
		while (comms[++i] != NULL)
		{
			dup2(pid[0], STDOUT_FILENO);
			dup2(pid[1], STDIN_FILENO);
			current_node = get_next_nodes(current_node, comms[i], pid);
		}
		run_list(start_node);
	}
	return (0);
}
