/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:23:14 by quenalla          #+#    #+#             */
/*   Updated: 2025/04/01 02:10:53 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	contains_redirection(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp(tokens[i], ">")
			|| !ft_strcmp(tokens[i], ">>")
			|| !ft_strcmp(tokens[i], "<")
			|| !ft_strcmp(tokens[i], "<<"))
			return (1);
		i++;
	}
	return (0);
}

pid_t	my_getpid(void)
{
	int		fd;
	char	buf[64];
	ssize_t	n;

	fd = open("/proc/self/stat", O_RDONLY);
	if (fd < 0)
		return (-1);
	n = read(fd, buf, sizeof(buf) - 1);
	close(fd);
	if (n <= 0)
		return (-1);
	buf[n] = '\0';
	return ((pid_t)ft_atoi(buf));
}

static t_env	*create_env_node(const char *name, const char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->name = ft_strdup(name);
	node->value = ft_strdup(value);
	node->next = NULL;
	return (node);
}

int	my_setenv(t_env **env, const char *name, const char *value, int overwrite)
{
	t_env	*curr;

	if (!name || !value)
		return (-1);
	curr = *env;
	while (curr)
	{
		if (!ft_strcmp(curr->name, name))
		{
			if (overwrite)
			{
				free(curr->value);
				curr->value = ft_strdup(value);
			}
			return (0);
		}
		curr = curr->next;
	}
	curr = create_env_node(name, value);
	if (!curr)
		return (-1);
	curr->next = *env;
	*env = curr;
	return (0);
}
