#include "minishell.h"

void	run_cd(char **params)
{
	if (chdir(params[1]) < 0)
		error_exit(errno);
	free_strlist(params, -1);
}

void	run_echo(char **params)
{
	int	i;

	i = 0;
	while (params[++i] != "\0")
		printf("%s ", params[i]);
	free_strlist(params, -1);
}

void	run_pwd(char **params)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		error_exit(errno);
	else
		error_exit(errno);
	free (cwd);
}

void	run_export(char **params)
{
	if (setenv(params[1], params[2], 1) < 0)
		error_exit(errno);
	free_strlist(params, -1);
}

void	run_unset(char **params)
{
	if (unsetenv(params[0]) < 0)
		error_exit(errno);
	free_strlist(params, -1);
}
