/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 17:53:23 by stliu             #+#    #+#             */
/*   Updated: 2026/02/24 18:08:25 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
#define PARSER_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "../GNL/get_next_line.h"
#include "../Printf/Libft/libft.h"
#include "rt_math.h"



int validate(int fd, t_scene *scene);

int parse_file(const char *path, t_scene *scene);
int check_line(char *line, t_scene *scene);


//	helpers	// 
int valid_ident(char *ident, t_scene *scene);
int ft_isspace(char c);
int valid_ambient(char *line, t_scene *scene);
int valid_camera(char *line, t_scene *scene);
int valid_light(char *line, t_scene *scene);
int valid_sphere(char *line, t_scene *scene);
int valid_plane(char *line, t_scene *scene);
int valid_cylinder(char *line, t_scene *scene);
int valid_cone(char *line, t_scene *scene);
double	ft_atod(const char *str);
void	free_split(char **split);
void	init_scene(t_scene *scene);
void	add_object(t_scene *scene, t_object *new);

#endif