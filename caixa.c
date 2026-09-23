#include <stdio.h>
#include <string.h>
#include <ctype.h>

void converterParaMinusculo(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int main() {
    FILE *arquivo;

    char itemProcurado[50];
    char nomeProduto[50];
    
    char itemProcuradoMin[50];
    char nomeProdutoMin[50];

    float preco, totalComImpostos, total = 0, valorPago, troco;

    float ICMS = 22.0, PIS = 1.65, COFINS = 7.6;
    float impostos = ICMS + PIS + COFINS;

    arquivo = fopen("lista.txt", "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }

    while (1) {
        printf("\nQual produto o cliente deseja comprar? (Digite '1' para fechar a conta)\n");
        
        scanf(" %49[^\n]", itemProcurado);

        if (strcmp(itemProcurado, "1") == 0) {
            break;
        }

        strcpy(itemProcuradoMin, itemProcurado);
        converterParaMinusculo(itemProcuradoMin);

        rewind(arquivo);
        
        int encontrado = 0;

        while (fscanf(arquivo, "%49[^;]; %f\n", nomeProduto, &preco) == 2) {
            
            strcpy(nomeProdutoMin, nomeProduto);
            converterParaMinusculo(nomeProdutoMin);

            if (strcmp(itemProcuradoMin, nomeProdutoMin) == 0) {
                total += preco;
                encontrado = 1;
                printf("=> '%s' adicionado! (Preco: R$ %.2f)\n", nomeProduto, preco);
                break;
            }
        }

        if (!encontrado) {
            printf("=> Produto '%s' nao encontrado na lista.\n", itemProcurado);
        }
    }

    fclose(arquivo);

totalComImpostos = total + (total * impostos / 100);

printf("\n==================================\n");
printf("O total dos itens e: R$ %.2f\n", total);
printf("Impostos a serem cobrados: ICMS: %.2f, PIS: %.2f, COFINS: %.2f\n", ICMS, PIS, COFINS);
printf("O total a pagar e: R$ %.2f\n", totalComImpostos);
printf("==================================\n");

printf("\nTotal pago pelo cliente\n");
scanf("%f", &valorPago);

troco = valorPago - totalComImpostos;
printf("\nTroco a ser devolvido: R$ %.2f\n", troco);

printf("\nAtendimento encerrado. Obrigado!\n");

    return 0;
}
