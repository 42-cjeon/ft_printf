/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format_parser2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/21 04:41:22 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 05:45:50 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

const char	*process_max_len(const char *format, struct s_format_info *fi)
{
	size_t	max_len;

	max_len = 0;
	format++;
	format = atoi_size_t(format, &max_len);
	fi->max_len = max_len;
	fi->flag |= PRECISION;
	return (format);
}

const char	*process_min_len(const char *format, struct s_format_info *fi)
{
	size_t	min_len;

	min_len = 0;
	format = atoi_size_t(format, &min_len);
	fi->min_len = min_len;
	return (format);
}
