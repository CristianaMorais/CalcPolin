#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"

void normalize(List *lista){
  Item *new1 = lista->first;
  Item *new2;
  int index = 0;
  int contsAux, indexLocal;

  while (new1 != NULL) {
    new2 = new1 -> next;
    switch (new1 -> value -> flag) {
      //Caso para se for um monomio
      case Expre:
        contsAux = new1 -> value -> exp ->coeficiente;
        indexLocal = index;
        while (new2 != NULL) {
          bool flag = true;
          if(new2 -> value -> flag == Expre){ //Verifica se e um monomio
            if(new1 -> value -> exp->variavel == new1 -> value -> exp -> variavel){ // se aplica se a mesma variavel
              if(new1 -> value ->exp -> expoente == new1 -> value-> exp -> expoente){ //se tem o mesmo expoente
                flag = false;
                contsAux = new1 -> value ->exp -> coeficiente + contsAux;
                new2 = new2 -> next;
                removeItem(lista,indexLocal);
              }
            }
          }
          //Se nao entrou no ultimo if a flag estara a  true
          if(flag){
            new2 = new2 -> next;
            ++indexLocal;
          }
        }
        new1 -> value -> exp -> coeficiente = contsAux;
        break;

      //Caso para se for uma constante
      case Consta:
        contsAux = new1 -> value -> constante;
        indexLocal = index;
        while (new2 != NULL) {
          if (new2 -> value -> flag==Consta) {
            contsAux = new1 -> value -> constante + contsAux;
            new2 = new2 -> next;
            removeItem(lista, indexLocal);
          }
          else{
            new2 = new2 -> next;
            ++indexLocal;
          }
        }
        new1 -> value -> constante = contsAux;
        break;
    }
    //avanco para o proximo no do new1
    new1 = new1 -> next;
    ++index;
  }
}

void derivate(List *lista){
  Item *newp = lista -> first;
  int index = 0;
  while (newp != NULL) {
    switch (newp -> value -> flag) {
      case Expre:
        if(newp -> value -> exp -> expoente == 1){
          removeItem(lista,index);
          addOn(lista,newConstante(newp -> value-> exp -> coeficiente),index);
        }
        else{
          newp -> value ->exp-> coeficiente = newp -> value ->exp-> coeficiente * newp -> value ->exp-> expoente;
          newp -> value ->exp-> expoente = newp -> value ->exp-> expoente - 1;
        }
        break;

      case Consta:
        removeItem(lista,index);
        newp = newp -> next;
        continue;
        break;
    }
    newp = newp -> next;
    ++index;
  }
}


int main(int argc, char const *argv[]) {

  return 0;
}
