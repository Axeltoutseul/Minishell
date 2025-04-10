/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:42:33 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/28 11:49:22 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redirect_file(const char *target, int std_fd, int flags, int mode)
{
	int	fd;

	fd = open(target, flags, mode);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	if (dup2(fd, std_fd) == -1)
	{
		perror("dup2");
		close(fd);
		return (-1);
	}
	close(fd);
	return (0);
}

int	apply_redirections(char **tokens)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	return (process_redirections_loop(tokens, i, ret));
}

int	apply_command_redirections(t_command *cmd)
{
	t_redir	*redir;
	int		ret;

	redir = reverse_redir_list(cmd->redirections);
	ret = 0;
	while (redir)
	{
		if (ft_strcmp(redir->op, ">") == 0)
			ret = redirect_file(redir->target, STDOUT_FILENO,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strcmp(redir->op, ">>") == 0)
			ret = redirect_file(redir->target, STDOUT_FILENO,
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		else if (ft_strcmp(redir->op, "<") == 0)
			ret = redirect_file(redir->target, STDIN_FILENO, O_RDONLY, 0);
		if (ret == -1)
			return (-1);
		redir = redir->next;
	}
	return (0);
}

static void	free_redirections(t_redir *redir)
{
	t_redir	*tmp;

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
				free(pipeline->commands[i].args[j++]);
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
