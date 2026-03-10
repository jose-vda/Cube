/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:41:24 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/10 18:47:26 by jose-vda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_rect(t_img *img, int x0, int y0, int w, int h, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < h)
	{
		x = 0;
		while (x < w)
		{
			put_pixel(img, x0 + x, y0 + y, color);
			x++;
		}
		y++;
	}
}

void	clear_image(t_img *img, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			put_pixel(img, x, y, color);
			x++;
		}
		y++;
	}
}

void	draw_minimap(t_game *game)
{
	int		start_row;
	int		start_col;
	double	px;
	double	py;

	if (!game->show_minimap || !game->map)
		return ;
	start_row = (int)(game->player.y - 0.5) - MINIMAP_MAX_H / 2;
	start_col = (int)(game->player.x - 0.5) - MINIMAP_MAX_W / 2;
	if (start_row < 0)
		start_row = 0;
	if (start_col < 0)
		start_col = 0;
	draw_minimap_grid(game, start_row, start_col);
	px = MINIMAP_OFFSET_X + (game->player.x - 0.5 - start_col) * MINIMAP_TILE;
	py = MINIMAP_OFFSET_Y + (game->player.y - 0.5 - start_row) * MINIMAP_TILE;
	draw_rect(&game->img, (int)(px - 1), (int)(py - 1), 3, 3, MINIMAP_PLAYER);
}

static void	apply_flash_row(t_game *game, int y, int ar, int ag, int ab)
{
	int	x;
	int	c;
	int	r;
	int	g;
	int	b;

	x = 0;
	while (x < WIDTH)
	{
		c = *(unsigned int *)(game->img.addr + y * game->img.line_len
				+ x * (game->img.bpp / 8));
		r = ((c >> 16) & 0xFF) + ar;
		g = ((c >> 8) & 0xFF) + ag;
		b = (c & 0xFF) + ab;
		if (r > 255)
			r = 255;
		if (g > 255)
			g = 255;
		if (b > 255)
			b = 255;
		put_pixel(&game->img, x, y, (r << 16) | (g << 8) | b);
		x++;
	}
}

static void	apply_flash_pass(t_game *game, int add_r, int add_g, int add_b)
{
	int	y;

	y = 0;
	while (y < HEIGHT)
	{
		apply_flash_row(game, y, add_r, add_g, add_b);
		y++;
	}
}

static void	apply_damage_flash(t_game *game)
{
	apply_flash_pass(game, 80, 0, 0);
	game->damage_flash--;
}

static void	apply_pickup_flash(t_game *game)
{
	apply_flash_pass(game, 40, 40, 40);
	game->pickup_flash--;
}

void	apply_screen_effects(t_game *game)
{
	if (game->damage_flash > 0)
		apply_damage_flash(game);
	if (game->pickup_flash > 0)
		apply_pickup_flash(game);
}

void	draw_crosshair(t_game *game)
{
	int	cx;
	int	cy;
	int	i;

	cx = WIDTH / 2;
	cy = HEIGHT / 2;
	i = -2;
	while (i <= 2)
	{
		put_pixel(&game->img, cx + i, cy, 0x00FF00);
		put_pixel(&game->img, cx, cy + i, 0x00FF00);
		i++;
	}
}

void	draw_hud(t_game *game)
{
	if (game->paused || game->exit_reached)
		return ;
	if (game->map_name)
		mlx_string_put(game->mlx, game->win, 10, 10, HUD_COLOR, game->map_name);
	mlx_string_put(game->mlx, game->win, 10, 28, HUD_COLOR,
		game->has_key ? "Key: Yes" : "Key: No");
	mlx_string_put(game->mlx, game->win, 10, 46, HUD_COLOR,
		"Objective: Find the exit");
}

void	draw_pause_overlay(t_game *game)
{
	(void)game;
}

static void	render_overlay(t_game *game)
{
	if (game->exit_reached)
		mlx_string_put(game->mlx, game->win, WIDTH / 2 - 40, HEIGHT / 2 - 10,
			HUD_COLOR, "You Win!");
	else if (game->paused)
	{
		mlx_string_put(game->mlx, game->win, WIDTH / 2 - 40, HEIGHT / 2 - 20,
			HUD_COLOR, "PAUSED");
		mlx_string_put(game->mlx, game->win, WIDTH / 2 - 80, HEIGHT / 2 + 0,
			HUD_COLOR, "P - Resume  ESC - Quit");
	}
	else
		draw_hud(game);
}

int	render(t_game *game)
{
	ft_bzero(game->img.addr, (size_t)HEIGHT * game->img.line_len);
	raycasting(game);
	draw_minimap(game);
	apply_screen_effects(game);
	draw_crosshair(game);
	if (game->paused)
		draw_rect(&game->img, 0, 0, WIDTH, HEIGHT,
			(100 << 16) | (100 << 8) | 100);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	render_overlay(game);
	return (0);
}
