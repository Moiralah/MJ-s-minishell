/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constructor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 03:28:04 by huidris           #+#    #+#             */
/*   Updated: 2025/01/09 01:18:33 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// constructor initialize all node for respective struct.

t_cmd*	execcmd(void)
{
	t_exec	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	cmd->type = EXEC;
	return ((t_cmd*)cmd);
}

t_cmd*	redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd)
{
	t_redir	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	cmd->type = REDIR;
	cmd->cmd = subcmd;
	cmd->file = file;
	cmd->efile = efile;
	cmd->mode = mode;
	cmd->fd = fd;
	return ((t_cmd*)cmd);
}

t_cmd*	pipecmd(t_cmd *left, t_cmd *right)
{
	t_pipe	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	cmd->type = PIPE;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd*)cmd);
}
t_cmd*	listcmd(t_cmd *left, t_cmd *right)
{
	t_list	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	cmd->type = LIST;
	cmd->left = left;
	cmd->right = right;
	return ((t_cmd*)cmd);
}

t_cmd*	backgcmd(t_cmd *subcmd)
{
	t_backg	*cmd;

	cmd = ft_calloc(1, sizeof(*cmd));
	cmd->type = BACKG;
	cmd->cmd = subcmd;
	return ((t_cmd*)cmd);
}
