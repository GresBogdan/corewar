/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_two.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 20:07:26 by bgres             #+#    #+#             */
/*   Updated: 2018/05/11 20:07:29 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"

void		add_to_cmndList(t_to_code *a)
{
	t_to_code	*tmp;

	tmp = NULL;
	if(g_cmndList == NULL)
		g_cmndList = a;
	else
	{
		tmp = g_cmndList;
		while(tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = a;
	}
}

char		*ft_copy_n(char *src, int n)
{
	size_t	i;
	char	*c;

	i = 0;
	c = (char *)ft_memalloc(sizeof(char) * n + 1);
	if (!c)
		return (NULL);
	while (src[i] != '\0' && (int)i < n)
	{
		c[i] = src[i];
		i++;
	}
	return (c);
}

t_comand	**make_f_list(void)
{
	t_comand	**a;

	a = (t_comand **)malloc(sizeof(t_comand *) * 17);

	a[0] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[0]->name = ft_strdup(LIVE);
	a[0]->op = 0;
	a[0]->lz = 4;
	a[0]->args = 0x010000;
	a[0]->count = 1;
	a[0]->op_est = 0;
	a[0]->cmnd_l = 5;

	a[1] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[1]->name = ft_strdup(LD);
	a[1]->op = 1;
	a[1]->lz = 4;
	a[1]->args = 0x120300;
	a[1]->count = 2;
	a[1]->op_est = 1;
	a[0]->cmnd_l = 0;

	a[2] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[2]->name = ft_strdup(ST);
	a[2]->op = 1;
	a[2]->lz = 4;
	a[2]->args = 0x032300;
	a[2]->count = 2;
	a[2]->op_est = 1;
	a[2]->cmnd_l = 0;

	a[3] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[3]->name = ft_strdup(ADD);
	a[3]->op = 1;
	a[3]->lz = 4;
	a[3]->args = 0x030303;
	a[3]->count = 3;
	a[3]->op_est = 1;
	a[3]->cmnd_l = 5;

	a[4] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[4]->name = ft_strdup(SUB);
	a[4]->op = 1;
	a[4]->lz = 4;
	a[4]->args = 0x030303;
	a[4]->count = 3;
	a[4]->op_est = 1;
	a[4]->cmnd_l = 5;

	a[5] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[5]->name = ft_strdup(AND);
	a[5]->op = 1;
	a[5]->lz = 4;
	a[5]->args = 0xffff03;
	a[5]->count = 3;
	a[5]->op_est = 1;
	a[5]->cmnd_l = 0;

	a[6] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[6]->name = ft_strdup(OR);
	a[6]->op = 1;
	a[6]->lz = 4;
	a[6]->args = 0xffff03;
	a[6]->count = 3;
	a[6]->op_est = 1;
	a[6]->cmnd_l = 0;

	a[7] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[7]->name = ft_strdup(XOR);
	a[7]->op = 1;
	a[7]->lz = 4;
	a[7]->args = 0xffff03;
	a[7]->count = 3;
	a[7]->op_est = 1;
	a[7]->cmnd_l = 0;

	a[8] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[8]->name = ft_strdup(ZJMP);
	a[8]->op = 0;
	a[8]->lz = 2;
	a[8]->args = 0x010000;
	a[8]->count = 1;
	a[8]->op_est = 0;
	a[8]->cmnd_l = 3;

	a[9] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[9]->name = ft_strdup(LDI);
	a[9]->op = 1;
	a[9]->lz = 2;
	a[9]->args = 0xffff03;
	a[9]->count = 3;
	a[9]->op_est = 1;
	a[9]->cmnd_l = 0;

	a[10] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[10]->name = ft_strdup(STI);
	a[10]->op = 1;
	a[10]->lz = 2;
	a[10]->args = 0x03ff13;
	a[10]->count = 3;
	a[10]->op_est = 1;
	a[10]->cmnd_l = 0;

	a[11] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[11]->name = ft_strdup(FORK);
	a[11]->op = 0;
	a[11]->lz = 2;
	a[11]->args = 0x010000;
	a[11]->count = 1;
	a[11]->op_est = 0;
	a[11]->cmnd_l = 3;

	a[12] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[12]->name = ft_strdup(LLD);
	a[12]->op = 1;
	a[12]->lz = 4;
	a[12]->args = 0x120300;
	a[12]->count = 2;
	a[12]->op_est = 1;
	a[12]->cmnd_l = 0;

	a[13] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[13]->name = ft_strdup(LLDI);
	a[13]->op = 1;
	a[13]->lz = 2;
	a[13]->args = 0xff1301;
	a[13]->count = 3;
	a[13]->op_est = 1;
	a[13]->cmnd_l = 0;

	a[14] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[14]->name = ft_strdup(LFORK);
	a[14]->op = 0;
	a[14]->lz = 2;
	a[14]->args = 0x010000;
	a[14]->count = 1;
	a[14]->op_est = 0;
	a[14]->cmnd_l = 3;

	a[15] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[15]->name = ft_strdup(AFF);
	a[15]->op = 1;
	a[15]->lz = 4;
	a[15]->args = 0x030000;
	a[15]->count = 1;
	a[15]->op_est = 1;
	a[15]->cmnd_l = 3;

	a[16] = NULL;
	return (a);
}

int		check_all_isdigit(char *param)
{
	int		i;
	int		a;

	i = 0;
	a = 0;
	while(param[i] != '\0')
	{
		if(!ft_isdigit(param[i]))
			a++;
		i++;
	}
	return (a);
}

char		*check_t_reg(char *param, t_to_code *f, unsigned char *op, char position)
{
	unsigned int	mask;
	int				sdvig;

	mask = 0xff;
	sdvig = (8 * (3 - position));
	mask = mask << sdvig;
	if (ft_strlen(param) >= 2 && ft_strlen(param) <= 3 && param[0] == 'r' && ft_isdigit(param[1]) && (ft_isdigit(param[2]) || param[2] == '\0'))
	{
		*op = *op | (1 << (2 * (3 - position + 1)));
		return (param);
	}
	else if (((f->op_f & mask) >> sdvig) <= 3)
	{
		g_error++;
		ft_printf("ERROR in check_t_reg s =|%s|line=%d\n",param, g_line);
	}
	return (NULL);
}

char		*check_t_ind(char *param, t_to_code *f, unsigned char *op, char position)
{
	unsigned int	mask;
	int				sdvig;

	mask = 0xff;
	sdvig = (8 * (3 - position));
	mask = mask << sdvig;
	if (param != NULL && (check_all_isdigit(param) == 0 || (check_all_isdigit(param) == 1 && ft_strlen(param) > 1 && param[0] == '-')))
	{
		*op = *op | (3 << (2 * (3 - position + 1)));
		return (param);
	}
	else if (param != NULL && param[0] == ':' && ft_strlen(param) > 1)
	{
		*op = *op | (3 << (2 * (3 - position + 1)));
		return (param);
	}
	else if (((f->op_f & mask) >> sdvig) <= 3)
	{
		g_error++;
		ft_printf("ERROR in check_t_ind line %d\n", g_line);
	}
	return (NULL);
}

char		*check_t_dir(char *param, t_to_code *f, unsigned char *op, int position)
{
	unsigned int	mask;
	int				sdvig;

	mask = 0xff;
	sdvig = (8 * (3 - position));
	mask = mask << sdvig;
	if (param != NULL && ft_strlen(param) >= 2 && param[0] == '%' &&
		(check_all_isdigit(&param[1]) == 0 || (ft_strlen(param) >= 3 && check_all_isdigit(&param[1]) == 1 && param[1] == '-')))
	{
		*op = *op | (2 << (2 * (3 - position + 1)));
		return (param);
	}
	else if (param != NULL && ft_strlen(param) >= 3 && param[0] == '%' && param[1] == ':')
	{
		*op = *op | (2 << (2 * (3 - position + 1)));
		return(param);
	}
	else if (((f->op_f & mask) >> sdvig) <= 3)
	{
		g_error++;
		ft_printf("!!!!ERROR s= |%s| in check_t_dir line %d, len = %d a[0] =|%c| a[1] = |%c|\n", param,g_line, ft_strlen(param), param[0], param[1]);
	}
	return (NULL);
}

char		*check_t_dir_ind(char *param, t_to_code *f, unsigned char *op, int position)
{
	int				i;
	unsigned char	tmp;
	char			*ansver;

	tmp = *op;
	i = 0;
	ansver = check_t_dir(param, f, op, position);
	if (tmp != *op)
		return (ansver);
	ansver = check_t_ind(param, f, op, position);
	if (tmp != *op)
		return (ansver);
	g_error++;
	ft_printf("ERROR!!!!! check_t_dir_ind in line %d", g_line);
	return(NULL);
}

char		*check_t_dir_reg(char *param, t_to_code *f, unsigned char *op, int position)
{
	int				i;
	unsigned char	tmp;
	char			*ansver;

	tmp = *op;
	i = 0;
	ansver = check_t_dir(param, f, op, position);
	if (tmp != *op)
		return (ansver);
	ansver = check_t_reg(param, f, op, position);
	if (tmp != *op)
		return (ansver);
		g_error++;
		ft_printf("ERROR!!!!!  check_t_dir_reg in line %d", g_line);
	return(NULL);
}

char	*check_t_ind_reg(char *param, t_to_code *f, unsigned char *op, int position)
{
	int				i;
	unsigned char	tmp;
	char			*ansver;

	tmp = *op;
	i = 0;
	ansver = check_t_ind(param, f, op, position);
	if (tmp != *op)
		return (ansver);
	ansver = check_t_reg(param, f, op, position);
	if (tmp != *op)
		return (ansver);
	g_error++;
	ft_printf("ERROR!!!!! in line check_t_ind_reg %d", g_line);
	return(NULL);
}

char	*check_t_ind_reg_dir(char *param, t_to_code *f, unsigned char *op, int position)
{
	int				i;
	unsigned char	tmp;
	char			*ansver;
	int				flag;

	tmp = *op;
	i = 0;
	ansver = check_t_ind(param, f, op, position);
	if (tmp != *op)
		return (ansver);
	ansver = check_t_reg(param, f, op, position);
	if (tmp != *op)
		return (ansver);
	ansver = check_t_dir(param, f, op, position);
	if (tmp != *op)
		return (ansver);
	g_error++;
	ft_printf("ERROR!!!!!????? check_t_ind_reg_dir in line %d", g_line);
	return(NULL);
}

int		get_need_f(char *param, int a, t_comand *f, t_to_code *tmp)
{
	unsigned int	mask;
	int				flag;
	int				sdvig;
	unsigned char	op;

	op = 0;
	sdvig = (8 * (3 - a));
	flag = 0;
	mask = 0xff;
	mask = mask << sdvig;
	if (((f->args & mask) >> sdvig) == 0x01)  /* T_DIR*/
		tmp->ar[a - 1]=check_t_dir(param, tmp, &op, a);
	else if (((f->args & mask) >> sdvig) == 0x02)
		tmp->ar[a - 1]=check_t_ind(param, tmp, &op, a);
	else if (((f->args & mask) >> sdvig) == 0x03)
		tmp->ar[a - 1]=check_t_reg(param, tmp, &op, a);
	else if (((f->args & mask) >> sdvig) == 0x12)
		tmp->ar[a - 1]=check_t_dir_ind(param, tmp, &op, a);
	else if (((f->args & mask) >> sdvig) == 0x13)
		tmp->ar[a - 1]=check_t_dir_reg(param, tmp, &op, a);
	else if (((f->args & mask) >> sdvig) == 0x23)
		tmp->ar[a - 1]=check_t_ind_reg(param, tmp, &op, a);
	else if (((f->args & mask) >> sdvig) == 0xff)
		tmp->ar[a - 1]=check_t_ind_reg_dir(param, tmp, &op, a);
	else
		ft_printf("kakoito pzdc\n");
	tmp->op = tmp->op | op;
	return (flag);
}

void	f_full_check(char *line, t_comand *f, t_to_code *tmp)
{
	int		i;
	char	**args;
	int		j;

	j = 0;
	i = 0;
	args = ft_strsplit(line, ',');
	while (args[i] != NULL)
	{
		args[i] = ft_strtrim_cw(args[i]);
		i++;
	}
	i = 0 ;
	while(args[i] != NULL)
		i++;
	if (i != f->count)
	{
		g_error++;
		ft_printf("ERROR in line %d ne to kolo4estvo argymentov\n",g_line);
		return ;
	}
	i = 0;
	while (args[i] != NULL)
	{
		get_need_f(args[i], i + 1, f, tmp);
		i++;
	}
	i = 0;
	 free(args);
}

void	check_f(t_to_code *tmp, char *line, int a)
{
	static t_comand		**f_list = NULL;
	unsigned char		i;
	int					j;
	char				*tmp2;

	j = 0;
	i = 0;
	if (f_list == NULL)
		f_list = make_f_list();
	if (line[i] == '#')
		return ;
	while(line[j] != ' ' && line[j] != '\t' && line[j] != '\0')
		j++;
	tmp2 = ft_copy_n(&line[0], j);
	j = 0;
	while(f_list[i++] != NULL)
	{
		if (ft_strequ(tmp2, f_list[i - 1]->name))
		{
			j = 1;
			tmp = (t_to_code *)ft_memalloc(sizeof(t_to_code));
			tmp->first_b = i;
			tmp->op_est = f_list[i - 1]->op_est;
			tmp->op_f = f_list[i - 1]->args;
			tmp->count = f_list[i - 1]->count;
			tmp->lz = f_list[i - 1]->lz;
			f_full_check(&line[ft_strlen(tmp2)], f_list[i - 1], tmp);
			add_to_cmndList(tmp);
		}
		if (i == 16 && j == 0)
		{
			g_error++;
			ft_printf("Oops, pleas use the available functions in line%d\n", g_line);
		}
	}
	free(tmp2);
}

void	check_label(char *name)
{
	int		i;

	i = 0;
	while(name[i] != ':')
	{
		if (ft_strchr(LABEL_CHARS, name[i]) == NULL)
		{
			g_error++;
			ft_printf("Oops, you're label feel bad about it character in line %d\n", g_line);
		}
		i++;
	}
}

void	pars_two(char *line, t_main *main_asm, t_comand *all_comand, int a)
{
	size_t			i;
	char			flag;
	t_to_code		*tmp;
	size_t			j;

	j = 0;
	tmp = NULL;
	flag = 0;
	i = 0;
		while(line[i] == ' ' || line[i] == '\t')
			i++;
		if (line[i] == '#')
			return ;
		while(line[i + j] != ' ' && line[i + j] != '\t' && line[i + j] != '\0')
			j++;
		if (line[i] == '.')
		{
			ft_printf("error in line %d", g_line);
			g_error++;
		}
		if (j > 0 && line[i + j - 1] == ':')
		{
			tmp = (t_to_code *)ft_memalloc(sizeof(t_to_code));
			tmp->lbl = ft_copy_n(&line[i], j);
			check_label(tmp->lbl);
			flag = 1;
			add_to_cmndList(tmp);
			flag = 1;
		}
		if (flag == 1)
		{
			i += j;
			while(line[i] == ' ' || line[i] == '\t')
				i++;
		}
		if (line[i] == '#' || line [i] == '\0')
			return ;
		check_f(tmp, &line[i], a);
}