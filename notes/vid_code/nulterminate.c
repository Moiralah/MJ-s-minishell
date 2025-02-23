/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nulterminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 06:28:50 by huidris           #+#    #+#             */
/*   Updated: 2025/01/03 06:41:26 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

t_cmd *nulterminate(t_cmd *cmd)
{
	int	i;
	t_backg *bcmd;
	t_exec	*ecmd;
	t_list	*lcmd;
	t_pipe	*pcmd;
	t_redir *rcmd;

	if (cmd == 0)
		return (0);
	if(cmd->type == EXEC)
	{
		ecmd = (t_exec *)cmd;
		i = 0;
		while (ecmd->argv[i])
		{
			*ecmd->eargv[i] = 0;
			i++;
		}
	}
	else if(cmd->type == REDIR)
	{
		rcmd = (t_redir *)cmd;
		nulterminate(rcmd->cmd);
		*rcmd->efile = 0;
	}
	else if(cmd->type == PIPE)
	{
		pcmd = (t_pipe *)cmd;
		nulterminate(pcmd->left);
		nulterminate(pcmd->right);
	}
	else if(cmd->type == LIST)
	{
		lcmd = (t_list *)cmd;
		nulterminate(lcmd->left);
		nulterminate(lcmd->right);
	}
	else if(cmd->type == BACKG)
	{
		bcmd = (t_backg *)cmd;
		nulterminate(bcmd->cmd);
	}
	return cmd;
}
