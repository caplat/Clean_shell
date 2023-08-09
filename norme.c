/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norme.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/09 12:40:18 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/09 17:34:42 by acaplat          ###   ########.fr       */
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

void	norme_pipe_ter()
{
	perror("fork error\n");
	return ;
}

void norme_pipe_4()
{
	perror("pipe error\n");
	return ;
}

