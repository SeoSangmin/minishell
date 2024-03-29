/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tree_build_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yecnam <yecnam@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 16:31:26 by saseo             #+#    #+#             */
/*   Updated: 2023/04/18 18:44:20 by yecnam           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "utils.h"

t_tree	*tree_builder(t_list *head)
{
	t_tree	*tree;
	t_node	*root;
	t_list	*last;

	tree = init_tree();
	root = create_node(PIPE);
	tree_set_root(tree, root);
	last = ft_lstlast(head);
	if (!last)
		malloc_fail();
	set_pipe(root, head, last);
	return (tree);
}

void	set_pipe(t_node *parent, t_list *start, t_list *last)
{
	t_list	*tmp;
	t_list	*lst_pipe;
	t_node	*node;

	if (start == NULL)
		return ;
	lst_pipe = start;
	while (lst_pipe->type != L_PIPE && lst_pipe->next != NULL)
		lst_pipe = lst_pipe->next;
	set_cmd(parent, start, lst_pipe);
	tmp = lst_pipe;
	while (tmp->type != L_PIPE && tmp->next != NULL)
		tmp = tmp->next;
	node = create_node(PIPE);
	insert_right(parent, node);
	set_pipe(node, lst_pipe->next, last);
}

void	set_cmd(t_node *parent, t_list *start, t_list *last)
{
	t_node	*node;

	node = create_node(CMD);
	insert_left(parent, node);
	set_redir(node, start, last);
	set_simple_cmd(node, start, last);
}

void	set_redir(t_node *parent, t_list *start, t_list *last)
{
	t_node	*node;
	t_list	*tmp;

	if (start == NULL || start->type == L_PIPE)
		return ;
	tmp = start;
	while (tmp->type != L_REDIR && tmp != last)
		tmp = tmp->next;
	if (tmp->type != L_REDIR)
		return ;
	node = create_node(REDIR);
	if (ft_strcmp(tmp->line, "<") == 0)
		node->cont.redir_type = IN;
	else if (ft_strcmp(tmp->line, "<<") == 0)
		node->cont.redir_type = HERE_DOC;
	else if (ft_strcmp(tmp->line, ">") == 0)
		node->cont.redir_type = OUT_T;
	else if (ft_strcmp(tmp->line, ">>") == 0)
		node->cont.redir_type = OUT_A;
	node->cont.file_name = ft_strdup(tmp->next->line);
	if (!node->cont.file_name)
		malloc_fail();
	insert_left(parent, node);
	set_redir(node, tmp->next->next, last);
}

void	set_simple_cmd(t_node *parent, t_list *start, t_list *last)
{
	t_node	*node;
	t_list	*word_end;
	int		range_size;
	int		redir_num;

	range_size = get_list_range_size(start, last);
	redir_num = get_redir_num_in_range(start, last);
	if (redir_num * 2 == range_size)
		node = create_node(NO_CMD);
	else
	{
		start = get_word_start_list(start, last, redir_num);
		word_end = get_word_end_list(start, last);
		node = create_node(SIMPLE_CMD);
		node->cont.args = get_args(start, word_end);
		node->cont.path = ft_strdup(start->line);
		if (!node->cont.path)
			malloc_fail();
	}
	insert_right(parent, node);
}
