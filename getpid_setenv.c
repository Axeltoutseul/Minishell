/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getpid_setenv.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:23:14 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/28 15:41:13 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	my_setenv(t_env **env, const char *name, const char *value, int overwrite)
{
	t_env	*curr;
	t_env	*new_node;

	if (name == NULL || value == NULL)
		return (-1);
	curr = *env;
	while (curr)
	{
		if (ft_strcmp(curr->name, name) == 0)
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
	new_node = malloc(sizeof(t_env));
	if (new_node == NULL)
		return (-1);
	new_node->name = ft_strdup(name);
	new_node->value = ft_strdup(value);
	new_node->next = *env;
	*env = new_node;
	return (0);
}
