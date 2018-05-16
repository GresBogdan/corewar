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
	a->next = g_cmndList;
	if (g_cmndList != NULL)
		g_cmndList->prvs = a;
	g_cmndList = a;
}

t_comand	**make_f_list(void)
{
	t_comand	**a;
	int			i;

	i = 0;
	a = (t_comand **)malloc(sizeof(t_comand *) * 17);

	a[0] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[0]->name = ft_strdup(LIVE);
	a[0]->op = 0;
	a[0]->lz = 4;
	a[0]->args = 0x010000;

	a[1] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[1]->name = ft_strdup(LD);
	a[1]->op = 1;
	a[1]->lz = 4;
	a[1]->args = 0x120300;

	a[2] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[2]->name = ft_strdup(ST);
	a[2]->op = 1;
	a[2]->lz = 4;
	a[2]->args = 0x030000;

	a[3] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[3]->name = ft_strdup(ADD);
	a[3]->op = 1;
	a[3]->lz = 4;
	a[3]->args = 0x030303;

	a[4] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[4]->name = ft_strdup(SUB);
	a[4]->op = 1;
	a[4]->lz = 4;
	a[4]->args = 0x030303;

	a[5] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[5]->name = ft_strdup(AND);
	a[5]->op = 1;
	a[5]->lz = 4;
	a[5]->args = 0xffff03;

	a[6] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[6]->name = ft_strdup(OR);
	a[6]->op = 1;
	a[6]->lz = 4;
	a[6]->args = 0xffff03;

	a[7] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[7]->name = ft_strdup(XOR);
	a[7]->op = 1;
	a[7]->lz = 4;
	a[7]->args = 0xffff03;

	a[8] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[8]->name = ft_strdup(ZJMP);
	a[8]->op = 0;
	a[8]->lz = 2;
	a[8]->args = 0x030000;

	a[9] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[9]->name = ft_strdup(LDI);
	a[9]->op = 1;
	a[9]->lz = 2;
	a[9]->args = 0xffff03;

	a[10] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[10]->name = ft_strdup(STI);
	a[10]->op = 1;
	a[10]->lz = 2;
	a[10]->args = 0x03ff13;

	a[11] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[11]->name = ft_strdup(FORK);
	a[11]->op = 0;
	a[11]->lz = 2;
	a[11]->args = 0x010000;

	a[12] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[12]->name = ft_strdup(LLD);
	a[12]->op = 1;
	a[12]->lz = 4;
	a[12]->args = 0x120300;

	a[13] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[13]->name = ft_strdup(LLDI);
	a[13]->op = 1;
	a[13]->lz = 2;
	a[13]->args = 0xff1301;

	a[14] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[14]->name = ft_strdup(LFORK);
	a[14]->op = 0;
	a[14]->lz = 2;
	a[14]->args = 0x010000;

	a[15] = (t_comand *)ft_memalloc(sizeof(t_comand));
	a[15]->name = ft_strdup(AFF);
	a[15]->op = 1;
	a[15]->lz = 4;
	a[15]->args = 0x030000;

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

int		check_t_reg(char *param, t_comand *f)
{
	if (ft_strlen(param) == 3 && param[0] == 'r' && ft_isdigit(param[1]) && ft_isdigit(param[2]))
		return (ft_atoi(&param[1]));
	else
		return (-1);
}

int		check_t_ind(char *param, t_comand *f)
{
	if (param != NULL && (check_all_isdigit(param) == 0 || (check_all_isdigit(param) == 1 && ft_strlen(param) > 1 && param[0] == '-')))
		return (ft_atoi_cw(param, 2));
	ft_printf("!!!!ERROR in line %d\n", g_line);
		return (-1);
}

int		check_t_dir(char *param, t_comand *f)
{
	int		i;

	i = 0;
	if (param != NULL && ft_strlen(param) >= 2 && param[0] == '%' &&
		(check_all_isdigit(&param[1]) == 0 || (ft_strlen(param) >= 3 && check_all_isdigit(&param[1]) == 1 && param[1] == '-')))
		return (ft_atoi_cw(&param[1], f->lz));
	ft_printf("!!!!ERROR in line %d\n", g_line);
	return (-1);
}

int		get_need_f(char *param, char a, t_comand *f, t_to_code *tmp)
{
	unsigned int	mask;
	int				flag;

	flag = 0;
	mask = 0xff;
	mask = mask << (3 - a);
	if (param[ft_strlen(param) - 1] == ',')
	{
		param[ft_strlen(param) - 1] = '\0';
		flag = 1;
	}
	if (((f->args & mask) >> (3 - a)) == 0x01)  /* T_DIR*/
		check_t_dir(param, f);
	else if (((f->args & mask) >> (3 - a)) == 0x02)
		check_t_ind(param, f);
	else if (((f->args & mask) >> (3 - a)) == 0x03)
		check_t_reg(param, f);
	//else if (((f->args & mask) >> (3 - a)) == 0x12)
	//	check_t_dir_ind();
	//else if (((f->args & mask) >> (3 - a)) == 0x13)
	//	check_t_dir_reg();
	//else if (((f->args & mask) >> (3 - a)) == 0x23)
	//	check_t_ind_reg();
	//else if (((f->args & mask) >> (3 - a)) == 0xff)
	//	check_t_ind_reg_dir();
	return (0);
}

void	f_full_check(char *param, char **params, t_comand *f, t_to_code *tmp)
{
	int		i;
	char	a;
	char	coma;

	i = 1;
	a = 1;
	coma = 0;
	while (params[i] != NULL)
	{
		coma = get_need_f(params[i], a, f, tmp);
		a++;
		i++;
		if (params[i + 1] != NULL && params[i + 2] != NULL && params[i][0] == ',' && ft_strlen(params[i]) == 1 && coma == 1)
			i++;
		else
			ft_printf("ERROR!!!!! in line %d", g_line);
		coma = 0;

	}
}

void	check_f(char *param, char **params, t_to_code * tmp)
{
	static t_comand		**f_name = NULL;
	unsigned char		i;
	int					j;

	j = 0;
	i = 0;
	if (f_name == NULL)
		f_name = make_f_list();
	if (param == NULL)
		return ;
	while(f_name[i++] != NULL)
	{
		if (ft_strequ(param, f_name[i - 1]->name))
		{
			j = 1;
			ft_printf("f = %s\n", param);
			tmp = (t_to_code *)ft_memalloc(sizeof(t_to_code));
			tmp->first_b = i;
			f_full_check(param, params, f_name[i - 1], tmp);
		}
		if (i == 16 && j == 0)
			ft_printf("error in f in line%d s=%s\n", g_line, param);
	}
}

void	pars_two(char *line, t_main *main_asm, t_comand *all_comand)
{
	char			**par;
	size_t			i;
	char			flag;
	t_to_code		*tmp;

	tmp = NULL;
	flag = 0;
	i = 0;
	par = ft_split_cw(line);
	while(par[i] != NULL)
	{
		if (i == 0)
		{
			if (par[i][ft_strlen(par[i]) - 1] == ':')
			{
				i++;
				flag = 1;
				tmp = (t_to_code *)ft_memalloc(sizeof(t_to_code));
				tmp->lbl = ft_strdup(par[i - 1]);
				ft_printf("label v %i\n", i);
			}
		}
		if (i == 0 || (i == 1 && flag == 1))
			check_f(par[i], &par[i], tmp);
		//ft_printf("%s ",par[i]);
		i++;
	}
	//ft_printf("\nf_line = %d i = %d\n", g_line, i);
}