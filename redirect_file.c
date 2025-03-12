/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/17 02:42:33 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/12 15:22:22 by quenalla         ###   ########.fr       */
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
void	apply_redirections(t_command *cmd)
{
	int		i;
	int		j;
	char	**new_args;
	char	*op;
	char	*target;

	i = 0;
	j = 0;
	new_args = malloc(sizeof(char *) * (count_strings(cmd->args) + 1));
	if (new_args == NULL)
		exit(EXIT_FAILURE);
	while (cmd->args[i])
	{
		if (ft_strcmp(cmd->args[i], ">") == 0
			|| ft_strcmp(cmd->args[i], ">>") == 0
			|| ft_strcmp(cmd->args[i], "<") == 0)
		{
			op = cmd->args[i];
			if (cmd->args[i + 1] == NULL)
				break ;
			target = cmd->args[i + 1];
			adv_handle_redirect(target, op,
				(ft_strcmp(op, "<") == 0) ? STDIN_FILENO : STDOUT_FILENO);
			i = i + 2;
		}
		else
		{
			new_args[j] = ft_strdup(cmd->args[i]);
			j = j + 1;
			i = i + 1;
		}
	}
	new_args[j] = NULL;
	free_2d_array(cmd->args);
	cmd->args = new_args;
}
