/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:49 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/26 16:37:05 by axbaudri         ###   ########.fr       */
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

int	valid_arg(char *name, char *arg)
{
	int		i;
	char	*value;

	i = 0;
	if (!(isalpha(name[i]) || name[i] == '_'
		|| name[i] == '$' || name[i] == '<' || name[i] == '>'))
		return (0);
	i++;
	while (name[i] && name[i] != '=')
	{
		if (!(isalnum(name[i]) || name[i] == '_'
			|| name[i] == '$' || name[i] == '<' || name[i] == '>'))
			return (0);
		i++;
	}
	if (count_occurrences(arg, '='))
	{
		value = ft_strchr(arg, '=') + 1;
		if (!valid_value(value))
			return (0);
	}
	return (1);
}

int	valid_value(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s) - 1;
	if ((s[i] == '\'' && s[j] == '"') || (s[i] == '"' && s[j] == '\''))
		return (0);
	else if (s[i] == '\'' && count_occurrences(s, '\'') % 2 == 1)
		return (0);
	else if (s[i] == '"' && count_occurrences(s, '"') % 2 == 1)
		return (0);
	return (1);
}

void	check_error(char *name, char *arg)
{
	int		i;
	char	*val;

	i = 0;
	if (count_occurrences(arg, '='))
		val = ft_strchr(arg, '=') + 1;
	else
		val = NULL;
	while (name[i] && name[i] != '&' && name[i] != '(' && name[i] != ')')
		i++;
	if (val && !valid_value(val))
		printf("unexpected newline while looking for matching `%c'\n", val[0]);
	else if (name[i] == '&' || name[i] == '(' || name[i] == ')')
		printf("minishell: syntax error near unexpected token '%c'\n",
			name[i]);
	else
		printf("export: not valid in this context: '%s'\n", name);
}
