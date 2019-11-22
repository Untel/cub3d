/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:36:59 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/22 17:50:43 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	generate_texture(t_game *game)
{
	for(int x = 0; x < TEX_WIDTH; x++)
		for(int y = 0; y < TEX_HEIGHT; y++)
		{
			int xorcolor = (x * 256 / TEX_WIDTH) ^ (y * 256 / TEX_HEIGHT);
			//int xcolor = x * 256 / TEX_WIDTH;
			int ycolor = y * 256 / TEX_HEIGHT;
			int xycolor = y * 128 / TEX_HEIGHT + x * 128 / TEX_WIDTH;
			game->tex[0][TEX_WIDTH * y + x] = 65536 * 254 * (x != y && x != TEX_WIDTH - y); //flat red game->texture with black cross
			game->tex[1][TEX_WIDTH * y + x] = xycolor + 256 * xycolor + 65536 * xycolor; //sloped greyscale
			game->tex[2][TEX_WIDTH * y + x] = 256 * xycolor + 65536 * xycolor; //sloped yellow gradient
			game->tex[3][TEX_WIDTH * y + x] = xorcolor + 256 * xorcolor + 65536 * xorcolor; //xor greyscale
			game->tex[4][TEX_WIDTH * y + x] = 256 * xorcolor; //xor green
			game->tex[5][TEX_WIDTH * y + x] = 65536 * 192 * (x % 16 && y % 16); //red bricks
			game->tex[6][TEX_WIDTH * y + x] = 65536 * ycolor; //red gradient
			game->tex[7][TEX_WIDTH * y + x] = 128 + 256 * 128 + 65536 * 128; //flat grey game->texture
		}
}

// int	c3d_load_textures(t_game *game)
// {
// 	game->image[0].ref = mlx_png_file_to_image(
// 		game->mlx,
// 		game->env.NO,
// 		&(game->image[0].width),
// 		&(game->image[0].height));
// }
