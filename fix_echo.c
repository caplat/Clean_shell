/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:29:39 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/17 17:58:14 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fix_echo(t_mini *shell)
{
	shell->tab_bis = ft_split(shell->newline_bis,'|');
	printf("tab_bis-->");
	print_tab(shell->tab_bis);
} 

