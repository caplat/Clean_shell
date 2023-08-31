/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fix_echo.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/17 16:29:39 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/31 17:00:41 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fix_echo(t_mini *shell)
{
	t_lex	*newlist;

	replace_char(shell->newline_bis, ' ', 31, shell);
	if (shell->newline_bis != NULL)
		newlist = echo_list(shell);
}

t_lex	*echo_list(t_mini *shell)
{
	int		i;
	char	*str;
	t_lex	*newlist;

	newlist = NULL;
	i = -1;
	str = ft_calloc(1, 1);
	while (shell->newline_bis[++i])
	{
		set_flag(shell->newline_bis, shell, i);
		str = add_char(str, shell->newline_bis[i]);
		if (shell->newline_bis[i + 1] == '|' && shell->flag == 0
			&& shell->newline_bis[i + 1])
		{
			add_element_bis(&newlist, ft_strdup(str));
			str = ft_calloc(1, 1);
			i++;
		}
	}
	add_element_bis(&newlist, ft_strdup(str));
	safe_free(&str);
	str = NULL;
	shell->echo_lst = newlist;
	return (newlist);
}
