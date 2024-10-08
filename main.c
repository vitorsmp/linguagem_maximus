#include <stdio.h>
#include <stdlib.h>
#include "lexico.h"

void imprimirTokens(Lexer *lexer) {
    Token token;
    printf("%-20s %-30s %-10s\n", "Tipo Token", "Lexema", "Linha");
    printf("--------------------------------------------------------------\n");

    do {
        token = obterProximoToken(lexer);
        printf("%-20s %-30s %-10d\n", tipoTokenParaString(token.tipo), token.lexema, token.linha);
    } while (token.tipo != EOF_TOKEN);
}

char *lerArquivo(const char *nomeArquivo) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo %s\n", nomeArquivo);
        exit(1);
    }

    fseek(arquivo, 0, SEEK_END);
    long tamanhoArquivo = ftell(arquivo);
    rewind(arquivo);

    char *buffer = (char *)malloc(tamanhoArquivo + 1);
    if (buffer == NULL) {
        fprintf(stderr, "Erro ao alocar memória\n");
        exit(1);
    }

    fread(buffer, 1, tamanhoArquivo, arquivo);
    buffer[tamanhoArquivo] = '\0';
    fclose(arquivo);

    return buffer;
}

int main() {
    const char *nomeArquivo = "../codigo.txt";
    char *codigoFonte = lerArquivo(nomeArquivo);

    Lexer lexer;
    inicializarLexer(&lexer, codigoFonte);

    imprimirTokens(&lexer);

    free(codigoFonte);
    return 0;
}
