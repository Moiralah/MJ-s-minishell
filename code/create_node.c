#include "minishell.h"

t_node	create_generic_node(void)
{
	t_node	generic_node;

	generic_node = malloc(sizeof(t_node));
	generic_node->type = NULL;
	generic_node->next = NULL;
	return (generic_node);
}

t_node	create_rd_node(int ch, int special, char *filename)
{
	t_node	rd_node;
	char	*params[2];

	params[0] = ch;
	if (special)
		params[0] += 1;
	params[1] = filename;
	rd_node = malloc(sizeof(t_node));
	rd_node->type = malloc(sizeof(redir_node));
	rd_node->type->params = params;
	rd_node->next = NULL;
	return (rd_node);
}
