/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_code.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/06 16:55:42 by acaplat           #+#    #+#             */
/*   Updated: 2023/09/05 17:39:25 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit_code(char **tab, t_mini *shell)
{
	int		i;
	char	*exit_code_str;
	(void)shell;

	i = -1;
	while (tab[++i])
	{
		if (ft_strncmp(tab[i], "$?", 2) == 0)
		{
			// exit_code_str = ft_itoa(shell->exit_code);
			exit_code_str = ft_itoa(error_code);
			if (exit_code_str != NULL)
			{
				free(tab[i]);
				// tab[i] = ft_strdup(ft_itoa(shell->exit_code));
				tab[i] = ft_strdup(ft_itoa(error_code));
				free(exit_code_str);
			}
		}
	}
}
