/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_rot.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

void	do_rotation(t_player *p, t_keys *k)
{
	double	rot;
	double	old_dir_x;
	double	old_plane_x;

	rot = 0;
	if (k->left)
		rot = -p->rot_speed;
	if (k->right)
		rot = p->rot_speed;
	if (rot == 0)
		return ;
	old_dir_x = p->dir_x;
	old_plane_x = p->plane_x;
	p->dir_x = p->dir_x * cos(rot) - p->dir_y * sin(rot);
	p->dir_y = old_dir_x * sin(rot) + p->dir_y * cos(rot);
	p->plane_x = p->plane_x * cos(rot) - p->plane_y * sin(rot);
	p->plane_y = old_plane_x * sin(rot) + p->plane_y * cos(rot);
}

void	update_player(t_game *game)
{
	t_player	*p;
	t_keys		*k;
	double		speed;

	if (game->paused)
		return ;
	p = &game->player;
	k = &game->keys;
	speed = p->move_speed;
	if (k->w)
		do_move_forward(game, p, speed);
	if (k->s)
		do_move_back(game, p, speed);
	if (k->a)
		do_strafe_left(game, p, speed);
	if (k->d)
		do_strafe_right(game, p, speed);
	do_rotation(p, k);
}
