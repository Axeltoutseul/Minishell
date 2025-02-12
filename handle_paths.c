/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:07:10 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/12 18:22:29 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec_cd(t_shell *shell, t_prompt *prompt)
{
	char	buffer[PATH_MAX];

	if (chdir(prompt->strs[1]) != 0)
		ft_printf("cd: no such file or directory: %s\n", prompt->strs[1]);
	else
	{
		if (ft_strcmp(shell->old_pwd, shell->pwd) != 0)
		{
			free(shell->old_pwd);
			shell->old_pwd = ft_strdup(shell->pwd);
		}
		getcwd(buffer, PATH_MAX);
		free(shell->pwd);
		shell->pwd = ft_strdup(buffer);
	}
	update_paths(shell, shell->env_lines);
	update_paths_export(shell, shell->export_lines);
}

void	update_paths(t_shell *shell, t_list *lst)
{
	t_list	*temp;

	temp = lst;
	while (temp)
	{
		if (ft_strncmp(temp->content, "OLDPWD=", 7) == 0)
		{
			free(temp->content);
			temp->content = ft_strjoin("OLDPWD=", shell->old_pwd);
		}
		else if (ft_strncmp(temp->content, "PWD=", 4) == 0)
		{
			free(temp->content);
			temp->content = ft_strjoin("PWD=", shell->pwd);
		}
		temp = temp->next;
	}
}

void	update_paths_export(t_shell *shell, t_list *lst)
{
	t_list	*temp;
	char	*line;

	temp = lst;
	line = NULL;
	while (temp)
	{
		if (ft_strncmp(temp->content, "OLDPWD=", 7) == 0)
		{
			free(temp->content);
			line = ft_strjoin("OLDPWD=", shell->old_pwd);
			temp->content = copy_line_with_quotes(line);
			free(line);
		}
		else if (ft_strncmp(temp->content, "PWD=", 4) == 0)
		{
			free(temp->content);
			line = ft_strjoin("PWD=", shell->pwd);
			temp->content = copy_line_with_quotes(line);
			free(line);
		}
		temp = temp->next;
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
