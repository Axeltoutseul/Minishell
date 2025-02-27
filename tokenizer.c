/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 20:49:34 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/27 15:25:34 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*void	tokenizer(char *prompt, t_token **lst)
{
	int	i;

	i = 0;
	while (prompt[i])
	{
		if (is_redirect(prompt[i]))
			redirect_manager(prompt, &i, lst);
		if (is_pipe(prompt[i]))
			pipe_manager(prompt, &i, lst);
		if (is_word(prompt[i]))
			word_manager(prompt, &i, lst);
		if (is_separator(prompt[i]))
			i++;
	}
}*/

char	*cpy_word(char *str, int *i)
{
	int		len;
	int		j;
	char	*dup;

	j = 0;
	len = cpy_word_len(str + *i);
	dup = malloc(sizeof(char) * (len + 1));
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '\"')
			if (cpy_double_quote(dup, str, i, &j))
				return (free(dup), 1);
		if (str[*i] == '\'')
			if (cpy_single_quote(dup, str, i, &j))
				return (free(dup), 2);
		else
			dup[j++] = str[(*i)++];
	}
	if (str[*i] == '\"')
		dup[j++] = str[(*i)++];
	else
		return (1);
	return (0);
}

int	is_redirect(char c)
{
	if (c == '>' || c == '<')
		return (1);
	return (0);
}
