/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderization_effects.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 18:41:24 by jose-vda          #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

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
