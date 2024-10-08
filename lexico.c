#include "lexico.h"
#include <ctype.h>
#include <string.h>

void inicializarLexer(Lexer *lexer, const char *fonte) {
    lexer->fonte = fonte;
    lexer->indiceAtual = 0;
    lexer->linha = 1;
    lexer->coluna = 1;
}

char avancar(Lexer *lexer) {
    lexer->coluna++;
    return lexer->fonte[lexer->indiceAtual++];
}

char espiar(Lexer *lexer) {
    return lexer->fonte[lexer->indiceAtual];
}

int estaNoFim(Lexer *lexer) {
    return lexer->fonte[lexer->indiceAtual] == '\0';
}

Token criarToken(TipoToken tipo, const char *lexema, int linha, int coluna) {
    Token token;
    token.tipo = tipo;
    strcpy(token.lexema, lexema);
    token.linha = linha;
    token.coluna = coluna;
    return token;
}

const char* tipoTokenParaString(TipoToken tipo) {
    switch (tipo) {
        case PALAVRA_CHAVE: return "PALAVRA_CHAVE";
        case IDENTIFICADOR: return "IDENTIFICADOR";
        case LITERAL: return "LITERAL";
        case OPERADOR: return "OPERADOR";
        case DELIMITADOR: return "DELIMITADOR";
        case DESCONHECIDO: return "DESCONHECIDO";
        case EOF_TOKEN: return "EOF_TOKEN";
        case DIRETIVA_PRE_PROCESSAMENTO: return "DIRETIVA_PRE_PROCESSAMENTO";
        default: return "TOKEN_DESCONHECIDO";
    }
}

Token obterProximoToken(Lexer *lexer) {
    while (!estaNoFim(lexer)) {
        char c = avancar(lexer);

        if (isspace(c)) {
            if (c == '\n') {
                lexer->linha++;
                lexer->coluna = 1;
            }
            continue;
        }

        if (c == '#') {
            int colunaInicial = lexer->coluna - 1;
            char lexema[100];
            int i = 0;
            lexema[i++] = c;

            while (isalnum(espiar(lexer))) {
                lexema[i++] = avancar(lexer);
            }
            lexema[i] = '\0';

            return criarToken(DIRETIVA_PRE_PROCESSAMENTO, lexema, lexer->linha, colunaInicial);
        }

        if (isalpha(c)) {
            char lexema[100];
            int colunaInicial = lexer->coluna - 1;
            int i = 0;
            lexema[i++] = c;
            while (isalnum(espiar(lexer)) || espiar(lexer) == '_') {
                lexema[i++] = avancar(lexer);
            }
            lexema[i] = '\0';

            if (strcmp(lexema, "num") == 0 || strcmp(lexema, "if") == 0 || strcmp(lexema, "tambem") == 0 || strcmp(lexema, "zonazul") == 0
                || strcmp(lexema, "mandeva") == 0 || strcmp(lexema, "txt") == 0 || strcmp(lexema, "recebaa") == 0) {
                return criarToken(PALAVRA_CHAVE, lexema, lexer->linha, colunaInicial);
            }
            return criarToken(IDENTIFICADOR, lexema, lexer->linha, colunaInicial);
        }

        if (isdigit(c)) {
            char lexema[100];
            int colunaInicial = lexer->coluna - 1;
            int i = 0;
            lexema[i++] = c;
            while (isdigit(espiar(lexer))) {
                lexema[i++] = avancar(lexer);
            }
            lexema[i] = '\0';
            return criarToken(LITERAL, lexema, lexer->linha, colunaInicial);
        }

        if (c == '+' || c == '-' || c == '=' || c == ';' || c == '<' || c == '>' || c == '<=' || c == '>=') {
            char lexema[2] = {c, '\0'};
            return criarToken(OPERADOR, lexema, lexer->linha, lexer->coluna - 1);
        }

        if (c == '(' || c == ')' || c == ':' || c == '{' || c == '}' || c == ',') {
            char lexema[2] = {c, '\0'};
            return criarToken(DELIMITADOR, lexema, lexer->linha, lexer->coluna - 1);
        }

        char lexema[2] = {c, '\0'};
        return criarToken(DESCONHECIDO, lexema, lexer->linha, lexer->coluna - 1);
    }

    return criarToken(EOF_TOKEN, "", lexer->linha, lexer->coluna);
}
