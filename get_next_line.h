/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkarakay <tkarakay@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 13:46:44 by tayki             #+#    #+#             */
/*   Updated: 2024/08/23 16:18:52 by tkarakay         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct list
{
	char		*str;
	struct list	*next;
}				list_t;

char			*get_next_line(int fd);
void			write_to_buffer(list_t *list, int fd);
void			append(list_t **head, char *str);
int				has_endline(list_t *list);
char			*get_line(list_t *list);
int				count_line(list_t *list);
void			clean_list(list_t **head);

#endif
