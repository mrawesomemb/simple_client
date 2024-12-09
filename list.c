// list/list.c
// 
// Implementation for linked list.
//
// <Author>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "list.h"

list_t *list_alloc() 
{ 
  list_t* mylist =  (list_t *) malloc(sizeof(list_t)); 
  mylist->head = NULL;
  return mylist;
}

void list_free(list_t *l) 
{
  node_t *current = l->head;
  node_t *next;
  while (current != NULL) 
  {
    next = current->next;
    free(current);
    current = next;
  }
  free(l);
}

void list_print(list_t *l) 
{
  node_t *curr = l->head;
  while (curr != NULL) {
    printf("%d->", curr->value);
    curr = curr->next;
  }
  printf("NULL\n");
}

char * listToString(list_t *l) 
{
  char* buf = (char *) malloc(sizeof(char) * 1024);
  char tbuf[20];

	node_t* curr = l->head;
  while (curr != NULL) 
  {
    sprintf(tbuf, "%d->", curr->value);
    curr = curr->next;
    strcat(buf, tbuf);
  }
  strcat(buf, "NULL");
  return buf;
}

int list_length(list_t *l) 
{ 
  int count = 0;
  node_t *current = l->head;
  while (current != NULL) 
  {
    count++;
    current = current->next;
  }
  return count; 
}

void list_add_to_back(list_t *l, elem value) 
{
  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;
  new_node->next = NULL;

  if (l->head == NULL) 
  {
    l->head = new_node;
  } 
  else 
  {
    node_t *curr = l->head;
    while (curr->next != NULL) 
    {
      curr = curr->next;
    }
    curr->next = new_node;
  }
}

void list_add_to_front(list_t *l, elem value) 
{
  node_t* cur_node = (node_t *) malloc(sizeof(node_t));
  cur_node->value = value;
  cur_node->next = l->head;  // insert the new node at the front
  l->head = cur_node;


}
void list_add_at_index(list_t *l, elem value, int index) 
{

  if (index < 0) return;

  if (index == 0) {
    list_add_to_front(l, value);
    return;
  }

  node_t *new_node = (node_t *)malloc(sizeof(node_t));
  new_node->value = value;

  int i;
  node_t *curr = l->head;
  for (i = 0; i < index - 1 && curr != NULL; i++) {
    curr = curr->next;
  }

  if (curr == NULL) {
    free(new_node); // Out of bounds
    return;
  }

  new_node->next = curr->next;
  curr->next = new_node;
}

elem list_remove_from_back(list_t *l) 
{ 
  if (l->head == NULL) return -1;

  node_t *curr = l->head;
  if (curr->next == NULL) {
    int value = curr->value;
    free(curr);
    l->head = NULL;
    return value;
  }

  while (curr->next->next != NULL) {
    curr = curr->next;
  }

  int value = curr->next->value;
  free(curr->next);
  curr->next = NULL;
  return value; 
}

elem list_remove_from_front(list_t *l) 
{ 
  if (l->head == NULL) return -1;

  node_t *temp = l->head;
  int value = temp->value;
  l->head = l->head->next;
  free(temp);
  return value; 
}

elem list_remove_at_index(list_t *l, int index) 
{ 
  if (index < 0 || l->head == NULL) return -1;

  node_t* temp = l->head;
  if (index == 0) {
    l->head = temp->next;
    free(temp);
    return 0;  // successfully removed
  }

  // Declare the variable `i` outside the for loop
  int i;
  for (i = 0; temp != NULL && i < index - 1; i++) {
    temp = temp->next;
  }

  if (temp == NULL || temp->next == NULL) return -1;

  node_t* next = temp->next->next;
  free(temp->next);
  temp->next = next;
  return 0; 
}

bool list_is_in(list_t *l, elem value) 
{ 
  node_t *curr = l->head;
  while (curr != NULL) {
    if (curr->value == value) return true;
    curr = curr->next;
  }
  return false; 
}

elem list_get_elem_at(list_t *l, int index) 
{ 
  if (index < 0) return -1;

  node_t *current = l->head;
  int count = 0;

  while (current != NULL) 
  {
    if (count == index)
      return current->value;
    count++;
    current = current->next;
  }

  return -1; 
}

int list_get_index_of(list_t *l, elem value) 
{ 
  node_t *current = l->head;
  int index = 0;

  while (current != NULL) 
  {
    if (current->value == value)
      return index;
    current = current->next;
    index++;
  }

  return -1; 
}

