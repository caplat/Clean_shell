/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 13:07:48 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/21 13:08:47 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_SIGINT(int signal)
{
	(void)signal;

	printf("\n");
	rl_on_new_line(); 
    rl_replace_line("", 0); 
    rl_redisplay();
}

void handle_SIGQUIT(int signal)
{
	(void)signal;
}
void do_signal()
{
	if(signal(SIGINT,handle_SIGINT) == SIG_ERR)
		printf("erreur SIGINT");
	if(signal(SIGQUIT,handle_SIGQUIT) == SIG_ERR)
		printf("error SIGQUIT");
}