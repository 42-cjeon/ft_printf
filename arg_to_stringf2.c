/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_stringf2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:48:37 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/20 19:31:25 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	char_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	**string = arg->c;
	return (1);
}

size_t	percent_sign_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	**string = '%';
	return (1);
}

void copy_null(char *buf)
{
	*buf++ = '(';
	*buf++ = 'n';
	*buf++ = 'u';
	*buf++ = 'l';
	*buf++ = 'l';
	*buf++ = ')';
}

size_t	string_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	size_t len;
	size_t max_len;

	copy_null(*string);
	*string = pointer_selector(arg->s, *string, arg->s == NULL);
	len = 0;
	max_len = size_selector(~0U, fi->max_len, fi->flag & PRECISION);
	while ((*string)[len] && len < max_len)
		len++;
	return (len);
}