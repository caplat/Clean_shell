/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/08 15:59:02 by acaplat           #+#    #+#             */
/*   Updated: 2023/09/13 14:54:38 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(t_lex *simplecommand, t_mini *shell)
{
	t_here	var;

	var.current = simplecommand;
	var.del = NULL;
	var.fd = open(".heredoc", O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (var.fd == -1)
		norme_heredoc_bis();
	while (var.current)
	{
		var.next = var.current->next;
		check_flag_ter(var.current, shell);
		if (ft_strncmp(var.current->str, "<<", 3) == 0 && var.next
			&& shell->flag == 0)
		{
			var.del = ft_strdup(var.next->str);
			if (too_much(var.fd, var.del) == 1)
				break ;
			safe_free(&var.del);
			var.current = var.next->next;
		}
		else
			var.current = var.current->next;
	}
	safe_free(&var.del);
	close(var.fd);
}

int	too_much(int fd, char *del)
{
	char	*buffer;

	while (1)
	{
		buffer = readline(">");
		if (!buffer)
		{
			perror("readline error");
			too_much_bis(fd);
		}
		if (ft_strncmp(buffer, del, ft_strlen(del) + 1) == 0)
		{
			safe_free(&buffer);
			return (1);
		}
		if (write(fd, buffer, ft_strlen(buffer)) == -1)
		{
			perror("write error");
			safe_free(&buffer);
			too_much_bis(fd);
		}
		write(fd, "\n", 1);
		safe_free(&buffer);
	}
	return (0);
}

void	too_much_bis(int fd)
{
	close(fd);
	exit(1);
}

void	norme_heredoc_bis(void)
{
	perror("open error");
	exit(1);
}

void	erase(t_lex **simplecommand, t_mini *shell)
{
	t_lex	*current;
	t_lex	*previous;
	t_lex	*next;

	current = *simplecommand;
	previous = NULL;
	while (current)
	{
		next = current->next;
		check_flag_bis(current, shell);
		if (ft_strncmp(current->str, "<<", 3) == 0 && next && shell->flag == 0)
		{
			delete_node(simplecommand, current);
			delete_node(simplecommand, next);
			add_element_bis(simplecommand, ft_strdup(".heredoc"));
			current = *simplecommand;
			continue ;
		}
		else
			previous = current;
		current = next;
	}
}
