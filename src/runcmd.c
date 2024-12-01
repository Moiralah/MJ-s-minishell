/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:28:09 by huidris           #+#    #+#             */
/*   Updated: 2024/12/01 05:52:33 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void runcmd(t_cmd *cmd)
{
	int p[2];
	t_backg	*bcmd;
	t_exec	*ecmd;
	t_list	*lcmd;
	t_pipe	*pcmd;
	t_redir	*rcmd;

	if(cmd == 0)
		exit(1);

	if(cmd->type == EXEC)
	{
		ecmd = (t_exec*)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		exec(ecmd->argv[0], ecmd->argv);
		ft_putstr_fd ("Error", 2);
		ft_printf(" : exec %s failed\n", ecmd->argv);
	}
	else if(cmd->type == REDIR)
	{
		rcmd = (t_redir*)cmd;
		close(rcmd->fd);
		if (open(rcmd->file, rcmd->mode) < 0)
		{
			ft_putstr_fd ("Error", 2);
			ft_printf(" : open %s failed\n", rcmd->file);
			exit(1);
		}
		runcmd(rcmd->cmd);
	}
	else if(cmd->type == PIPE)
	{
		pcmd = (t_pipe*)cmd;
		if (pipe(p) < 0)
			error_exit("pipe");
		if (forky() == 0)
		{
			close(1);
			dup(p[1]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->left);
		}
		if (forky() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right);
		}
		close(p[0]);
		close(p[1]);
		wait(0);
		wait(0);
	}
	else if(cmd->type == LIST)
	{
		lcmd = (t_list*)cmd;
		if (forky() == 0)
			runcmd(lcmd->left);
		wait(0);
		runcmd(lcmd->right);
	}
	else if(cmd->type == BACKG)
	{
		bcmd = (t_backg*)cmd;
		if (forky == 0)
			runcmd(bcmd->cmd);
	}
	else
		error_exit("runcmd");
	exit(0);


}


