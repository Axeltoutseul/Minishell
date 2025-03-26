/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   adv_tokeniser3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: quenalla <quenalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:48:32 by quenalla          #+#    #+#             */
/*   Updated: 2025/03/26 15:51:26 by quenalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"minishell.h"

void	process_char(char c, t_state *state, char **curr)
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
