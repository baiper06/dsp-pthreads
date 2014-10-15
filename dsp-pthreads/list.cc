/*
 * queue.cc
 *
 *  Created on: 14/10/2014
 *      Author: luis
 */

#include <cstddef>
#include <cstdlib>
#include "list.h"
#include <stdio.h>


void list_add(List* list, s_samples* item)
{
	// Create a new node
	Node* n = (Node*) malloc (sizeof(Node));
	n->item = item;
	n->next = NULL;

	if (list->head == NULL) { // no head
		list->head = n;
	} else{
		list->tail->next = n;
	}
	list->tail = n;
	list->size++;
}

s_samples* list_first_element_in_state (List* list, S_SAMPLE_ETAPA state)
{
	// get the first item
	Node* node = list->head;
	bool found = false;

	//Recorre lista para buscar el primer elemento en el estado
	int index;
	for(index = 1; index < list->size; index++) //index = 1 porque ya antes se asigno uno
	{
		if(node != NULL && node->item != NULL && (node->item->etapa == state))
		{
			printf("ELEMENTO ENCONTRADO EN POS %d\n", index);
			found = true;
			break;
		}
		node = node->next;
	}
	if(found)
		return node->item;
	printf("ELEMENTO NO ENCONTRADO\n");
	return NULL;
}

List create_list_with_capacity (int capacity) {
	List list;
	list.size = 0;
	list.head = NULL;
	list.tail = NULL;
	return list;
}
