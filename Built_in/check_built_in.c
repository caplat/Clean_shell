/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:58:47 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/01 16:26:14 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void check_built_in(t_mini *shell)
{
	export(shell);
	print_env(shell);
	unset(shell);
	pwd(shell);
	cd(shell);
}