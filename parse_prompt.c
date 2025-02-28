/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_prompt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 19:54:44 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/28 14:38:34 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	valid_prompt(char *cmd_line)
{
	int	i;
	int	s_quote_count;
	int	d_quote_count;

	i = 0;
	s_quote_count = count_occurs(cmd_line, '\'');
	d_quote_count = count_occurs(cmd_line, '"');
	if (s_quote_count % 2 == 1 || d_quote_count % 2 == 1)
		return (0);
	while (cmd_line[i])
	{
		if (count_occurs2(cmd_line, "||"))
			ft_printf("syntax error");
	}
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
	else if ((count_occurs(s, '"') % 2 == 1 && !count_occurs(s, '\''))
		|| (count_occurs(s, '\'') % 2 == 1 && !count_occurs(s, '"')))
		return (0);
	return (1);
}
