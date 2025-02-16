#include "minishell.h"

void	run_cd(char **params)
{
	if (chdir(params[0]) < 0)
		error_exit(errno);
}

void	run_echo(char **params)
{
	printf("%s", params[0]);
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
	if (setenv(params[0], params[1], 1) < 0)
		error_exit(errno);
}

void	run_unset(char **params)
{
	if (unsetenv(params[0]) < 0)
		error_exit(errno);
}
