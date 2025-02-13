/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ana-cast <ana-cast@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:55:12 by ana-cast          #+#    #+#             */
/*   Updated: 2025/02/13 20:41:40 by ana-cast         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

// ------------------- ARGUMENT ERRORS ------------------- //
# define E_ARGS_COUNT "Invalid number of arguments. Usage: %s <map.cub>" // arg0

// ------------------- FILE ERRORS ------------------- //
# define E_FILE_OPEN "Failed to open file: %s"                   // file_path
# define E_FILE_EXT "Invalid file extension: %s (expected .cub)" // file_path

#endif /* ERROR_H */
