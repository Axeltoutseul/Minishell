/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qacjl <qacjl@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:56 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/27 12:59:45 by qacjl            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

char	*append_str(char *dest, const char *src)
{
	size_t	size;
	size_t	i;
	size_t	j;
	char	*new_str;

	size = ft_strlen(dest) + ft_strlen(src);
	new_str = malloc(size + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (dest && dest[i])
	{
		new_str[i] = dest[i];
		i = i + 1;
	}
	while (src[j])
	{
		new_str[i + j] = src[j];
		j = j + 1;
	}
	new_str[i + j] = '\0';
	if (dest)
		free(dest);
	return (new_str);
}

char	*expand_variables(const char *input)
{
	int		i;
	int		state;
	char	*result;

	i = 0;
	state = 0;
	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	return (do_expand_loop(input, &i, &state, result));
}
