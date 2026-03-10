/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_draw_fog.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static void	get_fog_params(t_game *g, double *fog_dist, int *fr, int *fg,
		int *fb)
{
	if (g->theme_sunny)
	{
		*fog_dist = FOG_DIST_SUNNY;
		*fr = FOG_R_SUNNY;
		*fg = FOG_G_SUNNY;
		*fb = FOG_B_SUNNY;
	}
	else
	{
		*fog_dist = FOG_DIST;
		*fr = FOG_R;
		*fg = FOG_G;
		*fb = FOG_B;
	}
}

static void	compute_fog_components(int color, int fog_r, int fog_g, int fog_b,
		double fog, int *fr, int *fg, int *fb)
{
	int	r;
	int	b;

	r = (color >> 16) & 0xFF;
	*fg = (color >> 8) & 0xFF;
	b = color & 0xFF;
	*fr = (int)(r * (1.0 - fog) + fog_r * fog);
	*fg = (int)(*fg * (1.0 - fog) + fog_g * fog);
	*fb = (int)(b * (1.0 - fog) + fog_b * fog);
	if (*fr > 255)
		*fr = 255;
	if (*fg > 255)
		*fg = 255;
	if (*fb > 255)
		*fb = 255;
}

int	apply_fog(t_game *g, int color, double perp_dist)
{
	double	fog;
	double	fog_dist;
	int		fog_r;
	int		fog_g;
	int		fog_b;
	int		fr;
	int		fg;
	int		fb;

	get_fog_params(g, &fog_dist, &fog_r, &fog_g, &fog_b);
	if (perp_dist >= fog_dist)
		return ((fog_r << 16) | (fog_g << 8) | fog_b);
	fog = perp_dist / fog_dist;
	if (fog > 1.0)
		fog = 1.0;
	compute_fog_components(color, fog_r, fog_g, fog_b, fog, &fr, &fg, &fb);
	return ((fr << 16) | (fg << 8) | fb);
}

int	apply_sunny_brighten(int color)
{
	int	r;
	int	g;
	int	b;

	r = ((color >> 16) & 0xFF) * 13 / 10;
	g = ((color >> 8) & 0xFF) * 13 / 10;
	b = (color & 0xFF) * 12 / 10;
	if (r > 255)
		r = 255;
	if (g > 255)
		g = 255;
	if (b > 255)
		b = 255;
	return ((r << 16) | (g << 8) | b);
}

int	apply_door_tint(int color)
{
	int	r;
	int	gr;
	int	b;

	r = ((color >> 16) & 0xFF) * 6 / 10;
	gr = ((color >> 8) & 0xFF) * 4 / 10;
	b = (color & 0xFF) * 3 / 10;
	return ((r << 16) | (gr << 8) | b);
}
