/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:29:51 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/17 19:49:16 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	draw_frame()
{
	int x;

	x = -1;
	while (++x < game.win.width)
    {
		//calculate ray position and direction
		double camera_x = 2 * x / (double)game.win.width - 1; //x-coordinate in camera space
		double ray_x = game.player.dir.x + game.player.plane.x * camera_x;
		double ray_y = game.player.dir.y + game.player.plane.y * camera_x;
		//which box of the map we're in
		int map_x = (int)game.player.pos.x;
		int map_y = (int)game.player.pos.y;

		//length of ray from current position to next x or y-side
		double side_dist_x;
		double side_dist_y;

		//length of ray from one x or y-side to next x or y-side
		double delta_dist_x = abs(1 / ray_x);
		double delta_dist_y = abs(1 / ray_y);
		double perp_wall_dist;

		//what direction to step in x or y-direction (either +1 or -1)
		int step_x;
		int step_y;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (ray_x < 0)
		{
			step_x = -1;
			side_dist_x = (game.player.pos.x - map_x) * delta_dist_x;
		}
		else
		{
			step_x = 1;
			side_dist_x = (map_x + 1.0 - game.player.pos.x) * delta_dist_x;
		}
		if (ray_y < 0)
		{
			step_y = -1;
			side_dist_y = (game.player.pos.y - map_y) * delta_dist_y;
		}
		else
		{
			step_y = 1;
			side_dist_y = (map_y + 1.0 - game.player.pos.y) * delta_dist_y;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (side_dist_x < side_dist_y)
			{
				side_dist_x += delta_dist_x;
				map_x += step_x;
				side = 0;
			}
			else
			{
				side_dist_y += delta_dist_y;
				map_y += step_y;
				side = 1;
			}
			//Check if ray has hit a wall
			if (game.map.grid[map_x][map_y] != EMPTY) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perp_wall_dist = (map_x - game.player.pos.x + (1 - step_x) / 2) / ray_x;
		else           perp_wall_dist = (map_y - game.player.pos.y + (1 - step_y) / 2) / ray_y;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(game.win.height / perp_wall_dist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game.win.height / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + game.win.height / 2;
		if (drawEnd >= game.win.height) drawEnd = game.win.height - 1;

		//choose wall color
		long color;
		switch(game.map.grid[map_x][map_y])
		{
			case 1:  color = 0xff0000; break; //red
			case 2:  color = (0x0000ff); break; //green
			case 3:  color = 0x0000ff; break; //blue
			case 4:  color = 0x00ffff; break; //white
			default: color = 0xff00ff; break; //yellow
		}

		if (game.map.grid[map_x][map_y] == 2)
		{
			color = ((x * 255) + 0x000000);
			while (color > 0xffffff)
				color -= color % 0xffffff;
		}

		//give x and y sides different brightness
		if (side == 1) {color = color * .8;}

		//draw the pixels of the stripe as a vertical line
		// verLine(x, drawStart, drawEnd, color);
		unsigned int t = 0;
		while (t++ <= drawStart)
			mlx_pixel_put(game.mlx, game.win.ref, x, t, game.env.CEIL);
		int realStart = drawStart;
		while (drawStart++ <= drawEnd)
		{
			int val = color;
			if (!(x % 50))
				val = 0xff00ff;
			mlx_pixel_put(game.mlx, game.win.ref, x, drawStart, val);
		}
		while (drawEnd++ <= game.win.height)
			mlx_pixel_put(game.mlx, game.win.ref, x, drawEnd, game.env.FLOOR);
	}


    //timing for input and FPS counter
    // oldTime = time;
    // time = getTicks();
    // print(1.0 / frameTime); //FPS counter
    // redraw();
    // cls();

    //speed modifiers
	return (1);
}

int	game_loop()
{
	char	txt[300];
	int		fps;

	*txt = 0;
	fps = 0;
	draw_frame();
	printf("%d, %");
	ft_sprintf(txt, "Fps:%d X:%d Y:%d -", fps, (int)game.player.pos.x, (int)game.player.pos.y);
	mlx_string_put(game.mlx, game.win.ref, 50, 50, 0xffffff, txt);
}

int	key_hook(int keycode, void *param)
{
	if (keycode == FORWARD)
		move_forward();
	else if (keycode == BACKWARD)
		move_backward();
	else if (keycode == STRAFE_LEFT)
		strafe_left();
	else if (keycode == STRAFE_RIGHT)
		strafe_right();
	else if (keycode == ROTATE_LEFT)
		rotate((game.player.rs));
	else if (keycode == ROTATE_RIGHT)
		rotate(-(game.player.rs));
	if (keycode == ESCAPE)
	{
		printf("destroying\n");
		mlx_clear_window(game.mlx, game.win.ref);
		mlx_destroy_window(game.mlx, game.win.ref);
		exit(0);
	}
	// SUC("Press %d\n", keycode);
	printf("Key %d, POS(%.2f, %.2f)\n", keycode, game.player.pos.x, game.player.pos.y);
	return (1);
}

int	keypress_hook()
{
	SUC("PRESS");
	return (1);
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)av;

	if (ft_args(ac, av) == ERROR)
		return (EXIT_FAILURE);
	system("leaks a.out");
	// return (0);
	if (!(game.mlx = mlx_init()))
		return (EXIT_FAILURE);
	if (!(game.win.ref = mlx_new_window(game.mlx, game.win.width, game.win.height, "Cub3d")))
		return (EXIT_FAILURE);
	SUC("RUNNING GAME\n");
	// mlx_do_key_autorepeatoff(game.mlx);
	
	mlx_hook(game.win.ref, 1, 4, keypress_hook, NULL);
	mlx_key_hook(game.win.ref, key_hook, NULL);
	// mlx_mouse_hook(game.win.ref, mouse_hook, NULL);
	// mlx_expose_hook(game.mlx, game, NULL);
	// mlx_mouse_get_pos(game.mlx);
	// draw_frame();
	mlx_loop_hook(game.mlx, game_loop, NULL);
    mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}