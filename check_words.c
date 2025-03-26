/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_words.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:49 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/26 16:54:31 by axbaudri         ###   ########.fr       */
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
	if (val && !valid_value(val))
		ft_printf("syntax error: unclosed quote\n");
	else if (name[i] == '&' || name[i] == '(' || name[i] == ')')
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

int	invalid_prompt(char	*line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_strlen(line + i) >= 2 && line[i] == '|' && line[i + 1] == '|')
			return (1);
		if (ft_strlen(line + i) >= 2 && ((line[i] == '<' && line[i + 1] == '>')
			|| (line[i] == '>' && line[i + 1] == '<')))
			return (1);
		if (ft_strlen(line + i) >= 3)
		{
			if ((line[i] == '<' || line[i] == '>')
				&& (line[i + 1] == '<' || line[i + 1] == '>')
				&& (line[i + 2] == '<' || line[i + 2] == '>'))
				return (1);
		}
		i++;
	}
	return (0);
}
