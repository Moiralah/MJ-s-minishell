/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:33:03 by huidris           #+#    #+#             */
/*   Updated: 2025/02/21 04:22:58 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtin.h"

int	legitnum(char *argv)
{
	if (!argv || !*argv)
		return (0);
	if (argv[0] == '-' || argv[0] == '+')
		argv++;
	if (!*argv)
		return (0);
	while (*argv)
	{
		if (!ft_isdigit(*argv))
			return (0);
		argv++;
	}
	return (1);
}

void	run_exit(int argc, char **argv, t_node *node)
{
	if (argc == 1)
		exit(node->exit_status);
	if (argc >= 2 && legitnum(argv[1]))
	{
		node->exit_status = ft_atol(argv[1]);
		if (argc > 2)
		{
			ft_putstr_fd("exit: too many arguments\n", 2);
			return ;
		}
		exit((unsigned char)node->exit_status);
	}
	else
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(argv[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		node->exit_status = 2;
		exit(node->exit_status);
	}
}
