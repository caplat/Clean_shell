/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:32:59 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/24 18:05:37 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void print_env(t_mini *shell)
{
	int i;

	i = 0;
		while(shell->env[i])
			printf("%s\n",shell->env[i++]);
}

void env_cpy(t_mini *shell)
{
	int i;

	i = 0;
	shell->env_cpy = malloc(sizeof(char *) * (find_length(shell->env) + 1));
	while(shell->env[i])
	{
		shell->env_cpy[i] = ft_strdup(shell->env[i]);
		i++;
	}
	shell->env_cpy[i] = NULL;
}