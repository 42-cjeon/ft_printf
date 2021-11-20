/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_stringf1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:47:47 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/20 21:32:13 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "ft_printf.h"

int handle_positive_sign(unsigned int flag)
{
	char sign_char;
	int sign_space;

	sign_char = int_selector(' ', '+', flag & POS_SIGN);
	sign_space = (flag & POS_SIGN) || (flag & EMPTY_SPACE);
	write(1, &sign_char, sign_space);
	return (sign_space);
}

int handle_negative_sign(unsigned int flag)
{
	(void)flag;
	write(1, "-", 1);
	return (1);
}

static const t_sign_handlerf g_sign_handler_table[2] = \
{
	handle_positive_sign,
	handle_negative_sign
};

void int_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	char		sign;
	char		sign_left;
	size_t		i;

	sign = int_selector(int_selector('-', '\0', 0 <= arg->i), int_selector(' ', '+', fi->flag & POS_SIGN), (0 <= arg->i));
	sign_left = (fi->flag & RIGHT_ALIGN) && (fi->flag & ZERO_PAD);
	sign_space = g_sign_handler_table[arg->i < 0](fi->flag);
	i = 0;
	arg->li = (long long)arg->i;
	arg->li = (((arg->li > 0) - 1) ^ arg->li) - ((arg->li > 0) - 1);
	(*string)[i++] = arg->li % 10 + '0';

	arg->li /= 10;
	while (arg->li)
	{
		(*string)[i++] = arg->li % 10 + '0';
		arg->li /= 10;
	}
	ft_strrev(*string, 0, i - 1);
	return (i + sign_space);
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