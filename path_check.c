/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:11:38 by dakojic           #+#    #+#             */
/*   Updated: 2024/02/05 12:21:01 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	path_check(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '/')
			return (1);
		i++;
	}
	return (0);
}
