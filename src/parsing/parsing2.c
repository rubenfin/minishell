/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parsing2.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: jade-haa <jade-haa@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/02/09 15:51:29 by rfinneru      #+#    #+#                 */
/*   Updated: 2024/03/12 14:36:33 by rfinneru      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	createnode(t_command **head, char *data, int redirection)
{
	t_command	*newnode;
	t_command	*temp;

	if (!data || !data[0])
		return (0);
	newnode = (t_command *)malloc(sizeof(t_command));
	if (!newnode)
		return (-1);
	newnode->string = data;
	newnode->token = redirection;
	newnode->next = NULL;
	if (*head == NULL)
		*head = newnode;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	return (1);
}

t_command	*createnode_return(t_command **head, char *data, int redirection)
{
	t_command	*newnode;
	t_command	*temp;

	newnode = (t_command *)malloc(sizeof(t_command));
	if (!newnode)
		return (NULL);
	newnode->string = data;
	newnode->token = redirection;
	newnode->next = NULL;
	if (*head == NULL)
		*head = newnode;
	else
	{
		temp = *head;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = newnode;
	}
	return (newnode);
}
