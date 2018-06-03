/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_code.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/26 15:35:38 by bgres             #+#    #+#             */
/*   Updated: 2018/05/26 15:35:40 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"


void	write_int(int fd, unsigned int m)
{
	m = ((m >> 24) & 0xff) | ((m << 8) & 0xff0000) |
		((m >> 8) & 0xff00) | ((m << 24) & 0xff000000);
	write(fd, (char *)&m, 4);
}

void	write_short(int fd, unsigned int mm)
{
	unsigned short	m;
	m = (unsigned short)mm;
	m = (m >> 8) | (m << 8);
	write(fd, (char *)&m, 2);
}

void	write_name(int fd, t_main *main_asm)
{
	char	*tmp;
	char	*tmp2;

	tmp2 = ft_memalloc(sizeof(char) * 8);
	tmp = ft_memalloc(sizeof(char) * (PROG_NAME_LENGTH - ft_strlen(main_asm->name)));
	write(fd, main_asm->name, ft_strlen(main_asm->name));
	write(fd, tmp, (PROG_NAME_LENGTH - ft_strlen(main_asm->name)));
	free(tmp);
	write(fd, tmp2, 4);
	write_int(fd, g_cmnd_len);
	tmp = ft_memalloc(sizeof(char) * (COMMENT_LENGTH - ft_strlen(main_asm->comment)));
	write(fd, main_asm->comment, ft_strlen(main_asm->comment));
	write(fd, tmp, (COMMENT_LENGTH - ft_strlen(main_asm->comment)));
	write(fd, tmp2, 4);
	free(tmp);
	free(tmp2);
}

void	write_t_dir(t_to_code *tmp, int fd, int i)
{
	if (tmp->lz == 2)
		write_short(fd, tmp->args[i]);
	else
		write_int(fd, tmp->args[i]);
}

void	write_t_reg(t_to_code *tmp, int fd, int i)
{
	char	a;

	a = tmp->args[i] & 0xff;
	write(fd, &a, 1);
}
void	write_comand(int fd)
{
	t_to_code	*tmp;
	int			i;

	tmp = g_cmndList;
	while(tmp)
	{
		if (tmp->first_b != 0)
		{
			write(fd, &tmp->first_b, 1);
			if (tmp->op_est != 0)
				write(fd, (char *)&tmp->op, 1);
			i = 0;
			while(i < tmp->count)
			{
				if (tmp->ar[i][0] == 'r')
					write_t_reg(tmp, fd, i);
				else if (tmp->ar[i][0] == '%')
					write_t_dir(tmp, fd, i);
				else
					write_short(fd, tmp->args[i]);
				i++;
			}
		}
		tmp = tmp->next;
	}
}

void	start_write(char *name, t_main *main_asm)
{
	t_to_code	*tmp;
	int			fd;
	int			i;

	i = 0;
	tmp = g_cmndList;
	fd = open(name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	write_int(fd, COREWAR_EXEC_MAGIC);
	write_name(fd, main_asm);
	write_comand(fd);
	free(name);
}
