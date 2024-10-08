#ifndef LEXICO_H
#define LEXICO_H

#include "token.h"

typedef struct {
    const char *fonte;
    int indiceAtual;
    int linha;
    int coluna;
} Lexer;

void inicializarLexer(Lexer *lexer, const char *fonte);
Token obterProximoToken(Lexer *lexer);
const char* tipoTokenParaString(TipoToken tipo);

#endif
