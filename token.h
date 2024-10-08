#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    PALAVRA_CHAVE,
    IDENTIFICADOR,
    LITERAL,
    OPERADOR,
    DELIMITADOR,
    DESCONHECIDO,
    EOF_TOKEN,
    DIRETIVA_PRE_PROCESSAMENTO
} TipoToken;

typedef struct {
    TipoToken tipo;
    char lexema[100];
    int linha;
    int coluna;
} Token;

#endif
