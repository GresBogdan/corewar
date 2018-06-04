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

char	*read_read(char *line, int fd)
{
	char	*tmp;
	char	*tmp2;
	char	*a;
	int		i;

	line = ft_strjoin(line, "\n");
	a = NULL;
	while((i = get_next_line(fd, &tmp2)) > 0 && (a = ft_strchr(tmp2, '\"')) == NULL)
	{
		tmp = line;
		line = ft_strjoin(line, tmp2);
		free(tmp);
		tmp = line;
		line = ft_strjoin(line, "\n");
		free(tmp);
		free(tmp2);
		g_line++;
	}
	g_line++;
	if (a == NULL)
	{
		ft_printf("Oops, wheare \"?\n");
		free(tmp2);
		g_error++;
	}
	else
	{
		tmp = line;
		line = ft_strjoin(line, tmp2);
		free(tmp);
		free(tmp2);
		tmp = ft_strdup(line);
		i = 0;
		while(line[i] != '\"')
			i++;
		line[i] = '\0';
		i++;
		while(line[i] == ' ' || line[i] == '\t')
			i++;
		if(line[i] != '\0' && line[i] != '#')
		{
			ft_printf("Oops, something wrong on line|%d|\n", g_line);
			g_error++;
		}
		free(line);
		return(tmp);
	}
	return("(");
}
char	*write_n_c(char *line, int flag, int fd)
{
	int		i;
	int		j;
	char	*name;

	j = 0;
	i = 0;
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] != '\"')
	{
		ft_printf("Oops, something wrong afte .name/.comment on line %d\n", g_line);
		g_error++;
	}
	else
	{
		i++;
		while(line[i + j] != '\"' && line[i + j] != '\0')
			j++;
		if (line[i + j] != '\"')
			name = read_read(&line[i], fd);
		else
		{
			name = (char *)ft_memalloc((j + 2) * sizeof(char));
			while (--j >= 0)
			{
				name[j] = line[i + j];
			}
		}
		return(name);
	}
	return (NULL);
}

void	check_name_comment(char *line, t_main *main_asm, int fd)
{
	int		i;

	i = 0;
	while(line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '#' || line[i] == '\0')
		return;
	if (ft_strnequ(&line[i], NAME_CMD_STRING, ft_strlen(NAME_CMD_STRING)))
	{
		if ((main_asm->flag & 1) != 0)
		{
			ft_printf("Oops, double comment, chek line %d\n", g_line);
			g_error++;
		}
		else
		{
			main_asm->flag = main_asm->flag | 1;
			main_asm->name = write_n_c(&line[i + 5], 1, fd);
		}
	}
	else if (ft_strnequ(&line[i], COMMENT_CMD_STRING, ft_strlen(COMMENT_CMD_STRING)))
	{
		if ((main_asm->flag & 2) != 0)
		{
			ft_printf("Oops, double comment, chek line %d\n", g_line);
							g_error++;
		}
		else
		{
			main_asm->flag = main_asm->flag | 2;
			main_asm->comment = write_n_c(&line[i + 8], 2, fd);
		}
	}
	else
	{
		ft_printf("Oops, somthing wrong on line %d\n", g_line);
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
		g_line++;
		if (line[0] != '#' && ft_strlen(line) != 0 && check_sp(line) != 1 && ((main_asm->flag & 3) != 3) )
		{
			check_name_comment(line, main_asm, fd);
		}
		else if (line[0] != '#' && check_sp(line) != 1 && ft_strlen(line) != 0)
		{
			do_whot_need(line);
			pars_two(line, main_asm, all_comand, 0);
		}
			free(line);
	}
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

int		ft_strequ_cw(char const *s1, char const *s2)
{
	int		i;

	if (s1 && s2)
	{
		i = 0;
		while (s1[i] != ':' || s2[i] != '\0')
		{
			if (s1[i] != s2[i])
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

unsigned int	magic_with_link(t_to_code *tmp, char *a)
{
	t_to_code	*tmp2;

	tmp2 = g_cmndList;
	while (tmp2)
	{
		if (tmp2->first_b == 0 && ft_strequ_cw(tmp2->lbl, &a[2]))
			return ((unsigned int)(tmp2->cmnd_i - tmp->cmnd_i));
		tmp2 = tmp2->next;
	}
	ft_printf("Oops, there is no such label [%s]\n", a);
	g_error++;
	return ('(');
}

unsigned int	magic_with_link2(t_to_code *tmp, char *a)
{
	t_to_code	*tmp2;

	tmp2 = g_cmndList;
	while (tmp2)
	{
		if (tmp2->first_b == 0 && ft_strequ_cw(tmp2->lbl, &a[1]))
			return ((unsigned int)(tmp2->cmnd_i - tmp->cmnd_i));
		tmp2 = tmp2->next;
	}
	ft_printf("Oops, there is no such label[%s]\n", a);
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
		if (res > 16)
			ft_printf("Warning, youre T_REG > 16\n");
		return (res);
	}
	ft_printf("Oops, youre T_REG-[%a] feels bad\n");
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
	i = ft_strlen(a) - 1;
	tmp = ft_memalloc(sizeof(char) * (i + 4));
	tmp[i++] = 'c';
	tmp[i++] = 'o';
	tmp[i++] = 'r';
	i = i - 4;
	while(i >= 0)
	{
		tmp[i] = a[i];
		i--;
	}
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
	char	a;

	fd = open(av[1], O_RDONLY);
	if (fd < 0 || ft_strlen(av[1]) < 3 || av[1][ft_strlen(av[1]) - 1] != 's' || av[1][ft_strlen(av[1]) - 2] != '.' || ft_strlen(av[1]) < 3 || read(fd, &a, 0) == -1)
	{
		ft_printf("Oops, wrong file\n");
		return ;
	}
	main_asm = start_pars(fd);
	if (g_error > 0 || ft_strlen(main_asm->name) > PROG_NAME_LENGTH || ft_strlen(main_asm->comment) > COMMENT_LENGTH)
	{
		ft_printf("Oops, you hawe %d errors\n", g_error);
	}
	else
	{

			count_cmnd_len(NULL);
			check_double_lbl();
			convert_args();
			start_write(make_name(av[1]), main_asm);
			name = make_name(av[1]);
		ft_printf("vse zbs file %s sdelan cmndL\n",name, g_cmnd_len);
		free(name);
	}
}

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
			name = make_name(av[i]);
			if (g_error > 0 || ft_strlen(main_asm->name) > PROG_NAME_LENGTH || ft_strlen(main_asm->comment) > COMMENT_LENGTH || g_cmnd_len > CHAMP_MAX_SIZE)
			{
				if(g_error > 0)
					ft_printf("Oops, you hawe %d errors in file %s\n", g_error, name);
				if (main_asm->name != NULL && ft_strlen(main_asm->name) > PROG_NAME_LENGTH)
					ft_printf("Oops, youre name too big\n");
				if (main_asm->comment != NULL && ft_strlen(main_asm->comment) > COMMENT_LENGTH)
					ft_printf("Oops, youre comment too big\n");
				if (g_cmnd_len > CHAMP_MAX_SIZE)
					ft_printf("Oops, youre bot too big\n");
			}
			else
			{
				start_write(make_name(av[i]), main_asm);
				ft_printf("vse zbs file %s sdelan cmndLen=%d!\n",name, g_cmnd_len);
			}
			free(name);
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
