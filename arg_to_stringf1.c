/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_stringf1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:47:47 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/19 08:39:46 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int handle_positive_sign(char *sign_place, unsigned int flag)
{
	char sign_selector[2];

	sign_selector[0] = ' ';
	sign_selector[1] = '+';
	*sign_place = ' ';
	*sign_place = sign_selector[0 < (flag & POS_SIGN)];
	return ((flag & POS_SIGN) || (flag & EMPTY_SPACE));
}

int handle_negative_sign(char *sign_place, unsigned int flag)
{
	(void)flag;
	*sign_place = '-';
	return (1);
}

static const t_sign_handlerf g_sign_handler_table[2] = \
{
	handle_positive_sign,
	handle_negative_sign
};

size_t int_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	int			sign_factor;
	size_t		i;
	size_t		left;

	i = g_sign_handler_table[arg->i < 0](*string, fi->flag);
	left = i;
	arg->li = (long long)arg->i;
	arg->li = (((arg->li > 0) - 1) ^ arg->li) - ((arg->li > 0) - 1);
	(*string)[i++] = arg->li % 10 + '0';
	arg->li /= 10;
	while (arg->li)
	{
		(*string)[i++] = arg->li % 10 + '0';
		arg->li /= 10;
	}
	ft_strrev(*string, left, i - 1);
	return (i);
}

size_t uint_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	size_t	i;

	i = 0;
	(*string)[i++] = arg->u % 10 + '0';
	arg->u /= 10;
	while(arg->u)
	{
		(*string)[i++] = arg->u % 10 + '0';
		arg->u /= 10;
	}
	ft_strrev(*string, 0, i - 1);
	return (i);
}