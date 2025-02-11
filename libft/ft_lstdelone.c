/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:26:57 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/11 18:18:23 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	t_list	*temp;

	if (lst)
	{
		temp = lst->next;
		del(lst->content);
		free(lst);
		lst = temp;
	}
}*/

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
