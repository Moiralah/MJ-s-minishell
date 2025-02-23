/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:47:25 by huidris           #+#    #+#             */
/*   Updated: 2025/01/10 02:09:48 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_exit(char *str)
{
	ft_putstr_fd ("Error", 2);
	ft_printf (": %s\n", str);
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

int getcmd(char *buf, size_t buf_size)
{
	char *input;

	input = readline("\nminishell>");
	if(!input)
		return (-1);
	if(*input)
		add_history(input);
	ft_strlcpy(buf, input, buf_size -1);
	buf[buf_size -1] = '\0';
	free(input);

	return (0);
}

int main(int argc, char **argv, char **envp)
{
	static char	buf[100];

	while(getcmd(buf, sizeof(buf)) >= 0)
	{
		if(buf[0] == 'c' && buf[1] == 'd' && buf[2] == ' ')
		{
			buf[ft_strlen(buf)-1] = '\0';
			if (chdir(buf + 3) < 0)
			{
				ft_putstr_fd ("Error", 2);
				ft_printf(" : cannot cd %s\n", buf+3);
			}
			continue;
		}
		if(forky() == 0)
			runcmd(parsecmd(buf), envp);
		wait(0);
	}
	rl_clear_history();
	exit(0);
}
