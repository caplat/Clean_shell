/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:36:57 by acaplat           #+#    #+#             */
/*   Updated: 2023/09/05 17:42:41 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	*shell;
	(void)argv;

	error_code = 0;
	if (argc != 1)
	{
		printf("retry without arguments\n");
		exit(0);
	}
	shell = malloc(sizeof(t_mini));
	initialize(env, shell);
	shell->env_cpy = do_export(shell);
	rl_catch_signals = 0;
	do_signal(shell);
	// printf("%d\n",shell->exit_code);
	minishell_loop(shell);
	// system("leaks ./minishell");
}

void	minishell_loop(t_mini *shell)
{
	while (1)
	{
		shell->line = readline(">>");
		// shell->exit_code = error_code;
		// printf("%d\n",shell->exit_code);
		if (shell->line)
		{
			if (ft_strlen(shell->line) > 0)
				add_history(shell->line);
			if (count_quotes(shell->line, shell) == 1)
			{
				norme_main(shell);
				if (get_nb_node(shell->args) == 1)
					check_built_in(shell);
				do_the_pipe(shell);
			}
			dup2(shell->stdout_cpy, STDOUT_FILENO);
			dup2(shell->stdin_cpy, STDIN_FILENO);
			shell->redir_input = 0;
		}
		else
		{
			free_shell(shell);
			exit(0);
		}
	}
}

void	norme_main(t_mini *shell)
{
	replace_line(shell->line, shell);
	shell->lst = get_my_list(shell);
	shell->lst_bis = get_my_list(shell);
	shell->newline_bis = convert_to_str(shell->lst_bis);
	if(shell->newline_bis != NULL)
		parse_newline_bis(shell, shell->newline_bis);
	// printf("%s\n",shell->newline_bis);
	fix_echo(shell);
	safe_free(&shell->add_char);
	shell->add_char = ft_calloc(1, 2);
	separate_command(shell->lst);
	shell->newline = convert_to_str(shell->lst);
	shell->simplecommand = get_my_element(shell);
	here_doc(shell->simplecommand, shell);
	erase(&shell->simplecommand, shell);
	redir(shell);
	shell->args = set_command(shell->simplecommand, shell);
	// printlist_bis(shell->args);
}

void	parse_newline_bis(t_mini *shell, char *str)
{
	int		i;
	char	*newstr;

	(void)shell;
	i = 0;
	newstr = ft_calloc(1, 2);
	while (str[i])
	{
		set_flag(str, shell, i);
		if (str[i] == ' ' && (str[i + 1] == '<' || str[i + 1] == '<')
			&& shell->flag == 0)
			i++;
		main_ter(shell, str, &i);
		newstr = add_char(newstr, str[i]);
		i++;
	}
	// printf("%zu\n",ft_strlen(newstr));
	// printf("newstr --> %s\n",newstr);
	safe_free(&shell->newline_bis);
	shell->newline_bis = newstr;
}

void	main_ter(t_mini *shell, char *str, int *i)
{
	if ((str[*i] == '<' || str[*i] == '>') && shell->flag == 0)
	{
		(*i)++;
		if (str[*i] == '<' || str[*i] == '>')
			(*i)++;
		if (str[*i] != ' ')
			while (str[*i] != ' ' && str[*i])
				(*i)++;
		else if (str[*i] == ' ')
		{
			while (str[*i] == ' ' && str[*i])
			{
				set_flag(str, shell, *i);
				(*i)++;
			}
			while (str[*i] != ' ' && str[*i])
			{
				set_flag(str, shell, *i);
				(*i)++;
			}
		}
	}
}
