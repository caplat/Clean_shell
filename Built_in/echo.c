/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: derblang <derblang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/01 16:33:42 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/21 12:08:40 by derblang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_n(char **compare)
{
	int	i;
	int	j;

	i = 0;
	while (compare[++i])
	{
		j = 0;
		if (compare[i][j++] == '-' && compare[i][j] && compare[i][j] == 'n')
		{
			while (compare[i][j] == 'n')
				j++;
			if (compare[i][j] && compare[i][j] != 'n')
				return (1);
		}
		else
			return (i);
	}
	return (i);
}

void	echo(char **compare, t_mini *shell)
{
	int	i;
	int	k;

	k = 0;
	i = check_n(compare);
	ft_exit_code(compare, shell);
	while (compare[i])
	{
		echo_norme(i, k, compare);
		printf(" ");
		i++;
		k = 0;
	}
	printf("\n");
}

void	exec_echo(t_mini *shell)
{
	t_lex	*current;

	current = shell->echo_lst;
	while (current)
	{
		shell->tab = ft_split(current->str, ' ');
		if (ft_strncmp(shell->tab[0], "echo", 5) == 0)
			echo(shell->tab, shell);
		free_arr(shell->tab);
		shell->tab = NULL;
		current = current->next;
	}
}

int	echo_help(char *compare, int k, char cote)
{
	int	i;
	int	j;

	i = 0;
	j = k;
	k++;
	while (compare[k] && compare[k] != cote)
	{
		printf("%c", compare[k]);
		k++;
	}
	k++;
	return (k - j);
}

void	echo_norme(int i, int k, char **compare)
{
	while (compare[i][k])
	{
		if (compare[i][k] == '\'')
		{	
			k += echo_help(compare[i], k, '\'');
			if (compare[i][k] == '\'')
				continue ;
		}
		if (compare[i][k] == '\"')
		{
			k += echo_help(compare[i], k, '\"');
			if (compare[i][k] == '\"')
				continue ;
		}
		printf("%c", compare[i][k]);
		k++;
	}
}
