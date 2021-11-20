/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeon <cjeon@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/19 01:38:51 by cjeon             #+#    #+#             */
/*   Updated: 2021/11/21 07:03:03 by cjeon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	is_digit(char c)
{
	return ('0' <= c && c <= '9');
}

int	int_selector(int when_false, int when_true, int select)
{
	int	arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}

size_t	size_selector(size_t when_false, size_t when_true, int select)
{
	size_t	arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}

void	*pointer_selector(void *when_false, void *when_true, int select)
{
	void	*arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}

ssize_t	ssize_selector(ssize_t when_false, ssize_t when_true, int select)
{
	ssize_t	arr[2];

	arr[0] = when_false;
	arr[1] = when_true;
	return (arr[select != 0]);
}
