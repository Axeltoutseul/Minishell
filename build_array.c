/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_array.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 13:46:21 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/28 13:56:10 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(const char *cmd)
{
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	if (ft_strcmp(cmd, "history") == 0)
		return (1);
	return (0);
}

char	**build_env_array(t_env *env_list)
{
	int		count;
	int		i;
	char	**envp;
	char	*line;
	char	*tmp;

	count = env_size(env_list);
	envp = malloc(sizeof(char *) * (count + 1));
	if (envp == NULL)
		return (NULL);
	i = 0;
	while (env_list)
	{
		tmp = ft_strjoin(env_list->name, "=");
		if (tmp == NULL)
			return (NULL);
		if (env_list->value)
			line = ft_strjoin(tmp, env_list->value);
		else
			line = ft_strjoin(tmp, "");
		free(tmp);
		envp[i] = line;
		i = i + 1;
		env_list = env_list->next;
	}
	envp[i] = NULL;
	return (envp);
}
