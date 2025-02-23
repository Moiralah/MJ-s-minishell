#define MINISHELL_H
#ifdef MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_list
{
	char			*key;
	char			*value;
	struct s_list	*next;
}	t_list;

typedef struct s_nodes
{
	t_list			*envp;
	char			**params;
	int				(*run)(char **params, t_list *envp);
	struct s_nodes	*next;
}	t_node;

t_node	create_cd_node(char **path);

t_node	create_echo_node(char **to_print);

t_node	create_pwd_node(char **params_to_verify);

t_node	create_export_node(char **to_set);

t_node	create_unset_node(char **to_unset);

t_node	create_exec_node(char **comm_n_flags);

t_node	create_exit_node(char **code);

t_node	create_env_node(char **var);

t_node	create_redir_node(char *ch, char *filename);

int	run_cd(char **params, t_list *envp);

int	run_echo(char **params, t_list *envp);

int	run_pwd(char **params, t_list envp);

int	run_export(char **params, t_list *envp);

int	run_unset(char **params, t_list *envp);

int	run_redir(char **params, t_list *envp);

int	run_env(char **params, t_list *envp);

int	run_exec(char **params, t_list *envp);

int	run_exit(char **params, t_list *envp);

#endif
