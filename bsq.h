/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bsq.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*                                                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*                                                     #+#    #+#             */
/*                                                    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BSQ_H
# define BSQ_H

typedef struct s_info
{
	int		nb_lines;
	int		line_len;
	char	empty;
	char	obstacle;
	char	full;
}	t_info;

typedef struct s_map
{
	t_info	info;
	char	**lines;
}	t_map;

typedef struct s_result
{
	int		size;
	int		row;
	int		col;
}	t_result;

/*	utils.c		*/
int			ft_strlen(char *s);
void		ft_putchar(char c);
void		ft_putstr(char *s);
char		*ft_read_all(int fd);

/*	parse.c		*/
int			ft_parse(char *data, t_map *map);

/*	solve.c		*/
t_result	ft_solve(t_map *map);

/*	display.c	*/
void		ft_display(t_map *map, t_result res);
void		ft_free_map(t_map *map);

#endif
