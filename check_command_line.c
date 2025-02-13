/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_command_line.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 12:43:49 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/13 19:53:00 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_quotes(const char *cmd_line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (cmd_line[i] != '\'' && cmd_line[i] != '"' && cmd_line[i])
		i++;
	if (cmd_line[i] == '\'')
		count = count_occurrences(cmd_line, '\'');
	else if (cmd_line[i] == '"')
		count = count_occurrences(cmd_line, '"');
	return (count);
}

int	check_path_validity(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == -1 || !ft_strlen(ft_strrchr(cmd, '/') + 1))
		return (0);
	return (1);
}

int	existing_command(char **paths, char *cmd)
{
	int		i;
	int		result;
	char	*cmd_path;

	i = 0;
	if (!cmd)
		return (0);
	if (ft_strchr(cmd, '/'))
		return (check_path_validity(cmd));
	while (paths[i])
	{
		cmd_path = ft_strjoin(paths[i], cmd);
		if (!cmd_path)
			return (0);
		result = access(cmd_path, F_OK | X_OK);
		free(cmd_path);
		if (result == 0)
			return (1);
		i++;
	}
	return (0);
}

void	exec_unset(t_shell *shell, t_prompt *prompt)
{
	int	i;

	i = 1;
	while (prompt->strs[i])
		remove_line(shell, prompt->strs[i++]);
}

/*void	remove_line(t_shell *shell, char *var)
{
	int	i;
	int	j;
	int	size;

	i = 0;
	j = 0;
	while (shell->var_names[i]
		&& ft_strcmp(shell->var_names[i], var) != 0)
		i++;
	if (shell->var_names[i])
	{
		size = ft_strlen(shell->var_names[i]);
		while (ft_strncmp(shell->var_names[i], shell->export[j], size) != 0)
			j++;
		if (ft_strcmp(shell->var_names[i], "_") != 0)
		{
			shell->env[i][0] = 0;
			shell->export[j][0] = 0;
		}
	}
}*/

void	remove_line(t_shell *shell, char *var)
{
	int		i;
	int		size;
	t_list	*temp;

	i = 0;
	temp = shell->export_lines;
	while (shell->var_names[i]
		&& ft_strcmp(shell->var_names[i], var) != 0)
		i++;
	if (shell->var_names[i] && ft_strcmp(shell->var_names[i], "_") != 0)
	{
		size = ft_strlen(shell->var_names[i]);
		while (ft_strncmp(shell->var_names[i], temp->content, size) != 0)
			temp = temp->next;
		ft_printf("temp->content = %s\n", temp->content);
	}
}

/*static void	find_var_name(char *name, t_env **env)
{
	t_env	*curr;
	t_env	*tmp;

	curr = *env;
	if (curr && !ft_strcmp(curr->name, name))
	{
		*env = curr->next;
		free(curr->name);
		free(curr->value);
		free(curr);
		return ;
	}
	while (curr)
	{
		if (curr->next && !ft_strcmp(curr->next->name, name))
		{
			tmp = curr->next;
			curr->next = curr->next->next;
			free(tmp->name);
			free(tmp->value);
			free(tmp);
			return ;
		}
		curr = curr->next;
	}
}*/
