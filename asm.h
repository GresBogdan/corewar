/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 12:45:08 by bgres             #+#    #+#             */
/*   Updated: 2018/05/09 12:45:09 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_H
# define ASM_H

# include "libftprintf/ft_printf.h"


int		g_line;
int		g_error;
int		g_cmnd_i;
int		g_cmnd_len;
#define LIVE "live"
#define LD "ld"
#define ST "st"
#define ADD "add"
#define SUB "sub"
#define AND "and"
#define OR "or"
#define XOR "xor"
#define ZJMP "zjmp"
#define LDI "ldi"
#define STI "sti"
#define FORK "fork"
#define LLD "lld"
#define LLDI "lldi"
#define LFORK "lfork"
#define AFF "aff"
# define PROG_NAME_LENGTH		(128)
# define COMMENT_LENGTH			(2048)
# define COREWAR_EXEC_MAGIC		0xea83f3
# define LABEL_CHARS				"abcdefghijklmnopqrstuvwxyz_0123456789"
typedef	struct		s_main
{
	unsigned char	flag; /* flag & 1 = .name; flag & 2 = .comment*/
	char			*name;
	char			*comment;
}					t_main;

typedef struct		s_arg_lbl
{
	char			*mas[3];
}					t_arg_lbl;

typedef struct		s_comand
{
	char			*name;
	unsigned char	op;
	unsigned char	op_est;
	char			lz;
	char			count;
	int				cmnd_l;
	unsigned int	args; /* args[0] & 0xff binary_code last & 0xff00 binary_code second &0xff0000 first. 0x00 = no, 0x01 = T_DIR, 0x02 = T_IND, 0x03 = T_REG, 0x12 = T_DIR | T_IND, 0x13 = T_DIR | T_REG, 0x23 = T_IND | T_REG, 0xFF = T_IND | T_REG | T_DIR  */

}					t_comand;

typedef struct			s_to_code
{
	char				*lbl;
	char				*f_name;
	struct s_arg_lbl	arg_lbl;
	unsigned char		first_b;
	unsigned char		op;
	char				lz;
	unsigned char		count;
	char				*ar[4];
	unsigned int		args[3];
	unsigned char		op_est;
	unsigned int		op_f;
	unsigned char		cmnd_len;
	unsigned int		cmnd_i;
	int					cmnd_l;
	struct s_to_code	*next;
}						t_to_code;

void				start_write(char *name, t_main *main_asm);
t_to_code			*comand_list;
void				pars_two(char *line, t_main *main_asm, t_comand *all_comand, int a);
t_comand			**make_f_list(void);
t_to_code			*g_cmndList;
void				start_write(char *name, t_main *main_asm);


#endif