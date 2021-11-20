/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:38:51 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 03:16:59 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"


int	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

size_t min(size_t x, size_t y)
{
	size_t arr[2];

	arr[0] = x;
	arr[1] = y;
	return (arr[(x > y)]);
}

size_t max(size_t x, size_t y)
{
	size_t arr[2];

	arr[0] = x;
	arr[1] = y;
	return (arr[(x < y)]);
}

int int_selector(int when_false, int when_true, int select)
{
	int arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}

size_t size_selector(size_t when_false, size_t when_true, int select)
{
	size_t arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}

void *pointer_selector(void *when_false, void *when_true, int select)
{
	void *arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}

long long abs_64(long long x)
{
	return (0);
}

void init_si(struct s_string_info *si)
{
	si->left_sign = 0;
	si->prefix[0] = '\0';
	si->prefix[1] = '\0';
	si->prefix[2] = '\0';
	si->mid_padding = 0;
	si->total_len = 0;
	si->main_part = NULL;
}