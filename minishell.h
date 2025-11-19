/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzangaro <mzangaro@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 20:24:36 by mzangaro          #+#    #+#             */
/*   Updated: 2025/11/19 19:23:34 by mzangaro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include "libft/libft.h"

typedef enum e_labels
{
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_IN_REDIR,
	TOKEN_HEREDOC,
	TOKEN_OUT_REDIR,
	TOKEN_APPEND,
	TOKEN_QUOTES,
	TOKEN_SING_Q,
	TOKEN_EOF,
}	t_labels;

typedef struct s_token
{
	char			*value;
	t_labels		type;
	struct s_token	*next;
}	t_token;

#endif