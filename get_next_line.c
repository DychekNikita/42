/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorren <cdorren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:40:06 by cdorren           #+#    #+#             */
/*   Updated: 2020/11/10 12:10:29 by cdorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

size_t		ft_strlen(const char *s)
{
	size_t i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}


char		*ft_strdup(const char *s1)
{
	int		i;
	int		size;
	char	*dup;

	i = 0;
	size = ft_strlen(s1);
	if ((dup = malloc(sizeof(char) * size + 1)))
	{
		while (s1[i])
		{
			dup[i] = s1[i];
			i++;
		}
		dup[i] = '\0';
		return (dup);
	}
	else
		return (NULL);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char	*sub;
	size_t	i;
	size_t	n;

	i = 0;
	if (!s1 || !(sub = malloc(sizeof(char)
	* (ft_strlen(s1) + ft_strlen(s2)) + 1)))
		return (NULL);
	while (s1[i])
	{
		sub[i] = s1[i];
		i++;
	}
	n = i;
	i = 0;
	while (s2[i])
	{
		sub[n] = s2[i];
		i++;
		n++;
	}
	sub[n] = '\0';
	return (sub);
}

char 			*check_rem(char *rem, char **line)
{
	char	*pn;

	pn = NULL;
	if (rem)
		if ((pn = ft_strchr(rem, '\n')))
		{
			*pn = '\0';
			*line = ft_strdup(rem);
			ft_strcpy(rem, ++pn);
		}
		else
		{
			*line = ft_strdup(rem);
			ft_strclr(rem);
		}
	else
		*line = ft_strdup("");
	return (pn);
}

int				next_line(int fd, char **line, char **rem)
{
	char		buf[BUFFER_SIZE + 1];
	int			bwr;
	char		*pn;
	char		*tmp;

	pn = check_rem(*rem, line);
	while (!pn && (bwr = read(fd, buf, BUFFER_SIZE)))
	{
		buf[bwr] = '\0';
		if ((pn = ft_strchr(buf, '\n')))
		{
			*pn = '\0';
			*rem = ft_strdup(++pn);
		}
		tmp = *line;
		*line = ft_strjoin(*line, buf);
		free(tmp);
	}
	return ((bwr == BUFFER_SIZE && ft_strlen(*rem)) || bwr || ft_strlen(*line) ? 1 : 0);
}

g_n_l			*new_elem(int fd)
{
	g_n_l		*elem;

	if (!(elem = (g_n_l *)malloc(sizeof(g_n_l))))
		return (NULL);
	elem->fd = fd;
	elem->rem = NULL;
	elem->next = NULL;
	return (elem);
}

int				get_next_line(int fd, char **line)
{
	static g_n_l		*main;
	g_n_l				*tmp;

	if (fd < 0 || line == NULL)
		return (-1);
	if (main == NULL)
		main = new_elem(fd);
	tmp = main;
	while (main->fd != fd)
	{
		if (tmp->next == NULL)
			tmp->next = new_elem(fd);
		tmp = tmp->next;
	}
	return (next_line(tmp->fd, line, &tmp->rem));
}

//int main() {
//    int		fd;
//    char	*line;
//
//    fd = open("text.txt", O_RDONLY);
//    while (get_next_line(fd, &line))
//        printf("%s\n", line);
//}
