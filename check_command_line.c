/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:49 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/25 18:57:08 by axbaudri         ###   ########.fr       */
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

int	valid_name(char *arg)
{
	int	i;

	i = 0;
	if (!(isalpha(arg[i]) || arg[i] == '_'
		|| arg[i] == '$' || arg[i] == '<' || arg[i] == '>'))
		return (0);
	i++;
	while (arg[i] && arg[i] != '=')
	{
		if (!(isalnum(arg[i]) || arg[i] == '_'
			|| arg[i] == '$' || arg[i] == '<' || arg[i] == '>'))
			return (0);
		i++;
	}
	return (1);
}

int	valid_value(char *s)
{
	int	i;
	int	j;

	i = 0;
	j = ft_strlen(s) - 1;
	if ((s[i] == '\'' && s[j] == '"') || (s[i] == '\'' && s[j] == '"')
		|| count_occurrences(s, '\'') % 2 == 1
		|| count_occurrences(s, '"') % 2 == 1)
	{
		printf("minishell: unexpected newline while looking for matching '%c'",
			s[0]);
		return (0);
	}
	return (1);
}

void	check_error(char *name)
{
	int	i;

	i = 0;
	while (name[i] && name[i] != '&' && name[i] != '(' && name[i] != ')')
		i++;
	if (name[i] == '&' || name[i] == '(' || name[i] == ')')
		ft_printf("minishell: syntax error near unexpected token '%c'\n",
			name[i]);
	else
		ft_printf("export: not valid in this context: '%s'\n", name);
}
