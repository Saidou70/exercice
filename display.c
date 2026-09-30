/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                           :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdlib.h>
#include <unistd.h>

/*
** ft_fill_square - Remplit le carre trouve dans la grille.
** Calcule le coin haut-gauche a partir du coin bas-droit (res.row, res.col)
** et de la taille (res.size), puis remplace chaque case par info.full.
*/
static void	ft_fill_square(t_map *map, t_result res)
{
	int	i;
	int	j;
	int	start_r;
	int	start_c;

	start_r = res.row - res.size + 1;
	start_c = res.col - res.size + 1;
	i = start_r;
	while (i <= res.row)
	{
		j = start_c;
		while (j <= res.col)
		{
			map->lines[i][j] = map->info.full;
			j++;
		}
		i++;
	}
}

/*
** ft_display - Affiche la carte sur la sortie standard.
** Si un carre a ete trouve (size > 0), le remplit d'abord.
** Ecrit ensuite chaque ligne suivie d'un '\n'.
*/
void	ft_display(t_map *map, t_result res)
{
	int	i;

	if (res.size > 0)
		ft_fill_square(map, res);
	i = 0;
	while (i < map->info.nb_lines)
	{
		write(1, map->lines[i], map->info.line_len);
		ft_putchar('\n');
		i++;
	}
}

/*
** ft_free_map - Libere le tableau de pointeurs de lignes.
** Note : les lignes elles-memes pointent dans le buffer 'data'
** qui est libere separement dans ft_process (main.c).
*/
void	ft_free_map(t_map *map)
{
	free(map->lines);
	map->lines = NULL;
}
