#include "LinkedList.h"

List *newList(){
  List *lista;
  lista = (List *)malloc(sizeof(List));
  lista -> size = 0;
  lista -> first;
  lista -> end = NULL;
  return lista;
}

Item *newItem(Monom *value){
  Item *newp;
  newp=(Item*)malloc(sizeof(Item));
  newp -> value = value;
  newp -> next = NULL;
  return newp;
}

void addOn(List *lista, Monom *value, int index){
  Item *aux = lista -> first;
  Item *newp = aux -> next;

  //caso ser o primeiro
  if(index == 0){
    lista -> first == newItem(value);
    lista -> first -> next;
    lista -> size = lista -> size + 1;
    return;
  }

  int i = 0;
  while (newp != NULL) {
    if(++i == index){
      aux -> next = newItem(value);
      aux -> next -> next = newp;
    }
    aux = newp;
    newp = newp -> next;
  }

  //tratar se for no fim
  if((lista -> size) == index){
    aux -> next = newItem(value);
    lista -> end = aux -> next;
  }
  //atualizar o size
  lista -> size = lista -> size + 1;
}

void add(List *lista, Monom *value){
  Item *newp = lista -> end;

  //criacao do novo item
  if(newp == NULL){
    lista -> first = lista -> end = newItem(value);
  }
  else{
    newp -> next = newItem(value);
    lista -> end = newp -> next;
  }
  //incremento do tamanho da lista
  lista -> size = lista -> size + 1;
}

void removeItem(List *lista, int index){

  //verificar se o array encontra s edentros do limites
  if(lista->size<=index){
    exit(0);
  }

  int count = 0;
  Item *newp = lista -> first;

  //eliminar o primeiro no
  if(index == 0){
    lista -> first = newp -> next;
    free(newp);
  }

  //eliminar no meio
  while (newp -> next -> next != NULL) {
    if(++count==index){
      Item *aux = newp -> next;
      newp -> next = aux -> next;
      free(aux);
      break;
    }
    newp = newp -> next;
  }

  if(++count==index){
    newp -> next = NULL;
  }
  lista -> size = lista -> size--;
}


//Debug of list
void printList(List *lista){
  printf("Entrei na printlist");
  Item *newp = lista -> first;

  while (newp != NULL) {
    printf("Estou aqui antes switch");
    switch (newp->value->flag) {
      case Expre:
        printf("Mon: %d*%c^%d\n",newp->value->exp->coeficiente,newp->value->exp->variavel,newp->value->exp->expoente );
        printf("Estou aqui");
        break;
      case Consta:
        printf("Const: %d\n",newp->value->constante );
        break;
    }
    newp = newp -> next;
  }
  printf("\n");
}

/*
int main(int argc, char const *argv[]) {
  int n;
  List *lista = newList();
  scanf("%d",&n );
  while (n != -1) {
    add(lista,n);
    scanf("%d",&n );
  }
  printList(lista);
  removeItem(lista,0);
  printList(lista);


  return 0;
}
*/
