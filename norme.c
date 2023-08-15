/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:40:18 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/15 18:03:17 by acaplat          ###   ########.fr       */
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

int parse_export(char **tab,int i)
{

    if(tab[i][0] != '-' || ft_isdigit(tab[i][0]) == 1)
    {
        printf("%c\n",tab[i][0]);
        printf("ft_is_digit-->%d\n",ft_isdigit(tab[i][0]));
        printf("minishell: export: `%s': not a valid identifier\n",tab[i]);
        return(0);
    }
    return(1);
}

