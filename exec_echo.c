/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_echo.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 18:05:39 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/14 14:37:51 by quenalla         ###   ########.fr       */
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
	int	i;

	i = 1;
	while (prompt->strs[i])
	{
		if (ft_strcmp(prompt->strs[i], ">") == 0
			|| ft_strcmp(prompt->strs[i], ">>") == 0)
			break ;
		if (ft_strcmp(prompt->strs[i], "|") == 0)
			break ;
		ft_printf("%s", prompt->strs[i]);
		if (prompt->strs[i + 1] && ft_strcmp(prompt->strs[i + 1], ">") != 0
			&& ft_strcmp(prompt->strs[i + 1], ">>") != 0)
			ft_printf(" ");
		i++;
	}
	if (!(prompt->strs[1] && ft_strcmp(prompt->strs[1], "-n") == 0))
		ft_printf("\n");
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
