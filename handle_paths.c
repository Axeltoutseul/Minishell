/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:07:10 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/05 17:14:10 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_shell *shell, t_prompt *prompt)
{
    char    buffer[PATH_MAX];

	if (chdir(prompt->strs[1]) != 0)
		ft_putstr_fd("cd command failed\n", 2);
	else
	{
		getcwd(buffer, PATH_MAX);
        free(shell->folder_path);
		shell->folder_path = ft_strdup(buffer);
        //ft_printf("getenv = %s\n", getenv("PWD"));
	}
}

/*void exec_cd(t_shell *shell, t_prompt *prompt)
{
    char buffer[PATH_MAX];

    if (chdir(prompt->strs[1]) == 0) {
        getcwd(buffer, sizeof(buffer));
        shell->folder_path = ft_strdup(buffer);
    } else {
        perror("cd");
    }
}*/
