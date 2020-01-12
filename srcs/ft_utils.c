/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 08:55:41 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 14:55:45 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	*ft_free(void *ptr, void *res)
{
	ft_memdel(&ptr);
	return (res);
}

void
	to_intpos(t_ipos *ret, t_dpos pos)
{
	ret->x = (int)pos.x;
	ret->y = (int)pos.y;
}

double
	decim(double val)
{
	return (val - (int)val);
}
