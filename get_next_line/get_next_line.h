/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:40:27 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/28 09:36:27 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1
# endif

typedef struct s_llist
{
	char			content;
	struct s_llist	*next;
}					t_llist;

# ifndef T_ELEMENT
#  define T_ELEMENT

typedef struct s_element
{
	size_t			count;
	char			*str;
	char			*buffer;
}					t_element;
# endif

char				*get_next_line(int fd);
int					check_endline(t_llist **save);
char				*extract_string(t_llist *save);
void				delete_and_free(t_llist **save);
void				ft_llstadd_back(t_llist **lst, char data);
int					ft_llstsize(t_llist *lst);
t_llist				*save_the_buffer(char *buffer, t_llist **save);
#endif
