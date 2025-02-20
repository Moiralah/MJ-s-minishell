/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/18 22:33:03 by huidris           #+#    #+#             */
/*   Updated: 2025/02/21 04:26:27 by huidris          ###   ########.fr       */
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

// tried to push under ft_atoi under libft using main branch but it was rejected
static long	ft_atol(const char *str)
{
	int		i;
	long	num;
	int		sign;

	i = 0;
	num = 0;
	sign = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		num = num * 10 + str[i] - '0';
		i++;
	}
	return (num * sign);
}
