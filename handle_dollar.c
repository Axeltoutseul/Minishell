/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:56 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/08 15:21:31 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static char	*append_str(char *dest, const char *src)
{
	int		i;
	int		j;
	char	*new_str;

	new_str = malloc(ft_strlen(dest) + ft_strlen(src) + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (dest && dest[i])
	{
		new_str[i] = dest[i];
		i = i + 1;
	}
	j = 0;
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

static char	*expand_var(const char *input, int *i)
{
	int		j;
	char	*var_name;
	char	*value;

	if (input[*i + 1] == '?')
	{
		*i = *i + 2;
		return (ft_itoa(g_exit_status));
	}
	j = *i + 1;
	while (input[j]
		&& ((input[j] >= 'A' && input[j] <= 'Z')
			|| (input[j] >= 'a' && input[j] <= 'z')
			|| (input[j] >= '0' && input[j] <= '9')
			|| input[j] == '_'))
	{
		j = j + 1;
	}
	var_name = ft_strndup(input + *i + 1, j - *i - 1);
	value = getenv(var_name);
	if (!value)
		value = "";
	free(var_name);
	*i = j;
	return (ft_strdup(value));
}

char	*expand_variables(const char *input)
{
	int		i;
	char	*result;
	char	*temp;
	char	ch[2];

	i = 0;
	result = ft_strdup("");
	if (!result)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$')
		{
			temp = expand_var(input, &i);
			result = append_str(result, temp);
			free(temp);
		}
		else
		{
			ch[0] = input[i++];
			ch[1] = '\0';
			result = append_str(result, ch);
		}
	}
	return (result);
}
