//
// LinkedList header
//
#include <stdio.h>
#include <stdlib.h>
#include "Monomio.h"

typedef struct List List;
typedef struct Item Item;

// Struct ITEM
struct Item{
  Monom *value;
  Item *next;
};

//Struct LIST
struct List{
  Item *first;
  Item *end;
  int size;
};


List *newList();
Item *newItem(Monom *value);
void add(List *lista,Monom *value);
void addOn(List *lista, Monom *value, int index);
void removeItem(List *lista, int index);
void printList(List *lista);
