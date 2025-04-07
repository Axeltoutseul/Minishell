/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_terminal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 15:09:19 by axbaudri          #+#    #+#             */
/*   Updated: 2025/03/30 21:15:57 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	*init_shell(char **envp)
{
	t_shell	*shell;

	shell = (t_shell *)malloc(sizeof(t_shell));
	if (!shell)
		return (NULL);
	shell->env_lines = NULL;
	copy_env(&shell->env_lines, envp);
	shell->export_lines = NULL;
	copy_export(&shell->export_lines, envp);
	shell->env = get_env_lines(shell->env_lines);
	shell->path = get_path_value(shell->env, "PATH");
	shell->home_path = get_path_value(shell->env, "HOME");
	shell->old_pwd = get_path_value(shell->env, "PWD");
	shell->pwd = get_path_value(shell->env, "PWD");
	shell->splitted_path = split_path(shell->path);
	shell->shlvl = get_shell_level(envp);
	shell->history = NULL;
	return (shell);
}

t_prompt	*init_prompt(const char *buffer, char **env)
{
	t_prompt	*prompt;
	char		*expanded;
	char		*preprocessed;

	prompt = malloc(sizeof(t_prompt));
	if (prompt == NULL)
		return (NULL);
	expanded = expand_variables(buffer, env);
	preprocessed = preprocess_line(expanded);
	prompt->cmd_line = ft_strdup(preprocessed);
	prompt->strs = advanced_tokenize(preprocessed);
	prompt->nb_args = count_strings(prompt->strs);
	free(expanded);
	free(preprocessed);
	return (prompt);
}

void	get_mini_env(t_env **env)
{
	t_env	*new;
	char	*pwd_line;
	char	buffer[1000];

	getcwd(buffer, PATH_MAX);
	pwd_line = ft_strjoin("PWD=", buffer);
	new = new_line(pwd_line);
	add_env_line(env, new);
	new = new_line("SHLVL=1");
	add_env_line(env, new);
	new = new_line("_=/usr/bin/env");
	add_env_line(env, new);
}

void	copy_env(t_env **env, char **envp)
{
	t_env	*new;
	int		i;

	i = 0;
	if (!envp[0])
		return (get_mini_env(env));
	while (envp[i])
	{
		new = new_line(envp[i]);
		add_env_line(env, new);
		i++;
	}
}

void	copy_export(t_env **export, char **envp)
{
	t_env	*new;
	int		i;

	i = 0;
	if (!envp[0])
		return (get_mini_env(export));
	sort_strings(envp, count_strings(envp));
	while (envp[i])
	{
		new = new_line(envp[i]);
		add_env_line(export, new);
		i++;
	}
}
