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

//////////////////// Global Variable ///////////////////////////////////////

extern int	g_signal;

//////////////////// Link List Node ////////////////////////////////////////

typedef struct s_exit
{
	int	code;
}	t_exit;

//////////////////// Link List Node ////////////////////////////////////////

typedef struct s_list
{
	char			*key;
	char			*val;
	struct s_list	*next;
}	t_list;

//////////////////// Head Node /////////////////////////////////////////////

typedef struct s_head
{
	t_list			*envp;
	char			*input;
	int				*ori_fd;
	int				*fd;
	int				com_amnt;
	int				cur_pipe;
	struct s_node	*start;
}	t_head;

//////////////////// Execution Node ////////////////////////////////////////

typedef struct s_node
{
	char			**params;
	int				(*run)(char **p, struct s_head *head);
	int				to_pipe;
	struct s_node	*next;
}	t_node;

//////////////////// Create Node ////////////////////////////////////////

t_head	*create_head_node(t_list *envp, char *input, int com_amnt);

t_node	*create_cd_node(char **path);

t_node	*create_echo_node(char **to_print);

t_node	*create_pwd_node(char **params_to_verify);

t_node	*create_export_node(char **to_set);

t_node	*create_unset_node(char **to_unset);

t_node	*create_exec_node(char **_n_flags);

t_node	*create_exit_node(char **code);

t_node	*create_env_node(char **var);

t_node	*create_redir_node(char ch, char *filename);

////////////////////  Manage Run Node //////////////////////////////////////////

int		run_redir(char **params, t_head *head);

int		run_pipe(char **params, t_head *head);

int		run_env(char **params, t_head *head);

int		run_exec(char **params, t_head *head);

int		run_exit(char **params, t_head *head);

//////////////////// Built-In Run Node /////////////////////////////////////

int		run_cd(char **params, t_head *head);

int		run_echo(char **params, t_head *head);

int		run_pwd(char **params, t_head *head);

int		run_export(char **params, t_head *head);

int		run_unset(char **params, t_head *head);

//////////////////// ENV Utils //////////////////////////////////////////

t_list	*init_envp(char **envp);

char	*ft_getenv(char *key, t_list *envp);

void	ft_setenv(t_list **envp, char *key, char *val, int overwrite);

t_list	*dup_env(t_list *envp);

void	ft_sortenv(t_list **envp);

////////////////////  Generic Utils ////////////////////////////////////////

t_node	*function_matching(char *str);

char	*fnames_to_nodes(t_node *cur_node, char *comm, char ch);

int		pipe_handling(int **pipe, int len);

void	free_exec_list(t_head *head);

void	remove_link(t_list **head, t_list *cur, t_list *prev);

////////////////////  More Generic Utils ///////////////////////////////////

char	*expansion(t_list *envp, t_exit *ex, char *str, int i);

char	*find_path(char *params, t_list *envp);

int		verify_ch(char ch, char *set);

int		legitnum(char *str);

int		run_heredoc(char **params, t_head *head);

////////////////////  Parent Signal Utils //////////////////////////////////

void	disable_echoctl(void);

void	sigint_handler(int signo);

void	signal_ignore(void);

void	init_signal(void);

////////////////////  Child Signal Utils ///////////////////////////////////

void	restore_signal(void);

void	sigint_child(int signo);

void	sigquit_child(int signo);

void	printerror(const char *str, ...);

////////////////////  Str Utils ////////////////////////////////////////

char	**linklist_to_strlist(t_list *linklist);

char	*strjoin_n_gnl(int fd);

char	*strnrplc(char *str, char *replace, int start, int len);

int		fname_len(char *word, char *ig_set);

int		strlist_len(char **strlist);

///////////////////   Create Special Node //////////////////////////////

t_node	*create_heredoc_node(char **delimiter);

t_node	*create_pipe_node(int index);

char	*str_remove_q(char *str);

char	*exp_correct_key(char *str);

void	finish_heredoc(t_head *head, char **str, int *fds);

////////////////////  END ///////////////////////////////////////////////

#endif
