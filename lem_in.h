/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 16:49:54 by bgres             #+#    #+#             */
/*   Updated: 2018/02/23 16:49:57 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libftprintf/ft_printf.h"

typedef	struct		s_links
{
	struct s_rooms	*room;
	struct s_links	*next;
}					t_links;
typedef	struct		s_rooms
{
	char			*name;
	int				x;
	int				y;
	unsigned char	strt_end;
	struct s_links	*links;
	struct s_rooms	*next;
	struct s_rooms	*prvs;
	int				len_to_end;
	int				blocl;
	int				ant_n;
}					t_rooms;
typedef	struct		s_ht
{
	struct s_rooms	*room;
	struct s_ht		*next;
}					t_ht;
unsigned long		g_i;
unsigned long		g_j;
t_ht				**g_ht;
t_rooms				*g_start;
t_rooms				*g_end;
int					g_ants;
int					g_nl_ret;
int					get_ant(void);
void				ant_error(char *line);
void				room_error(t_rooms *tmp, t_rooms **last, char *error_txt);
void				strt_end_error(char *line);
int					count_a(char *line, char a);
void				a_t_l(char *line, t_rooms **last, t_rooms *tmp);
t_rooms				*room_assign(int fgl, int j, char *line, t_rooms **last);
int					a_r_srt_end(int fgl, t_rooms *tmp, char *a, t_rooms **last);
void				skip(char **line);
char				*check_one(char **line, t_rooms **tmp, int fgl, int *j);
void				skip_dig(char **line, int *j);
int					check_space(char *line, t_rooms *tmp, t_rooms **last);
int					add_room(int fgl, char *line, t_rooms **last);
int					get_room(t_rooms **last, char **line);
t_rooms				*chek_name(t_rooms *tail, char *tmp);
void				add_link(t_rooms *a, t_rooms *b, int flg);
void				make_ht(t_rooms *last);
size_t				hash_f(char *s);
t_rooms				*get_from_ht(char *tmp, char **line);
void				skip_two(int *i, int *j, t_rooms **last, char **line);
void				f_one(char **line, int k);
int					check_link(char **line);
int					get_links(char **line, t_rooms **last, int k);
void				link_error(char **line, char *txt);
void				get_way(t_rooms *tmp, int i, int *j);
void				error_for_alg(char **line);
void				ft_algoritm(char **line);
void				turn_assign(t_rooms **tmp, t_rooms **tmp2,
								t_links **tmpl, t_rooms **ant);
void				turn_out(t_rooms **tmp2, t_rooms **ant, int i);
void				turn(int i, t_rooms **ant);
void				push_ants_v2(void);
#endif
