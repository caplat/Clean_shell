/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acaplat <acaplat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 12:50:26 by acaplat           #+#    #+#             */
/*   Updated: 2023/08/01 16:38:40 by acaplat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <fcntl.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <termios.h>
# include <unistd.h>
# include <readline/history.h>
# include <readline/readline.h>

typedef struct s_elem
{
	char			data;
	struct s_elem	*next;
	struct s_elem	*prev;
}					t_elem;

typedef struct s_lex
{
	char			*str;
	struct s_lex	*next;
	struct s_lex	*prev;
}					t_lex;

typedef struct s_mini
{
	char			*line;
	char			*newline;
	char			**env;
	int				flag;
	char			**command;
	int				length_command;
	char			*add_char;
	t_elem			*lst;
	char			**simple_command;
	t_lex			*simplecommand;
	t_lex			*redir;
	t_lex			*args;
	char			**env_cpy;
	char			**tab;
}					t_mini;

typedef struct s_compteur
{
	int				i;
	int				j;
	int				length;
}					t_compteur;

//Main

void				minishell_loop(t_mini *shell);

//Utils

void				initialize(char **env, t_mini *shell);
char				*add_char(char *str, char c);
int					find_length(char **str);
void				print_tab(char **tab);

//Signal

void				handle_SIGINT(int signal);
void				handle_SIGQUIT(int signal);
void				do_signal(void);

//Parsing

int					count_quotes(char *line, t_mini *shell);
int					find_matching_quote(char *line, int i, int *nb_del,
						int del);
t_elem				*get_my_list(t_mini *shell);
void				separate_command(t_elem *lst);
t_elem				*get_my_list(t_mini *shell);

//Dollar

void				replace_line(char *line, t_mini *shell);
void				set_flag(char *line, t_mini *shell, int i);
char				*compare_line(char *line, int i);
int					compare_with_env(char *compare, t_mini *shell);

//Linked_list

void				add_element(t_elem **head, char data);
void				printlist(t_elem *head);
t_elem				*create_elem(char data);
void				insert_after(t_elem *lst, char newdata);
void				processlist(t_elem *head, char targetchar, char newdata);

//Linked_list_bis1

void				processlist_chevron(t_elem *head, char targetchar,
						char newdata);
char				*convert_to_str(t_elem *head);
void				delete_node(t_lex **head, t_lex *node_to_del);

//Free

void				free_shell(t_mini *shell);
void				free_arr(char **arr);
void				free_list(t_elem *head);
void				free_list_bis(t_lex *head);
void				safe_free(char **str);

//Lex

void				add_element_bis(t_lex **head, char *simple_command);
void				printlist_bis(t_lex *head);
t_lex				*get_my_element(t_mini *shell);
t_lex				*set_command(t_lex *head, t_mini *shell);
int					check_flag_bis(t_lex *current, int flag);

// Parse_redir

void				parse_redir(t_lex *simplecommand, t_mini *shell);
void				remove_redir(t_lex **simplecommand);

// BUILT-IN

// Env

void				print_env(t_mini *shell);
void				env_cpy(t_mini *shell);

// Export

void				sort_tab(char **tab);
void				swap_strings(char **str1, char **str2);
int					compare_length(char *str1, char *str2);
void				declare_x(char **env_cpy);
void				insert_char(char **str, char c, int pos);

//Export_bis

int					find_character(char *str, char c);
void				add_quotes(char **env_cpy);
char				**do_export(t_mini *shell);
void				add_var_export(char *str, t_mini *shell);
void				export(t_mini *shell);

//Add_var_export

void				add_str_to_tab(char ***tab, char *str);
void				remove_str_from_tab(char ***tab, int position);
int					check_dup(char **tab, char *compare);
int					check_dup_env(char **tab, char *compare);
void				add_var_env(char *str, t_mini *shell);

// Unset

void				unset(t_mini *shell);

//Cd

void				change_env(char *cwd, t_mini *shell);
void				change_directory(char *dir, t_mini *shell);
void				too_much_line(char **dir, char **path, char **cwd);
void				cd(t_mini *shell);

//Pwd

void				pwd(t_mini *shell);

//Echo

int					check_n(char **compare);
void				echo(char **compare);
int					cote(char c, int flag);
void				echo_bis(char **compare, int i, int k, int flag_bis);

//Check_built_in

void				check_built_in(t_mini *shell);

#endif