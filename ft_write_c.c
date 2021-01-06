/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_write_c.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adupuy <adupuy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/06 15:46:06 by adupuy            #+#    #+#             */
/*   Updated: 2020/12/08 14:45:46 by adupuy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_new_str_c(t_cf *ptr, unsigned char c, int i, int r)
{
	char	*tmp;
	int		ret;

	ret = 0;
	if ((tmp = ft_malloc(ptr->fw)) == NULL)
		return (ret);
	if (r == 0)
		tmp[i++] = c;
	while (i < (ptr->fw - r))
	{
		tmp[i] = ' ';
		i++;
	}
	if (r == 1)
		tmp[i++] = c;
	tmp[i] = '\0';
	ret = ft_write(tmp, ptr->fw, 0);
	free(tmp);
	return (ret);
}

int	ft_write_c(t_cf *ptr, va_list *ap)
{
	unsigned char	c;
	int				i;
	int				ret;

	i = 0;
	ret = 0;
	c = va_arg(*ap, int);
	if (ptr->fw == 0)
		ret = write(1, &c, 1);
	else if (ptr->minus == 0)
		ret = ft_new_str_c(ptr, c, i, 1);
	else if (ptr->minus == 1)
		ret = ft_new_str_c(ptr, c, i, 0);
	else
		return (ret);
	return (ret);
}
