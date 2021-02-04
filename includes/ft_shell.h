/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shell.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: frfrance <frfrance@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 15:03:31 by frfrance          #+#    #+#             */
/*   Updated: 2021/01/27 12:55:03 by frfrance         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SHELL_H
# define FT_SHELL_H

# include "../libft/libft.h"
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdbool.h>
# include <errno.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/wait.h>
# include <dirent.h>

# define PATH_MAX 4096
# define SHELL "minishell"
# define PARENT_ERR "can't access to parent directory"
# define SYNTAX_ERR "syntax error near unexpected token"
# define BUFFER_SIZE 100

/*
** 			-- main structure --
*/

typedef	struct		s_shell
{
	char			*buffer;
	char			**copyenv;
	int				erreur_pour_cote;
	char			*env_path;
	char			*bin;
	char			**path_split;
	char			*temp;
}					t_shell;

typedef	struct		s_strt
{
	char			**env;
	char			*str;
	int				input_s;
	int				output_s;
	int				ret;
	int				erreur_pour_cote;
}					t_strt;

/*
** 			-- variable global --
*/

pid_t				*g_pipe_pid;
char				*g_last;
int					g_return_valu;
int					g_error_bin;
int					g_error;
int					g_file;

/*
** 			-- parsing pipes --
*/

char				**parse_v2(char *str);
int					ft_prsg_pipe(char *str, t_strt *strt);
int					ft_nb_pipe(char *str, int o);
int					arg_pipe(t_strt *strt);

/*
**			-- parsing arg and var --
*/

char				**prsg_center(char *str, t_shell *data);
char				*parse_arg(char *str, t_shell *data);
void				free_handle_arg(char **str, int *i, int *nb_arg);
void				prsg_slash(char *str);
void				replace_g_last(char **last, char *last_arg);
char				*var_name_prsg(char *str);
char				*prsg_valu(char *str, t_shell *data);
char				*var_1(char *str, int index, t_shell *data);

/*
**				-- parsing util --
*/

int					ft_nb_cote(char *str, int option);
int					ft_nb_arg(char *str);
int					is_built_in(char *cmd);
int					handle_file_name_error(char *str);
int					is_correct(char *str, int i);
char				*check_validity(char *str, int i, t_shell *data);
char				*new_str_moove(char *str);

/*
** 				-- main pipes --
*/

int					ft_exec_pipe(char *str, t_shell *data);
void				ft_pipe_center(t_strt *strt, int **pipes, char *str,
									t_shell *data);
int					ft_create_pipes(t_strt *strt, int **pipes);
void				ft_co_pipes(t_strt *strt, int n_pipe, int **pipes);

/*
**				-- fd and int/out --
*/

void				ft_redirec_for_pipe(t_strt *strt);
void				fd_center(t_strt *strt);
int					get_fd(char *str, int option);

/*
**				-- execut --
*/

int					ft_func_name(char *str);
void				bin_center(t_shell *data, char **func);
pid_t				ft_pipes_exec(t_strt *strt, int **pipes, int size,
									t_shell *data);
void				no_pipe_exec(t_strt *strt, t_shell *data);
int					ft_exec_builtin(t_strt *strt, char **func, t_shell *data);

/*
**				-- execut util --
*/

pid_t				exit_exec1(char ***func, char ***env_var, pid_t pid);
void				fonction_cat_for_bin(t_shell *data, char **func, int i);
int					check_function(char **func, t_strt *strt);

/*
**				-- free init pipes --
*/

void				wait_pids(pid_t *pids, int size, t_strt *strt);
void				clean_pipes(int **pipes, int n_pipes);
int					free_clean_input(t_strt *strt, int **pipes, int nb_pipe);
t_strt				*init_array(char *str);
int					init_pipe(int nb_pipe, int ***pipes);
void				ft_close_pipes(int **pipes, int size);
void				clean_array(char **array);
int					check_closed(char *str);
void				free_last_v(char *str, t_shell *data);

/*
**				-- exec des bin --
*/

void				exec_vague(char **func, t_shell *data, int j);
void				exec_bin(char **func, t_shell *data);
char				*pwd_for_exec_bin(void);
void				free_chaine_three(char *str_1, char *str_2, char *str_3);
void				exec_point(char **func, t_shell *data);
void				exec_slash(char **func, t_shell *data);
void				path_error(char **func);

/*
** 				-- bulletin --
*/

int					ft_cmd_echo(char **str, char **env);
int					ft_cd(char **arg, char **env);
int					ft_pwd(char **pwd);
void				ft_export(char **cmd, t_shell *data);
void				ft_unset(char **cmd, t_shell *data);
int					env_size(char **list);
char				**ft_cd_path(char **env);
int					ft_exit(char **str, char **env);
void				ft_set_old_pwd(char **env);
void				ft_set_new_pwd(char **env);

/*
**				-- var et env --
*/

void				recupere_le_path(t_shell *data);
void				free_array(char **array);
char				*get_env(char **env, char *str);
char				*parse_var(char *str, t_shell *data);
void				ft_env_var(t_shell *data);
char				**ft_sort_matrice(char **env);
void				aff_var_env(char **env);
char				*ft_old_path(char **env);
void				ft_copy_tab2d(t_shell *data, char **original);
void				parse_dollar(char **buffer, char **env);
int					get_id(char *str);

/*
**				-- signaux --
*/

int					ctrl_d(void);
void				ctrl_c(int sig);
void				ctrl_slash_quit(int sig);
int					main_signal(void);

/*
**				-- fonction tiers --
*/

char				*ft_strnew(size_t size);
int					search_str(char *first, char **env);
int					ft_full_space(char *str);
int					gnl_ctrl_input(int fd, char **line, int *go, int option);
void				print_for_export(char **str, int i);
int					is_valide(char *str, int index, int option);
int					is_backslash(char *str, int index);
int					ft_search_str(char *str, char **env);
char				*ft_strnew(size_t size);
char				*ft_mystr(char *str_1, char *str_2, char c);
int					check_error(char **str, int count);
char				*ft_strcomb(char **split, char *sep);
void				print_home(void);

#endif
