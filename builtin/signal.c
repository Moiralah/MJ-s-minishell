/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 20:08:35 by huidris           #+#    #+#             */
/*   Updated: 2025/02/21 05:30:21 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"
#include <signal.h>
#include <stdlib.h>
#include <string.h>

// Purpose : Handles SIGINT by displaying a new prompt.
// Behavior : Writes a newline (\n), clears the current input line, and redisplays the prompt.
void	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

// Purpose : Handles the SIGQUIT (Ctrl+\) - Ignore in parent process.
// Behavior : Prints "Quit: 3" to the standard output.
void	sigquit_handler(int signo)
{
	(void)signo;
	write(1, "Quit: 3\n", 8);
}

// Purpose : Initializes the signal handlers for SIGINT and SIGQUIT.
// Behavior : Calls signal() to set the signal handlers for SIGINT and SIGQUIT.
void	init_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

// Purpose : Restores the default signal behaviour for execution. b4 calling execve.
// Behavior : Calls signal() to set the signal to SIG_DFL.
void	restore_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}
