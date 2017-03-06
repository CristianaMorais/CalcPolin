#include "LinkedList.h"

//Struct LIST
struct List{
  Item *first;
  Item *end;
  int size;
};

// Struct ITEM
struct Item{
  Monom value;
  Item *next;
};


List *newList(){
  List *lista;
  lista = (List *)malloc(sizeof(List));
  lista -> size = 0;
  lista -> end = NULL;
}

Item *newItem(){
  Item *newp;
  newp=(Item*)malloc(sizeof(Item));
  newp -> value = newMonom();
  newp -> next = NULL;
  return newp;
}

void add(List *lista){
  Item *newp = lista -> end;

  //criacao do novo item
  if(newp == NULL){
    lista -> end = newItem();
  }
  else{
    newp -> next = newItem();
    lista -> end = newp -> next;
  }
  //incremento do tamanho da lista
  lista -> size = lista -> size + 1;
}
