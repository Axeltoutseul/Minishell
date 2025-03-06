/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:44 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/06 18:47:28 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	check_string(int *i, int *count, char c, char *str)
{
	(*i)++;
	(*count)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	if (str[*i] == c)
		(*count)++;
}

int	closed_quotes(char *cmd_line)
{
	int	i;
	int	quote_count;

	i = 0;
	quote_count = 0;
	while (cmd_line[i])
	{
		if (cmd_line[i] == '\'')
			check_string(&i, &quote_count, '\'', cmd_line);
		else if (cmd_line[i] == '"')
			check_string(&i, &quote_count, '"', cmd_line);
		if (cmd_line[i])
			i++;
	}
	if (quote_count % 2 == 1)
		return (0);
	return (1);
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
	if (count_occurs(arg, '='))
	{
		value = ft_strchr(arg, '=') + 1;
		if (!valid_value(value))
			return (0);
	}
	return (1);
}

int	valid_name(char *name)
{
	int	i;

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
	else if ((s[i] == '\'' || s[j] == '\'')
		&& count_occurs(s, '\'') % 2 == 1)
		return (0);
	else if ((s[i] == '"' || s[j] == '\'')
		&& count_occurs(s, '"') % 2 == 1)
		return (0);
	return (1);
}
