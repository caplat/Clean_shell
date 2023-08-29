/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 16:32:59 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/29 14:35:36 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_env(t_mini *shell)
{
	t_lex	*current;

	current = shell->args;
	while (current)
	{
		shell->tab = ft_split(current->str, ' ');
		if (ft_strncmp(shell->tab[0], "env", 4) == 0)
			print_tab(shell->env);
		free_arr(shell->tab);
		shell->tab = NULL;
		current = current->next;
	}
}

void	env_cpy(t_mini *shell)
{
	int	i;

	i = 0;
	shell->env_cpy = malloc(sizeof(char *) * (find_length(shell->env) + 1));
	while (shell->env[i])
	{
		shell->env_cpy[i] = ft_strdup(shell->env[i]);
		i++;
	}
	shell->env_cpy[i] = NULL;
}

void	shlvl(t_mini *shell)
{
	int		i;
	char	*shlvl;
	char	*level;

	level = NULL;
	shlvl = NULL;
	level = getenv("SHLVL");
	i = ft_atoi(level);
	i++;
	level = ft_itoa(i);
	shlvl = ft_strjoin("SHLVL=", level);
	add_var_env(shlvl, shell);
	add_var_export(shlvl, shell);
	free(shlvl);
	free(level);
}
