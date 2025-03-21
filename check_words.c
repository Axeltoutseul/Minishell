/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:49 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/22 15:30:11 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_path_validity(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == -1 || !ft_strlen(ft_strrchr(cmd, '/') + 1))
		return (0);
	return (1);
}

int	existing_command(char **paths, char *cmd)
{
	int		i;
	int		result;
	char	*cmd_path;

	i = 0;
	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/'))
		return (check_path_validity(cmd));
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
			return (0);
		result = access(cmd_path, F_OK | X_OK);
		free(cmd_path);
		if (result == 0)
			return (1);
		i++;
	}
	return (0);
}

void	check_error(char *name, char *arg)
{
	int		i;
	char	*val;

	i = 0;
	if (count_occurs(arg, '='))
		val = ft_strchr(arg, '=') + 1;
	else
		val = NULL;
	while (name[i] && name[i] != '&' && name[i] != '(' && name[i] != ')')
		i++;
	if (name[i] == '&' || name[i] == '(' || name[i] == ')')
		ft_printf("minishell: syntax error near unexpected token '%c'\n",
			name[i]);
	else
		ft_printf("export: not valid in this context: '%s'\n", name);
}

int	is_space(int c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

char	*get_line_without_space(char *line)
{
	int		i;
	int		j;
	int		size;
	char	*new_string;

	i = 0;
	size = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			size++;
		i++;
	}
	new_string = (char *)malloc(sizeof(char) * (size + 1));
	if (!new_string)
		return (NULL);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (!is_space(line[i]))
			new_string[j++] = line[i];
		i++;
	}
	new_string[j] = 0;
	return (new_string);
}
