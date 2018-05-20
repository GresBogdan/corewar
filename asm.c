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
			ft_printf("error on line %d", g_line);
			exit(0);
		}
		i= i + 5;
		i = i +skip_space(&line[i]);
		//ft_printf("%s\n", &line[i]);
		if (line[i] != '\"')
		{
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
			ft_printf("error on line %d", g_line);
			exit(0);			
		}
	}
	else
	{
		if ((ft_strstr_cw(&line[i], ".comment")) != 0)
		{
			ft_printf("error on line %d", g_line);
			exit(0);
		}
		i= i + 8;
		i = i +skip_space(&line[i]);
		//ft_printf("%s\n", &line[i]);
		if (line[i] != '\"')
		{
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
	//ft_printf("|%i||%s\n",ft_strlen(name), name);
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
		//ft_printf("da1 i=%i j=%i   s=|%s|\n", i, j, line);
		if (i != -1)
		{
			//ft_printf("da2\n");
			k = skip_space(line);
			if ((main_asm->flag & 1) != 0 || (ft_strstr_cw(&line[k], ".name") != 0))
			{
				//ft_printf("da4\n");
				ft_printf("double name, chek line %d", g_line);
				exit(0);
			}
			else
			{
				//ft_printf("da6\n");
				main_asm->flag = main_asm->flag | 1;
				main_asm->name = get_name(line, 1);
			}
		}
		if (j != -1)
		{
			//ft_printf("da3 j = %d  |%s|\n", j, ft_strstr(line, ".comment"));
			k = skip_space(line);
			if ((main_asm->flag & 2) != 0 || (ft_strstr_cw(&line[k], ".comment") != 0))
			{
				ft_printf("double comment, chek line %d", g_line);
				exit(0);
			}
			else 
			{
				main_asm->flag = main_asm->flag | 2;
				main_asm->comment = get_name(line, 2);
			}
		}
		//ft_printf("i=%d j=%d", i, j);
	}
	free(line);
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
void	start_pars(int fd)
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
			check_name_comment(line, main_asm);
		else if (line[0] != '#' && check_sp(line) != 1 && ft_strlen(line) != 0)
			pars_two(line, main_asm, all_comand, 0);
		else
			free(line);
	}
	ft_printf("name=|%s| comment = |%s|", main_asm->name, main_asm->comment);
	free(main_asm->name);
	free(main_asm->comment);
	free(main_asm);
}

int main(int ac, char **av)
{
	int		fd;

	g_line = 0;
	g_error = 0;
	g_cmndList = NULL;
	if (ac < 2)
	{
		ft_printf("no argument\n");
		return (0);
	}
	fd = open(av[1], O_RDONLY);
	if (fd < 0 || ft_strstr(av[1], ".s") == NULL || ft_strlen(av[1]) < 3)
	{
		ft_printf("wrong file\n");
		return (0);
	}
	start_pars(fd);
	//system("leaks a.out");
	return (0);
}
