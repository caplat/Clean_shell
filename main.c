/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:36:57 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/21 14:07:22 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_mini	*shell;

	(void)argv;
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
	minishell_loop(shell);
}

void	minishell_loop(t_mini *shell)
{
	while (1)
	{
		shell->line = readline(">>");
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
}
