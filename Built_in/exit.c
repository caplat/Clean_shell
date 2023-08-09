/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:41:57 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/09 12:31:04 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_exit(t_mini *shell)
{
	t_lex	*current;

	current = shell->args;
	while (current)
	{
		shell->tab = ft_split(current->str, ' ');
		if (ft_strncmp(shell->tab[0], "exit", 5) == 0)
			exec_exit(shell->tab, shell);
		free_arr(shell->tab);
		shell->tab = NULL;
		current = current->next;
	}
}

void	exec_exit(char **tab, t_mini *shell)
{
	int	i;

	i = 0;
	if (find_length(tab) == 1)
	{
		shell->exit_code = 0;
		exit(0);
	}
	if (find_length(tab) > 2)
		norme_exit(shell);
	if (ft_is_digit_str(tab[1]) == 0
		|| (long long)ft_atoi(tab[1]) > __LONG_MAX__)
	{
		printf("minishell: exit: %s: numeric argument required\n", tab[1]);
		shell->exit_code = 255;
		exit(shell->exit_code);
	}
	else
	{
		shell->exit_code = ft_atoi(tab[1]) % 256;
		printf("exit\n");
		exit(ft_atoi(tab[1]) % 256);
	}
}

int	ft_is_digit_str(const char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i])
	{
		if (!isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

void	norme_exit(t_mini *shell)
{
	printf("exit: too many arguments\n");
	shell->exit_code = 1;
	exit(shell->exit_code);
}
