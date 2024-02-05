/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dakojic <dakojic@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 10:11:48 by dakojic           #+#    #+#             */
/*   Updated: 2024/02/05 12:20:09 by dakojic          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// static char	*ft_strjoin(char const *s1, char const *s2)
// {
// 	size_t	len;
// 	size_t	cur;
// 	size_t	i;
// 	char	*new;

// 	cur = 0;
// 	i = 0;
// 	if (!s1 || !s2)
// 		return (NULL);
// 	len = ft_strlen(s1) + ft_strlen(s2);
// 	new = (char *)malloc(sizeof (char) * len + 1);
// 	if (!new)
// 		return (NULL);
// 	while (s1[cur] != '\0')
// 	{
// 		new[cur] = s1[cur];
// 		cur++;
// 	}
// 	while (s2[i] != '\0')
// 	{
// 		new[cur++] = s2[i++];
// 	}
// 	new[cur] = '\0';
// 	return (new);
// }

static int	ft_strcmpn(char *str1, char *str2, int n)
{
	while (--n > 0 && *str1 && *str2 && *str1 == *str2)
	{
		++str1;
		++str2;
	}
	return (*str2 - *str1);
}

static int	check(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

static char	*ft_strdupn(char *str, unsigned int n)
{
	char				*new;
	unsigned int		i;

	i = 0;
	new = malloc(sizeof(char) * (n + 1));
	while (i < n)
		new[i++] = *str++;
	new[i] = 0;
	return (new);
}

static char	*path_join(char *path, char *cmd)
{
	char	*new;
	int		i;
	int		j;

	new = malloc(sizeof(char) * (check(path, 0) + check(cmd, 0) + 2));
	i = 0;
	j = 0;
	while (path[j])
		new[i++] = path[j++];
	new[i++] = '/';
	j = 0;
	while (cmd[j])
		new[i++] = cmd[j++];
	new[i] = 0;
	return (new);
}

char	*get_path(char *cmd, char **env)
{
	char	*temp_path;
	char	*true_path;
	char	*dir;
	int		i;

	i = 0;
	while (env[i] && ft_strcmpn(env[i], "PATH=", 5))
		i++;
	if (!env[i])
		return (cmd);
	temp_path = env[i] + 5;
	while (temp_path && check(temp_path, ':') > -1)
	{
		dir = ft_strdupn(temp_path, check(temp_path, ':'));
		true_path = path_join(dir, cmd);
		free(dir);
		if (access(true_path, F_OK | X_OK) == 0)
			return (true_path);
		free(true_path);
		temp_path += check(temp_path, ':') + 1;
	}
	return (cmd);
}
