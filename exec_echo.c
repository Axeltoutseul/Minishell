/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:05:39 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/28 12:54:35 by axbaudri         ###   ########.fr       */
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

void	exec_echo(t_prompt *prompt)
{
	prompt->echo = ft_strjoin2(prompt->nb_args - 2, prompt->strs + 2, " ");
	ft_printf("%s", prompt->echo);
	free(prompt->echo);
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
