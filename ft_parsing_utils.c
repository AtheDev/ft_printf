/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 14:31:39 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/06 20:22:03 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_atoi(char *str)
{
	int	i;
	int	res;

	i = 0;
	res = 0;
	while (str && str[i] == '0')
		i++;
	while (str && str[i])
	{
		res = res * 10 + (str[i] - 48);
		i++;
	}
	return (res);
}

void	ft_init_struct_cf(t_cf *cf)
{
	cf->minus = 0;
	cf->zero = 0;
	cf->fw = 0;
	cf->prcs = 0;
	cf->ci = 0;
}

void	ft_if_isnot_number(int size, va_list *ap, t_cf *ptr)
{
	size = va_arg(*ap, int);
	if (size == 0)
		ptr->prcs = -1;
	else if (size < 0)
		ptr->prcs = 0;
	else
		ptr->prcs = size;
}

int		ft_if_is_number(const char *str, t_cf *ptr, int i, int r)
{
	int		j;
	int		size;
	char	*tmp;

	size = i++;
	while (str[i] >= '0' && str[i] <= '9')
		i++;
	if (!(tmp = malloc(sizeof(char) * (i - size + 1))))
	{
		tmp = NULL;
		return (0);
	}
	j = 0;
	while (j < (i - size + j))
		tmp[j++] = str[size++];
	tmp[j] = '\0';
	if (r == 0)
		ptr->fw = ft_atoi(tmp);
	else
		ptr->prcs = ft_atoi(tmp);
	free(tmp);
	return (i);
}
