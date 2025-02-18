/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utility.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 18:07:35 by huidris           #+#    #+#             */
/*   Updated: 2025/02/13 19:41:51 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// for all the function that need error checking,
// like fork, malloc ect.

#include "builtin.h"


void	error_exit(const char *msg)
{
	perror(msg);
	exit(1);
}

char	**copy2d(char **array)
{
	int		i;
	int		j;
	int		count;
	char	**copy;

	if (!array)
		return (NULL);
	count = 0;
	while (array[count] != NULL)
		count++;
	copy = malloc((count + 1) * sizeof(char *));
	i = -1;
	while (++i < count)
	{
		copy[i] = ft_strdup(array[i]);
		if (!copy[i])
		{
			j = -1;
			while (++j < i)
				free(copy[j]);
			free(copy);
			return (NULL);
		}
	}
	copy[count] = NULL;
	return (copy);
}

int	forky(void)
{
	int	pid;

	pid = fork();
	if (pid == -1)
		error_exit("fork failed");
	return (pid);
}

void *mallocy(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		error_exit("malloc failed");
	return (ptr);
}

int openy(char *filename, int flags)
{
	int	fd;

	fd = open(filename, flags);
	if (fd == -1)
		error_exit("open failed");
	return (fd);
}

int	dup2y(int oldfd, int newfd)
{
	if (dup2(oldfd, newfd) == -1)
		error_exit("dup2 failed");
	return (1);
}

int	closey(int fd)
{
	if (close(fd) == -1)
		error_exit("close failed");
	return (1);
}

int	execvpy(char *path, char **params)
{
	if (execvp(path, params) == -1)
		error_exit("execvp failed");
	return (1);
}

int	chdiry(char *path)
{
	if (chdir(path) == -1)
		error_exit("chdir failed");
	return (1);
}

int	pipey(int *fd)
{
	if (pipe(fd) == -1)
		error_exit("pipe failed");
	return (1);
}
