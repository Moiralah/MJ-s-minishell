/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 19:21:10 by huidris           #+#    #+#             */
/*   Updated: 2024/12/01 02:48:25 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define EXEC	1
# define REDIR	2
# define PIPE	3
# define LIST	4
# define BACKG	5

typedef struct	s_cmd
{
	int	type;
}		t_cmd;

typedef	struct s_exec
{
	int		type;
	char	**argv;
	char	**eargv;
}				t_exec;

typedef	struct s_redir
{
	int		type;
	char	*file;
	char	*efile;
	char	mode;
	int		fd;
	t_cmd	*cmd;
}			t_redir;

typedef	struct s_pipe
{
	int				type;
	struct s_pipe	*left;
	struct s_pipe	*right;
}					t_pipe;

typedef	struct s_list
{
	int				type;
	struct s_list	*left;
	struct s_list	*right;
}					t_list;

typedef	struct s_backg
{
	int		type;
	t_cmd	*cmd;
}			t_backg;

typedef struct s_token
{
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

// main.c
void	error_exit(char *str);
int		forky(void);

//constructor.c
t_cmd*	execcmd(void);
t_cmd*	redircmd(t_cmd *subcmd, char *file, char *efile, int mode, int fd);
t_cmd*	pipecmd(t_cmd *left, t_cmd *right);
t_cmd*	listcmd(t_cmd *left, t_cmd *right);
t_cmd*	backgcmd(t_cmd *subcmd);


#endif
