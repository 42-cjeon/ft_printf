/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_helper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 04:44:29 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 06:00:35 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

ssize_t	print_left_sign(const struct s_string_info *si)
{
	return (write(1, si->prefix, si->left_sign != 0));
}

ssize_t	print_prefix(const struct s_string_info *si)
{
	ssize_t	ret;

	ret = write(1, si->prefix, (si->prefix[0] != '\0') \
								&& (si->left_sign == 0));
	ret += write(1, si->prefix + 1, (si->prefix[1] != '\0') \
									&& (si->left_sign == 0));
	return (ret);
}

const static t_putchar_repeat	g_putchar_repeat_next_function[2] = \
									{putchar_repeat, end_putchar_repeat};

ssize_t	putchar_repeat(char c, size_t r)
{
	ssize_t	ret;

	ret = write(1, &c, r != 0);
	return (g_putchar_repeat_next_function[r == 0](c, r - 1) + ret);
}

ssize_t	end_putchar_repeat(char c, size_t r)
{
	(void)c;
	(void)r;
	return (0);
}

size_t	calc_main_part_len(struct s_string_info *si)
{
	size_t	total_len;

	total_len = si->total_len;
	total_len -= (si->prefix[0] != '\0');
	total_len -= (si->prefix[1] != '\0');
	total_len -= si->mid_padding;
	return (total_len);
}
