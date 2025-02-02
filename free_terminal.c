/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:06:58 by axbaudri          #+#    #+#             */
/*   Updated: 2025/01/31 16:06:39 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_2d_array(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
		free(strs[i++]);
	free(strs);
}

void	free_terminal(t_shell *shell)
{
	free(shell->path);
	free(shell->folder_path);
	free(shell->echo);
	free_2d_array(shell->splitted_path);
	free_2d_array(shell->export);
	free(shell);
}
