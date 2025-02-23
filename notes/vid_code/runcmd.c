/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:28:09 by huidris           #+#    #+#             */
/*   Updated: 2025/01/09 05:58:07 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void runcmd(t_cmd *cmd, char **envp)
{
	int p[2];
	t_backg	*bcmd;
	t_exec	*ecmd;
	t_list	*lcmd;
	t_pipe	*pcmd;
	t_redir	*rcmd;
	char *path;

	if(cmd == 0)
		exit(1);

	if(cmd->type == EXEC)
	{
		ecmd = (t_exec*)cmd;
		if (ecmd->argv[0] == 0)
			exit(1);
		path = get_path(ecmd->argv[0]);
		execve(path, ecmd->argv, envp);
		ft_putstr_fd ("Error", 2);
		ft_printf(" : execve %s failed\n", ecmd->argv);
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
		runcmd(rcmd->cmd, envp);
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
			runcmd(pcmd->left, envp);
		}
		if (forky() == 0)
		{
			close(0);
			dup(p[0]);
			close(p[0]);
			close(p[1]);
			runcmd(pcmd->right, envp);
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
			runcmd(lcmd->left, envp);
		wait(0);
		runcmd(lcmd->right, envp);
	}
	else if(cmd->type == BACKG)
	{
		bcmd = (t_backg*)cmd;
		if (forky == 0)
			runcmd(bcmd->cmd, envp);
	}
	else
		error_exit("error runcmd");

	exit(0);
}

char *get_path(char *argv)
{
	char *path;
	char *full_path;
	char *env_path;
	char **paths;
	int	i;

	env_path = getenv("PATH");
	if(!env_path)
		error_exit(" : PATH not found\n");
	paths = ft_split(env_path, ':');
	if(!paths)
		error_exit(" : PATH parsing failed\n");
	i = 0;
	while (paths[i])
	{
		full_path = ft_strjoin(paths[i], "/");
		path = ft_strjoin(full_path, argv);
		free(full_path);
		i++;
	}
	i = 0;
	while (paths[i])
		free(paths[i++]);
	free(paths);
	return(path);
}

