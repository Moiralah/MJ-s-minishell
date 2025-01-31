/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsecmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 05:21:28 by huidris           #+#    #+#             */
/*   Updated: 2025/01/09 18:04:51 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd *parsecmd(char *s)
{
	char *es;
	t_cmd *cmd;

	es = s + ft_strlen(s);
	cmd = parseline (&s, es);
	peek(&s, es, "");
	if(s != es)
	{
		ft_putstr_fd ("leftovers", 2);
		ft_printf(" : %s\n", s);
		error_exit("syntax");
	}
	nulterminate(cmd);
	return cmd;
}

t_cmd *parsepipe(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "|"))
	{
		getttoken(ps, es, 0, 0);
		cmd = pipecmd(cmd, parsepipe(ps, es));
	}
	return (cmd);
}

t_cmd *parseline(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parsepipe(ps, es);
	while (peek(ps, es, "&"))
	{
		getttoken(ps, es, 0, 0);
		cmd = backgcmd(cmd);
	}
	if (peek (ps, es, ";"))
	{
		gettoken(ps, es, 0, 0);
		cmd = listcmd(cmd, parseline(ps, es));
	}
	return (cmd);
}

t_cmd *parseblock(char **ps, char *es)
{
	t_cmd *cmd;

	cmd = parseexec(ps, es);
	if (peek(ps, es, "("))
		error_exit("parseblock");
	getttoken(ps, es, 0, 0);
	cmd = parseline(ps, es);
	if (peek(ps, es, ")"))
		error_exit("syntax - missing )");
	getttoken(ps, es, 0, 0);
	cmd = parseredirs(cmd, ps, es);
	return (cmd);
}

t_cmd *parseredirs(t_cmd *cmd, char **ps, char *es)
{
	int token;
	char *q;
	char *eq;

	while(peek (ps, es, "<>"))
	{
		token = gettoken(ps, es, 0, 0);
		if (gettoken(ps, es, &q, &eq) != 'a')
			error_exit("missing file for redirection");
		if (token == '<')
			cmd = redircmd(cmd, q, eq, O_RDONLY, 0);
		else if (token == '>')
			cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT|O_TRUNC, 1);
		else if (token == '+')
			cmd = redircmd(cmd, q, eq, O_WRONLY|O_CREAT, 1);
	}
	return (cmd);
}

t_cmd *parseexec(char **ps, char *es)
{
	int token;
	int argc;
	char *q;
	char *eq;
	t_exec *cmd;
	t_cmd *ret;

	if(peek (ps, es, "("))
		return(parseblock(ps, es));
	ret = execcmd();
	cmd = (t_exec *)ret;

	argc = 0;
	ret = parseredirs(ret, ps, es);
	while(!peek(ps, es, "|)&;"))
	{
		if (token = gettoken(ps, es, &q, &eq) == 0)
			break;
		if (token != 'a')
			error_exit("syntax");
		cmd->argv[argc] = q;
		cmd->eargv[argc] = eq;
		argc++;
		if (argc >= MAXARGS)
			error_exit("too many args");
		ret = parseredirs(ret, ps, es);
	}
	cmd->argv[argc] = 0;
	cmd->eargv[argc] = 0;
	return ret;
}

