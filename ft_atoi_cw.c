/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_cw.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:20:55 by bgres             #+#    #+#             */
/*   Updated: 2018/05/15 20:20:56 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	return_1(const char *a)
{
	unsigned short	result;
	int				z;

	result = 0;
	z = 1;
	while ((*a > 8 && *a < 14) || *a == ' ')
		a++;
	if (*a == '-')
		z = -1;
	if (*a == '-' || *a == '+')
		a++;
	while (*a >= '0' && *a <= '9')
	{
		result = (result * 10) + (*a - '0');
		a++;
	}
	return ((int)(result * z));
}

static int	return_2(const char *a)
{
	unsigned int	result;
	int				z;

	result = 0;
	z = 1;
	while ((*a > 8 && *a < 14) || *a == ' ')
		a++;
	if (*a == '-')
		z = -1;
	if (*a == '-' || *a == '+')
		a++;
	while (*a >= '0' && *a <= '9')
	{
		result = (result * 10) + (*a - '0');
		a++;
	}
	return ((int)(result * z));
}

int		ft_atoi(const char *a , char size)
{
	if (size == 2)
		return(return_1(a));
	else
		return(return_2(a));

	
	return (0);
}

