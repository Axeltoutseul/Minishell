/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:05:39 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/27 17:39:41 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*char	**parse_echo(t_prompt *prompt)
{
	char	**strs;
	int		i;

	i = 0;
	while (prompt->echo[i] && prompt->echo[i] != '\'' && prompt->echo[i] != '"')
		i++;
	if (prompt->echo[i] == '\'')
		strs = ft_split(prompt->echo, '\'');
	else
		strs = ft_split(prompt->echo, '"');
	return (strs);
}*/

char	*exec_echo(char *cmd_line, char **strs)
{
	char	*echo;

	if (!count_quotes(cmd_line))
		echo = ft_strjoin2(count_words(cmd_line) - 2, strs + 2, " ");
	else if (count_quotes(cmd_line) % 2 == 1)
		echo = ft_strdup("Error\n");
	else
		echo = find_third_word(cmd_line);
	return (echo);
}

char	*join_strings(char **strs)
{
	char	*joined_str;

	joined_str = ft_strjoin2(count_strings(strs), strs, "");
	return (joined_str);
}

int	count_quotes(const char *cmd_line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd_line[i] != '\'' && cmd_line[i] != '"' && cmd_line[i])
		i++;
	if (cmd_line[i] == '\'')
		count = count_occurs(cmd_line, '\'');
	else if (cmd_line[i] == '"')
		count = count_occurs(cmd_line, '"');
	return (count);
}
