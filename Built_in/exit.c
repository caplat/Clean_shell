/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:41:57 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/04 14:47:16 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_exit(t_mini *shell)
{
	if(ft_strncmp(shell->args->str,"exit",4) == 0)
	{
		builtin_exit(&shell->args->str);
	}
}


void print_exit(void)
{
	int fd;
	fd = open("/dev/stdin", O_WRONLY, 0777);
	ft_putendl_fd("exit ", fd);
	close(fd);
}



void builtin_exit(t_mini *shell)
{	
	char **compare;
	compare = ft_split(shell->args->str, ' ');

	 if(ft_strncmp(compare[0], "exit", 5) == 0)
	{
		print_exit();
		
	}	
	else if(ft_strncmp(compare[0], "exit", 4) == 0 && (ft_isnum(compare[1]) == 1))
	{
		print_exit();
		
	}
	else if(ft_strncmp(compare[0], "exit", 5) == 0 && compare[1] && compare[2])
	{
		print_exit();
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
	}
	else
	{
		print_exit();
		ft_putstr_fd("minishell: exit:", STDERR_FILENO);
		ft_putstr_fd(compare[1], STDERR_FILENO);
		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
	}
	free(compare);
}


// int	is_full_digit(char *str)
// {
// 	while (*str)
// 	{
// 		if (!ft_isdigit(*str))
// 			return (0);
// 		str++;
// 	}
// 	return (1);
// }

// int	command_exit(char **arg)
// {
// 	int	i;

// 	i = -1;
// 	printf("exit\n");
// 	while (arg[++i])
// 	{
		
// 		if (i > 1)
// 		{
			
// 			if (is_full_digit(arg[1]) == 0)
// 			{
// 				printf("exit: %s: numeric argument required", arg[1]);
// 				exit(255);
// 			}
// 			else if (i > 2)
// 				exit(ft_atoi(arg[1]));
// 			else
// 			{
// 				printf("exit: too many arguments\n");
// 				return (1);
// 			}
// 		}
// 		else
// 			exit(0);
// 	}
// 		return (0);
// }