/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipeline.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:11:01 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/26 16:43:55 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_state(char c, int state)
{
	if (c == '\'' && state != 2)
	{
		if (state == 1)
			return (0);
		return (1);
	}
	if (c == '\"' && state != 1)
	{
		if (state == 2)
			return (0);
		return (2);
	}
	return (state);
}

static void	process_char_for_split(const char *line, t_split_context *ctx)
{
	if (line[ctx->i] == '\'' || line[ctx->i] == '\"')
	{
		ctx->state = update_state(line[ctx->i], ctx->state);
	}
	else if (line[ctx->i] == '|' && ctx->state == 0)
	{
		ctx->segments[ctx->count] = ft_strndup(line + ctx->start, ctx->i - ctx->start);
		ctx->count = ctx->count + 1;
		ctx->start = ctx->i + 1;
	}
	ctx->i = ctx->i + 1;
}

static int	count_segments(const char *line)
{
	int		i;
	int		count;
	int		state;

	i = 0;
	count = 0;
	state = 0;
	while (line[i])
	{
		if (line[i] == '\'' || line[i] == '\"')
			state = update_state(line[i], state);
		else if (line[i] == '|' && state == 0)
			count = count + 1;
		i = i + 1;
	}
	return (count);
}

static char	**fill_segments(const char *line, int seg_count)
{
	t_split_context	ctx;
	char			**segments;

	segments = malloc(sizeof(char *) * (seg_count + 2));
	if (segments == NULL)
		return (NULL);
	ctx.i = 0;
	ctx.start = 0;
	ctx.count = 0;
	ctx.state = 0;
	ctx.segments = segments;
	while (line[ctx.i])
	{
		process_char_for_split(line, &ctx);
	}
	ctx.segments[ctx.count] = ft_strdup(line + ctx.start);
	ctx.segments[ctx.count + 1] = NULL;
	return (segments);
}

char	**split_pipeline(const char *line)
{
	int		seg_count;
	char	**segments;

	seg_count = count_segments(line);
	segments = fill_segments(line, seg_count);
	return (segments);
}
