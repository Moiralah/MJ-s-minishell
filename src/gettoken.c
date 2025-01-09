/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gettoken.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 03:43:56 by huidris           #+#    #+#             */
/*   Updated: 2025/01/09 01:41:36 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"



//ps = pointer str
//es = end of str
//q = token
//eq = end after token

int	gettoken(char **ps, char **es, char **q, char **eq)
{
	static char	whitespace[] = " \t\r\n\v";
	static char	symbols[] = "<|>&;()";
	char	*s;
	int		ret;

	s = *ps;
	while (s < es && ft_strchr(whitespace, *s))
		s++;
	if (q)
		*q = s;
	ret = *s;
	if (*s == 0)
		ret = '\0';
	// else if (*s == '|' || *s == '(' || *s == ')' || *s == ';'
	// 	|| *s == '&' || *s == '<')
	else if(ft_strchr(symbols, *s) && *s != '>')
		s++;
	else if (*s == '>')
	{
		s++;
		if (*s == '>')
		{
			ret = '+';
			s++;
		}
	}
	else
	{
		ret = 'a';
		while (s < es && !ft_strchr(whitespace, *s)
			&& !ft_strchr(symbols, *s))
			s++;
	}
	if (eq)
		*eq = s;

	while (s < es && !ft_strchr(whitespace, *s))
		s++;
	*ps = s;
	return (ret);
}

int peek (char **ps, char *es, char *tokens)
{
	char	whitespace[] = " \t\r\n\v";
	char *s;

	s = *ps;
	while (s < es && ft_strchr(whitespace, *s))
		s++;
	*ps = s;
	return (*s && ft_strchr(tokens, *s));
}
