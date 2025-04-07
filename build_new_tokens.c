/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_new_tokens.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:51:41 by qacjl             #+#    #+#             */
/*   Updated: 2025/04/01 15:07:52 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_token_build_new_tokens(t_build_ctx *ctx)
{
	char	*temp;
	t_redir	*new_redir;

	temp = ft_strdup(ctx->tokens[ctx->i]);
	if (!temp)
		return (-1);
	if (ft_strcmp(temp, ">") == 0 || ft_strcmp(temp, ">>") == 0
		|| ft_strcmp(temp, "<") == 0)
	{
		free(temp);
		if (!ctx->tokens[ctx->i + 1])
			return (-1);
		new_redir = create_redirection_token(ctx->tokens, &ctx->i);
		if (!new_redir)
			return (-1);
		new_redir->next = *(ctx->redir);
		*(ctx->redir) = new_redir;
		return (0);
	}
	ctx->new_tokens[ctx->j] = ft_strdup(temp);
	free(temp);
	ctx->j++;
	ctx->i++;
	return (0);
}

char	**build_new_tokens(char **tokens, t_redir **redir, int size)
{
	t_build_ctx	ctx;
	char		**new_tokens;

	new_tokens = malloc(sizeof(char *) * (size + 1));
	if (!new_tokens)
		return (NULL);
	ctx.tokens = tokens;
	ctx.i = 0;
	ctx.j = 0;
	ctx.new_tokens = new_tokens;
	ctx.redir = redir;
	while (tokens[ctx.i])
	{
		if (handle_token_build_new_tokens(&ctx) == -1)
		{
			free_2d_array(new_tokens);
			return (NULL);
		}
	}
	new_tokens[ctx.j] = NULL;
	return (new_tokens);
}
