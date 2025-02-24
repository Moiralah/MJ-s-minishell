/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free2d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: huidris <huidris@student.42kl.edu.my>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 22:21:30 by huidris           #+#    #+#             */
/*   Updated: 2025/01/29 22:23:02 by huidris          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	free2d(char **str)
{
	int	i;

	i = 0;
	if (str == NULL)
		printf("NULL\n");
	while (str[i])
	{
		printf("%d\n", i);
		free(str[i]);
		i++;
	}
	printf("Hi\n");
	free(str);
	str = NULL;
}
