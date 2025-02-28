/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/27 16:26:06 by qacjl             #+#    #+#             */
/*   Updated: 2025/02/28 16:01:33 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_exit_status;

static char	*append_str(char *dest, const char *src)
{
	size_t	len_dest;
	size_t	len_src;
	size_t	i;
	size_t	j;
	char	*new_str;

	len_dest = ft_strlen(dest);
	len_src = ft_strlen(src);
	new_str = malloc(len_dest + len_src + 1);
	if (new_str == NULL)
		return (NULL);
	i = 0;
	while (dest != NULL && dest[i] != '\0')
	{
		new_str[i] = dest[i];
		i = i + 1;
	}
	j = 0;
	while (src[j] != '\0')
	{
		new_str[i + j] = src[j];
		j = j + 1;
	}
	new_str[i + j] = '\0';
	if (dest != NULL)
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
	while (input[j] != '\0')
	{
		if ((input[j] >= 'A' && input[j] <= 'Z')
			|| (input[j] >= 'a' && input[j] <= 'z')
			|| (input[j] >= '0' && input[j] <= '9')
			|| (input[j] == '_'))
			j = j + 1;
		else
			break ;
	}
	var_name = ft_strndup(input + *i + 1, j - *i - 1);
	value = getenv(var_name);
	if (value == NULL)
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
	if (result == NULL)
		return (NULL);
	while (input[i] != '\0')
	{
		if (input[i] == '$')
		{
			temp = expand_var(input, &i);
			result = append_str(result, temp);
			free(temp);
		}
		else
		{
			ch[0] = input[i];
			ch[1] = '\0';
			result = append_str(result, ch);
			i = i + 1;
		}
	}
	return (result);
}
