/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 13:28:27 by huidris           #+#    #+#             */
/*   Updated: 2025/02/19 00:15:16 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H
# include "../libft/libft.h"
# include "minishell.h"

void	error_exit(const char *msg);
char	**copy2d(char **array);
void	run_cd(int argc, char **argv, t_node *node);
t_env_node *init_env(char **envp);
char	*ft_getenv(char *key, t_node *node);
void	ft_setenv(t_node *node, char *key, char *val, int overwrite);
void	run_env(t_env_node *env);
void	run_echo(char **argv);
void	run_pwd();
void	run_export(char **argv, t_node *node);
void	run_unset(char **argv, t_node *node);
void	free_env_node(char *key, char *val);

/////// UTILITY ///////

int	forky(void);
void	*mallocy(size_t size);
int	openy(char *filename, int flags);
int	dup2y(int oldfd, int newfd);
int	closey(int fd);
int	execvpy(char *path, char **params);
int	chdiry(char *path);
int	pipey(int *fd);

#endif
