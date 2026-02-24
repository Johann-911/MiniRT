/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stliu <stliu@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 15:32:22 by stliu             #+#    #+#             */
/*   Updated: 2026/02/24 16:21:37 by stliu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/parser.h"


/*
Ambient lighting: 
- Identifier: A 
- light ratio : 0.1-1.0
- RGB: 0 - 255
*/

/*
Camera:
- Identifier: C
- coords x,y,z 
- vector : -1 - 1
- FOV: 0 - 180
*/

/*
Light:
- Identifier: L
- coords x,y,z
- brightness: 0 - 1.0
- RBG: 0 - 255
*/

/*
Sphere:
- Ident: sp
- coords x,y,z
- sphere diameter
- RBG: 255
*/

/*
Plane:
- Ident pl
- coords x,y,z
- 3D vector: - 1 - 1
- RGB: 255
*/

/*
Cylinder:
- Ident: cy
- coords x,y,z
- 3D vector: -1 - 1
- cylinder diamter
- cylinder height
- RBG: 255
*/