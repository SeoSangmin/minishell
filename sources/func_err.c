/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_err.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:26 by yecnam            #+#    #+#             */
/*   Updated: 2023/04/17 16:33:13 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	func_err(char *str)
{
	perror(str);
	exit(1);
}
