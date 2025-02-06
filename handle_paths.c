/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:07:10 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/06 13:33:49 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_shell *shell, t_prompt *prompt)
{
	char	buffer[PATH_MAX];

	if (ft_strcmp(shell->old_pwd, shell->pwd) != 0)
	{
		free(shell->old_pwd);
		shell->old_pwd = shell->pwd;
	}
	if (chdir(prompt->strs[1]) != 0)
		ft_putstr_fd("cd command failed\n", 2);
	else
	{
		getcwd(buffer, PATH_MAX);
		free(shell->pwd);
		shell->pwd = ft_strdup(buffer);
	}
	update_paths(shell);
}

void	update_paths(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], "OLDPWD=", 8) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("OLDPWD=", shell->old_pwd);
		}
		else if (ft_strncmp(shell->env[i], "PWD=", 4) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strjoin("PWD=", shell->pwd);
		}
		i++;
	}
}

/*void exec_cd(t_shell *shell, t_prompt *prompt)
{
	char buffer[PATH_MAX];

	if (chdir(prompt->strs[1]) == 0) {
		getcwd(buffer, sizeof(buffer));
		shell->pwd = ft_strdup(buffer);
	} else {
		perror("cd");
	}
}*/
