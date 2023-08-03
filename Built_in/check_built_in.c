/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:58:47 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/03 15:46:50 by derblang         ###   ########.fr       */
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
	exec_echo(shell);
}