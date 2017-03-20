#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"
#include <ctype.h>

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
        contsAux = new1 -> value ->val-> exp ->coeficiente;
        indexLocal = index+1;
        while (new2 != NULL) {
          bool flag = true;
          if(new2 -> value -> flag == Expre){ //Verifica se e um monomio
            if(new1 -> value -> val->exp->variavel == new2 -> value ->val-> exp -> variavel){ // se aplica se a mesma variavel
              if(new1 -> value ->val->exp -> expoente == new2 -> value->val-> exp -> expoente){ //se tem o mesmo expoente
                flag = false;
                contsAux = new2 -> value ->val->exp -> coeficiente + contsAux;
                new2 = new2 -> next;
                removeItem(lista,indexLocal);

              }
            }
          }
          //Se nao entrou no ultimo if a flag estara a  true
          if(flag){
            flag = true;
            new2 = new2 -> next;
            ++indexLocal;
          }
        }
        //printf("Estou aqui %d \n",contsAux);
        new1 -> value ->val-> exp -> coeficiente = contsAux;
        //printf("Estou aqui\n");
        break;

      //Caso para se for uma constante
      case Consta:
        contsAux = new1 -> value ->val-> constante;
        indexLocal = index+1;
        while (new2 != NULL) {
          if (new2 -> value -> flag==Consta) {
            contsAux = new1 -> value -> val->constante + contsAux;
            new2 = new2 -> next;
            removeItem(lista, indexLocal);
          }
          else{
            new2 = new2 -> next;
            ++indexLocal;
          }
        }
        new1 -> value -> val->constante = contsAux;
        break;
    }
    //avanco para o proximo no do new1
    new1 = new1 -> next;
    ++index;
  }
}

void derivate(List *lista,char target){
  Item *newp = lista -> first;
  int index = 0;
  while (newp != NULL) {
    switch (newp -> value -> flag) {
      case Expre:
        if(newp -> value -> val->exp -> variavel != target)
          break;
        if(newp -> value -> val->exp -> expoente == 1){
          int aux = newp -> value->val-> exp -> coeficiente;
          newp = newp -> next;
          removeItem(lista,index);
          addOn(lista,newConstante(aux),index);
          ++index;
          continue;
        }
        else{
          newp -> value ->val->exp-> coeficiente = newp -> value ->val->exp-> coeficiente * newp -> value ->val->exp-> expoente;
          newp -> value ->val->exp-> expoente = newp -> value ->val->exp-> expoente - 1;
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

List *soma(List *lista1, List *lista2){
  normalize(lista1);
  normalize(lista2);

  Item *newp1 = lista1 -> first;

  while(newp1 != NULL){
    Item *newp2 = lista2 -> first;
    bool flag = false;
    int index= 0;
    while (newp2 != NULL) {
      switch (newp2 -> value -> flag) {
        case Expre:
        if(newp1 -> value -> flag==Expre){
          if (newp1 -> value ->val->exp -> variavel == newp2 -> value ->val->exp -> variavel){
            if(newp1 -> value ->val->exp -> expoente == newp2 -> value ->val->exp -> expoente){
              newp1 -> value ->val->exp -> coeficiente = newp1 -> value ->val->exp -> coeficiente + newp2 -> value ->val->exp -> coeficiente;
              removeItem(lista2,index);
            }
          }
          flag = true;
        }

        case Consta:
        if(newp1 -> value -> flag==Expre){
          flag = true;
          newp1 -> value -> val -> constante = newp1 -> value -> val -> constante + newp2 -> value -> val -> constante;
          removeItem(lista2,index);
        }
      }
      if (flag){
        break;
      }
      else
      ++index;
    }
    newp1 = lista1 -> end;
    newp1 -> next = lista2 -> first;
    //teste
    free(lista2);
  }
}

void integrate(List *lista,char target){
  int aux;
  Item *newp = lista -> first;
  int index = 0;
  while (newp != NULL) {
    switch (newp -> value -> flag) {
      case Expre:
        if(newp -> value ->val->exp -> variavel != target)
          break;
        else{
          newp -> value ->val->exp-> expoente = newp -> value ->val->exp-> expoente + 1;
          newp -> value ->val->exp-> coeficiente = newp -> value ->val->exp-> coeficiente / newp -> value ->val->exp-> expoente;
        }
        break;

      case Consta:
        aux = newp -> value-> val -> constante;
        newp = newp -> next;
        removeItem(lista,index);
        addOn(lista,newExpre(aux,target,1),index);
        ++index;
        continue;
        break;
    }
    newp = newp -> next;
    ++index;
  }
}

int main(int argc, char const *argv[]) {
  List *lista = newList();
  //printf("Inserir mais um");
  int coeficiente;
  char variavel;
  int expoente;
  int aux;
  scanf("%d",&aux);
  while (aux != 42) {
    printf("Novo Polinomio\n");
    scanf("%d %c %d",&coeficiente,&variavel,&expoente);
    if(variavel == '-'){
      add(lista,newConstante(coeficiente));
    }
    else{
//      printf("%d %c %d\n",coeficiente, variavel,expoente );
      add(lista,newExpre(coeficiente,variavel,expoente));
    }
    scanf("%d",&aux);
  }
  normalize(lista);
  printList(lista);
  derivate(lista,'x');
  printList(lista);
  integrate(lista,'x');
  printList(lista);
  return 0;
}
