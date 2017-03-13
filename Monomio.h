#include <stdlib.h>

typedef union Monom Monom;
typedef struct Expressao Expressao;
struct Expressao{
  int coeficiente;
  char variavel;
  int expoente;
};

union Monom{
  enum {Expre, Consta} flag;

  int constante;

  Expressao* exp;

};

Monom *newExpre(int c, char v, int e);
Monom *newConstante(int c);
