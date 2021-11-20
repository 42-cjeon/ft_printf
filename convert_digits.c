/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_digits.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 01:14:00 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 05:39:14 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static const t_itoa_ulong	g_itoa_ulong_next_function[2] = \
	{itoa_ulong, itoa_ulong_end};

int	itoa_ulong(char *buf, unsigned long long n, int base, \
				const char *base_digit)
{
	int	i;

	i = g_itoa_ulong_next_function[(n / base) == 0] \
										(buf, n / base, base, base_digit);
	buf[i] = base_digit[n % base];
	return (i + 1);
}

int	itoa_ulong_end(char *buf, unsigned long long n, int base, \
					const char *base_digit)
{
	(void)buf;
	(void)n;
	(void)base;
	(void)base_digit;
	return (0);
}

int	itoa_int(char *buf, int n)
{
	long long	k;

	k = n;
	k *= ((k >= 0) * 2 - 1);
	return (itoa_ulong(buf, (unsigned long long)k, 10, "0123456789"));
}

static const t_atoi_size_t	g_atoi_next_function[2] = \
	{atoi_size_t, end_atoi_size_t};

const char	*atoi_size_t(const char *format, size_t *result)
{
	*result = int_selector(*result, *result * 10 + (*format - '0'), \
														is_digit(*format));
	return (g_atoi_next_function[!is_digit(*format)](format + 1, result));
}

const char	*end_atoi_size_t(const char *format, size_t *result)
{
	(void)result;
	return (format - 1);
}
