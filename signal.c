/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:07:48 by acaplat           #+#    #+#             */
/*   Updated: 2023/09/05 12:46:10 by acaplat          ###   ########.fr       */
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
}

void	handle_sigquit(int signal)
{
	(void)signal;
}

void	do_signal(t_mini *shell)
{
	if (signal(SIGINT, handle_sigint))
		shell->exit_code = 1;
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		printf("erreur SIGINT");
	if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
		printf("error SIGQUIT");
}
