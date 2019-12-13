/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsiche <bsiche@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/05 00:59:46 by mjose             #+#    #+#             */
/*   Updated: 2019/04/15 00:09:00 by bsiche           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh21.h"
#include <stdlib.h>

void	exec_left_branch(t_tree *tree, t_jobs *job)
{
	if (ft_strlen(tree->cmd) == 1 && tree->cmd[0] == '&')
		g_tracking.foreground = 1;
	exec_command(tree->left->list_cmd, g_tracking.foreground, job, 0);
	g_tracking.foreground = 0;
}

void	exec_right_branch(t_tree *tree, t_jobs *job)
{
	if (tree->prev && ft_strlen(tree->prev->cmd) == 1
			&& tree->prev->cmd[0] == '&')
		g_tracking.foreground = 1;
	exec_command(tree->right->list_cmd, g_tracking.foreground, job, 0);
	g_tracking.foreground = 0;
}

void	free_ast(t_tree *tree, t_last *next_free)
{
	t_tree	*left_tree;
	t_tree	*right_tree;

	left_tree = NULL;
	right_tree = NULL;
	if (tree->left)
		left_tree = tree->left;
	if (tree->right)
		right_tree = tree->right;
	if (tree->cmd)
		ft_strdel(&tree->cmd);
	while (tree->list_cmd)
	{
		next_free = tree->list_cmd->next;
		if (tree->list_cmd->name)
			ft_strdel(&tree->list_cmd->name);
		ft_memdel((void **)&tree->list_cmd);
		tree->list_cmd = next_free;
	}
	ft_memdel((void **)&tree);
	if (left_tree)
		free_ast(left_tree, NULL);
	if (right_tree)
		free_ast(right_tree, NULL);
}

void	execute_ast(t_tree *tree, t_jobs *job)
{
	g_tracking.foreground = 0;
	if (tree->type == SEP)
	{
		if (tree->left && tree->left->type != SEP)
			exec_left_branch(tree, job);
		else if (tree->left && tree->left->type == SEP)
			execute_ast(tree->left, job);
		if (ft_strlen(tree->cmd) > 1)
		{
			if (tree->cmd[0] == '&' && g_tracking.lastreturn == 1)
			{
				g_tracking.cmdindex++;
				return ;
			}
			if (tree->cmd[0] == '|' && g_tracking.lastreturn == 0)
			{
				g_tracking.cmdindex++;
				return ;
			}
		}
		if (tree->right && tree->right->type != SEP)
			exec_right_branch(tree, job);
		else if (tree->right)
			execute_ast(tree->right, job);
	}
}
