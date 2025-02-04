/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_paths.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: axbaudri <axbaudri@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 18:07:10 by axbaudri          #+#    #+#             */
/*   Updated: 2025/02/04 19:35:27 by axbaudri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    exec_cd(char *path)
{
    if (chdir(path) != 0)
       ft_putstr_fd("cd command failed\n", 2);
    else if (!ft_strlen(path))
        getenv("HOME");
    else
        getenv("PWD");
}
