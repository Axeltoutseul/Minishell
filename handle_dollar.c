/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:56 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/11 15:38:22 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static char	*append_str(char *dest, const char *src)
{
	size_t	ld;
	size_t	ls;
	size_t	i;
	size_t	j;
	char	*new_str;

	ld = ft_strlen(dest);
	ls = ft_strlen(src);
	new_str = malloc(ld + ls + 1);
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

static char	*expand_var(const char *in, int *i)
{
	int		j;
	char	*name;
	char	*val;

	if (in[*i + 1] == '?')
	{
		*i = *i + 2;
		return (ft_itoa(g_exit_status));
	}
	if (in[*i + 1] == '$')
	{
		*i = *i + 2;
		return (ft_itoa(getpid()));
	}
	j = *i + 1;
	while (in[j] && ((in[j] >= 'A' && in[j] <= 'Z')
			|| (in[j] >= 'a' && in[j] <= 'z')
			|| (in[j] >= '0' && in[j] <= '9') || in[j] == '_'))
		j = j + 1;
	name = ft_strndup(in + *i + 1, j - *i - 1);
	val = getenv(name);
	if (val == NULL)
		val = "";
	free(name);
	*i = j;
	return (ft_strdup(val));
}

char	*expand_variables(const char *input)
{
	int		i;
	int		state;
	char	*result;
	char	*temp;
	char	ch[2];

	i = 0;
	state = 0;
	result = ft_strdup("");
	if (result == NULL)
		return (NULL);
	while (input[i])
	{
		if (input[i] == '$' && state != 1)
		{
			temp = expand_var(input, &i);
			result = append_str(result, temp);
			free(temp);
			continue ;
		}
		if (input[i] == '\'' && state == 0)
			state = 1;
		else if (input[i] == '\'' && state == 1)
			state = 0;
		else if (input[i] == '"' && state == 0)
			state = 2;
		else if (input[i] == '"' && state == 2)
			state = 0;
		ch[0] = input[i];
		ch[1] = '\0';
		result = append_str(result, ch);
		i = i + 1;
	}
	return (result);
}
