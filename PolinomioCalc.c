#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "LinkedList.h"
#include <ctype.h>
#include <readline/readline.h>
#include <readline/history.h>


#define MAXARGS 100

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

void soma(List *lista1, List *lista2){
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
              flag = true;
            }
          }
        }
        break;

        case Consta:
        if(newp1 -> value -> flag==Expre){
          flag = true;
          newp1 -> value -> val -> constante = newp1 -> value -> val -> constante + newp2 -> value -> val -> constante;
          removeItem(lista2,index);
        }
        break;

      }
      if (flag){
        break;
      }
      else
      ++index;

      newp2 = newp2 -> next;
    }
    //printf("Saiu\n");
    newp1 = newp1 -> next;
    //teste
    //free(lista2);
  }
  newp1 = lista1 -> end;
  newp1 -> next = lista2 -> first;
  free(lista2);
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

Monom *parseMonom(char *token){
  char *aux1, *aux2, *aux3;

  //delimitadores
  const char delimiterEstrela[2] = "*";
  const char delimiterLevantado[2] = "^";
  aux1 = strtok(token,delimiterEstrela);
  aux2 = strtok(NULL,delimiterLevantado);
  //printf("%s %s\n",aux1,aux2 );
  if(aux2 == NULL){
    return newConstante(atoi(aux1));
  }
  else{
    aux3 = strtok(NULL,delimiterEstrela); //para meter nojo
    //printf("%s\n",aux3);
    return newExpre(atoi(aux1),aux2[0],atoi(aux3));
  }
}

void printHelp(){

}

int parse(char *linha){
  const char delimiter[2] = " ";
  const char delimiter2[2] = "+";
  char *token;
  char *resto;
  List *lista1;
  List *lista2;
  token = strtok(linha, delimiter);
  if(!strcmp(token,"exit")) return 0;
  if(!strcmp(token,"help")){ printHelp(); return 1;}

  //derivar
  if(!strcmp(token,"deriva")){
    token = strtok(NULL,delimiter);
    char target = token[0];
    lista1 = newList();
    token = strtok(NULL,delimiter2);
    resto = strtok(NULL,delimiter);
    while(token != NULL){
      //printf("%s %s\n",token,resto );
      add(lista1, parseMonom(token));
      token = strtok(resto,delimiter2);
      resto = strtok(NULL,delimiter);
    }
    //printList(lista1);
    derivate(lista1,target);
    putchar('\n');
    printList(lista1);
    putchar('\n');
    free(lista1);
    return 1;
  }

  //integra
  if(!strcmp(token,"integra")){
    token = strtok(NULL,delimiter);
    char target = token[0];
    lista1 = newList();
    token = strtok(NULL,delimiter2);
    resto = strtok(NULL,delimiter);
    while(token != NULL){
      //printf("%s %s\n",token,resto );
      add(lista1, parseMonom(token));
      token = strtok(resto,delimiter2);
      resto = strtok(NULL,delimiter);
    }
    //printList(lista1);
    integrate(lista1,target);
    putchar('\n');
    printList(lista1);
    putchar('\n');
    free(lista1);
    return 1;
  }

  //normaliza
  if(!strcmp(token,"normaliza")){
    lista1 = newList();
    token = strtok(NULL,delimiter2);
    resto = strtok(NULL,delimiter);
    while(token != NULL){
      //printf("%s %s\n",token,resto );
      add(lista1, parseMonom(token));
      token = strtok(resto,delimiter2);
      resto = strtok(NULL,delimiter);
    }
    //printList(lista1);
    normalize(lista1);
    putchar('\n');
    printList(lista1);
    putchar('\n');
    free(lista1);
    return 1;
  }

  //soma
  if(!strcmp(token,"soma")){
    lista1 = newList();
    lista2 = newList();
    token = strtok(NULL,delimiter);
    char *restBigger = strtok(NULL,delimiter);

    //lista 1
    token = strtok(token,delimiter2);
    resto = strtok(NULL,delimiter);
    while(token != NULL){
      //printf("%s %s\n",token,resto );
      add(lista1, parseMonom(token));
      token = strtok(resto,delimiter2);
      resto = strtok(NULL,delimiter);
    }

    //lista 2
    token = strtok(restBigger,delimiter2);
    resto = strtok(NULL,delimiter);
    while(token != NULL){
      //printf("%s %s\n",token,resto );
      add(lista2, parseMonom(token));
      token = strtok(resto,delimiter2);
      resto = strtok(NULL,delimiter);
    }
    soma(lista1, lista2);
    putchar('\n');
    printList(lista1);
    putchar('\n');
    return 1;
  }

  printf("Opção nao reconhecida!\n");
  printHelp();
  return -1;
}

int main(int argc, char const *argv[]) {
  while (1) {
      char *linha;
      if ((linha = readline(" >")) == NULL){
        putchar('\n');
        exit(0);
      }
      if (strlen(linha) != 0) {
        add_history(linha);
        int status = parse(linha);
        if(!status){
          putchar('\n');
          exit(0);
        }
      }
      free(linha);
    }
  return 0;
}
