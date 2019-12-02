/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_image.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 14:53:47 by adda-sil          #+#    #+#             */
/*   Updated: 2019/12/02 20:59:30 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_draw_sprite(t_game *game, t_sprite *spr, t_ipos draw, t_dpos draw_tex)
{
	unsigned int	color;
	t_ipos			draw_tex_pos;

	if (spr->frame_size.x > 0)
		draw_tex_pos = (t_ipos) {
			.x = (draw_tex.x * spr->frame_size.x) + (spr->index.x * spr->frame_size.x),
			.y = (draw_tex.y * spr->frame_size.y) + (spr->index.y * spr->frame_size.y)
		};
	else
		draw_tex_pos = (t_ipos) {
			.x = (draw_tex.x * spr->img.width),
			.y = (draw_tex.y * spr->img.height)
		};
	ft_transfert_pixel(&spr->img, draw_tex_pos, &(game->win.renderer), draw);
	// color = ft_get_pixel(spr, draw_tex_pos);
	// if (!game->collision)
	// 	color = color & 0x00FFFFFF ^ ft_get_pixel(&(game->win.renderer), draw);
	// if (color > 0)
	// 	ft_set_pixel(&(game->win.renderer), draw, color & 0x00FFFFFF);
}

int	ft_set_pixel(t_image *ptr, t_ipos pos, unsigned int color)
{
	int	index;
	int octets;
	
	octets = ptr->bits >> 3;
	index = (ptr->s_line * pos.y) + (octets * pos.x);
	while (--octets >= 0)
	{
		ptr->data[index++] = color & OCTET;
		color >>= 8;
	}
	return (SUCCESS);
}

unsigned int ft_get_pixel(t_image *ptr, t_ipos pos)
{
	int				index;
	unsigned int	color;
	int				octets;
	int				i;

	color = 0;
	i = -1;
	octets = ptr->bits >> 3;
	index = (ptr->s_line * pos.y) + (octets * pos.x);
	while (++i < octets - 1)
		color += ptr->data[index++] << (i << 3);
	return (color);
}

int	ft_transfert_pixel(t_image *from, t_ipos from_pos, t_image *to, t_ipos to_pos)
{
	t_ipos	oct;
	t_ipos	idx;
	int		i;
	double	alpha;

	oct.x = from->bits >> 3;
	oct.y = to->bits >> 3;
	idx.x = (from->s_line * from_pos.y) + (oct.x * from_pos.x);
	idx.y = (to->s_line * to_pos.y) + (oct.y * to_pos.x);
	i = -1;
	alpha = (unsigned char)from->data[idx.x + 3] / 255.0;
	while (++i < oct.y - 1)
	{
		to->data[idx.y + i] =
			(unsigned char)to->data[idx.y + i] * alpha
			+ (unsigned char)from->data[idx.x + i] * (1 - alpha);
	}
	return (SUCCESS);
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
