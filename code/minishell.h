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
	int				(*run)(char **params, t_list envp);
	struct s_nodes	*next;
}	t_node;

#endif
