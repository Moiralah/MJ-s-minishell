/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:47:25 by huidris           #+#    #+#             */
/*   Updated: 2024/12/01 02:27:54 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *str)
{
	ft_putstr_fd ("Error", 2);
	ft_printf (": %s", str);
	ft_printf ("\n");
	exit (1);
}

int	forky(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork");
	return (pid);
}

int main(void)
{
	static char	buf[100];
	int			fd;

	while((fd = open("console", O_RDWR)) >= 0)
	{
		if (fd >= 3)
		{
			close(fd);
			break;
		}
	}

	while(getcmd(buf, sizeof(buf)) >= 0)
	{
		if(buf[0] = 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			buf[ft_strlen(buf)-1] = 0;
			if (chdir(buf + 3) < 0)
			{
				ft_putstr_fd ("Error", 2);
				ft_printf(" : cannot cd %s\n", buf+3);
			}
			continue;
		}
		if(forky() == 0)
			runcmd(parsecmd(buf));
		wait(0);
	}
	exit(0);
}
