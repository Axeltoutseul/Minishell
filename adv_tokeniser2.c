/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_tokeniser2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 13:15:42 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/26 15:49:25 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenize_loop(const char *line, t_tokenize_context *ctx)
{
	while (line[ctx->i] != '\0')
	{
		process_char(line[ctx->i], &ctx->state, &ctx->curr);
		if (ctx->state == STATE_DEFAULT
			&& (line[ctx->i] == ' ' || line[ctx->i] == '\t'))
		{
			if (ctx->curr)
			{
				ctx->tokens[ctx->ti] = ctx->curr;
				ctx->ti = ctx->ti + 1;
				ctx->curr = NULL;
			}
		}
		ctx->i = ctx->i + 1;
	}
}

void	process_redirection(const char *line, int *i, int *j, char *new_line)
{
	if (*i > 0)
	{
		if (line[*i - 1] != ' ')
		{
			new_line[*j] = ' ';
			*j = *j + 1;
		}
	}
	new_line[*j] = line[*i];
	*j = *j + 1;
	if (line[*i + 1] != '\0')
	{
		if (line[*i + 1] == line[*i])
			new_line[*j++] = line[++*i];
	}
	if (line[*i + 1] != '\0')
	{
		if (line[*i + 1] != ' ')
		{
			new_line[*j] = ' ';
			*j = *j + 1;
		}
	}
}

char	*preprocess_line(const char *line)
{
	int		i;
	int		j;
	int		len;
	char	*new_line;

	i = 0;
	j = 0;
	len = ft_strlen(line);
	new_line = malloc(sizeof(char) * ((len * 3) + 1));
	if (new_line == NULL)
		return (NULL);
	while (line[i] != '\0')
	{
		if (line[i] == '>' || line[i] == '<')
			process_redirection(line, &i, &j, new_line);
		else
		{
			new_line[j] = line[i];
			j = j + 1;
		}
		i++;
	}
	new_line[j] = '\0';
	return (new_line);
}

char	**advanced_tokenize_modified(const char *line)
{
	char	*preprocessed;
	char	**tokens;

	preprocessed = preprocess_line(line);
	if (!preprocessed)
		return (NULL);
	tokens = advanced_tokenize(preprocessed);
	free(preprocessed);
	return (tokens);
}

char	**advanced_tokenize(const char *line)
{
	t_tokenize_context	ctx;

	ctx.i = 0;
	ctx.ti = 0;
	ctx.curr = NULL;
	ctx.state = STATE_DEFAULT;
	ctx.tokens = malloc(sizeof(char *) * (ft_strlen(line) + 1));
	if (!ctx.tokens)
		return (NULL);
	tokenize_loop(line, &ctx);
	if (ctx.curr)
	{
		ctx.tokens[ctx.ti] = ctx.curr;
		ctx.ti = ctx.ti + 1;
	}
	ctx.tokens[ctx.ti] = NULL;
	return (ctx.tokens);
}
