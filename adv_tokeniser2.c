/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_tokeniser2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:15:49 by qacjl             #+#    #+#             */
/*   Updated: 2025/02/28 14:23:46 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_char(char c, t_state *state, char **curr)
{
	if (*state == STATE_DEFAULT)
	{
		process_default(c, state, curr);
		return ;
	}
	if (*state == STATE_IN_SINGLE)
	{
		process_in_single(c, state, curr);
		return ;
	}
	if (*state == STATE_IN_DOUBLE)
	{
		process_in_double(c, state, curr);
		return ;
	}
	if (*state == STATE_ESCAPING)
	{
		process_escaping(c, state, curr);
		return ;
	}
}

static void	tokenize_loop(const char *line, t_tokenize_context *ctx)
{
	while (line[ctx->i] != '\0')
	{
		process_char(line[ctx->i], &ctx->state, &ctx->curr);
		if (ctx->state == STATE_DEFAULT
			&& (line[ctx->i] == ' ' || line[ctx->i] == '\t'))
		{
			if (ctx->curr != NULL)
			{
				ctx->tokens[ctx->ti] = ctx->curr;
				ctx->ti = ctx->ti + 1;
				ctx->curr = NULL;
			}
		}
		ctx->i = ctx->i + 1;
	}
}

char	**advanced_tokenize(const char *line)
{
	t_tokenize_context	ctx;

	ctx.i = 0;
	ctx.ti = 0;
	ctx.curr = NULL;
	ctx.state = STATE_DEFAULT;
	ctx.tokens = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (ctx.tokens == NULL)
		return (NULL);
	tokenize_loop(line, &ctx);
	if (ctx.curr != NULL)
	{
		ctx.tokens[ctx.ti] = ctx.curr;
		ctx.ti = ctx.ti + 1;
	}
	ctx.tokens[ctx.ti] = NULL;
	return (ctx.tokens);
}
