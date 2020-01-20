/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 21:33:46 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/20 17:56:20 by adda-sil         ###   ########.fr       */
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
	drawer->delta = (height - abs(game->p.view
		+ game->p.view2)) - game->win.height;
	if (game->p.view + game->p.view2 > 0)
		drawer->delta -= game->p.view + game->p.view2;
	else if (game->p.view + game->p.view2 < 0)
		drawer->delta += game->p.view + game->p.view2;
	drawer->step_posy = 1 / height;
	drawer->start = (game->win.height / 2 - height / 2)
		- game->p.view - game->p.view2;
	drawer->end = (game->win.height / 2 + height / 2)
		- game->p.view - game->p.view2;
	drawer->posy = 0;
	ft_adjust_drawer(game, drawer, drawer->delta);
	return (drawer->delta);
}

void
	ft_draw_column(t_game *g, int column, t_ray *ray, t_drawer *drawer)
{
	t_ipos		d;
	t_ipos		dt;
	int			de;

	d = (t_ipos) { .x = column, .y = 0 };
	de = ft_init_drawer(g, drawer,
		(g->win.height / ray->draw_dist / g->win.cos[column]));
	ft_draw_sky(g, drawer, &d);
	while (d.y < drawer->end)
	{
		dt.x = (int)(ray->po * drawer->tex->height);
		dt.y = (int)(drawer->posy * drawer->tex->width);
		g->win.renderer.draw = d;
		drawer->tex->draw = dt;
		ft_transfert_pixel(drawer->tex,
			&(g->win.renderer), g->shading ? ray->draw_dist * 1.5 : 0);
		drawer->posy += drawer->step_posy;
		d.y++;
	}
	ft_draw_floor(g, &d);
}

void
	ft_draw_frame(t_game *game)
{
	int			c;
	t_ray		r;
	t_drawer	d;

	c = 0;
	ft_draw_minimap(game);
	while (c < game->win.width)
	{
		game->p.plane = (t_dpos) { .x = game->p.dir.x * game->win.cos[c]
			- game->p.dir.y * game->win.sin[c], .y = game->p.dir.y
			* game->win.cos[c] + game->p.dir.x * game->win.sin[c] };
		init_ray(game, &r);
		ft_compute_ray(game, &r);
		if (r.vert)
			d.tex = game->p.pos.y < r.pos.y ? &game->env.so : &game->env.no;
		else
			d.tex = game->p.pos.x < r.pos.x ? &game->env.ea : &game->env.we;
		ft_draw_column(game, c, &r, &d);
		ft_update_minimap(game, &r);
		ft_draw_objects(game, c, &r, &d);
		if (game->map.show_mega)
			ft_update_megamap(game, &r);
		c++;
	}
	ft_hud(game);
}
