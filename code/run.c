#include "minishell.h"

void run_CD()
{
	char *new_path;

	chdir(new_path);
}

void run_ECHO(char **params)
{
	int i;

	i = 0;
	while (params[i])
	{
		printf("%s", params[i]);
		i++;
	}
}

void run_PWD()
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	printf("%s\n", cwd);
	free(cwd);
}

void run_PIPE(t_node *left, t_node *right)
{
	int fd[2];
	pid_t pid;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		left->PIPE->run(left->PIPE->params);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[1]);
		right->type->run(right->type->params);
	}
}

void run_REDIR(t_node *redir)
{
	int fd;
	pid_t pid;

	fd = open(redir->REDIR->filename, O_RDWR | O_CREAT, 0644);
	if(fd == -1)
		error_exit("open failed");
	pid = fork();
	if (pid == 0)
	{
		dup2(fd, redir->REDIR->ch == '>' ? 1 : 0);
		close(fd);
		redir->REDIR->run(redir->REDIR->params);
	}
}

void run_ENV(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

void run_EXPT(char *var, char *val)
{
	setenv(var, val, 1);
}

void run_UNSET(char *var)
{
	unsetenv(var);
}

void run_EXEC(char **argv, char **envp)
{
	execve(argv[0], argv, envp);
}

