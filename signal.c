/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:07:48 by acaplat           #+#    #+#             */
/*   Updated: 2023/09/05 17:41:54 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signal)
{
	(void)signal;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	error_code = 1;
}

void	handle_sigquit(int signal)
{
	(void)signal;
	error_code = 127;
}

void	do_signal(t_mini *shell)
{
	(void)shell;
	
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		printf("erreur SIGINT");
	if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
		printf("error SIGQUIT");
}
