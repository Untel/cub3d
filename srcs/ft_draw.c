/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:33:46 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/12 21:31:55 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ft_adjust_drawer(t_game *game, t_drawer *drawer, int delta)
{
	if (drawer->delta > 0)
	{
		drawer->start += delta / 2;
		drawer->end -= delta / 2;
		drawer->posy += (drawer->step_posy * (delta / 2));
	}
	if (drawer->start < 0)
	{
		drawer->posy += (-drawer->start * drawer->step_posy);
		drawer->start = 0;
	}
	if (drawer->start > game->win.height)
		drawer->start = game->win.height;
	if (drawer->end < 0)
		drawer->end = 0;
	if (drawer->end > game->win.height)
		drawer->end = game->win.height;
}

int
	ft_init_drawer(t_game *game, t_drawer *drawer, double height)
{
	drawer->delta =	(height - 
		fabs(game->player.view + game->player.view2)) - game->win.height;
	if (game->player.view + game->player.view2 > 0)
		drawer->delta -= game->player.view + game->player.view2;
	else if (game->player.view + game->player.view2 < 0)
		drawer->delta += game->player.view + game->player.view2;
	drawer->step_posy = 1 / height;
	drawer->start = (game->win.height / 2 - height / 2)
		- game->player.view - game->player.view2;
	drawer->end = (game->win.height / 2 + height / 2)
		- game->player.view - game->player.view2;
	drawer->posy = 0;
	ft_adjust_drawer(game, drawer, drawer->delta);
	return (drawer->delta);
}

void
	ft_draw_column(t_game *game, int column, t_ray *ray, t_drawer *drawer)
{
    double		posy;
	t_ipos		draw;
	t_ipos		draw_tex;
	int			delta;

	draw.x = column;
	draw.y = 0;
	delta = ft_init_drawer(game, drawer, (game->win.height / ray->draw_dist / game->win.cos[column]));
	while (draw.y < drawer->start)
	{
		if (game->shading)
			ft_set_pixel(&(game->win.renderer), draw, ft_shader(game->env.CEIL, game->win.sky_dist[(draw.y + ((game->player.view2 + game->player.view) / 2))]))
				&& draw.y++;
		else
			ft_set_pixel(&(game->win.renderer), draw, game->env.CEIL) && draw.y++;
	}
    while (draw.y < drawer->end)
    {
		draw_tex.x = (int)(ray->po * drawer->texture->height);
		draw_tex.y = (int)(drawer->posy * drawer->texture->width);
		game->win.renderer.draw = draw;
		drawer->texture->draw = draw_tex;
		ft_transfert_pixel(drawer->texture, &(game->win.renderer), game->shading ? ray->draw_dist * 1.5 : 0);
        drawer->posy += drawer->step_posy;
		draw.y++;
    }
	while (draw.y < game->win.height)
		if (game->shading)
			ft_set_pixel(&(game->win.renderer), draw, ft_shader(game->env.FLOOR, game->win.sky_dist[game->win.height - (draw.y - (-(game->player.view2 + game->player.view) / 2))]))
				&& draw.y++;
		else
			ft_set_pixel(&(game->win.renderer), draw, game->env.FLOOR)
				&& draw.y++;
}

int	ft_draw_frame(t_game *game)
{
	int			column;
    t_ray		ray;
    t_drawer	drawer;

    column = 0;

	ft_draw_minimap(game);
	while (column < game->win.width)
    {
		game->player.plane.x = game->player.dir.x * game->win.cos[column] - game->player.dir.y * game->win.sin[column];
		game->player.plane.y = game->player.dir.y * game->win.cos[column] + game->player.dir.x * game->win.sin[column];
        init_ray(game, &ray);
        compute_ray(game, &ray);
        ray.draw_dist = (ray.vert ? ray.dist.y : ray.dist.x);
        ray.po = decim((ray.vert ? game->player.pos.x + ray.draw_dist * game->player.plane.x :
            game->player.pos.y + ray.draw_dist * game->player.plane.y));
   		if (ray.vert)
            drawer.texture = (game->player.pos.y < ray.pos.y ? &(game->env.SO) : &(game->env.NO));
        else
            drawer.texture = (game->player.pos.x < ray.pos.x ? &(game->env.EA) : &(game->env.WE));
		ft_draw_column(game, column, &ray, &drawer);
		ft_update_minimap(game, &ray);
		ft_draw_objects(game, column, &ray, &drawer);
		if (game->map.show_mega)
			ft_update_megamap(game, &ray);
        column++;
    }
	ft_hud(game);
}
