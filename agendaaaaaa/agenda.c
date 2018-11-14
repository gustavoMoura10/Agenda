#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct Agenda Agenda;
struct Agenda
{
    int dia;
    int mes;
    int ano;
    char evento[500];
    Agenda *prox;
};
int tam;
void inicia(Agenda *agenda)
{
    agenda->prox = NULL;
    tam = 0;
}
int menu()
{
    int opt;
    printf("Escolha a opcao \n");
    printf("0) Sair \n");
    printf("1) Zerar lista \n");
    printf("2) Exibir lista \n");
    printf("3) Adicionar informacao no inicio \n");
    printf("4) Adicionar informacao no fim \n");
    printf("5) Escolher onde inserir informacao \n");
    printf("6) Retirar do inicio \n");
    printf("7) Retirar do fim \n");
    printf("8) Escolher onde tirar \n");
    printf("Opcao:");
    scanf("%d", opt);
    return opt;
}
int vazia(Agenda *agenda)
{
    if (agenda->prox == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
Agenda *aloca()
{
    Agenda *aloca = (Agenda *)malloc(sizeof(Agenda));
    if (aloca == NULL)
    {
        return NULL;
    }
    else
    {
        printf("Digite o dia:");
        scanf("%d", &aloca->dia);
        printf("Digite o mes:");
        scanf("%d", &aloca->mes);
        printf("Digite o ano:");
        scanf("%d", &aloca->ano);
        printf("Digite o evento:");
        scanf("%s", &aloca->evento);
        return aloca;
    }
}
void libera(Agenda *agenda)
{
    if (!vazia(agenda))
    {
        Agenda *proximo, *atual;
        atual = agenda->prox;
        while (atual != NULL)
        {
            proximo = atual->prox;
            free(atual);
            atual = proximo;
        }
    }
}
void exibe(Agenda *agenda)
{
    if (vazia(agenda))
    {
        printf("Lista vazia \n");
        return;
    }
    Agenda *temporaria;
    temporaria = agenda->prox;
    printf("Lista:");
    while (temporaria != NULL)
    {
        printf("%d-", temporaria->dia);
        printf("%d-", temporaria->mes);
        printf("%d \n", temporaria->ano);
        printf("%s \n", temporaria->evento);
        temporaria = temporaria->prox;
    }
}
void insereFim(Agenda *agenda)
{
    Agenda *novo = aloca();
    novo->prox = NULL;
    if(novo != NULL){
    if (vazia(agenda))
    {
        agenda->prox = novo;
    }
    else
    {
        Agenda *temporaria = agenda->prox;
        while (temporaria->prox != NULL)
        {
            temporaria = temporaria->prox;
        }
        temporaria->prox = novo;
    }
    tam++;    	
	}else{
		printf("Sem memoria \n");
	}

}
void insereInicio(Agenda *agenda)
{
    Agenda *novo = aloca();
    if(novo != NULL){
    	    Agenda *old = agenda->prox;
    agenda->prox = novo;
    novo->prox = old;
    tam++;
	}else{
		printf("Sem memoria \n");
	}

}
void insere(Agenda *agenda)
{
    int pos, count;
    printf("Em que posicao, [1 ate %d] voce deseja inserir \n", tam);
    scanf("%d", &pos);
    if (pos > 0 && pos <= tam)
    {
        if (pos == 1)
        {
            insereInicio(agenda);
        }
        else
        {
            Agenda *atual = agenda->prox, *anterior = agenda;
            Agenda *novo = aloca();
            if(novo != NULL){
            	            for (count = 1; count < pos; count++)
            {
                anterior = atual;
                atual = atual->prox;
            }
            anterior->prox = novo;
            novo->prox = atual;
            tam++;
			}else{
				printf("Sem memoria \n");
			}

        }
    }
    else
    {
        printf("Posicao invalida \n");
    }
}
void retiraInicio(Agenda *agenda)
{
    if (agenda->prox == NULL)
    {
        printf("Lista esta vazia \n");
    }
    else
    {
        Agenda *temporaria = agenda->prox;
        agenda->prox = temporaria->prox;
        tam--;
    }
}
void retiraFim(Agenda *agenda)
{
    if (agenda->prox == NULL)
    {
        printf("Lista vazia \n");
    }
    else
    {
        Agenda *ultimo = agenda->prox, *penultimo = agenda;
        while (ultimo->prox != NULL)
        {
            penultimo = ultimo;
            ultimo = ultimo->prox;
        }
        penultimo->prox = NULL;
        tam--;
    }
}
void retira(Agenda *agenda)
{
    int opt, count;
    printf("Que posicao, [1 ate %d] voce deseja retirar:",tam);
    scanf("%d", &opt);
    if (opt > 0 && opt <= tam)
    {
        if (opt == 1)
        {
            return retiraInicio(agenda);
        }
        else
        {
        	Agenda *atual = agenda->prox,
        	*anterior = agenda;
        	for(count = 1;count<opt;count++){
        		anterior = atual;
        		atual = atual->prox;
			}
			anterior->prox=atual->prox;
			tam--;
        }
    }else{
    	printf("Posicao invalida \n");
	}
}
void opcao(Agenda *agenda, int opcao)
{
    switch (opcao)
    {
    case 0:
        libera(agenda);
        break;
    case 1:
        libera(agenda);
        inicia(agenda);
        break;
    case 2:
        exibe(agenda);
        break;
    case 3:
        insereFim(agenda);
        break;
    case 4:
        insereInicio(agenda);
        break;
    case 5:
        insere(agenda);
        break;
    case 6:
        retiraInicio(agenda);
        break;
    case 7:
        retiraFim(agenda);
        break;
    case 8:
        retira(agenda);
        break;
    }
}
int main()
{
	Agenda *agenda = (Agenda *) malloc(sizeof(Agenda));
	if(agenda != NULL){
		inicia(agenda);
		int opt;
		do{
			opt = menu();
			opcao(agenda,opt);
		}while(opt == 0);
		free(agenda);
	} else{
		printf("Sem memoria suficiente \n");
	}
    return 0;
}
