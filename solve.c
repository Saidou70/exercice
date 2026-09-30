/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   solve.c                                             :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <stdlib.h>

/*
** ft_min - Retourne le minimum de trois entiers.
** Utilise pour la formule DP : min(haut, gauche, diagonale).
*/
static int	ft_min(int a, int b, int c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= c)
		return (b);
	return (c);
}

/*
** ft_alloc_dp - Alloue une table 2D d'entiers (rows x cols).
** En cas d'echec en cours d'allocation, libere ce qui a deja ete alloue.
** Retourne le tableau 2D ou NULL en cas d'erreur.
*/
static int	**ft_alloc_dp(int rows, int cols)
{
	int	**dp;
	int	i;

	dp = malloc(sizeof(int *) * rows);
	if (!dp)
		return (NULL);
	i = 0;
	while (i < rows)
	{
		dp[i] = malloc(sizeof(int) * cols);
		if (!dp[i])
		{
			while (--i >= 0)
				free(dp[i]);
			free(dp);
			return (NULL);
		}
		i++;
	}
	return (dp);
}

/*
** ft_free_dp - Libere la table DP 2D ligne par ligne, puis le tableau.
*/
static void	ft_free_dp(int **dp, int rows)
{
	int	i;

	i = 0;
	while (i < rows)
	{
		free(dp[i]);
		i++;
	}
	free(dp);
}

/*
** ft_compute_dp - Remplit la table DP avec la programmation dynamique.
*/
static void	ft_compute_dp(t_map *map, int **dp, t_result *res)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->info.nb_lines)
	{
		j = 0;
		while (j < map->info.line_len)
		{
			if (map->lines[i][j] == map->info.obstacle)
				dp[i][j] = 0;
			else if (i == 0 || j == 0)
				dp[i][j] = 1;
			else
				dp[i][j] = ft_min(dp[i - 1][j], dp[i][j - 1],
						dp[i - 1][j - 1]) + 1;
			if (dp[i][j] > res->size)
			{
				res->size = dp[i][j];
				res->row = i;
				res->col = j;
			}
			j++;
		}
		i++;
	}
}

/*
** ft_solve - Point d'entree de la resolution par programmation dynamique.
*/
t_result	ft_solve(t_map *map)
{
	t_result	res;
	int			**dp;

	res.size = 0;
	res.row = 0;
	res.col = 0;
	dp = ft_alloc_dp(map->info.nb_lines, map->info.line_len);
	if (!dp)
		return (res);
	ft_compute_dp(map, dp, &res);
	ft_free_dp(dp, map->info.nb_lines);
	return (res);
}
