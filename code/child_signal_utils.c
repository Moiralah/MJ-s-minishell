/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_signal_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:48 by huidris           #+#    #+#             */
/*   Updated: 2025/03/14 04:51:21 by huidris          ###   ########.fr       */
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
	printerror("Quit (core dumped)\n");
	g_signal = 131;
}

//// printerror ////

void	printerror(const char *str, ...)
{
	va_list	ap;
	int		i;

	i = 0;
	va_start(ap, str);
	while (str[i])
	{
		if (str[i] == '%' && str[i+1] && str[i+1] == 's')
		{
			i++;
			ft_putstr_fd(va_arg(ap, char *), 2);
		}
		else
			ft_putchar_fd(str[i], 2);
		i++;
	}
	va_end(ap);
}
