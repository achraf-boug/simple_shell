#include "shell.h"

/**
 * addNode - Add node at the end of linked list
 * @h: linked list's head.
 * @s: String value
 * @n: index value
 *
 * Return: newly added node, NULL on error
 */
list_str *addNode(list_str **h, const char *s, int n)
{
	list_str *new, *node;

	if (!h)
		return (NULL);

	node = *h;
	new = malloc(sizeof(list_str));
	if (!new)
		return (NULL);
	setMem((void *)new, 0, sizeof(list_str));
	new->n = n;
	if (s)
	{
		new->s = _strcpy2(s);
		if (!new->s)
		{
			free(new);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*h = new;
	return (new);
}

/**
 * printLinkedList - prints all nodes
 * @h: head of linked list
 *
 * Return: size of list
 */
size_t printLinkedList(const list_str *h)
{
	size_t i = 0;

	while (h)
	{
		_putstr(h->s ? h->s : "(nil)");
		_putstr("\n");
		h = h->next;
		i++;
	}
	return (i);
}

/**
 * rmNodeIndex - delete node at index
 * @h: head of linked list
 * @index: index of node to delete
 *
 * Return: 1 if OK, 0 if KO
 */
int rmNodeIndex(list_str **h, unsigned int index)
{
	list_str *node, *pnode;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		node = *h;
		*h = (*h)->next;
		free(node->s);
		free(node);
		return (1);
	}
	node = *h;
	while (node)
	{
		if (i == index)
		{
			pnode->next = node->next;
			free(node->s);
			free(node);
			return (1);
		}
		i++;
		pnode = node;
		node = node->next;
	}
	return (0);
}

/**
 * flushLinkedList - free linked list
 * @h: head of the list
 *
 * Return: void
 */
void flushLinkedList(list_str **h)
{
	list_str *node, *nxnode, *head;

	if (!h || !*h)
		return;
	head = *h;
	node = head;
	while (node)
	{
		nxnode = node->next;
		free(node->s);
		free(node);
		node = nxnode;
	}
	*h = NULL;
}
