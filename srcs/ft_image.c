/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:53:47 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/24 21:16:02 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_set_pixel(t_image *ptr, t_ipos pos, int color)
{
	int	index;

	index = (ptr->s_line * pos.y) + ((ptr->bits / 8) * pos.x);
	ptr->data[index++] = (char)((color) & 0xFF);
	ptr->data[index++] = (char)((color >>= 8) & 0xFF);
	ptr->data[index++] = (char)((color >>= 8) & 0xFF);
	// ptr->data[index++] = (char)(0x9f);
}

int	ft_get_pixel(t_image *ptr, t_ipos pos)
{
	int	index;
	int color;

	color = 0;
	index = (ptr->s_line * pos.y) + ((ptr->bits / 8) * pos.x);
	color += ptr->data[index++];
	color += ptr->data[index++] * 0xFF;
	color += ptr->data[index++] * 0xFF * 0xFF;
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
