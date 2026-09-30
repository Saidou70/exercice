/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                             :+:      :+:    :+:  */
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
** ft_atoi_bsq - Convertit les 'len' premiers caracteres de 's' en int.
** Retourne -1 si un caractere n'est pas un chiffre ou si len <= 0.
*/
static int	ft_atoi_bsq(char *s, int len)
{
	int	result;
	int	i;

	if (len <= 0)
		return (-1);
	result = 0;
	i = 0;
	while (i < len)
	{
		if (s[i] < '0' || s[i] > '9')
			return (-1);
		result = result * 10 + (s[i] - '0');
		i++;
	}
	return (result);
}

/*
** ft_parse_header - Parse la premiere ligne du fichier.
** Format attendu : <nombre_de_lignes><vide><obstacle><plein>
** Les 3 derniers caracteres sont les caracteres speciaux.
** Verifie qu'ils sont tous printables et differents entre eux.
** Retourne 1 si valide, 0 sinon.
*/
static int	ft_parse_header(char *line, t_info *info)
{
	int	len;

	len = ft_strlen(line);
	if (len < 4)
		return (0);
	info->empty = line[len - 3];
	info->obstacle = line[len - 2];
	info->full = line[len - 1];
	if (info->empty == info->obstacle || info->empty == info->full
		|| info->obstacle == info->full)
		return (0);
	if (info->empty < 32 || info->empty > 126
		|| info->obstacle < 32 || info->obstacle > 126
		|| info->full < 32 || info->full > 126)
		return (0);
	info->nb_lines = ft_atoi_bsq(line, len - 3);
	if (info->nb_lines <= 0)
		return (0);
	return (1);
}

/*
** ft_validate_map - Verifie l'integrite de la carte parsee.
** Toutes les lignes doivent avoir la meme longueur (> 0).
** Chaque caractere doit etre soit 'empty' soit 'obstacle'.
** Retourne 1 si valide, 0 sinon.
*/
static int	ft_validate_map(t_map *map)
{
	int	i;
	int	j;
	int	len;

	map->info.line_len = ft_strlen(map->lines[0]);
	if (map->info.line_len == 0)
		return (0);
	i = 0;
	while (i < map->info.nb_lines)
	{
		len = ft_strlen(map->lines[i]);
		if (len != map->info.line_len)
			return (0);
		j = 0;
		while (j < len)
		{
			if (map->lines[i][j] != map->info.empty
				&& map->lines[i][j] != map->info.obstacle)
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*
** ft_split_lines - Decoupe le buffer en lignes a partir de 'start'.
** Remplace les '\n' par '\0' et stocke les pointeurs dans map->lines.
** Verifie que le nombre de lignes correspond au header.
** Appelle ft_validate_map pour valider le contenu.
*/
static int	ft_split_lines(char *data, int start, t_map *map)
{
	int	i;
	int	idx;

	map->lines = malloc(sizeof(char *) * map->info.nb_lines);
	if (!map->lines)
		return (0);
	i = start;
	idx = 0;
	while (idx < map->info.nb_lines && data[i])
	{
		map->lines[idx] = &data[i];
		while (data[i] && data[i] != '\n')
			i++;
		if (data[i] == '\n')
			data[i++] = '\0';
		idx++;
	}
	if (idx != map->info.nb_lines)
		return (0);
	return (ft_validate_map(map));
}

/*
** ft_parse - Orchestre le parsing complet d'un buffer de carte.
** 1. Isole la premiere ligne (header) en remplacant '\n' par '\0'
** 2. Parse le header pour extraire nb_lines et les 3 caracteres
** 3. Decoupe le reste en lignes et valide la carte
** Retourne 1 si tout est valide, 0 sinon.
*/
int	ft_parse(char *data, t_map *map)
{
	int	i;

	i = 0;
	while (data[i] && data[i] != '\n')
		i++;
	if (!data[i] || i == 0)
		return (0);
	data[i] = '\0';
	if (!ft_parse_header(data, &map->info))
		return (0);
	return (ft_split_lines(data, i + 1, map));
}
