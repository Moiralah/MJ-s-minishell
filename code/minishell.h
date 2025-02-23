#define MINISHELL_H
#ifdef MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

//////////////////// Link List Node ////////////////////////////////////////

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

//////////////////// Execution Node ////////////////////////////////////////

typedef struct s_nodes
{
	t_list			*envp;
	char			**params;
	int				(*run)(char **params, t_list *envp);
	struct s_nodes	*next;
}	t_node;

//////////////////// Create Node ////////////////////////////////////////

t_node	create_cd_node(char **path);

t_node	create_echo_node(char **to_print);

t_node	create_pwd_node(char **params_to_verify);

t_node	create_export_node(char **to_set);

t_node	create_unset_node(char **to_unset);

t_node	create_exec_node(char **comm_n_flags);

t_node	create_exit_node(char **code);

t_node	create_env_node(char **var);

t_node	create_redir_node(char *ch, char *filename);

//////////////////// Run Node //////////////////////////////////////////

int	run_cd(char **params, t_list *envp);

int	run_echo(char **params, t_list *envp);

int	run_pwd(char **params, t_list envp);

int	run_export(char **params, t_list *envp);

int	run_unset(char **params, t_list *envp);

int	run_redir(char **params, t_list *envp);

int	run_env(char **params, t_list *envp);

int	run_exec(char **params, t_list *envp);

int	run_exit(char **params, t_list *envp);

//////////////////// ENV Utils //////////////////////////////////////////

t_list	*init_env(char **envp);

char	*ft_getenv(t_list *envp, char *key);

void	ft_setenv(t_list *envp, char *key, char *val, int overwrite);

void	close_pipe(int *pipe, int len);

////////////////////  Generic Utils ////////////////////////////////////////

t_node	function_matching(char *str, char **envp);

char	*fnames_to_nodes(t_node cur_node, char *comm, char ch);

void	heredoc(char *str);

void	remove_link(t_list *head, t_list *cur, t_list *prev);

void	error_exit(int errno);

////////////////////  Signal Utils ////////////////////////////////////////

void	sigint_handler(int signo);

void	sigquit_handler(int signo);

void	init_signal(void);

void	restore_signal(void);

////////////////////  Str Utils ////////////////////////////////////////

char	*expansion(char *str);

char	*strjoin_n_gnl(int fd);

char	*strnrplc(char *str, char *replace, int start, int len);

int	strlist_len(char **strlist);

int	word_end(char *word, char *end_set, int print);

void	free_strlist(char **strlist, int index);

////////////////////  END ///////////////////////////////////////////////

#endif
