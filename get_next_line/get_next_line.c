/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: luvallee <luvallee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/11 12:40:45 by luvallee          #+#    #+#             */
/*   Updated: 2024/06/28 09:37:00 by vafleith         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	check_endline(t_llist **save)
{
	int		i;
	t_llist	*temp;

	i = 0;
	temp = *save;
	while (temp != NULL)
	{
		if (temp->content == '\n')
		{
			i++;
			return (i);
		}
		i++;
		temp = temp->next;
	}
	return (0);
}

char	*extract_string(t_llist *save)
{
	char	*new_str;
	int		len;
	int		i;

	if (!save)
		return (NULL);
	len = ft_llstsize(save);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (save)
	{
		if (save->content == '\n')
		{
			new_str[i++] = '\n';
			break ;
		}
		new_str[i] = save->content;
		i++;
		save = save->next;
	}
	new_str[i] = '\0';
	return (new_str);
}

void	delete_and_free(t_llist **save)
{
	t_llist	*temp;

	if (!*save)
		return ;
	while (*save != NULL)
	{
		temp = (*save)->next;
		if ((*save)->content == '\n')
		{
			free(*save);
			*save = temp;
			break ;
		}
		else if (*save != NULL)
			free(*save);
		*save = temp;
	}
}

t_llist	*save_the_buffer(char *buffer, t_llist **save)
{
	t_llist	*new;
	int		i;

	i = 0;
	if (*save == NULL)
	{
		new = malloc(sizeof(t_llist));
		if (!new)
			return (NULL);
		new->content = buffer[i];
		save = &new;
		(*save)->next = NULL;
		i++;
	}
	while (buffer[i])
	{
		ft_llstadd_back(save, buffer[i]);
		i++;
	}
	return (*save);
}

char	*get_next_line(int fd)
{
	static t_llist	*save = NULL;
	t_element		element;
	char			*str;

	if (BUFFER_SIZE < 1 || fd < 0 || read(fd, &str, 0) < 0)
		return (NULL);
	while (check_endline(&save) == 0)
	{
		element.buffer = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!element.buffer)
			return (NULL);
		element.count = read(fd, element.buffer, BUFFER_SIZE);
		if (element.count == 0 || (int)element.count == -1)
		{
			free(element.buffer);
			break ;
		}
		element.buffer[element.count] = '\0';
		save = save_the_buffer(element.buffer, &save);
		free(element.buffer);
	}
	str = extract_string(save);
	delete_and_free(&save);
	return (str);
}
// #include <fcntl.h>
// #include <stdio.h>
// #include <sys/stat.h>

// int	main(void)
// {
// 	int		fd;
// 	char	*text;

// 	fd = open("test/fd2", O_RDONLY);
// 	while (1)
// 	{
// 		text = get_next_line(fd);
// 		printf("%s", text);
// 		if (text == NULL)
// 			break ;
// 		free(text);
// 	}
// 	return (0);
// }
