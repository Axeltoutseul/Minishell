/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:06:58 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/11 18:30:30 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_array(char **strs)
{
	int	i;

	i = 0;
	if (!strs)
		return ;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	free_prompt(t_prompt *prompt)
{
	free(prompt->cmd_line);
	free_2d_array(prompt->strs);
}

void	free_terminal(t_shell *shell)
{
	free(shell->path);
	free(shell->pwd);
	free(shell->old_pwd);
	free_2d_array(shell->splitted_path);
	free_2d_array(shell->env);
	free_2d_array(shell->export);
	free_2d_array(shell->var_names);
	ft_lstclear(&shell->env_lines, &free);
	free(shell);
}
