/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:22:16 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/27 13:55:00 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*create_redirection_op(char *token)
{
	return (ft_strtrim(token, " \t"));
}

t_redirection	*create_redirection_token(char **tokens, int *i)
{
	char			*temp;
	t_redirection	*new_redir;

	temp = ft_strtrim(tokens[*i + 1], " \t");
	if (!temp)
		return (NULL);
	if (temp[0] == '\0')
		return (free(temp), NULL);
	new_redir = malloc(sizeof(t_redirection));
	if (!new_redir)
		return (free(temp), NULL);
	new_redir->op = create_redirection_op(tokens[*i]);
	if (!new_redir->op)
	{
		free(new_redir);
		free(temp);
		return (NULL);
	}
	new_redir->target = ft_strdup(temp);
	free(temp);
	new_redir->next = NULL;
	*i = *i + 2;
	return (new_redir);
}

int	count_tokens_without_hd(char **tokens)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			if (tokens[i + 1] == NULL)
				return (-1);
			i = i + 2;
		}
		else
		{
			count++;
			i++;
		}
	}
	return (count);
}

int	process_hd_token(char **tokens, int *i, char **heredoc)
{
	if (tokens[*i + 1] == NULL)
	{
		ft_printf("bash: unexpected error: missing heredoc delimiter\n");
		return (-1);
	}
	*heredoc = ft_strdup(tokens[*i + 1]);
	*i = *i + 2;
	return (0);
}

char	**build_tokens_without_hd(char **tokens, char **heredoc, int new_count)
{
	int		i;
	int		j;
	char	**new_tokens;

	i = 0;
	j = 0;
	new_tokens = malloc(sizeof(char *) * (new_count + 1));
	if (new_tokens == NULL)
		return (NULL);
	while (tokens[i])
	{
		if (ft_strcmp(tokens[i], "<<") == 0)
		{
			if (process_hd_token(tokens, &i, heredoc) == -1)
			{
				free_2d_array(new_tokens);
				return (NULL);
			}
		}
		else
			new_tokens[j++] = ft_strdup(tokens[i++]);
	}
	new_tokens[j] = NULL;
	return (new_tokens);
}
