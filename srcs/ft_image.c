/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:53:47 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/28 23:13:43 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_set_pixel(t_image *ptr, t_ipos pos, unsigned int color)
{
	int	index;
	int octets;
	
	octets = ptr->bits >> 3;
	index = (ptr->s_line * pos.y) + (octets * pos.x);
	while (--octets >= 0)
	{
		ptr->data[index++] = color & 0xFF;
		color >>= 8;
	}
	return (SUCCESS);
}

unsigned int ft_get_pixel(t_image *ptr, t_ipos pos)
{
	int	index;
	unsigned int color;
	int octets;
	int	i;

	color = 0;
	i = -1;
	octets = ptr->bits >> 3;
	index = (ptr->s_line * pos.y) + (octets * pos.x);
	while (++i < octets - 1)
		color += ptr->data[index++] << (i << 3);
	return (color);
}

int	ft_generate_image(t_game *game, t_image *ptr, int w, int h)
{
	if (!(ptr->ref = mlx_new_image(game->mlx, w, h)))
		return (ERROR);
	ptr->width = w;
	ptr->height = h;
	if (!(ptr->data = mlx_get_data_addr(ptr->ref, &ptr->bits, &ptr->s_line, &ptr->endian)))
		return (ERROR);
	printf("Bpp %d, sline %d, endian %d\n", ptr->bits, ptr->s_line, ptr->endian);
	return (SUCCESS);
}
