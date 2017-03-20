#include <stdlib.h>

typedef struct Monom Monom;
typedef struct Expressao Expressao;
typedef union Valor Valor;

struct Expressao{
  int coeficiente;
  char variavel;
  int expoente;
};

union Valor{
  int constante;
  Expressao* exp;
};


struct Monom{
  enum {Expre, Consta} flag;

  Valor *val;
};

Monom *newExpre(int c, char v, int e);
Monom *newConstante(int c);
