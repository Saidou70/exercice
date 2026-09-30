/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                             :+:      :+:    :+:  */
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
** ft_strlen - Calcule la longueur d'une chaine de caracteres.
** Parcourt la chaine jusqu'au '\0' et retourne le nombre de caracteres.
*/
int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/*
** ft_putchar - Ecrit un seul caractere sur la sortie standard.
*/
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/*
** ft_putstr - Ecrit une chaine de caracteres sur la sortie standard.
*/
void	ft_putstr(char *s)
{
	write(1, s, ft_strlen(s));
}

/*
** ft_realloc - Realloue un buffer en doublant sa capacite.
** Copie les anciennes donnees dans le nouveau buffer et libere l'ancien.
** Retourne NULL en cas d'echec d'allocation.
*/
static char	*ft_realloc(char *ptr, int old_sz, int new_sz)
{
	char	*new_ptr;
	int		i;

	new_ptr = malloc(new_sz);
	if (!new_ptr)
	{
		free(ptr);
		return (NULL);
	}
	i = 0;
	while (i < old_sz)
	{
		new_ptr[i] = ptr[i];
		i++;
	}
	free(ptr);
	return (new_ptr);
}

/*
** ft_read_all - Lit tout le contenu d'un file descriptor dans un buffer.
** Utilise une strategie de buffer doublant 
*/
char	*ft_read_all(int fd)
{
	char	*buf;
	int		cap;
	int		size;
	int		rd;

	cap = 4096;
	buf = malloc(cap + 1);
	if (!buf)
		return (NULL);
	size = 0;
	rd = read(fd, buf + size, cap - size);
	while (rd > 0)
	{
		size += rd;
		if (size >= cap)
		{
			buf = ft_realloc(buf, size, cap * 2 + 1);
			if (!buf)
				return (NULL);
			cap *= 2;
		}
		rd = read(fd, buf + size, cap - size);
	}
	if (rd < 0)
	{
		free(buf);
		return (NULL);
	}
	buf[size] = '\0';
	return (buf);
}
