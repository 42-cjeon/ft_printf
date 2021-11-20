/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 04:29:56 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 06:36:34 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_strnlen	g_strnlen_next_function[2] = {strnlen, end_strnlen};

size_t	strnlen(const char *str, size_t max_len)
{
	return (g_strnlen_next_function[(max_len < 1) || (*str == '\0')] \
				(str + 1, max_len - 1) + ((0 < max_len) && (*str != '\0')));
}

size_t	end_strnlen(const char *str, size_t max_len)
{
	(void)str;
	(void)max_len;
	return (0);
}

void	copy_null(char *buf)
{
	*buf++ = '(';
	*buf++ = 'n';
	*buf++ = 'u';
	*buf++ = 'l';
	*buf++ = 'l';
	*buf++ = ')';
	*buf = '\0';
}
