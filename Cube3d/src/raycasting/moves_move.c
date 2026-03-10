/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves_move.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23                                #+#    #+#             */
/*   Updated: 2026/02/23                                ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

static int	is_walkable(t_game *game, int my, int mx)
{
	if (my < 0 || my >= game->map_height || mx < 0 || mx >= game->map_width)
		return (0);
	if (mx >= ft_strlen(game->map[my]))
		return (0);
	if (game->map[my][mx] == '0')
		return (1);
	if (game->map[my][mx] == 'D' && door_is_open(game, my, mx))
		return (1);
	if (game->map[my][mx] == 'K' || game->map[my][mx] == 'X')
		return (1);
	if (game->map[my][mx] == 'P' && cell_is_pushed(game, my, mx))
		return (1);
	return (0);
}

static void	check_key_and_exit_at(t_game *game, double new_x, double new_y)
{
	int	mx;
	int	my;

	mx = (int)new_x;
	my = (int)new_y;
	if (my < 0 || my >= game->map_height || mx < 0 || mx >= game->map_width)
		return ;
	if (mx >= ft_strlen(game->map[my]))
		return ;
	if (game->map[my][mx] == 'K')
	{
		game->has_key = 1;
		game->map[my][mx] = '0';
		game->pickup_flash = PICKUP_FLASH_FRAMES;
	}
	if (game->map[my][mx] == 'X' && game->has_key)
		game->exit_reached = 1;
}

void	check_key_and_exit(t_game *game, double new_x, double new_y)
{
	check_key_and_exit_at(game, new_x, new_y);
}

void	do_move_forward(t_game *game, t_player *p, double speed)
{
	int	mx;
	int	my;

	mx = (int)(p->x + p->dir_x * speed);
	my = (int)p->y;
	if (is_walkable(game, my, mx))
		p->x += p->dir_x * speed;
	mx = (int)p->x;
	my = (int)(p->y + p->dir_y * speed);
	if (is_walkable(game, my, mx))
		p->y += p->dir_y * speed;
	check_key_and_exit_at(game, p->x, p->y);
}

void	do_move_back(t_game *game, t_player *p, double speed)
{
	int	mx;
	int	my;

	mx = (int)(p->x - p->dir_x * speed);
	my = (int)p->y;
	if (is_walkable(game, my, mx))
		p->x -= p->dir_x * speed;
	mx = (int)p->x;
	my = (int)(p->y - p->dir_y * speed);
	if (is_walkable(game, my, mx))
		p->y -= p->dir_y * speed;
	check_key_and_exit_at(game, p->x, p->y);
}

void	do_strafe_left(t_game *game, t_player *p, double speed)
{
	int	mx;
	int	my;

	mx = (int)(p->x - p->plane_x * speed);
	my = (int)p->y;
	if (is_walkable(game, my, mx))
		p->x -= p->plane_x * speed;
	mx = (int)p->x;
	my = (int)(p->y - p->plane_y * speed);
	if (is_walkable(game, my, mx))
		p->y -= p->plane_y * speed;
	check_key_and_exit_at(game, p->x, p->y);
}

void	do_strafe_right(t_game *game, t_player *p, double speed)
{
	int	mx;
	int	my;

	mx = (int)(p->x + p->plane_x * speed);
	my = (int)p->y;
	if (is_walkable(game, my, mx))
		p->x += p->plane_x * speed;
	mx = (int)p->x;
	my = (int)(p->y + p->plane_y * speed);
	if (is_walkable(game, my, mx))
		p->y += p->plane_y * speed;
	check_key_and_exit_at(game, p->x, p->y);
}
