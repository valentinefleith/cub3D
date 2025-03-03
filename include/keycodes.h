/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keycodes.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vafleith <vafleith@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 10:28:45 by vafleith          #+#    #+#             */
/*   Updated: 2024/10/25 10:29:16 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYCODES_H
# define KEYCODES_H

# include "cub3d.h"

// ====== ARROWS ======
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_DOWN 65364
# define KEY_UP 65362
// ====== CLOSE ======
# define KEY_ESC 65307

typedef enum e_key
{
	up,
	down,
	left,
	right,
	left_rotation,
	right_rotation,
}	t_key;

#endif
