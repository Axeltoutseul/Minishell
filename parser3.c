/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:25:12 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/26 15:51:41 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

static int	count_non_hd_tokens(char **tokens)
{
	int	index;
	int	count;

	index = 0;
	count = 0;
	while (tokens[index])
	{
		if (ft_strcmp(tokens[index], "<<") == 0)
			index = index + 2;
		else
		{
			count = count + 1;
			index = index + 1;
		}
	}
	return (count);
}

static char	**dup_non_hd_tokens(char **tokens, char **heredoc, int count)
{
	int		index;
	int		pos;
	char	**new_tokens;

	index = 0;
	pos = 0;
	new_tokens = malloc(sizeof(char *) * (count + 1));
	if (new_tokens == NULL)
		return (NULL);
	while (tokens[index])
	{
		if (ft_strcmp(tokens[index], "<<") == 0)
		{
			*heredoc = ft_strdup(tokens[index + 1]);
			index = index + 2;
		}
		else
		{
			new_tokens[pos] = ft_strdup(tokens[index]);
			pos = pos + 1;
			index = index + 1;
		}
	}
	new_tokens[pos] = NULL;
	return (new_tokens);
}

char	**remove_hd_tokens(char **tokens, char **heredoc)
{
	int		non_hd_count;
	char	**new_tokens;

	non_hd_count = count_non_hd_tokens(tokens);
	new_tokens = dup_non_hd_tokens(tokens, heredoc, non_hd_count);
	free_2d_array(tokens);
	return (new_tokens);
}

char	**extract_redirections(char **tokens, t_redirection **redir)
{
	int		non_redir_count;
	char	**new_tokens;

	non_redir_count = count_non_redir_tokens(tokens);
	if (non_redir_count == -1)
	{
		ft_printf("bash: syntax error near unexpected token `newline'\n");
		free_2d_array(tokens);
		return (NULL);
	}
	new_tokens = build_new_tokens(tokens, redir, non_redir_count);
	free_2d_array(tokens);
	return (new_tokens);
}
