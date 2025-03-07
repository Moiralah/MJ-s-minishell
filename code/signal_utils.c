/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:48 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:03:48 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ECHOCTL
//               (not in POSIX) If ECHO is also set, terminal special
//               characters other than TAB, NL, START, and STOP are echoed
//               as ^X, where X is the character with ASCII code 0x40
//               greater than the special character.  For example, character
//               0x08 (BS) is echoed as ^H.  [requires _BSD_SOURCE or
//               _SVID_SOURCE]

// Retrieving and changing terminal settings
//        tcgetattr() gets the parameters associated with the object
//        referred by fd and stores them in the termios structure referenced
//        by termios_p.  This function may be invoked from a background
//        process; however, the terminal attributes may be subsequently
//        changed by a foreground process.

//        tcsetattr() sets the parameters associated with the terminal
//        (unless support is required from the underlying hardware that is
//        not available) from the termios structure referred to by
//        termios_p.  optional_actions specifies when the changes take
//        effect:

//        TCSANOW
//               the change occurs immediately.
//		  c_lflag
//			is a field in the struct termios that contains
//			various flags controlling the behavior of the terminal.

void	disable_echoctl(void)
{
	struct termios	term;

	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
}

void	sigint_handler(int signo)
{
	(void)signo;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_ignore(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = SIG_IGN;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	init_signal(void)
{
	struct sigaction	sa;

	ft_memset(&sa, 0, sizeof(sa));
	sa.sa_handler = sigint_handler;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
	disable_echoctl();
}

void	restore_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

// void enable_echoctl(void)
// {
//     struct termios term;

//     if (tcgetattr(STDIN_FILENO, &term) == -1)
//         return;
// Error handling: don't modify terminal settings if we can't retrieve them

//     term.c_lflag = printf("\n");
//     // Re-enable ^C printing for executed commands
//     tcsetattr(STDIN_FILENO, TCSANOW, &term);  // Apply changes immediately
// }

// void restore_signal(void)
// {
//     struct sigaction sa;

//     // Restore SIGINT (Ctrl+C) and SIGQUIT (Ctrl+\) to default
//     sa.sa_handler = SIG_DFL;
//     sigemptyset(&sa.sa_mask);
//     sa.sa_flags = 0;
//     sigaction(SIGINT, &sa, NULL);
//     sigaction(SIGQUIT, &sa, NULL);

//     // Re-enable ^C and other control character printing
//     enable_echoctl();
// }
