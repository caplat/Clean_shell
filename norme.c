/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:40:18 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/10 17:49:19 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	norme_export(void)
{
	perror("Memory alloc failed\n");
	return ;
}

void	norme_lex(t_lex **newlist, char *test)
{
	add_element_bis(newlist, ft_strdup(test));
	free(test);
}

int error_child(pid_t child_pid)
{
    if(child_pid == -1)
    {    
        perror("fork error\n");
        return(0);
    }
    return(1);
}

