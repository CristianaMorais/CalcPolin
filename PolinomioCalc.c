#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"

void normalize(List *lista){
  Item *new1 = lista->first;
  Item *new2;
  int index = 0;

  while (new1 != NULL) {
    new2 = new1 -> next;
    switch (new1 -> value -> flag) {
      //Caso para se for um monomio
      case Expre:
        int contsAux = newp1 -> value -> variavel -> coeficiente;
        int indexLocal = index;
        while (new2 != NULL) {
          boolean flag = true;
          if(new2 -> value -> flag == Expre){ //Verifica se e um monomio
            if(newp1 -> value -> variavel == newp1 -> value -> variavel){ // se aplica se a mesma variavel
              if(newp1 -> value -> expoente == newp1 -> value -> expoente){ //se tem o mesmo expoente
                flag = false;
                contsAux = newp1 -> value -> expoente + contsAux;
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
        newp1 -> value -> variavel -> coeficiente = contsAux;
        break;

      //Caso para se for uma constante
      case Consta:
        int contsAux = new1 -> value -> constante;
        int indexLocal = index;
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
        if(newp -> value -> expoente == 1){
          removeItem(lista,index);
          addOn(lista,newConstante(newp -> value -> coeficiente));
        }
        else{
          newp -> value -> coeficiente = newp -> value -> coeficiente * newp -> value -> expoente;
          newp -> value -> expoente = newp -> value -> expoente - 1;
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
