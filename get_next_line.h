/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdorren <cdorren@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/06 12:40:10 by cdorren           #+#    #+#             */
/*   Updated: 2020/11/09 15:48:01 by cdorren          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct 				get_next_line
{
	int						fd;
	char					*rem;
	struct	get_next_line	*next;
}							g_n_l;

size_t						ft_strlen(const char *s);
char						*ft_strrjoin(char const *s1, char const *s2, char c);
int							get_next_line(int fd, char **line);
char						*ft_strchr(const char *s, int c);
char						*ft_strcpy(char *dst, const char *src);
char						*ft_strdup(const char *s1);
void						ft_strclr(char *s);
char						*ft_strnew(size_t size);

#endif
