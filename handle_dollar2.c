/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 12:53:33 by qacjl             #+#    #+#             */
/*   Updated: 2025/03/30 15:38:21 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int	g_exit_status;

static char	*expand_special_var(const char *in, int *i)
{
	if (in[*i + 1] == '?')
	{
		*i = *i + 2;
		return (ft_itoa(g_exit_status));
	}
	if (in[*i + 1] == '$')
	{
		*i = *i + 2;
		return (ft_itoa(my_getpid()));
	}
	return (NULL);
}

char	*expand_var(const char *in, int *i, char **env)
{
	int		j;
	char	*name;
	char	*val;
	char	*special;

	special = expand_special_var(in, i);
	if (special != NULL)
		return (special);
	j = *i + 1;
	while (in[j] && (ft_isalnum(in[j]) || in[j] == '_'))
		j = j + 1;
	if (j == *i + 1)
	{
		*i = *i + 1;
		return (ft_strdup("$"));
	}
	name = ft_strndup(in + *i + 1, j - *i - 1);
	*i = j;
	val = get_path_value(env, name);
	if (val == NULL)
		val = ft_strdup("");
	free(name);
	return (val);
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

char	*handle_dollar_case(const char *input, int *i, char **env)
{
	char	*temp;

	if (input[*i + 1] == '?' || input[*i + 1] == '$')
	{
		temp = expand_var(input, i, env);
		return (temp);
	}
	if (!input[*i + 1] || (!ft_isalnum(input[*i + 1]) && input[*i + 1] != '_'))
	{
		*i = *i + 1;
		return (ft_strdup("$"));
	}
	temp = expand_var(input, i, env);
	return (temp);
}

char	*do_expand_loop(const char *input, int *i, char *result, char **env)
{
	char	*temp;
	char	ch[2];
	int		state;

	state = 0;
	while (input[*i])
	{
		if (input[*i] == '$' && state != 1)
		{
			temp = handle_dollar_case(input, i, env);
			result = append_str(result, temp);
			free(temp);
			continue ;
		}
		check_state(*i, &state, input);
		ch[0] = input[*i];
		ch[1] = '\0';
		result = append_str(result, ch);
		*i = *i + 1;
	}
	return (result);
}
