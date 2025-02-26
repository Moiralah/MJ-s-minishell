/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 23:03:17 by huidris           #+#    #+#             */
/*   Updated: 2025/02/25 23:03:17 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <errno.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <termios.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

//////////////////// Link List Node ////////////////////////////////////////

typedef struct s_list
{
	char			*key;
	char			*val;
	struct s_list	*next;
}	t_list;

//////////////////// Execution Node ////////////////////////////////////////

typedef struct s_nodes
{
	t_list			*envp;
	char			**params;
	int				(*run)(char **p, struct s_nodes *st, struct s_nodes *s);
	int				built;
	struct s_nodes	*next;
}	t_node;

//////////////////// Create Node ////////////////////////////////////////

t_node	*create_generic_node(void);

t_node	*create_cd_node(char **path);

t_node	*create_echo_node(char **to_print);

t_node	*create_pwd_node(char **params_to_verify);

t_node	*create_export_node(char **to_set);

t_node	*create_unset_node(char **to_unset);

t_node	*create_exec_node(char **_n_flags);

t_node	*create_exit_node(char **code);

t_node	*create_env_node(char **var);

t_node	*create_redir_node(char ch, char *filename);

//////////////////// Run Node //////////////////////////////////////////

int		run_cd(char **params, t_node *start_node, t_node *self);

int		run_echo(char **params, t_node *start_node, t_node *self);

int		run_pwd(char **params, t_node *start_node, t_node *self);

int		run_export(char **params, t_node *start_node, t_node *self);

int		run_unset(char **params, t_node *start_node, t_node *self);

int		run_redir(char **params, t_node *start_node, t_node *self);

int		run_env(char **params, t_node *start_node, t_node *self);

int		run_exec(char **params, t_node *start_node, t_node *self);

int		run_exit(char **params, t_node *start_node, t_node *self);

//////////////////// ENV Utils //////////////////////////////////////////

t_list	*init_envp(char **envp);

char	*ft_getenv(char *key, t_list *envp);

void	ft_setenv(t_list **envp, char *key, char *val, int overwrite);

////////////////////  Generic Utils ////////////////////////////////////////

t_node	*function_matching(char *str);

char	*fnames_to_nodes(t_node **cur_node, char *comm, char ch);

void	pipe_handling(int **pipe, int len);

void	remove_link(t_list **head, t_list *cur, t_list *prev);

void	error_exit(char *str_error, t_node *start, t_node *cur);

////////////////////  More Generic Utils ///////////////////////////////////

char	*expansion(char *str, t_list *envp, int i);

char	*find_path(char *params, t_list *envp);

void	run_node(t_node **nodes, char **input, int *fd, int com_amnt);

void	change_io(int *fd, int com_amnt, int q);

void	heredoc(char *str);

////////////////////  Signal Utils ////////////////////////////////////////

void	sigint_handler(int signo);

void	sigquit_handler(int signo);

void	init_signal(void);

void	restore_signal(void);

////////////////////  Str Utils ////////////////////////////////////////

char	*strjoin_n_gnl(int fd);

char	*strnrplc(char *str, char *replace, int start, int len);

int		strlist_len(char **strlist);

int		word_end(char *word, char *end_set, int print);

void	free_strlist(char **strlist, int index);

int		ft_lstsize(t_list *lst);

////////////////////  END ///////////////////////////////////////////////

#endif
