/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_built_in.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 11:58:47 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/29 14:33:09 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	check_built_in(t_mini *shell)
{
	export(shell);
	cd(shell);
	unset(shell);
	print_env(shell);
	pwd(shell);
	exec_echo(shell);
	ft_exit(shell);
}

int	verif_built_in(t_mini *shell)
{
	if (ft_strncmp("export", shell->arg_bis[0], 7) == 0 || ft_strncmp("cd",
			shell->arg_bis[0], 3) == 0 || ft_strncmp("echo", shell->arg_bis[0],
			5) == 0 || ft_strncmp("pwd", shell->arg_bis[0], 4) == 0
		|| ft_strncmp("unset", shell->arg_bis[0], 6) == 0 || ft_strncmp("env",
			shell->arg_bis[0], 4) == 0 || ft_strncmp("exit", shell->arg_bis[0],
			5) == 0)
		return (1);
	else
		return (0);
}

void	norme_export_bis(t_mini *shell, char *cpy)
{
	free_arr(shell->tab);
	cpy = NULL;
	shell->tab = NULL;
}
