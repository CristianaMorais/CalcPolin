//
// LinkedList header
//

#include <stdlib.h>

typedef struct List List;
typedef struct Item Item;

List *newList();
Item *newItem();
void add(List *lista);
void remove(List *lista, int index);
