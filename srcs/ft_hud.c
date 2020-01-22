/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hud.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/01 03:47:19 by adda-sil          #+#    #+#             */
/*   Updated: 2020/01/19 19:32:16 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void
	ft_draw_health(t_game *game, t_ipos pos)
{
	t_ipos			draw;
	double			ratio;
	unsigned int	color;
	int				hp;
	char			txt[300];

	ratio = (double)game->p.hp / (double)(game->p.max_hp);
	hp = HEALTHBAR_WIDTH * ratio - 1;
	draw = (t_ipos){ .x = pos.x, .y = pos.y };
	if (ratio > .5)
		color = ratio > .75 ? GREEN : YELLOW;
	else
		color = ratio > 0.25 ? ORANGE : RED;
	while (draw.x++ < pos.x + hp && (draw.y = pos.y))
		while (draw.y++ < pos.y + HEALTHBAR_HEIGHT - 1)
			ft_draw_renderer(game, draw, color);
	ft_sprintf(txt, "%d/%d - %d%%", game->p.hp,
		game->p.max_hp, (int)(ratio * 100));
	ft_render(game);
	mlx_string_put(game->mlx, game->win.ref, pos.x + 5,
		pos.y + (HEALTHBAR_HEIGHT / 2 - 11), 0x0, txt);
}

void
	ft_healthbar(t_game *game)
{
	t_ipos	pos;
	t_ipos	draw;

	pos = (t_ipos){ .x = HEALTHBAR_PADDING,
		.y = game->map.mini.height + HEALTHBAR_PADDING };
	draw = (t_ipos){ .x = pos.x, .y = pos.y };
	while (draw.x++ < pos.x + HEALTHBAR_WIDTH)
		ft_draw_renderer(game, draw, HEALTHBAR_BORDER);
	draw = (t_ipos){ .x = pos.x, .y = pos.y + HEALTHBAR_HEIGHT };
	while (draw.x++ < pos.x + HEALTHBAR_WIDTH)
		ft_draw_renderer(game, draw, HEALTHBAR_BORDER);
	draw = (t_ipos){ .x = pos.x, .y = pos.y };
	while (draw.y++ < pos.y + HEALTHBAR_HEIGHT)
		ft_draw_renderer(game, draw, HEALTHBAR_BORDER);
	draw = (t_ipos){ .x = pos.x + HEALTHBAR_WIDTH, .y = pos.y };
	while (draw.y++ < pos.y + HEALTHBAR_HEIGHT)
		ft_draw_renderer(game, draw, HEALTHBAR_BORDER);
	ft_draw_health(game, pos);
}

void
	ft_weapon(t_game *game)
{
	t_ipos	start_draw;
	t_ipos	draw;
	t_dpos	draw_tex_step;
	t_dpos	draw_tex;
	int		pad;

	pad = (game->win.width / 3);
	draw = (t_ipos) { .x = game->win.width - pad + (pad / 10) - 1,
		.y = game->win.height - pad + (pad / 5) - 1 };
	start_draw = (t_ipos) { .x = draw.x + pad, .y = draw.y + pad};
	draw_tex_step = (t_dpos) { .x = (1 / (double)(start_draw.x - draw.x)),
		.y = (1 / (double)(start_draw.y - draw.y)) };
	draw_tex = (t_dpos) { 0, 0 };
	while ((draw_tex.y = 0) || (draw.x < start_draw.x
		&& ++draw.x < game->win.width))
	{
		draw.y = game->win.height - pad + (pad / 5);
		while (++draw.y < (start_draw.y) && draw.y < game->win.height)
		{
			game->win.renderer.draw = draw;
			ft_draw_sprite(game, &(game->weapon), draw_tex, 0);
			draw_tex.y += draw_tex_step.y;
		}
		draw_tex.x += draw_tex_step.x;
	}
}

void
	ft_draw_crosshair(t_game *game)
{
	t_ipos	pos;
	int		i;

	i = -1;
	pos.x = game->win.width / 2 - CH_RADIAN;
	pos.y = game->win.height / 2;
	while (pos.x++ < game->win.width / 2 + CH_RADIAN)
		ft_draw_renderer(game, pos, CH_COLOR);
	pos.x = game->win.width / 2;
	pos.y = game->win.height / 2 - CH_RADIAN;
	while (pos.y++ < game->win.height / 2 + CH_RADIAN)
		ft_draw_renderer(game, pos, CH_COLOR);
}

void
	ft_hud(t_game *game)
{
	if (game->hud)
	{
		ft_weapon(game);
		ft_draw_crosshair(game);
		ft_healthbar(game);
		mlx_put_image_to_window(game->mlx, game->win.ref,
			game->map.mini.ref, 0, 0);
	}
	else
		ft_render(game);
}
