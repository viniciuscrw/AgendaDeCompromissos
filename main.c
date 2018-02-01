#include "definicoes.h"

int main()
{
    setlocale(LC_ALL, "Portuguese");

    agenda *compromisso;
    int num=0, op_busca, res;
    char opcao;

    num = persisteNum();
    compromisso = malloc((num+1)*sizeof(agenda));

    if(num > 0)
        persisteDados(compromisso, num);

    do
    {
        system("cls");
        opcao = menu();

        switch(opcao)
        {
        case 'a':
            compromisso = (agenda *) realloc(compromisso, (num+1)*sizeof(agenda));

            if(compromisso)
            {
                num = cadastrar(compromisso, num);
            }
            else
                printf("Memória insuficiente.\n");

        break;
        case 'b':
            if(num)
            {
                alterar(compromisso, num);
            }

            else
                printf("Nenhum compromisso cadastrado.");
        break;
        case 'c':
            if(num)
            {
                printf("Buscar compromisso por:");
                printf("\n1. Palavra-chave no título ou descrição");
                printf("\n2. Data e hora");
                printf("\n\nOpção: "); scanf("%d", &op_busca);
                system("cls");

                switch(op_busca)
                {
                case 1:
                    res = buscaPalavraChave(compromisso, num);
                break;
                case 2:
                    res = buscaDataHora(compromisso, num);
                break;
                default:
                    printf("Opção inválida.");
                    res = 0;
                break;
                }

                if(res>0)
                {
                    res--;
                    printf("\n");
                    listar(compromisso, res, res+1);
                }
            }

            else
                printf("Nenhum compromisso cadastrado.");
        break;
        case 'd':
            if(num)
            {
                printf("Visualizar compromissos por:\n");
                printf("1. Compromissos do dia\n2. Compromissos da semana\n3. Compromissos do mês\n4. Ordem cronológica\n");
                printf("\nOpção: "); scanf("%d", &op_busca);

                ordemCronologica(compromisso, num);
                system("cls");

                switch(op_busca)
                {
                case 1:
                    printf("Compromissos de hoje:\n\n");
                    listaPorDia(compromisso, num);
                break;
                case 2:
                    printf("Compromissos da semana:\n\n");
                    listaPorSemana(compromisso, num);
                break;
                case 3:
                    printf("Compromissos do mes:\n\n");
                    listaPorMes(compromisso, num);
                break;
                case 4:
                    listar(compromisso, 0, num);
                break;
                default:
                    printf("Opção inválida.");
                break;
                }
            }

            else
                printf("Nenhum compromisso cadastrado.");
        break;
        case 'e':
            if(num)
            {
                printf("Remover compromisso:\n");
                printf("1. Todos os compromissos passados\n");
                printf("2. Selecionar compromisso\n");
                printf("\nOpção: "); scanf("%d", &op_busca);
                system("cls");

                switch(op_busca)
                {
                case 1:
                    num = removerAnteriores(compromisso, num);
                break;
                case 2:
                    num = removerCompromisso(compromisso, num);
                break;
                default:
                    printf("Opção inválida.");
                break;
                }
            }

            else
                printf("Nenhum compromisso cadastrado.");
        break;
        case 'f':
            free(compromisso);
            return 0;
        break;
        default:
            printf("Opção inválida.");
        break;
        }

        printf("\n\nPressione qualquer tecla para retornar ao menu...");
        getch();

    }while(opcao!='f');

    free(compromisso);

    return 0;
}
