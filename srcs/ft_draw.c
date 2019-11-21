/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:33:46 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/21 15:12:11 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// int	draw_frame(t_game *game)
// {
// 	int x;

// 	x = -1;
// 	while (++x < game->win.width)
//     {
// 		//calculate ray position and direction
// 		double camera_x = 2 * x / (double)(game->win.width - 1); //x-coordinate in camera space
// 		double ray_x = game->player.dir.x + game->player.plane.x * camera_x;
// 		double ray_y = game->player.dir.y + game->player.plane.y * camera_x;
// 		//which box of the map we're in
// 		int map_x = (int)game->player.pos.x;
// 		int map_y = (int)game->player.pos.y;

// 		//length of ray from current position to next x or y-side
// 		double side_dist_x;
// 		double side_dist_y;

// 		//length of ray from one x or y-side to next x or y-side
// 		double delta_dist_x = abs(1 / ray_x);
// 		double delta_dist_y = abs(1 / ray_y);
// 		double perp_wall_dist;

// 		//what direction to step in x or y-direction (either +1 or -1)
// 		int step_x;
// 		int step_y;

// 		int hit = 0; //was there a wall hit?
// 		int side; //was a NS or a EW wall hit?
// 		//calculate step and initial sideDist
// 		if (ray_x < 0)
// 		{
// 			step_x = -1;
// 			side_dist_x = (game->player.pos.x - map_x) * delta_dist_x;
// 		}
// 		else
// 		{
// 			step_x = 1;
// 			side_dist_x = (map_x + 1.0 - game->player.pos.x) * delta_dist_x;
// 		}
// 		if (ray_y < 0)
// 		{
// 			step_y = -1;
// 			side_dist_y = (game->player.pos.y - map_y) * delta_dist_y;
// 		}
// 		else
// 		{
// 			step_y = 1;
// 			side_dist_y = (map_y + 1.0 - game->player.pos.y) * delta_dist_y;
// 		}
// 		//perform DDA
// 		while (hit == 0)
// 		{
// 			//jump to next map square, OR in x-direction, OR in y-direction
// 			if (side_dist_x < side_dist_y)
// 			{
// 				side_dist_x += delta_dist_x;
// 				map_x += step_x;
// 				side = 0;
// 			}
// 			else
// 			{
// 				side_dist_y += delta_dist_y;
// 				map_y += step_y;
// 				side = 1;
// 			}
// 			//Check if ray has hit a wall
// 			if (game->map.grid[map_x][map_y] != EMPTY) hit = 1;
// 		}
// 		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
// 		if (side == 0) perp_wall_dist = (map_x - game->player.pos.x + (1 - step_x) / 2) / ray_x;
// 		else           perp_wall_dist = (map_y - game->player.pos.y + (1 - step_y) / 2) / ray_y;

// 		//Calculate height of line to draw on screen
// 		int lineHeight = (int)(game->win.height / perp_wall_dist);

// 		//calculate lowest and highest pixel to fill in current stripe
// 		int drawStart = -lineHeight / 2 + game->win.height / 2;
// 		if (drawStart < 0) drawStart = 0;
// 		int drawEnd = lineHeight / 2 + game->win.height / 2;
// 		if (drawEnd >= game->win.height) drawEnd = game->win.height - 1;

// 		// //choose wall color
// 		// long color;
// 		// switch(game->map.grid[map_x][map_y])
// 		// {
// 		// 	case 1:  color = 0xff0000; break; //red
// 		// 	case 2:  color = 0x0000ff; break; //green
// 		// 	case 3:  color = 0x0000ff; break; //blue
// 		// 	case 4:  color = 0x00ffff; break; //white
// 		// 	default: color = 0xff00ff; break; //yellow
// 		// }
// 		// uint32_t buffer[MAX_HEIGHT][MAX_WIDTH];
// 		// for(int x = 0; x < game->win.width; x++) for(int y = 0; y < game->win.height; y++) buffer[y][x] = 0;
// 		// if (game->map.grid[map_x][map_y] == 2)
// 		// {
// 		// 	color = ((x * 255) + 0x000000);
// 		// 	while (color > 0xffffff)
// 		// 		color -= color % 0xffffff;
// 		// }

// 		// //give x and y sides different brightness
// 		// if (side == 1) {color = color * .8;}

// 		// //draw the pixels of the stripe as a vertical line
// 		// // verLine(x, drawStart, drawEnd, color);
// 		// unsigned int t = 0;
// 		// while (t++ <= drawStart)
// 		// 	mlx_pixel_put(game->mlx, game->win.ref, x, t, game->env.CEIL);
// 		// int realStart = drawStart;
// 		// while (drawStart++ <= drawEnd)
// 		// {
// 		// 	int val = color;
// 		// 	if (!(x % 50))
// 		// 		val = 0xff00ff;
// 		// 	mlx_pixel_put(game->mlx, game->win.ref, x, drawStart, val);
// 		// }
// 		// while (drawEnd++ <= game->win.height)
// 		// 	mlx_pixel_put(game->mlx, game->win.ref, x, drawEnd, game->env.FLOOR);

//       //texturing calculations
// 		int texNum = (int)(game->map.grid[map_x][map_y]) - 1; //1 subtracted from it so that texture 0 can be used!

// 		//calculate value of wallX
// 		double wallX; //where exactly the wall was hit
// 		if (side == 0) wallX = game->player.pos.y + perp_wall_dist * ray_y;
// 		else           wallX = game->player.pos.x + perp_wall_dist * ray_x;
// 		wallX -= floor((wallX));

// 		//x coordinate on the texture
// 		int texX = (int)(wallX * (double)TEX_WIDTH);
// 		if(side == 0 && ray_x > 0) texX = TEX_WIDTH - texX - 1;
// 		if(side == 1 && ray_y < 0) texX = TEX_WIDTH - texX - 1;
// 		unsigned int t = 0;
// 		while (t++ <= drawStart)
// 			mlx_pixel_put(game->mlx, game->win.ref, x, t, game->env.CEIL);
// 		for(int y = drawStart; y < drawEnd; y++)
// 		{
// 			int d = y * 256 - game->win.height * 128 + lineHeight * 128;  //256 and 128 factors to avoid floats
// 			// TODO: avoid the division to speed this up
// 			int texY = ((d * TEX_HEIGHT) / lineHeight) / 256;
// 			uint32_t color = game->texture[texNum][TEX_HEIGHT * texY + texX];
// 			//make color darker for y-sides: R, G and B byte each divided through two with a "shift" and an "and"
// 			if(side == 1) color = (color >> 1) & 8355711;
// 			// buffer[y][x] = color;
// 			mlx_pixel_put(game->mlx, game->win.ref, x, y, color);
// 		}
// 		while (drawEnd++ <= game->win.height)
// 			mlx_pixel_put(game->mlx, game->win.ref, x, drawEnd, game->env.FLOOR);
// 		// while (drawStart++ <= drawEnd)
// 		// {
// 		// }
// 	}
// 	return (1);
// }

// void    init_ray(t_game *game, t_ray *ray)
// {
//     ray->x = (int)game->player.pos.x;
//     ray->y = (int)game->player.pos.y;
//     ray->stepx = (game->dx2 >= 0 ? 1 : -1);
//     ray->stepy = (game->dy2 >= 0 ? 1 : -1);
//     ray->step_distx = sqrt(1 + (p->dy2 * p->dy2) / (p->dx2 * p->dx2));
//     ray->step_disty = sqrt(1 + (p->dx2 * p->dx2) / (p->dy2 * p->dy2));
//     ray->distx = ray->step_distx *
//         (p->dx2 >= 0 ? 1. - (p->x - (double)ray->x) :
//         (p->x - (double)ray->x));
//     ray->disty = ray->step_disty *
//         (p->dy2 >= 0 ? 1. - (p->y - (double)ray->y) :
//         (p->y - (double)ray->y));
//     ray->vert = (ray->distx >= ray->disty);
//     ray->lst_objects = NULL;
// }

// void    *newobj(t_game *game, int x, int y)
// {
//     t_object *gameobj;

//     pobj = malloc(sizeof(t_object));
//     if (pobj == NULL)
//         return (NULL);
//     pobj->a = (double)x + 0.5;
//     pobj->b = (double)y + 0.5;
//     pobj->dist = dist(p->x, p->y, pobj->a, pobj->b);
//     pobj->angle = asin(((pobj->a - p->x) * p->dy2 * -1 +
//                         (pobj->b - p->y) * p->dx2) / pobj->dist);
//     pobj->pos = 0.5 + pobj->dist * tan(pobj->angle);
//     return ((void*)pobj);
// }

// void    compute_ray(t_game *game, t_ray *ray)
// {
//     int    i;

//     i = -1;
//     while (++i < 100)
//     {
//         if (ray->distx < pray->disty)
//         {
//             ray->vert = 0;
//             ray->x += pray->stepx;
//             if (game->map.grid[ray->y][ray->x] != '1')
//                 pray->distx += pray->step_distx;
//         }
//         else
//         {
//             ray->vert = 1;
//             ray->y += ray->stepy;
//             if (game->map.grid[ray->y][ray->x] != '1')
//                 pray->disty += pray->step_disty;
//         }
//         // if (p->map[pray->y][pray->x] == '2')
//         //     ft_lstadd_front(pray->lst_objects, newobj(p, pray->x, pray->y));
//         if (p->map[pray->y][pray->x] == '1')
//             break ;
//     }
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
//         game->mlx.img.data[game->win.width * line + column] = p->colors_int[FLOOR];
//     posy = 0;
//     while (++line < pdrawer->end)
//     {
//         game->mlx.img.data[p->win_width * line + column] =
//             get_pixel(&p->textures[pdrawer->index_texture], pray->pos, posy);
//         posy += pdrawer->step_posy;
//     }
//     while (++line < p->win_height)
//         p->mlx.img.data[p->win_width * line + column] = p->colors_int[CEILING];
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
//     height = p->win_height / pobj->dist;
//     pdrawer->start = p->win_height / 2 - height / 2;
//     pdrawer->start = fmax(pdrawer->start, 0);
//     pdrawer->end = p->win_height / 2 + height / 2;
//     pdrawer->end = fmin(pdrawer->end, p->win_height - 1);
//     pdrawer->step_posy = 1 / ((double)(pdrawer->end - pdrawer->start));
//     line = pdrawer->start;
//     posy = 0;
//     while (++line < pdrawer->end)
//     {
//         pix = get_pixel(&p->textures[SPRITE], pobj->pos, posy);
//         if (((pix >> 24) & 0xFF) < 128)
//             p->mlx.img.data[p->win_width * line + column] = pix;
//         posy += pdrawer->step_posy;
//     }
// }
