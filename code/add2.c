#include "minishell.h"

t_node *create_CD_node(char *path)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->CD = malloc(sizeof(CD_node));
	new_node->CD->new_path = path;
	new_node->CD->run = run_CD;
	return (new_node);
}

t_node *create_ECHO_node(char **params)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->ECHO = malloc(sizeof(ECHO_node));
	new_node->ECHO->params = params;
	new_node->ECHO->run = run_ECHO();
	return (new_node);
}

t_node *create_PWD_node(void)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->PWD = malloc(sizeof(PWD_node));
	new_node->PWD->run = run_PWD();
	return (new_node);
}

t_node *create_EXEC_node(char **argv)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->EXEC = malloc(sizeof(EXEC_node));
	new_node->EXEC->argv = argv;
	new_node->EXEC->run = run_EXEC();
	return (new_node);
}

t_node *create_EXIT_node(void)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->EXIT = malloc(sizeof(EXIT_node));
	new_node->EXIT->run = run_EXIT();
	return (new_node);
}

t_node *create_EXPORT_node(char *var, char *val)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->EXPORT = malloc(sizeof(EXPORT_node));
	new_node->EXPORT->var = var;
	new_node->EXPORT->val = val;
	new_node->EXPORT->run = run_EXPORT();
	return (new_node);
}

t_node *create_UNSET_node(char *var)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->UNSET = malloc(sizeof(UNSET_node));
	new_node->UNSET->var = var;
	new_node->UNSET->run = run_UNSET();
	return (new_node);
}

t_node *create_ENV_node(void)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->ENV = malloc(sizeof(ENV_node));
	new_node->ENV->run = run_ENV();
	return (new_node);
}

t_node *create_LIST_node(t_node *start)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->LIST = malloc(sizeof(LIST_node));
	new_node->LIST->run = run_LIST();
	new_node->LIST->start = start;
	return (new_node);
}

t_node *create_PIPE_node(t_node *left, t_node *right)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->PIPE = malloc(sizeof(PIPE_node));
	new_node->PIPE->run = run_PIPE();
	new_node->PIPE->left = left;
	new_node->PIPE->right = right;
	return (new_node);
}

t_node *create_REDIR_node(char ch, char *filename, int *pid)
{
	t_node *new_node;

	new_node = malloc(sizeof(t_node));
	new_node->REDIR = malloc(sizeof(REDIR_node));
	new_node->REDIR->run = run_REDIR();
	new_node->REDIR->ch = ch;
	new_node->REDIR->filename = filename;
	new_node->REDIR->pid = pid;
	return (new_node);
}


