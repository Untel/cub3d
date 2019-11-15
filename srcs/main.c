/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:29:51 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/15 14:31:40 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
// double time = 0; //time of current frame

int	game_loop()
{
	int x;

	// draw_floor();
	// draw_ceil();

	x = -1;
	while (++x < game.win.width)
    {
		//calculate ray position and direction
		double cameraX = 2 * x / (double)game.win.width - 1; //x-coordinate in camera space
		double rayDirX = dirX + planeX * cameraX;
		double rayDirY = dirY + planeY * cameraX;
		//which box of the map we're in
		int mapX = (int)game.player.x;
		int mapY = (int)game.player.y;

		//length of ray from current position to next x or y-side
		double sideDistX;
		double sideDistY;

		//length of ray from one x or y-side to next x or y-side
		double deltaDistX = abs(1 / rayDirX);
		double deltaDistY = abs(1 / rayDirY);
		double perpWallDist;

		//what direction to step in x or y-direction (either +1 or -1)
		int stepX;
		int stepY;

		int hit = 0; //was there a wall hit?
		int side; //was a NS or a EW wall hit?
		//calculate step and initial sideDist
		if (rayDirX < 0)
		{
			stepX = -1;
			sideDistX = (game.player.x - mapX) * deltaDistX;
		}
		else
		{
			stepX = 1;
			sideDistX = (mapX + 1.0 - game.player.x) * deltaDistX;
		}
		if (rayDirY < 0)
		{
			stepY = -1;
			sideDistY = (game.player.y - mapY) * deltaDistY;
		}
		else
		{
			stepY = 1;
			sideDistY = (mapY + 1.0 - game.player.y) * deltaDistY;
		}
		//perform DDA
		while (hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (sideDistX < sideDistY)
			{
				sideDistX += deltaDistX;
				mapX += stepX;
				side = 0;
			}
			else
			{
				sideDistY += deltaDistY;
				mapY += stepY;
				side = 1;
			}
			//Check if ray has hit a wall
			if (game.map.grid[mapX][mapY] == WALL) hit = 1;
		}
		//Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		if (side == 0) perpWallDist = (mapX - game.player.x + (1 - stepX) / 2) / rayDirX;
		else           perpWallDist = (mapY - game.player.y + (1 - stepY) / 2) / rayDirY;

		//Calculate height of line to draw on screen
		int lineHeight = (int)(game.win.height / perpWallDist);

		//calculate lowest and highest pixel to fill in current stripe
		int drawStart = -lineHeight / 2 + game.win.height / 2;
		if (drawStart < 0) drawStart = 0;
		int drawEnd = lineHeight / 2 + game.win.height / 2;
		if (drawEnd >= game.win.height) drawEnd = game.win.height - 1;

		//choose wall color
		long color;
		switch(game.map.grid[mapX][mapY])
		{
			case 1:  color = 0xff0000;  break; //red
			case 2:  color = 0x00ff00;  break; //green
			case 3:  color = 0x0000ff;   break; //blue
			case 4:  color = 0x00ffff;  break; //white
			default: color = 0xff00ff; break; //yellow
		}

		//give x and y sides different brightness
		if (side == 1) {color = color * .8;}

		//draw the pixels of the stripe as a vertical line
		// verLine(x, drawStart, drawEnd, color);
		unsigned int t = 0;
		while (t++ <= drawStart)
			mlx_pixel_put(game.mlx, game.win.ref, x, t++, game.env.CEIL);
		while (drawStart++ <= drawEnd)
			mlx_pixel_put(game.mlx, game.win.ref, x, drawStart, (!(x % 50) ? 0xffff00 : color));
		while (drawEnd++ <= game.win.height)
			mlx_pixel_put(game.mlx, game.win.ref, x, drawEnd, game.env.FLOOR);
    }
    //timing for input and FPS counter
    // oldTime = time;
    // time = getTicks();
    // double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // print(1.0 / frameTime); //FPS counter
    // redraw();
    // cls();

    //speed modifiers
    // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
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
	if (!(game.win.ref = mlx_new_window(game.mlx, game.win.width, game.win.height, *av)))
		return (EXIT_FAILURE);
	SUC("RUNNING GAME\n");
	mlx_loop_hook(game.mlx, game_loop, NULL);
    mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}