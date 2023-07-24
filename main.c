/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:36:57 by acaplat           #+#    #+#             */
/*   Updated: 2023/07/24 18:08:51 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc,char **argv,char **env)
{
	t_mini *shell;
	(void)argv;

	if (argc != 1)
	{
		printf("retry without arguments\n");
		exit(0);
	}
	shell = malloc(sizeof(t_mini));
	initialize(env,shell);
	shell->env_cpy = do_export(shell);
	print_tab(shell->env_cpy);
	// rl_catch_signals = 0;
	do_signal();
	minishell_loop(shell);
}
void minishell_loop(t_mini *shell)
{
	while(1)
	{
		shell->line = readline(">>");
		if(shell->line)
		{
			if(ft_strlen(shell->line) > 0)
				add_history(shell->line);
			if(count_quotes(shell->line,shell) == 1)
			{
				replace_line(shell->line,shell);
				shell->lst = get_my_list(shell);
				safe_free(&shell->add_char);
				shell->add_char = ft_calloc(1,2);
				separate_command(shell->lst);
				shell->newline = convert_to_str(shell->lst);
				shell->simplecommand = get_my_element(shell);
				parse_redir(shell->simplecommand,shell);
				remove_redir(shell->simplecommand);
				printf("\n\n");
				shell->args = set_command(shell->simplecommand,shell);
				// print_tab(shell->env_cpy);
			}
		}
		else
		{
			printf("allo\n");
			free_shell(shell);
			exit(0);
		}
	}
}
