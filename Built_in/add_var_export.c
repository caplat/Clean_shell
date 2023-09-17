/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_var_export.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 18:15:06 by acaplat           #+#    #+#             */
/*   Updated: 2023/09/17 16:29:50 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// void	add_str_to_tab(char ***tab, char *str)
// {
// 	int		length;
// 	char	**newtab;
// 	int		i;

// 	length = find_length(*tab);
// 	newtab = malloc(sizeof(char *) * (length + 2));
// 	if (!newtab)
// 	{
// 		perror("erreur allocation memoire");
// 		return ;
// 	}
// 	i = -1;
// 	while (++i < length)
// 	{
// 		newtab[i] = ft_strdup((*tab)[i]);
// 		// safe_free((tab)[i]);
// 	}
// 	newtab[length] = ft_strdup(str);
// 	newtab[length + 1] = NULL;
// 	// safe_free(*tab);
// 	*tab = newtab;
// }

char	**add_str_to_tab(t_mini *shell,char **tab, char *str)
{
	int		length;
	char	**newtab;
	int		i;

	length = find_length(tab);
	newtab = ft_calloc((length + 2), sizeof(char *));
	i = 0;
	while (i < length)
	{
		newtab[i] = ft_strjoin(tab[i], "");
		i++;
	}
	newtab[i] = ft_strjoin(str, "");
	if(tab != shell->env)
		free_arr(tab);
	return (newtab);
}

// void	remove_str_from_tab(char ***tab, int position)
// {
// 	int		length;
// 	char	**newtab;
// 	int		i;
// 	int		j;

// 	i = -1;
// 	j = 0;
// 	length = find_length(*tab);
// 	newtab = malloc(sizeof(char *) * (length + 1));
// 	if (!newtab)
// 		return ;
// 	while (++i < length)
// 	{
// 		if (i != position)
// 		{
// 			newtab[j] = ft_strdup((*tab)[i]);
// 			j++;
// 		}
// 		// else
// 		// 	free((*tab)[i]);
// 	}
// 	// free((*tab));
// 	newtab[j] = NULL;
// 	*tab = newtab;
// }

void	remove_str_from_tab(t_mini *shell,char ***tab, int position)
{
	int		length;
	char	**newtab;
	int		i;
	int		j;

	i = -1;
	j = 0;
	length = find_length(*tab);
	newtab = malloc(sizeof(char *) * (length + 1));
	if (!newtab)
		return ;
	while (++i < length)
	{
		if (i != position)
		{
			newtab[j] = ((*tab)[i]);
			j++;
		}
		else if((*tab != shell->env))
			free((*tab)[i]);
	}
	if(*tab != shell->env)
		free((*tab));
	newtab[j] = NULL;
	*tab = newtab;
}

int	check_dup(char **tab, char *compare)
{
	int	i;
	int	result;
	int	pos;

	i = 0;
	pos = find_character(compare, '=');
	while (tab[i])
	{
		if (pos != -1)
			result = ft_strncmp(tab[i] + 11, compare, pos);
		else
			result = ft_strncmp(tab[i] + 11, compare, ft_strlen(compare));
		if (result == 0)
			return (i);
		i++;
	}
	return (-1);
}

int	check_dup_env(char **tab, char *compare)
{
	int	i;
	int	pos;

	i = -1;
	while (tab[++i])
	{
		pos = find_character(tab[i], '=');
		if (pos == -1)
			return (-2);
		if (ft_strncmp(tab[i], compare, pos) == 0)
			return (i);
	}
	return (-1);
}

void	add_var_env(char *str, t_mini *shell)
{
	int	res;

	if (find_character(str, '=') != -1)
	{
		res = check_dup_env(shell->env, str);
		if (res == -2)
			return ;
		if (res != -1)
		{
			remove_str_from_tab(shell,&shell->env, res);
		}
		shell->env = add_str_to_tab(shell,shell->env, str);
	}
}
