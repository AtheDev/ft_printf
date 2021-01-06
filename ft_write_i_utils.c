/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_i_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 19:32:14 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/08 15:07:46 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_convert_hexa(t_cf *ptr, unsigned int n)
{
	char			*base;
	char			*str;
	int				count;
	unsigned long	nb;

	nb = n;
	count = ft_count_base(nb) + 1;
	if (ptr->ci == 'x')
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if ((str = ft_malloc(count)) == NULL)
		return (str);
	str[count--] = '\0';
	while (count >= 0)
	{
		str[count--] = base[(n % 16)];
		n /= 16;
	}
	return (str);
}

void	ft_newstr_i_next(t_cf *ptr, char *tmp, char *str, int minus)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if (minus == 1)
		tmp[i++] = '-';
	while (i < (ptr->prcs - ft_strlen(str) + minus))
		tmp[i++] = '0';
	while (i < (ptr->prcs + minus))
		tmp[i++] = str[j++];
	if (ptr->prcs == 0)
		while (i < (ft_strlen(str) + minus))
			tmp[i++] = str[j++];
	while (i < ptr->fw)
		tmp[i++] = ' ';
	tmp[i] = '\0';
}

void	ft_newstr_i_next2(t_cf *ptr, char *tmp, char *str, int minus)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	if ((ptr->prcs != 0 && ptr->zero == 0) || ptr->zero != 0)
	{
		if (ptr->prcs != 0 && ptr->zero == 0)
			while (i < (ptr->fw - ptr->prcs - minus))
				tmp[i++] = ' ';
	}
	else
		while (i < (ptr->fw - (ft_strlen(str) + minus)))
			tmp[i++] = ' ';
	if (minus == 1)
		tmp[i++] = '-';
	while (i < (ptr->fw - ft_strlen(str)))
		tmp[i++] = '0';
	while (i < ptr->fw)
		tmp[i++] = str[j++];
	tmp[i] = '\0';
}

int		ft_newstr_i(t_cf *ptr, char *str, int size, int minus)
{
	char	*tmp;

	if ((tmp = ft_malloc(size)) == NULL)
	{
		free(str);
		return (0);
	}
	if (ptr->fw > 0 && ptr->minus == 0)
		ft_newstr_i_next2(ptr, tmp, str, minus);
	else
		ft_newstr_i_next(ptr, tmp, str, minus);
	minus = ft_write(tmp, size, 0);
	free(tmp);
	return (minus);
}
