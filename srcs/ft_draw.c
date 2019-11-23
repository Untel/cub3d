/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:33:46 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/23 17:45:08 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"



int	draw_frame(t_game *game)
{

    // int			column;
    // t_ray		ray;
    // // t_drawer	drawer;

    // column = -1;
    // while (++column < game->win.width)
    // {
    //     game->player.dir.x = game->player.plane.x * game->map.table_cos[column] - game->player.plane.y * game->map.table_sin[column];
    //     game->player.dir.y = game->player.plane.y * game->map.table_cos[column] + game->player.plane.x * game->map.table_sin[column];
    //     init_ray(game, &ray);
    //     compute_ray(game, &ray);
    //     ray.dist = (ray.vert ? ray.disty : ray.distx);
    //     ray.pos = decimal_part((ray.vert ? game->player.pos.x + ray.dist * game->player.dir.x :
    //                             game->player.pos.y + ray.dist * game->player.dir.y));
	// 	ft_update_minimap(game, &ray);
    //     // if (ray.vert)
    //     //     drawer.index_texture = (game->player.dy2 > 0 ? SOUTH : NORTH);
    //     // else
    //     //     drawer.index_texture = (game->player.dx2 > 0 ? WEST : EAST);
    //     // draw_column(p, column, &ray, &drawer);
    //     // draw_all_objects(p, column, ray.lst_objects, &drawer);
    //     // ft_lstclear(ray.lst_objects);
    //     // free(ray.lst_objects);
    // }
	// return (0);

	// int x;

	// x = -1;
	// while (++x < game->win.width)
    // {
	// 	//calculate ray position and direction
	// 	double camera_x = 2 * x / (double)(game->win.width - 1); //x-coordinate in camera space
	// 	double ray_x = game->player.dir.x + game->player.plane.x * camera_x;
	// 	double ray_y = game->player.dir.y + game->player.plane.y * camera_x;
	// 	//which box of the map we're in
	// 	int map_x = (int)game->player.pos.x;
	// 	int map_y = (int)game->player.pos.y;

	// 	//length of ray from current position to next x or y-side
	// 	double side_dist_x;
	// 	double side_dist_y;

	// 	//length of ray from one x or y-side to next x or y-side
	// 	double delta_dist_x = abs(1 / ray_x);
	// 	double delta_dist_y = abs(1 / ray_y);
	// 	double perp_wall_dist;

	// 	//what direction to step in x or y-direction (either +1 or -1)
	// 	int step_x;
	// 	int step_y;

	// 	int hit = 0; //was there a wall hit?
	// 	int side; //was a NS or a EW wall hit?
	// 	//calculate step and initial sideDist
	// 	if (ray_x < 0)
	// 	{
	// 		step_x = -1;
	// 		side_dist_x = (game->player.pos.x - map_x) * delta_dist_x;
	// 	}
	// 	else
	// 	{
	// 		step_x = 1;
	// 		side_dist_x = (map_x + 1.0 - game->player.pos.x) * delta_dist_x;
	// 	}
	// 	if (ray_y < 0)
	// 	{
	// 		step_y = -1;
	// 		side_dist_y = (game->player.pos.y - map_y) * delta_dist_y;
	// 	}
	// 	else
	// 	{
	// 		step_y = 1;
	// 		side_dist_y = (map_y + 1.0 - game->player.pos.y) * delta_dist_y;
	// 	}
	// 	//perform DDA
	// 	while (hit == 0)
	// 	{
	// 		//jump to next map square, OR in x-direction, OR in y-direction
	// 		if (side_dist_x < side_dist_y)
	// 		{
	// 			side_dist_x += delta_dist_x;
	// 			map_x += step_x;
	// 			side = 0;
	// 		}
	// 		else
	// 		{
	// 			side_dist_y += delta_dist_y;
	// 			map_y += step_y;
	// 			side = 1;
	// 		}
	// 		//Check if ray has hit a wall
	// 		if (game->map.grid[map_x][map_y] != EMPTY) hit = 1;
	// 	}
	// 	//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
	// 	if (side == 0) perp_wall_dist = (map_x - game->player.pos.x + (1 - step_x) / 2) / ray_x;
	// 	else           perp_wall_dist = (map_y - game->player.pos.y + (1 - step_y) / 2) / ray_y;

	// 	//Calculate height of line to draw on screen
	// 	int lineHeight = (int)(game->win.height / perp_wall_dist);

	// 	//calculate lowest and highest pixel to fill in current stripe
	// 	int drawStart = -lineHeight / 2 + game->win.height / 2;
	// 	if (drawStart < 0) drawStart = 0;
	// 	int drawEnd = lineHeight / 2 + game->win.height / 2;
	// 	if (drawEnd >= game->win.height) drawEnd = game->win.height - 1;

	// 	int texNum = (int)(game->map.grid[map_x][map_y]) - 1; //1 subtracted from it so that texture 0 can be used!

	// 	//calculate value of wallX
	// 	double wallX; //where exactly the wall was hit
	// 	if (side == 0) wallX = game->player.pos.y + perp_wall_dist * ray_y;
	// 	else           wallX = game->player.pos.x + perp_wall_dist * ray_x;
	// 	wallX -= floor((wallX));

	// 	int texX = (int)(wallX * (double)TEX_WIDTH);
	// 	if(side == 0 && ray_x > 0) texX = TEX_WIDTH - texX - 1;
	// 	if(side == 1 && ray_y < 0) texX = TEX_WIDTH - texX - 1;
	// 	unsigned int t = 0;
	// 	while (t++ <= drawStart)
	// 		ft_draw_renderer(game, x, t, game->env.CEIL);
	// 	while(drawStart++ < drawEnd)
	// 	{
	// 		int y = drawStart;
	// 		int d = (y << 8) - (game->win.height << 7) + (lineHeight << 7);
	// 		int texY = ((d * TEX_HEIGHT) / lineHeight) >> 8;
	// 		uint32_t color = (game->tex)[texNum][TEX_HEIGHT * texY + texX];
	// 		if(side == 1) color = (color >> 1) & 8355711;
	// 		ft_draw_renderer(game, x, y, color);
	// 	}
	// 	while (drawEnd++ <= game->win.height)
	// 		ft_draw_renderer(game, x, drawEnd, game->env.FLOOR);
	// }
	return (1);
}


// void    *newobj(t_game *game, int x, int y)
// {
//     t_object *gameobj;

//     pobj = malloc(sizeof(t_object));
//     if (pobj == NULL)
//         return (NULL);
//     pobj->a = (double)x + 0.5;
//     pobj->b = (double)y + 0.5;
//     pobj->dist = dist(game->player.x, game->player.y, pobj->a, pobj->b);
//     pobj->angle = asin(((pobj->a - game->player.x) * game->player.dy2 * -1 +
//                         (pobj->b - game->player.y) * game->player.dx2) / pobj->dist);
//     pobj->pos = 0.5 + pobj->dist * tan(pobj->angle);
//     return ((void*)pobj);
// }



// int        get_pixel(t_img *img, double posx, double posy)
// {
//     int posx2;
//     int posy2;
//     int width;

//     width = img->width;
//     posx2 = (int)(posx * (double)width);
//     posy2 = (int)(posy * (double)img->height);
//     return (img->data[width * posy2 + posx2]);
// }

// void    draw_column(t_game *game, int column, t_ray *ray, t_drawer *pdrawer)
// {
//     int            line;
//     double        posy;
//     double        height;

//     height = game->win.height / ray->dist / game->table_cos[column];
//     pdrawer->start = game->win.height / 2 - height / 2;
//     pdrawer->start = fmax(pdrawer->start, 0);
//     pdrawer->end = game->win.height / 2 + height / 2;
//     pdrawer->end = fmin(pdrawer->end, game->win.height - 1);
//     pdrawer->step_posy = 1 / ((double)(pdrawer->end - pdrawer->start));
//     line = -1;
//     while (++line < pdrawer->start)
//         game->mlx.img.data[game->win.width * line + column] = game->player.colors_int[FLOOR];
//     posy = 0;
//     while (++line < pdrawer->end)
//     {
//         game->mlx.img.data[game->player.win_width * line + column] =
//             get_pixel(&game->player.textures[pdrawer->index_texture], pray->pos, posy);
//         posy += pdrawer->step_posy;
//     }
//     while (++line < game->player.win_height)
//         game->player.mlx.img.data[game->player.win_width * line + column] = game->player.colors_int[CEILING];
// }

// void    draw_object(t_params *p, int column, char *content, t_drawer *pdrawer)
// {
//     t_object    *pobj;
//     int            line;
//     double        posy;
//     double        height;
//     int            pix;

//     pobj = (t_object*)content;
//     if (pobj->pos <= 0 || pobj->pos >= 1)
//         return ;
//     height = game->player.win_height / pobj->dist;
//     pdrawer->start = game->player.win_height / 2 - height / 2;
//     pdrawer->start = fmax(pdrawer->start, 0);
//     pdrawer->end = game->player.win_height / 2 + height / 2;
//     pdrawer->end = fmin(pdrawer->end, game->player.win_height - 1);
//     pdrawer->step_posy = 1 / ((double)(pdrawer->end - pdrawer->start));
//     line = pdrawer->start;
//     posy = 0;
//     while (++line < pdrawer->end)
//     {
//         pix = get_pixel(&game->player.textures[SPRITE], pobj->pos, posy);
//         if (((pix >> 24) & 0xFF) < 128)
//             game->player.mlx.img.data[game->player.win_width * line + column] = pix;
//         posy += pdrawer->step_posy;
//     }
// }
