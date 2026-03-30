/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jtoumani <jtoumani@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:53:23 by stliu             #+#    #+#             */
/*   Updated: 2026/03/26 12:30:22 by jtoumani         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "../GNL/get_next_line.h"
# include "../Printf/Libft/libft.h"
# include "rt_math.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		validate(int fd, t_scene *scene);

/*
** helpers
*/
int		valid_ident(char *ident, t_scene *scene);
int		ft_isspace(char c);
int		valid_ambient(char *line, t_scene *scene);
int		valid_camera(char *line, t_scene *scene);
int		valid_light(char *line, t_scene *scene);
int		valid_sphere(char *line, t_scene *scene);
int		valid_plane(char *line, t_scene *scene);
int		valid_cylinder(char *line, t_scene *scene);
int		valid_cone(char *line, t_scene *scene);
int		parse_flags(char **tokens, int count, int base, t_object *obj);
int		parse_double_strict(const char *s, double *out);
int		parse_int_strict(const char *s, int *out);
int		parse_vec3_token(const char *token, t_vec3 *out);
int		parse_rgb_token(const char *token, t_rgb *out);
int		parse_dir_token(const char *token, t_vec3 *out);
double	ft_atod(const char *str);
void	add_object(t_scene *scene, t_object *new);
void	free_split(char **split);
int		token_count(char **tokens);
char	**split_tokens(const char *line);

#endif
