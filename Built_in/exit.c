/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/04 14:41:57 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/07 11:18:06 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void ft_exit(t_mini *shell)
// {
// 	if(ft_strncmp(shell->args->str,"exit",4) == 0)
// 	{
// 		builtin_exit(&shell->args->str);
// 	}
// }


// void print_exit(void)
// {
// 	int fd;
// 	fd = open("/dev/stdin", O_WRONLY, 0777);
// 	ft_putendl_fd("exit ", fd);
// 	close(fd);
// }



// void builtin_exit(t_mini *shell)
// {	
// 	char **compare;
// 	compare = ft_split(shell->args->str, ' ');

// 	 if(ft_strncmp(compare[0], "exit", 5) == 0)
// 	{
// 		print_exit();
		
// 	}	
// 	else if(ft_strncmp(compare[0], "exit", 4) == 0 && (ft_isnum(compare[1]) == 1))
// 	{
// 		print_exit();
		
// 	}
// 	else if(ft_strncmp(compare[0], "exit", 5) == 0 && compare[1] && compare[2])
// 	{
// 		print_exit();
// 		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
// 	}
// 	else
// 	{
// 		print_exit();
// 		ft_putstr_fd("minishell: exit:", STDERR_FILENO);
// 		ft_putstr_fd(compare[1], STDERR_FILENO);
// 		ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
// 	}
// 	free(compare);
// }


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

void ft_exit(t_mini *shell)
{
	t_lex *current;

	current = shell->args;
	while(current)
	{
		shell->tab = ft_split(current->str,' ');
		if(ft_strncmp(shell->tab[0],"exit",5) == 0)
			exec_exit(shell->tab,shell);
		free_arr(shell->tab);
		shell->tab = NULL;
		current = current->next;
	}
}

void exec_exit(char **tab,t_mini *shell)
{
	int i;

	i = 0;
	if(find_length(tab) == 1)
	{
		shell->exit_code = 0;
		exit(0);
	}
	if(find_length(tab) > 2)
	{
		printf("exit: too many arguments\n");
		shell->exit_code = 1;
		exit(shell->exit_code);
	}
	if(ft_is_digit_str(tab[1]) == 0 || (long long)ft_atoi(tab[1]) > __LONG_MAX__)
	{
		printf("minishell: exit: %s: numeric argument required\n",tab[1]);
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

int ft_is_digit_str(const char *str)
{
    int i = 0;

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



