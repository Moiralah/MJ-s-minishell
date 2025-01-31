#define MINISHELL_H
#ifdef MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_nodes
{
	union	u_type
	{
		t_exec_node		*exec;
		t_cd_node		*cd;
		t_echo_node		*echo;
		t_export_node	*exprt;
		t_unset_node	*unset;
		t_env_node		*env;
		t_pwd_node		*pwd;
	};
	struct s_nodes	*next;
}	t_nodes;

typedef struct s_exec_node
{
	char	**params;
	int		(*run)(char **params);
}	t_exec_node;

typedef struct s_cd_node
{
	char	**params;
	int		(*run)(char *path);
}	t_cd_node;

typedef struct s_echo_node
{
	char	**params;
	int		(*run)(char *str);
}	t_echo_node;

typedef struct s_export_node
{
	char	**params;
	int		(*run)(void);
}	t_export_node;

typedef struct s_unset_node
{
	char	**params;
	int		(*run)(void);
}	t_unset_node;

typedef struct s_env_node
{
	int		(*run)(void);
}	t_env_node;

typedef struct s_pwd_node
{
	int		(*run)(void);
}	t_pwd_node;

typedef struct s_exit_node
{
	int		(*run)(void);
}	t_cd_node;

#endif
