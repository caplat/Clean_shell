/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:07:48 by acaplat           #+#    #+#             */
/*   Updated: 2023/09/18 17:18:55 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int signal)
{
	(void)signal;
	if (!(waitpid(-1, NULL, WNOHANG) > 0))
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_error_code = 1;
	}
	else if ((waitpid(-1, NULL, WNOHANG) > 0))
	{
		printf("\n");
		g_error_code = 130;
	}
}

void	handle_sigquit(int signal)
{
	(void)signal;
	g_error_code = 127;
}

void	do_signal(t_mini *shell)
{
	(void)shell;
	if (signal(SIGINT, handle_sigint) == SIG_ERR)
		printf("erreur SIGINT");
	if (signal(SIGQUIT, handle_sigquit) == SIG_ERR)
		printf("error SIGQUIT");
}
