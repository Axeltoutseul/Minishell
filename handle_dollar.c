/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 14:36:56 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/24 15:11:45 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status;

static char	*append_str(char *dest, const char *src)
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
	while (in[j] && (ft_isalnum(in[j]) || in[j] == '_'))
		j = j + 1;
	name = ft_strndup(in + *i + 1, j - *i - 1);
	val = getenv(name);
	if (val == NULL)
		val = "";
	free(name);
	*i = j;
	return (ft_strdup(val));
}

void	check_state(int i, int *state, const char *input)
{
	if (input[i] == '\'' && *state == 0)
		*state = 1;
	else if (input[i] == '\'' && *state == 1)
		*state = 0;
	else if (input[i] == '"' && *state == 0)
		*state = 2;
	else if (input[i] == '"' && *state == 2)
		*state = 0;
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
	while (input[i])
	{
		if (input[i] == '$' && state != 1)
		{
			temp = expand_var(input, &i);
			result = append_str(result, temp);
			free(temp);
			continue ;
		}
		check_state(i, &state, input);
		ch[0] = input[i];
		ch[1] = '\0';
		result = append_str(result, ch);
		i = i + 1;
	}
	return (result);
}
