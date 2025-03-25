/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_terminal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:06:58 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/25 05:01:33 by qacjl            ###   ########.fr       */
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
	if (prompt)
	{
		free(prompt->cmd_line);
		free_2d_array(prompt->strs);
		free(prompt);
	}
}

void	free_terminal(t_shell *shell)
{
	free(shell->path);
	free(shell->home_path);
	free(shell->pwd);
	free(shell->old_pwd);
	free_2d_array(shell->env);
	free_2d_array(shell->splitted_path);
	free_env_lines(shell->env_lines);
	free_env_lines(shell->export_lines);
	ft_lstclear(&shell->history, &free);
	rl_clear_history();
	free(shell);
}

void	free_new_and_temp(t_env *new, t_env *temp)
{
	free(new->name);
	free(new->value);
	free(new);
	free(temp->name);
	free(temp->value);
	free(temp);
}

static void	free_redirections(t_redirection *redir)
{
	t_redirection	*tmp;

	while (redir)
	{
		tmp = redir->next;
		free(redir->op);
		free(redir->target);
		free(redir);
		redir = tmp;
	}
}

void	free_pipeline(t_pipeline *pipeline)
{
	int	i;
	int	j;

	if (pipeline == NULL)
		return ;
	i = 0;
	while (i < pipeline->count)
	{
		if (pipeline->commands[i].args)
		{
			j = 0;
			while (pipeline->commands[i].args[j])
			{
				free(pipeline->commands[i].args[j]);
				j++;
			}
			free(pipeline->commands[i].args);
		}
		if (pipeline->commands[i].heredoc_delim)
			free(pipeline->commands[i].heredoc_delim);
		if (pipeline->commands[i].redirections)
			free_redirections(pipeline->commands[i].redirections);
		i++;
	}
	free(pipeline->commands);
	free(pipeline);
}
