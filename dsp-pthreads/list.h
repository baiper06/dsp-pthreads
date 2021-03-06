/*
 * queue.h
 *
 *  Created on: 14/10/2014
 *      Author: luis
 */

#ifndef LIST_H_
#define LIST_H_

//#include "stages.h"
#include "samples.h"

typedef struct Node {
    struct s_samples* item;
    struct Node* next;
} Node;

typedef struct List {

	Node* head;
    Node* tail;
    int size;

} Queue;

//Metodos internos de la lista
void list_add(List* list, s_samples* item);
s_samples* list_first_element_in_state (List* list, S_SAMPLE_ETAPA state);

//Metodos externos de la lista
List create_list_with_capacity(int capacity);

#endif /* LIST_H_ */
