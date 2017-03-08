//
// LinkedList header
//
#include <stdlib.h>
#include "Monomio.h"

typedef struct List List;
typedef struct Item Item;

List *newList();
Item *newItem(Monom *value);
void add(List *lista,Monom value);
void removeItem(List *lista, int index);
