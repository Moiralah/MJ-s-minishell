#define MINISHELL_H
#ifdef MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"

typedef struct s_env_node
{
	char				*key;
	char				*value;
	struct s_env_node	*next;
}	t_env_node;

typedef struct s_nodes
{
	t_env_node		*env;
	char 			*params;
	int				(*run)(char *params);
	struct s_nodes	*next;
}	t_node;

#endif
