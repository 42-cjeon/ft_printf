/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_stringf3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:48:10 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/20 19:13:16 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const static char * g_hex_low_digits = "0123456789abcdef";
const static char * g_hex_high_digits = "0123456789ABCDEF";

size_t pointer_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	size_t	i;
	size_t	left;

	i = 0;
	(*string)[i++] = '0';
	(*string)[i++] = 'x';
	(*string)[i++] = g_hex_low_digits[arg->p % 16];
	arg->p /= 16;
	while(arg->p)
	{
		(*string)[i++] = g_hex_low_digits[arg->p % 16];
		arg->p /= 16;
	}
	ft_strrev(*string, 2, i - 1);
	return (i);
}

size_t uhex_low_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	size_t	i;
	size_t	left;

	(*string)[0] = '0';
	(*string)[1] = 'x';
	i = (0 < (fi->flag & ALT_MOD)) * 2 * (arg->u != 0);
	left = i;
	(*string)[i++] = g_hex_low_digits[arg->u % 16];
	arg->u /= 16;
	while(arg->u)
	{
		(*string)[i++] = g_hex_low_digits[arg->u % 16];
		arg->u /= 16;
	}
	ft_strrev(*string, left, i - 1);
	return (i);
}

size_t uhex_high_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	size_t	i;
	size_t	left;
	(*string)[0] = '0';
	(*string)[1] = 'X';
	i = (0 < (fi->flag & ALT_MOD)) * 2 * (arg->u != 0);
	left = i;
	(*string)[i++] = g_hex_high_digits[arg->u % 16];
	arg->u /= 16;
	while(arg->u)
	{
		(*string)[i++] = g_hex_high_digits[arg->u % 16];
		arg->u /= 16;
	}
	ft_strrev(*string, left, i - 1);
	return (i);
}
