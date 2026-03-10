/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	draw_textured_wall(t_game *g, int x, int draw_start, int draw_end,
		int line_height, int tex_id, int tex_x, int is_door, double perp_dist)
{
	double	step;
	double	tex_pos;
	int		y;
	int		tex_y;
	int		color;

	step = 1.0 * g->tex[tex_id].height / line_height;
	tex_pos = (draw_start - HEIGHT / 2 + line_height / 2) * step;
	y = draw_start;
	while (y < draw_end)
	{
		tex_y = (int)tex_pos & (g->tex[tex_id].height - 1);
		tex_pos += step;
		color = g->tex[tex_id].addr[tex_y * (g->tex[tex_id].line_len / 4)
			+ tex_x];
		if (is_door)
			color = apply_door_tint(color);
		color = apply_fog(g, color, perp_dist);
		if (g->theme_sunny)
			color = apply_sunny_brighten(color);
		put_pixel(&g->img, x, y, color);
		y++;
	}
}

void	draw_vertical_line(t_img *img, int x, int y_start, int y_end, int color)
{
	int	y;

	y = y_start;
	while (y < y_end)
	{
		put_pixel(img, x, y, color);
		y++;
	}
}
