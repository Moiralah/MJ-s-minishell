/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:48 by huidris           #+#    #+#             */
/*   Updated: 2025/03/13 05:29:06 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* Restore SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) to default
 * Re-enable ^C and other control character printing
 * enable_echoctl(); */

void	restore_signal(void)
{
	struct sigaction	sa;

	sa.sa_handler = sigint_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sa.sa_handler = sigquit_child;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGQUIT, &sa, NULL);
}

void	sigint_child(int signo)
{
	(void) signo;
	ft_putstr_fd("\n", 1);
	g_signal = 130;
}

void	sigquit_child(int signo)
{
	(void) signo;
	write(2, "Quit (core dumped)\n", 20);
	g_signal = 131;
}
