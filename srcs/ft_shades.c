/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shades.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 21:24:10 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 21:24:48 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int
	ft_shader(int color, double divide)
{
	if (divide <= 1.)
		return (color);
	return (((int)(((0xFF0000 & color) >> 16) / divide) << 16)
		+ ((int)(((0x00FF00 & color) >> 8) / divide) << 8)
		+ ((int)((0x0000FF & color) / divide)));
}

unsigned char
	ft_shade(unsigned char oct, double divide, int idx)
{
	if (divide <= 1.)
		return (oct);
	return ((unsigned char)((int)((oct >> (idx << 3)) / divide) << (idx << 3)));
}
