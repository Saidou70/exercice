/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                              :+:      :+:    :+:  */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	ft_process(int fd)
{
	char		*data;
	t_map		map;
	t_result	res;

	data = ft_read_all(fd);
	map.lines = NULL;
	if (!data || !ft_parse(data, &map))
	{
		ft_putstr("map error\n");
		free(map.lines);
		free(data);
		return ;
	}
	res = ft_solve(&map);
	ft_display(&map, res);
	ft_free_map(&map);
	free(data);
}

/*
** ft_process_file - Ouvre un fichier par son nom et lance ft_process.
** Affiche "map error" si le fichier ne peut pas etre ouvert.
*/
static void	ft_process_file(char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		ft_putstr("map error\n");
		return ;
	}
	ft_process(fd);
	close(fd);
}



int	main(int argc, char **argv)
{
	int	i;

	if (argc == 1)
		ft_process(0);
	else
	{
		i = 1;
		while (i < argc)
		{
			if (i > 1)
				ft_putstr("\n");
			ft_process_file(argv[i]);
			i++;
		}
	}
	return (0);
}
