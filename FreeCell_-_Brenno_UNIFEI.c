#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>

int erro;

typedef struct noCarta
{
    short numero;
    char nape;
    struct noCarta *prox;
} tCarta;

tCarta *primMonte = NULL;
tCarta *primMesa[] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
tCarta *primNape[] = {NULL,NULL,NULL,NULL};
tCarta *temp[] = {NULL,NULL,NULL,NULL};

bool ehVermelho(tCarta *carta)
{
    return ((carta->nape>=3) && (carta->nape<=4));
}//end ehVermelho

bool ehPreto(tCarta *carta)
{
    return ((carta->nape>=5)&&(carta->nape<=6));
}//end ehPreto

bool saoCoresDiferentes(tCarta *carta1, tCarta *carta2)
{
    return ((ehVermelho(carta1)&&ehPreto(carta2))||
            (ehPreto(carta1)&&ehVermelho(carta2)));
}//end saoCoresDiferentes

void gerarBaralho()
{
    int i,j;
    tCarta *ult;

    //coracao=3, ouro=4, paus=5, espada=6
    for(i=0; i<4; i++)
    {
        for(j=1; j<14; j++)
        {
            if(primMonte==NULL)
            {
                primMonte = (tCarta *)malloc(sizeof(tCarta));
                ult = primMonte;
            }//end if
            else
            {
                ult->prox=(tCarta *)malloc(sizeof(tCarta));
                ult=ult->prox;
            }//end else
            ult->nape=i+3;
            ult->numero=j;
            ult->prox=NULL;
        }//end for j
    }//end for i
}//end gerarBaralho

void embaralhaBaralho()
{
    int i,j,sort;
    tCarta *ant, *atual;

    for(i=0; i<26; i++)
    {
        //total de mudanca
        sort=rand()%52;
        ant=NULL;
        atual=primMonte;
        for(j=0; j<sort; j++)
        {
            //localizar a carta no monte
            ant = atual;
            atual=atual->prox;
        }//end for j
        if(sort>0)
        {
            ant->prox=atual->prox;
            atual->prox=primMonte;
            primMonte=atual;
        }//end if
    }//end for i
}//end embaralhaBaralho

void distribuirMesa()
{
    int i=0;
    tCarta *auxMonte, *auxMesa;

    while(primMonte != NULL)
    {
        auxMonte = primMonte;
        primMonte=primMonte->prox;

        if(primMesa[i]==NULL)
        {
            primMesa[i]=auxMonte;
            primMesa[i]->prox=NULL;
        }//end if
        else
        {
            auxMesa=primMesa[i];
            primMesa[i]=auxMonte;
            primMesa[i]->prox=auxMesa;
        }//end else
        if(primMonte==NULL)
        {
            break;
        }//end if
        i=(i+1)%8;
    }//end while
}//end distribuirMesa

void imprime()
{
    int i;
    tCarta *atual;

    printf("[TEMP]=");
    for(i=0; i<4; i++)
    {
        if(temp[i]!=NULL)
        {
            printf("%d[%2d%c] ", i, temp[i]->numero,temp[i]->nape);
        }//end if
        else
        {
            printf("%d[    ] ", i);
        }//end else
    }//end for i
    printf("\n\n");
    for(i=0; i<4; i++)
    {
        atual=primNape[i];
        printf("[NAPE %d]=", i);
        while(atual!=NULL)
        {
            printf(" %2d%c ", atual->numero,atual->nape);
            atual=atual->prox;
        }//end while
        printf("\n");
    }//end for i
    printf("\n");
    for(i=0; i<8; i++)
    {
        atual=primMesa[i];
        printf("[MESA %d]=", i);
        while(atual!=NULL)
        {
            printf(" %2d%c ", atual->numero, atual->nape);
            atual=atual->prox;
        }//end while
        printf("\n");
    }//end for i
    printf("\n");

    printf("-----------------------------------------------------------------\n");
    mensagem();
    printf("-----------------------------------------------------------------\n");

}//end imprime

void moveMesaNape()
{
    int posMesa, posNape;
    tCarta *aux, *ant, *atual;

    printf("Posicao Pilha Mesa (0-7): ");
    scanf("%d", &posMesa);
    getchar();
    if((posMesa>=0)&&(posMesa<=7)&&(primMesa[posMesa]!=NULL))
    {
        printf("Posicao Nape (0-3): ");
        scanf("%d", &posNape);
        getchar();
        ant = NULL;
        atual=primMesa[posMesa];
        while(atual->prox!=NULL)
        {
            ant=atual;
            atual=atual->prox;
        }//end while
        if((posNape>=0)&&(posNape<=3)&&
                (((atual->numero==1)&&(primNape[posNape]==NULL))||
                 ((primNape[posNape]!=NULL)&&
                  (atual->nape==primNape[posNape]->nape)&&
                  (atual->numero-1==primNape[posNape]->numero))))
        {
            if(ant==NULL)
            {
                primMesa[posMesa]=NULL;
            }
            else
            {
                ant->prox=NULL; /*         AAAAATEEEEEEEEEEENNNNNNNNNNNÇÇÇÇÇÇÇÃÃÃÃÃÃÃOOOOOOOOOOOOOOOOOO*/
            }//end else
            if(primNape[posNape]==NULL)
            {
                primNape[posNape]=atual;
            }//end if
            else
            {
                aux = primNape[posNape];
                primNape[posNape]=atual;
                primNape[posNape]->prox=aux;
            }//end else
        }//end if
        else
        {
            erro = 5;
        }//end else
    }//end if
    else
    {
        erro = 1;
    }//end else
}//end moveMesaNape

void moveMesaTemp()
{
    int posMesa, posTemp;
    tCarta *ant, *atual, *aux;

    printf("Posicao Pilha Mesa (0-7): ");
    scanf("%d", &posMesa);
    getchar();
    if((posMesa>=0)&&(posMesa<=7)&&(primMesa[posMesa]!=NULL))
    {
        printf("Posicao Temp (0-3): ");
        scanf("%d", &posTemp);
        getchar();
        ant=NULL;
        atual=primMesa[posMesa];
        while(atual->prox!=NULL)
        {
            ant=atual;
            atual=atual->prox;
        }//end while
        if((posTemp>=0)&&(posTemp<=3)&&(temp[posTemp]==NULL))
        {
            if(ant==NULL)
            {
                primMesa[posMesa]=NULL;
            }
            else
            {
                ant->prox=NULL;    /*         AAAAATEEEEEEEEEEENNNNNNNNNNNÇÇÇÇÇÇÇÃÃÃÃÃÃÃOOOOOOOOOOOOOOOOOO*/
                temp[posTemp]=atual;  /*         AAAAATEEEEEEEEEEENNNNNNNNNNNÇÇÇÇÇÇÇÃÃÃÃÃÃÃOOOOOOOOOOOOOOOOOO*/
            }//end else
        }//end if
        else
        {
            erro = 3;
        }//end else
    }//end if
    else
    {
        erro = 1;
    }//end else
}//end moveMesaTemp

void moveTempMesa()
{
    int posTemp, posMesa;
    tCarta *atual;
    printf("Posicao Temp (0-3): ");
    scanf("%d",&posTemp);
    getchar();
    if((posTemp>=0)&&(posTemp<=3)&&(temp[posTemp]!=NULL))
    {
        printf("Posicao Pilha Mesa (0-7): ");
        scanf("%d", &posMesa);
        getchar();
        if((posMesa>=0)&&(posMesa<=7))
        {
            if(primMesa[posMesa]==NULL)
            {
                primMesa[posMesa]=temp[posTemp];
                temp[posTemp]=NULL;
            }//end if
            else
            {
                atual=primMesa[posMesa];
                while(atual->prox!=NULL)
                {
                    atual=atual->prox;
                }//end while
                if((saoCoresDiferentes(temp[posTemp],atual))&&
                        ((atual->numero-1==temp[posTemp]->numero)))
                {
                    atual->prox=temp[posTemp];
                    temp[posTemp]=NULL;
                }//end if
                else
                {
                    erro = 5;
                }//end else
            }//end else
        }//end if
    }//end if
    else
    {
        erro = 3;
    }//end else
}//end moveTempMesa

void moveNapeTemp()
{
    int tempo, naipe;
    tCarta *aux;

    printf("\t  Informe a pilha de Naipe da qual deseja retirar a carta: ");
    scanf("%d", &naipe);

    if(naipe>= 0 && naipe<= 3)
    {
        if(primNape[naipe]!=NULL)
        {

            printf("\t  Informe a pilha de TEMP em que deseja colocar a carta: ");
            scanf("%d", &tempo);

            if(tempo>= 0 && tempo <= 3)
            {
                if(temp[tempo]==NULL)
                {
                    aux = primNape[naipe];
                    primNape[naipe] = primNape[naipe]->prox;
                    aux->prox = temp[tempo];
                    temp[tempo] = aux;
                }
                else
                {
                    erro = 4;
                }
            }
            else
            {
                erro = 5;
            }
        }
        else
        {
            erro = 2;
        }
    }
    else
    {
        erro = 2;
    }
}
void moveTempNape()
{
    int posTemp, posNape;
    tCarta *aux, *ant, *atual;

    printf("Posicao Pilha Temp (0-3): ");
    scanf("%d", &posTemp);
    getchar();
    if((posTemp>=0)&&(posTemp<=3)&&(temp[posTemp]!=NULL)) //verifica se local de temp é valido
    {
        printf("Posicao Nape (0-3): ");
        scanf("%d", &posNape);
        getchar();
        ant = NULL;
        atual=temp[posTemp];
        while(atual->prox!=NULL)
        {
            ant=atual;
            atual=atual->prox;
        }//end while
        if((posNape>=0)&&(posNape<=3)&&
                (((atual->numero==1)&&(primNape[posNape]==NULL))||
                 ((primNape[posNape]!=NULL)&&
                  (atual->nape==primNape[posNape]->nape)&&
                  (atual->numero-1==primNape[posNape]->numero))))
        {
            if(ant==NULL)
            {
                temp[posTemp]=NULL;
            }
            else
            {
                ant->prox=NULL;
            }//end else
            if(primNape[posNape]==NULL)
            {
                primNape[posNape]=atual;
            }//end if
            else
            {
                aux = primNape[posNape];
                primNape[posNape]=atual;
                primNape[posNape]->prox=aux;
            }//end else
        }//end if
        else
        {
            erro = 5;
        }//end else
    }//end if
    else
    {
        erro = 3;
    }//end else
}

void moveNapeMesa()
{
    int posNape, posMesa;
    tCarta *atual, *aux;
    printf("Posicao nape (0-3): ");
    scanf("%d",&posNape);
    getchar();
    if((posNape>=0)&&(posNape<=3)&&(primNape[posNape]!=NULL))   //verifica se naipe solicitado é valido
    {
        printf("Posicao Pilha Mesa (0-7): ");
        scanf("%d", &posMesa);
        getchar();
        if((posMesa>=0)&&(posMesa<=7))
        {
            if(primMesa[posMesa]==NULL)
            {
                primMesa[posMesa]=primNape[posNape];    //Coloca a carta na primeira posição
                primNape[posNape]=NULL;
            }
            else
            {
                atual=primMesa[posMesa];
                while(atual->prox!=NULL)    // Percorre a mesa até a última posiçao
                {
                    atual=atual->prox;
                }//end while
                if((saoCoresDiferentes(primNape[posNape],atual))&&
                        ((atual->numero-1==primNape[posNape]->numero)))
                {
                    aux = primNape[posNape];
                    primNape[posNape] = primNape[posNape]->prox;
                    atual->prox = aux;
                    aux->prox=NULL;
                }
                else
                {
                    erro = 5;
                }//end else
            }//end else
        }//end if
    }
    else
    {
        printf("nape vazio\n");
    }//end else
}

void moveMesaMesa()
{
    tCarta *Carta,*aux,*ini, *atual,*penultimo;
    int posMesa1=75,posMesa2=99,i,op;

    if((posMesa1<0)||(posMesa1>=8))
    {
        if(posMesa1!=75)
        {
            erro = 1;
        }//end for
        printf("Indique a mesa de origem: ");
        scanf(" %d",&posMesa1);
    }//end while

    if((posMesa2<0)||(posMesa2>=8)) //verifica se posição da mesa é valida
    {
        if(posMesa2!=99)
        {
            erro = 1;
        }//end for
        printf("Indique a mesa de destino: ");
        scanf(" %d",&posMesa2);
    }//end while

    if(primMesa[posMesa1]==NULL)
    {
        erro = 6;
        return;
    }

    //
    ini = primMesa[posMesa1];
    aux = primMesa[posMesa1];
    atual = primMesa[posMesa1];
    while(atual!=NULL)
    {
        if(((aux->nape == 3)||(aux->nape == 4))&&((atual->nape == 6)||(atual->nape == 5))&&(aux->numero - atual->numero == 1))          // faz a verificaçao do movimento
        {
            aux = atual;
            atual = atual->prox; //percorre as cartas enquanto condição for válida
        }
        else if(((aux->nape == 5)||(aux->nape == 6))&&((atual ->nape == 3)||(atual->nape == 4))&&(aux->numero - atual->numero == 1)) // faz a verificaçao do movimento (cores inversas)
        {
            aux = atual;
            atual = atual->prox;    //percorre as cartas enquanto condição for válida
        }
        else
        {
            aux = atual;
            ini = aux;
            atual = atual->prox;
        }//end else
    }//end while


    //encontra penultimo
    penultimo = primMesa[posMesa1];
    while((penultimo->prox!=ini)&&(penultimo!=ini))
    {
        penultimo = penultimo->prox;
    }//end while

    if(primMesa[posMesa2]==NULL)
    {
        primMesa[posMesa2] = ini;
        if(primMesa[posMesa1]==ini)
        {
            primMesa[posMesa1] = NULL;
        }
        else
        {
            penultimo->prox = NULL;
        }
        return;
    }//end if mesa 2 vazia

    Carta = primMesa[posMesa2];
    while(Carta->prox!=NULL)
    {
        Carta = Carta->prox;
    }



    if(((Carta->nape == 3)||(Carta->nape == 4))&&((ini->nape == 6)||(ini->nape == 5))&&(Carta->numero - ini->numero == 1))
    {
        Carta->prox = ini;
        if(primMesa[posMesa1]==ini)
        {
            primMesa[posMesa1] = NULL;
        }
        else
        {
            penultimo->prox = NULL;
        }
    }
    else if(((Carta->nape == 5)||(Carta->nape == 6))&&((ini ->nape == 3)||(ini->nape == 4))&&(Carta->numero - ini->numero == 1))
    {
        Carta->prox = ini;
        if(primMesa[posMesa1]==ini)
        {
            primMesa[posMesa1] = NULL;
        }
        else
        {
            penultimo->prox = NULL;
        }
    }
    else
    {
        erro = 5;
        return;
    }
    return;
}


void mensagem()
{
    printf("   ");
    switch(erro)
    {
    case 1:
        printf(" * * * ERRO: NAO EH POSSIVEL ESCOLHER MESA * * * \n");
        break;
    case 2:
        printf(" * * * ERRO: NAO EH POSSIVEL ESCOLHER NAIPE * * * \n");
        break;
    case 3:
        printf(" * * * ERRO: NAO EH POSSIVEL ESCOLHER TEMP * * * \n");
        break;
    case 4:
        printf(" * * * ERRO: TEMP JA OCUPADA OU INEXISTENTE * * * \n");
        break;
    case 5:
        printf(" * * * ERRO: MOVIMENTO INVALIDO * * * \n");
        break;
    case 6:
        printf(" * * * ERRO: O LOCAL ESTA VAZIO * * * \n");
        break;
    default:
        printf(" ORGANIZE AS CARTAS POR NAIPE NAS REGIOES ""NAIPE"" \n");
        break;
    }
    erro = 0;
}

int main(int argc, char **argv)
{
    int op=0;
    srand(time(NULL));
    gerarBaralho();
    embaralhaBaralho();
    distribuirMesa();

    while(op!=8)
    {
        system("cls");
        imprime();
        printf("    COMANDOS:\n");
        printf("    1.  Move da Mesa para o Naipe          5.  Move do temp para o naipe\n");
        printf("    2.  Move da Mesa para o Temp           6.  Move do naipe para a mesa\n");
        printf("    3.  Move do Temp para a Mesa           7.  Move de uma mesa para outra\n");
        printf("    4.  Move do Naipe para o Temp          8.  Sair\n");
        printf("-----------------------------------------------------------------\n");
        printf("  COMANDO ESCOLHIDO: ");
        scanf("%d", &op);
        getchar();
        switch(op)
        {
        case 1:
            moveMesaNape();
            break;
        case 2:
            moveMesaTemp();
            break;
        case 3:
            moveTempMesa();
            break;
        case 4:
            moveNapeTemp();
            break;
        case 5:
            moveTempNape();
            break;
        case 6:
            moveNapeMesa();
            break;
        case 7:
            moveMesaMesa();
            break;
        case 8:
            printf("\n\n\n     F I M   D E  J O G O    \n\n\n\n");
            break;
        default:
            printf("Opcao Invalida\n");
            break;
        }//end switch
    }//end while
    return 0;
}//end main
