/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_to_stringf2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:48:37 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/19 01:48:48 by cjeon            ###   ########.fr       */
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

size_t	string_to_string(char **string, union u_arg *arg, struct s_format_info *fi)
{
	*string = arg->s;
	return (min(ft_strlen(*string), fi->max_len));
}