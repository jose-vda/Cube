/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jose-vda <jose-vda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:53:02 by josevictord       #+#    #+#             */
/*   Updated: 2026/02/12 19:34:18 by jose-vda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube.h"

#ifdef __APPLE__
# define KEY_W      13
# define KEY_A      0
# define KEY_S      1
# define KEY_D      2
# define KEY_LEFT   123
# define KEY_RIGHT  124
# define KEY_ESC    53
# define KEY_E      14
# define KEY_M      46
# define KEY_TAB    48
# define KEY_SHIFT_LEFT 56
# define KEY_SPACE  49
# define KEY_P      35
#else
# define KEY_W      119
# define KEY_A      97
# define KEY_S      115
# define KEY_D      100
# define KEY_LEFT   65361
# define KEY_RIGHT  65363
# define KEY_ESC    65307
# define KEY_E      101
# define KEY_M      109
# define KEY_TAB    65289
# define KEY_SHIFT_LEFT 65505
# define KEY_SPACE  32
# define KEY_P      112
#endif

static void	key_press_movement(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 1;
	if (keycode == KEY_A)
		game->keys.a = 1;
	if (keycode == KEY_S)
		game->keys.s = 1;
	if (keycode == KEY_D)
		game->keys.d = 1;
	if (keycode == KEY_LEFT)
		game->keys.left = 1;
	if (keycode == KEY_RIGHT)
		game->keys.right = 1;
}

static void	key_press_actions(int keycode, t_game *game)
{
	int	mx_e;
	int	my_e;

	if (keycode == KEY_ESC)
		close_window(game);
	if (keycode == KEY_TAB && game->player.move_speed < 0.20)
		game->player.move_speed += 0.02;
	if (keycode == KEY_SHIFT_LEFT && game->player.move_speed > 0.02)
		game->player.move_speed -= 0.02;
	if (keycode == KEY_M)
		game->show_minimap = !game->show_minimap;
	if (keycode == KEY_SPACE)
		game->theme_sunny = !game->theme_sunny;
	if (keycode == KEY_P)
		game->paused = !game->paused;
	if (keycode == KEY_E)
	{
		mx_e = (int)(game->player.x + game->player.dir_x * 0.6);
		my_e = (int)(game->player.y + game->player.dir_y * 0.6);
		toggle_door_at(game, my_e, mx_e);
		push_wall_at(game, my_e, mx_e);
	}
}

int	key_press(int keycode, t_game *game)
{
	key_press_movement(keycode, game);
	key_press_actions(keycode, game);
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->keys.w = 0;
	if (keycode == KEY_A)
		game->keys.a = 0;
	if (keycode == KEY_S)
		game->keys.s = 0;
	if (keycode == KEY_D)
		game->keys.d = 0;
	if (keycode == KEY_LEFT)
		game->keys.left = 0;
	if (keycode == KEY_RIGHT)
		game->keys.right = 0;
	return (0);
}

static void	apply_mouse_rotation(t_game *game, double rot)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.plane_x;
	game->player.dir_x = game->player.dir_x * cos(rot)
		- game->player.dir_y * sin(rot);
	game->player.dir_y = old_dir_x * sin(rot)
		+ game->player.dir_y * cos(rot);
	game->player.plane_x = game->player.plane_x * cos(rot)
		- game->player.plane_y * sin(rot);
	game->player.plane_y = old_plane_x * sin(rot)
		+ game->player.plane_y * cos(rot);
}

int	mouse_move(int x, int y, void *param)
{
	t_game	*game;
	int		delta;
	double	rot;

	(void)y;
	game = (t_game *)param;
	if (game->mouse_last_x < 0)
	{
		game->mouse_last_x = x;
		return (0);
	}
	delta = x - game->mouse_last_x;
	game->mouse_last_x = x;
	rot = delta * MOUSE_SENS;
	if (rot != 0)
		apply_mouse_rotation(game, rot);
	return (0);
}
