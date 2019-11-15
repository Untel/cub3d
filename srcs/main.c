/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adda-sil <adda-sil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 05:29:51 by adda-sil          #+#    #+#             */
/*   Updated: 2019/11/15 19:34:26 by adda-sil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double dirX = -1, dirY = 0; //initial direction vector
double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
int	draw_frame()
{
	int x;

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
			case 1:  color = 0xff0000; break; //red
			case 2:  color = 0x00ff00; break; //green
			case 3:  color = 0x0000ff; break; //blue
			case 4:  color = 0x00ffff; break; //white
			default: color = 0xff00ff; break; //yellow
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
	char txt[300];
	*txt = 0;
	// draw_frame();
	ft_sprintf(txt, "Fps: X:%d Y:%d -", (int)game.player.x, (int)game.player.y);
    // double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
    // double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
    // double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
	mlx_string_put(game.mlx, game.win.ref, 50, 50, 0xffffff, txt);
	draw_frame();
}
int moveSpeed = 1.3;
int rotSpeed = 1;

int	move_forward()
{
	if(game.map.grid[(int)(game.player.x + dirX * moveSpeed)][(int)game.player.y] == EMPTY)
		game.player.x += (dirX * moveSpeed);
	if(game.map.grid[(int)game.player.x][(int)(game.player.y + dirY * moveSpeed)] == EMPTY)
		game.player.y += (dirY * moveSpeed);
}

int	move_backward()
{
	if(game.map.grid[(int)(game.player.x - dirX * moveSpeed)][(int)game.player.y] == EMPTY)
		game.player.x -= (dirX * moveSpeed);
	if(game.map.grid[(int)game.player.x][(int)(game.player.y - dirY * moveSpeed)] == EMPTY)
		game.player.y -= (dirY * moveSpeed);
}


int rotate(int deg)
{
	double oldDirX = dirX;
	dirX = dirX * cos(deg) - dirY * sin(deg);
	dirY = oldDirX * sin(deg) + dirY * cos(deg);
	double oldPlaneX = planeX;
	planeX = planeX * cos(deg) - planeY * sin(deg);
	planeY = oldPlaneX * sin(deg) + planeY * cos(deg);
}
int	key_hook(int keycode, void *param)
{
	if (keycode == FORWARD)
		move_forward();
	else if (keycode == BACKWARD)
		move_backward();
	else if (keycode == STRAFE_LEFT)
		if(game.map.grid[(int)(game.player.x)][(int)(game.player.y + dirY * moveSpeed)] == EMPTY) game.player.y += (dirY * moveSpeed);
      	// if(game.map.grid[(int)game.player.x][(int)(game.player.y - dirY * moveSpeed)] == EMPTY) game.player.y += dirY * moveSpeed;
	else if (keycode == STRAFE_RIGHT)
		if(game.map.grid[(int)(game.player.x - dirX * moveSpeed)][(int)game.player.y] == EMPTY) game.player.x -= (dirX * moveSpeed);
      	// if(game.map.grid[(int)game.player.x][(int)(game.player.y - dirY * moveSpeed)] == EMPTY) game.player.y -= dirY * moveSpeed;
	else if (keycode == ROTATE_LEFT)
		rotate(-rotSpeed);
	else if (keycode == ROTATE_RIGHT)
		rotate(rotSpeed);
	if (keycode == ESCAPE)
	{
		printf("destroying\n");
		mlx_clear_window(game.mlx, game.win.ref);
		mlx_destroy_window(game.mlx, game.win.ref);
	}
	// SUC("Press %d\n", keycode);
	printf("Key %d, POS(%.2f, %.2f)\n", keycode, game.player.x, game.player.y);
	return (1);
}

int	mouse_hook(int button, int x, int y, void *param)
{
	// SUC("Press b%d x%d y%d\n", button, x, y);
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
	draw_frame();
	mlx_do_key_autorepeaton(game.mlx);
	mlx_key_hook(game.win.ref, key_hook, NULL);
	mlx_mouse_hook(game.win.ref, mouse_hook, NULL);
	// mlx_expose_hook(game.mlx, game, NULL);
	// mlx_mouse_get_pos(game.mlx);
	mlx_loop_hook(game.mlx, game_loop, NULL);
    mlx_loop(game.mlx);
	return (EXIT_SUCCESS);
}