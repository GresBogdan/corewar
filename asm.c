/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/09 12:43:39 by bgres             #+#    #+#             */
/*   Updated: 2018/05/09 12:43:41 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

int		skip_space(char *line)
{
	int		i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	return (i);
}

char	*get_name(char *line, int flag)
{
	int		i;
	int		j;
	char	*name;

	i = skip_space(line);
	j = 0;
	if (flag == 1)
	{
		if ((ft_strstr_cw(&line[i], ".name")) != 0)
		{
			g_error++;
			ft_printf("error on line %d", g_line);
			exit(0);
		}
		i= i + 5;
		i = i +skip_space(&line[i]);
		if (line[i] != '\"')
		{
			g_error++;
			ft_printf("error on line %d", g_line);
			exit(0);
		}
		i++;
		while (line[i + j] != '\"')
			j++;
		j++;
		while ((line[i + j] == ' ' || line[i + j] == '\t'))
			j++;
		if (line[i + j] != '\0' && line[i +j] != '#')
		{
			g_error++;
			ft_printf("error on line %d", g_line);
			exit(0);			
		}
	}
	else
	{
		if ((ft_strstr_cw(&line[i], ".comment")) != 0)
		{
			g_error++;
			ft_printf("error on line %d", g_line);
			exit(0);
		}
		i= i + 8;
		i = i + skip_space(&line[i]);
		if (line[i] != '\"')
		{
			g_error++;
			ft_printf("error on line %d", g_line);
			exit(0);
		}
		i++;
		while (line[i + j] != '\"')
			j++;
		j++;
		while ((line[i + j] == ' ' || line[i + j] == '\t'))
			j++;
		if (line[i + j] != '\0' && line[i +j] != '#')
		{
			g_error++;
			ft_printf("error on line %d", g_line);
			exit(0);			
		}
	}
	j = 0;
	while (line[i + j] != '\"')
		j++;
	name = (char *)ft_memalloc(j * sizeof(char));
	while (--j >= 0)
	{
		name[j] = line[i + j];
	}
	return (name);
}


void	check_name_comment(char *line, t_main *main_asm)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	j = -1;
	k = 0;
	if ((i = ft_strstr_cw(line, ".name")) != -1 || (j = ft_strstr_cw(line, ".comment")) != -1)
	{
		if (i != -1)
		{
			k = skip_space(line);
			if ((main_asm->flag & 1) != 0 || (ft_strstr_cw(&line[k], ".name") != 0))
			{
				g_error++;
				ft_printf("double name, chek line %d", g_line);
				exit(0);
			}
			else
			{
				main_asm->flag = main_asm->flag | 1;
				main_asm->name = get_name(line, 1);
			}
		}
		if (j != -1)
		{
			k = skip_space(line);
			if ((main_asm->flag & 2) != 0 || (ft_strstr_cw(&line[k], ".comment") != 0))
			{
				g_error++;
				ft_printf("double comment, chek line %d", g_line);
				exit(0);
			}
			else 
			{
				main_asm->flag = main_asm->flag | 2;
				main_asm->comment = get_name(line, 2);
			}
		}
	}
	else
	{
		ft_printf("!!!ERROR in %d\n", g_line);
		g_error++;
	}
}
int		check_sp(char *line)
{
	int		i;

	i = 0;
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '\0' || line[i] == '#')
		return (1);
	return (0);
}

void	do_whot_need(char *line)
{
	int		i;

	i = 0;
	if (ft_strchr(line, '#') != NULL)
	{
		while(line[i] != '#')
			i++;
		line[i] = '\0';
	}
}

t_main	*start_pars(int fd)
{

	char		*line;
	t_main		*main_asm;
	t_comand	*all_comand;

	main_asm = (t_main *)ft_memalloc(sizeof(t_main));
	all_comand = (t_comand *)ft_memalloc(sizeof(t_comand));
	while (get_next_line(fd, &line))
	{
		do_whot_need(line);
		g_line++;
		if (line[0] != '#' && ft_strlen(line) != 0 && check_sp(line) != 1 && ((main_asm->flag & 3) != 3) )
		{
			check_name_comment(line, main_asm);
		}
		else if (line[0] != '#' && check_sp(line) != 1 && ft_strlen(line) != 0)
		{
			pars_two(line, main_asm, all_comand, 0);
		}
			free(line);
	}
				//system("leaks my_asm");
	if(main_asm->name == NULL || main_asm->comment == NULL)
	{
		if (main_asm->name == NULL)
		{
			ft_printf("Oops, no name (\n");
					g_error++;
		}
		if (main_asm->comment == NULL)
		{
			ft_printf("Oops, no comment(\n");
					g_error++;
		}
	}
	free(line);
	free(all_comand);
	return (main_asm);

}


void	count_cmnd_len(t_comand **f)
{
	t_to_code		*tmp;
	int				i;
	unsigned char	mask;
	char			a[4];

	f = make_f_list();
	a[0] = 0;
	a[1] = 1;
	a[3] = 2;
	mask = 0x3;
	i = 1;
	tmp = g_cmndList;
	while (tmp)
	{
		i = 1;
		if (tmp->first_b != 0 && f[tmp->first_b - 1]->cmnd_l == 0)
		{
			a[2] = f[tmp->first_b - 1]->lz;
			i = i + f[tmp->first_b - 1]->op + a[(tmp->op & (mask << 6)) >> 6] + a[(tmp->op & (mask << 4)) >> 4] + a[(tmp->op & (mask << 2)) >> 2];
			tmp->cmnd_l = i;
			tmp->cmnd_i = g_cmnd_len;
			g_cmnd_len += i;
		}
		else if (tmp->first_b != 0)
		{
			tmp->cmnd_i = g_cmnd_len;
			tmp->cmnd_l = f[tmp->first_b - 1]->cmnd_l;
			g_cmnd_len += f[tmp->first_b - 1]->cmnd_l;
		}
		else
		{
			tmp->cmnd_i = g_cmnd_len;
			tmp->cmnd_l = -1;
		}
		tmp = tmp->next;
	}
	i = 0;
	while(f[i] != NULL)
	{
		free(f[i]->name);
		free(f[i]);
		i++;
	}
	free(f);
}

unsigned int	magic_with_link(t_to_code *tmp, char *a)
{
	t_to_code	*tmp2;

	tmp2 = g_cmndList;
	while (tmp2)
	{
		if (tmp2->first_b == 0 && ft_strnequ(tmp2->lbl, &a[2], ft_strlen(&a[2])))
			return ((unsigned int)(tmp2->cmnd_i - tmp->cmnd_i));
		tmp2 = tmp2->next;
	}
	ft_printf("Oops, there is no such label==%s\n", a);
	g_error++;
	return ('(');
}

unsigned int	magic_with_link2(t_to_code *tmp, char *a)
{
	t_to_code	*tmp2;

	tmp2 = g_cmndList;
	while (tmp2)
	{
		if (tmp2->first_b == 0 && ft_strnequ(tmp2->lbl, &a[1], ft_strlen(&a[2])))
			return ((unsigned int)(tmp2->cmnd_i - tmp->cmnd_i));
		tmp2 = tmp2->next;
	}
	ft_printf("Oops, there is no such label==%s\n", a);
	g_error++;
	return ('(');
}

unsigned int	convert_T_REG(t_to_code *tmp, char *a)
{
	unsigned int	res;

	if (ft_strlen(a) > 1 && ft_strlen(a) < 4)
	{
		res = -1;
		res = ft_atoi(&a[1]);
		return (res);
	}
	ft_printf("Oops, youre T_REG-|%a| feels bad\n");
	g_error++;
	return (-1);
}

unsigned int	convert_T_DIR(t_to_code *tmp, char *a)
{
	unsigned int	res;
	res = 0;
	if (a[1] == ':')
		return(magic_with_link(tmp, a));
	else
		res = ft_atoi_cw(&a[1], tmp->lz);
	return (res);
}

unsigned int	convert_T_IND(t_to_code *tmp, char *a)
{
	unsigned int	res;
	res = 0;
	if (a[0] == ':')
		return(magic_with_link2(tmp, a));
	res = ft_atoi_cw(a, 2);
	return(res);
}

void	zaebali_nazv(t_to_code *tmp, char i, char flag)
{
	if (flag == 1)
		tmp->args[i] = convert_T_REG(tmp, tmp->ar[i]);
	else if (flag == 2)
		tmp->args[i] = convert_T_DIR(tmp, tmp->ar[i]);		
	else if (flag == 3)
		tmp->args[i] = convert_T_IND(tmp, tmp->ar[i]);
	else
	ft_printf("4toto poshlo ne tak flag = %d f_b = %d s=%s(\n", flag, tmp->first_b, tmp->ar[i]);
}

void	convert_args(void)
{
	t_to_code	*tmp;
	char		i;

	i = -1;
	tmp = g_cmndList;
	while(tmp)
	{
		while(++i < tmp->count)
			zaebali_nazv(tmp, i, (tmp->op & (3 << (2 * (3 - i)))) >>  (2 * (3 - i)));
		i = -1;
		tmp = tmp->next;
	}
}
char	*make_name(char *a)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	while(a[i] != '.' && a[i] != '\0')
		i++;
	tmp = ft_memalloc(sizeof(char) * (i + 5));
	i = 0;
	while(a[i] != '.' && a[i] != '\0')
	{
		tmp[i] = a[i];
		i++;
	}
	tmp[i++] = '.';
	tmp[i++] = 'c';
	tmp[i++] = 'o';
	tmp[i++] = 'r';
	return (tmp);
}

void	need(t_to_code *tmp, char *a)
{
	while(tmp)
	{
		if (tmp->lbl != NULL)
		{
			if (ft_strequ(tmp->lbl, a))
			{
				ft_printf("Oops, you have same label [%s]\n", a);
				g_error++;
			}
		}
		tmp = tmp->next;
	}
}

void	check_double_lbl(void)
{
	t_to_code	*tmp;

	tmp = g_cmndList;
	while(tmp)
	{
		if (tmp->lbl != NULL)
			need(tmp->next, tmp->lbl);
		tmp = tmp->next;
	}
}


void	need2(int i, char **av, t_main *main_asm, char *name)
{
	int		fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0 || ft_strlen(av[1]) < 3 || av[1][ft_strlen(av[1]) - 1] != 's' || av[1][ft_strlen(av[1]) - 2] != '.' || ft_strlen(av[1]) < 3)
	{
		ft_printf("wrong file\n");
		return ;
	}
	main_asm = start_pars(fd);
	if (g_error > 0 || ft_strlen(main_asm->name) > PROG_NAME_LENGTH || ft_strlen(main_asm->comment) > COMMENT_LENGTH)
	{
		ft_printf("\nOops, you hawe %d errors\n", g_error);
	}
	else
	{

			count_cmnd_len(NULL);
			check_double_lbl();
			convert_args();
			start_write(make_name(av[1]), main_asm);
			name = make_name(av[1]);
		ft_printf("vse zbs file %s sdelan cmndLen=%d!\n",name, g_cmnd_len);
		free(name);
	}
}

// void	free_list(t_to_code *tmp)
// {
// 	t_to_code	*tmp2;

// 	while(tmp)
// 	{
// 		tmp2 = tmp->next;
// 		if(tmp->lbl != NULL)
// 			free(tmp->lbl);
// 		if(tmp->f_name != NULL)
// 			free(tmp->f_name);
// 		tmp = tmp2;
// 	}
// }

void	free_list(void)
{
	int			i;
	t_to_code	*tmp;
	t_to_code	*tmp2;

	tmp = g_cmndList;
	while (tmp)
	{
		if(tmp->lbl != NULL)
			free(tmp->lbl);
		if(tmp->f_name != NULL)
			free(tmp->f_name);
		i = 0;
		while(i < 4)
		{
			if (tmp->ar[i] != NULL)
				free(tmp->ar[i]);
			i++;
		}
		free(tmp);
		tmp = tmp->next;
	}
}

int main(int ac, char **av)
{
	int			fd;
	t_main		*main_asm;
	char		*name;
	int			i;

	i = 1;
	if (ac < 2)
	{
		ft_printf("no argument\n");
		return (0);
	}
	while(i < ac)
	{
			fd = open(av[i], O_RDONLY);
		if (fd < 0 || ft_strlen(av[1]) < 3 || av[1][ft_strlen(av[1]) - 1] != 's' || av[1][ft_strlen(av[1]) - 2] != '.' || ft_strlen(av[1]) < 3)
			ft_printf("wrong file n-%i\n", i - 1);
		else
		{
			g_line = 0;
			g_error = 0;
			g_cmndList = NULL;
			g_cmnd_len = 0;
			main_asm = start_pars(fd);
			count_cmnd_len(NULL);
			check_double_lbl();
			convert_args();
			if (g_error > 0 || ft_strlen(main_asm->name) > PROG_NAME_LENGTH || ft_strlen(main_asm->comment) > COMMENT_LENGTH || g_cmnd_len > CHAMP_MAX_SIZE)
				ft_printf("Oops, you hawe %d errors\n", g_error);
			else
			{
				start_write(make_name(av[i]), main_asm);
				name = make_name(av[i]);
				ft_printf("vse zbs file %s sdelan cmndLen=%d!\n",name, g_cmnd_len);
				free(name);
			}
			if (main_asm->name != NULL)
				free(main_asm->name);
			if (main_asm->comment != NULL)
				free(main_asm->comment);
			free_list();
			if (main_asm != NULL)
			 free(main_asm);
		}
		i++;
	}
	return (0);
}
