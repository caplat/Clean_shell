/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:44:47 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/16 17:10:20 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_redir(t_mini *shell)
{
	t_lex	*current;
	t_lex	*next;
	char	*redir;

	current = shell->simplecommand;
	redir = NULL;
	while (current)
	{
		next = current->next;
		check_flag_ter(current,shell);
		if (ft_strncmp(current->str, ">>", 2) == 0 && next && shell->flag == 0)
		{
			redir = ft_strdup(next->str);
			delete_node(&shell->simplecommand, current);
			current = next;
			delete_node(&shell->simplecommand, current);
			redir_output_append(redir);
			free(redir);
			redir = NULL;
		}
		current = current->next;
	}
	if (redir != NULL)
		free(redir);
}

void	do_redir_output(t_mini *shell)
{
	t_lex	*current;
	t_lex	*next;
	char	*redir;

	current = shell->simplecommand;
	redir = NULL;
	while (current)
	{
		next = current->next;
		check_flag_ter(current,shell);
		if (ft_strncmp(current->str, ">", 1) == 0 && next && shell->flag == 0)
		{
			redir = ft_strdup(next->str);
			delete_node(&shell->simplecommand, current);
			current = next;
			delete_node(&shell->simplecommand, current);
			redir_output(redir);
			free(redir);
			redir = NULL;
		}
		current = current->next;
	}
	if (redir != NULL)
		free(redir);
}

void	do_redir_input(t_mini *shell)
{
	t_lex	*current;
	t_lex	*next;
	char	*redir;

	{
		current = shell->simplecommand;
		redir = NULL;
		while (current)
		{
			next = current->next;
			check_flag_ter(current,shell);
			// printf("shell->flag %d\n",shell->flag);
			if (ft_strncmp(current->str, "<", 1) == 0 && next && shell->flag == 0)
			{
				redir = ft_strdup(next->str);
				delete_node(&shell->simplecommand, current);
				current = next;
				delete_node(&shell->simplecommand, current);
				redir_input(redir, shell);
				free(redir);
				redir = NULL;
			}
			current = current->next;
		}
		norme_parse_redir(redir);
	}
}

void	redir(t_mini *shell)
{
	
	do_redir(shell);
	do_redir_output(shell);
	do_redir_input(shell);
}

void	norme_parse_redir(char *redir)
{
	if (redir != NULL)
		free(redir);
}
