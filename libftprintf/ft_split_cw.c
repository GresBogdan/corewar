/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cw.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/11 16:42:50 by bgres             #+#    #+#             */
/*   Updated: 2018/05/11 16:42:52 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		kw(char const *s)
{
	int		i;
	int		n;

	n = 0;
	i = 0;
	while ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		while (s[i] != ' ' && s[i] != '\t' && s[i] != '\0')
			i++;
		n++;
		while ((s[i] == ' ' || s[i] == '\t') && s[i] != '\0')
			i++;
	}
	return (n);
}

static void		*fill(char const *s, char *a, int n)
{
	int		i;

	i = 0;
	while (i <= n)
	{
		a[i] = s[i];
		i++;
	}
	a[i] = '\0';
	return (a);
}

static int		check(int *n, int *j, int *i, char const *s)
{
	*n = 0;
	*j = 0;
	*i = 0;
	if (!s)
		return (1);
	return (0);
}

char			**ft_split_cw(char const *s)
{
	char	**av;
	int		j;
	int		i;
	int		n;

	if (check(&n, &i, &j, s))
		return (NULL);
	av = (char **)malloc(sizeof(char *) * kw(s) + 1);
	if (!av)
		return (NULL);
	while (i < kw(s))
	{
		while (s[j] == ' ' || s[j] == '\t')
			j++;
		while (s[j] != ' ' && s[j] != '\t' && s[j] != '\0')
		{
			j++;
			n++;
		}
		av[i] = (char *)malloc(sizeof(char) * (n + 2));
		fill(&s[j - n], av[i++], n - 1);
		n = 0;
	}
	av[i] = NULL;
	return (av);
}
