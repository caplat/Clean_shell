/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:41:57 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/21 11:51:26 by derblang         ###   ########.fr       */
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
	int	num;
	int	flag;

	flag = 0;
	printf("exit\n");
	if (find_length(tab) == 1)
		exit(0);
	else
	{
		num = ft_atol(tab[1], &flag);
		if (flag)
			norme_exit(tab, shell);
	}
	if (find_length(tab) > 2 && ft_is_digit_str(tab[1]) == 1)
	{
		printf("minishell: exit: too many arguments\n");
		shell->exit_code = 1;
	}
	else
	{
		shell->exit_code = ft_atoi(tab[1]) % 256;
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

void	norme_exit(char **tab, t_mini *shell)
{
	ft_putstr_fd("minishell: exit: ", 2);
	ft_putstr_fd(tab[1], 2);
	ft_putstr_fd(": numeric argument required\n", 2);
	shell->exit_code = 255;
	exit(shell->exit_code);
}
