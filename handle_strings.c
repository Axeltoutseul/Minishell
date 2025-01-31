/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_strings.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 15:55:41 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/31 13:58:28 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_swap(char **s1, char **s2)
{
	char	*tmp;

	tmp = *s1;
	*s1 = *s2;
	*s2 = tmp;
}

void	sort_strings(char **envp, int size)
{
	int		i;
	char	*tmp;

	i = 0;
	while (i < size - 1)
	{
		if (ft_strcmp(envp[i], envp[i + 1]) > 0)
		{
			tmp = envp[i];
			envp[i] = envp[i + 1];
			envp[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	write_sorted_strings(char **strs)
{
	int	i;

	i = 0;
	sort_strings(strs, count_strings(strs));
	while (strs[i])
		ft_printf("%s\n", strs[i++]);
}

char	*exec_echo(char *command_line)
{
	char	*echo;

	echo = ft_strtrim(command_line, ("\""));
	return (echo);
}
