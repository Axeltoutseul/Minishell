/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:26:57 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/13 17:24:04 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}

/*void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list *tmp;

	if (!lst || !del)
		return ;
	tmp = lst->next->next;
	del(&lst->next->content);
	free(lst->next);
	lst->next = tmp;
}*/
