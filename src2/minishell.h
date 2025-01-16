/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 23:08:53 by huidris           #+#    #+#             */
/*   Updated: 2025/01/16 23:09:18 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>

// Node structure for commands
typedef struct s_node
{
	union
	{
		struct CD_node		*CD;
		struct ECHO_node	*ECHO;
		struct PWD_node		*PWD;
		struct EXPORT_node	*EXPORT;
		struct UNSET_node	*UNSET;
		struct ENV_node		*ENV;
		struct LIST_node	*LIST;
		struct PIPE_node	*PIPE;
		struct REDIR_node	*REDIR;
		struct EXEC_node	*EXEC;
		struct EXIT_node	*EXIT;
	};
	struct s_node	*next;
}					t_node;

typedef struct	CD_node
{
	char	*new_path;
	void	(*run)(char *new_path);
}			CD_node;

typedef struct	EXEC_node
{
	char	**argv;
	void	(*run)(char **argv);
}			EXEC_node;

// Utility functions
void error_exit(const char *msg, int errnum);

// Command node creation functions
t_node *create_CD_node(char *path);
t_node *create_EXEC_node(char **argv);

// Command matching
t_node *func_match(char *comm);

// Command execution
void run_list(t_node *start);

#endif
