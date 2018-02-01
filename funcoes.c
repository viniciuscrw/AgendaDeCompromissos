#include "definicoes.h"

int removerCompromisso(agenda *compromisso, int n)
{
    int result, select;
    char certeza;

    printf("REMOVER COMPROMISSO\n\n");
    result = buscaPalavraChave(compromisso, n);

    if(result<0) //mais de um compromisso com a mesma palavra-chave
    {
        printf("\nDigite o numero do compromisso que deseja remover: ");
        do {
            scanf("%d", &select);
            select--;
        }while((validaInput(select, 0, n, "Opcao")) == 0);
    }

    else if(!result)
        return n;

    else
    {
        select = --result;
        printf("\nCompromisso encontrado:\n\n");
        listar(compromisso, select, select+1);
    }

    do
    {
        printf("\nTem certeza que deseja remover compromisso? (y/n)\n");
        fflush(stdin);
        certeza = getchar();

        if(certeza == 'y' || certeza == 'Y')
        {
            removePosicao(compromisso, select, n-1);
            n--;
            reescreveDados(compromisso, n);
            system("cls");
            printf("Compromisso removido.");
        }

        else if(certeza == 'n' || certeza == 'N')
        {
            system("cls");
            printf("Operacao cancelada.");
            return n;
        }

        else printf("Opcao invalida.");
    }while(certeza != 'y' && certeza != 'Y' && certeza != 'N' && certeza != 'n');

    return n;
}

void removePosicao(agenda *compromisso, int ini, int n)
{
    int j;

    for(j=ini; j<n; j++)
    {
        strcpy(compromisso[j].titulo, compromisso[j+1].titulo);
        strcpy(compromisso[j].descricao, compromisso[j+1].descricao);
        strcpy(compromisso[j].local, compromisso[j+1].local);

        compromisso[j].data.dia = compromisso[j+1].data.dia;
        compromisso[j].data.mes = compromisso[j+1].data.mes;
        compromisso[j].data.ano = compromisso[j+1].data.ano;

        compromisso[j].horario.hora = compromisso[j+1].horario.hora;
        compromisso[j].horario.min = compromisso[j+1].horario.min;

        compromisso[j].alarme.hora = compromisso[j+1].alarme.hora;
        compromisso[j].alarme.min = compromisso[j+1].alarme.min;
    }
}

int removerAnteriores(agenda *compromisso, int n)
{
    int i, sys_dia, sys_mes, sys_ano, sys_hora, sys_min, found=0;

    dataDoSistema(&sys_dia, &sys_mes, &sys_ano);
    horaDoSistema(&sys_hora, &sys_min);
    ordemCronologica(compromisso, n);

    i = 0;

    while(compromisso[i].data.ano < sys_ano)
    {
        removePosicao(compromisso, i, n-1);
        found++;
        n--;;
    }

    while((compromisso[i].data.ano == sys_ano) && (compromisso[i].data.mes < sys_mes))
    {
        removePosicao(compromisso, i, n-1);
        found++;
        n--;
    }

    while((compromisso[i].data.ano == sys_ano) && (compromisso[i].data.mes == sys_mes) && (compromisso[i].data.dia < sys_dia))
    {
        removePosicao(compromisso, i, n-1);
        found++;
        n--;
    }

    while((compromisso[i].data.ano == sys_ano) && (compromisso[i].data.mes == sys_mes) && (compromisso[i].data.dia == sys_dia) && (compromisso[i].horario.hora < sys_hora))
    {
        removePosicao(compromisso, i, n-1);
        found++;
        n--;
    }

    while((compromisso[i].data.ano == sys_ano) && (compromisso[i].data.mes == sys_mes) && (compromisso[i].data.dia == sys_dia) && (compromisso[i].horario.hora == sys_hora) && (compromisso[i].horario.min < sys_min))
    {
        removePosicao(compromisso, i, n-1);
        found++;
        n--;
    }

    if(!found)
        printf("Nao existem compromissos anteriores ao momento de agora.");

    else
    {
       reescreveDados(compromisso, n);
       printf("Compromissos removidos.");
    }

    return n;
}

void horaDoSistema(int *hora, int *min)
{
    char strtime[9], strhora[3], strmin[3];
    int i, j;

    strcpy(strtime, __TIME__);

    for(i=0; i<2; i++)
    {
        strhora[i] = strtime[i];
    }

    strhora[2] = '\0';

    for(++i, j=0; strtime[i]!=':'; i++, j++)
    {
        strmin[j] = strtime[i];
    }

    strmin[2] = '\0';

    *hora = atoi(strhora);
    *min = atoi(strmin);
}

void trataString (char string[], int nc)
{
    int i;

    if(strlen(string) >= nc)
    {
        for(i=nc; i>=0; i--)
        {
            if(i <= nc  && string[i] == ' ')
            {
                string[i] = '\0';
                return;
            }
        }

        string[nc] = '\0';
    }
}

int validaCompromisso(agenda *compromisso, int index, int n)
{
    int i;

    for(i=0; i<n; i++)
    {
        if((compromisso[i].data.dia == compromisso[index].data.dia) && (compromisso[i].data.mes == compromisso[index].data.mes) && (compromisso[i].data.ano == compromisso[index].data.ano) && (compromisso[i].horario.hora == compromisso[index].horario.hora) && (compromisso[i].horario.min == compromisso[index].horario.min) && (i != index))
        {
            if(strcmp(compromisso[i].titulo, compromisso[index].titulo) == 0)
                return 0;
        }
    }

    return 1;
}

int validaData(int dia, int mes, int ano)
{
    int valido;

    if((dia<1 || dia>31) || (mes<1 || mes>12) || (ano<1500))
    {
        valido = 0;
    }

    if(dia == 31)
    {
        if(mes==2 || mes==4 || mes==6 || mes==9 || mes==11)
        {
            valido = 0;
        }
    }

    if(mes == 2)
    {
        if(dia > 29)
        {
            valido = 0;
        }

        if(!(((ano % 4 == 0) && (ano % 100 != 0)) || (ano % 400 == 0)) && dia==29)
        {
            valido = 0;
        }
    }

    if(!valido)
    {
        printf("Data invalida. Digite novamente: ");
        return 0;
    }

    return 1;
}

int validaInput(int valor, int min, int max, char msg[31])
{
    if(valor < min || valor > max)
    {
        printf("%s invalida. Digite novamente: ", msg);

        return 0;
    }

    return 1;
}

int getDiaDaSemana(int dia, int mes, int ano)
{
    int a, b, c, d, e, f, g, h, i, j;
    //Algoritmo para descobrir o dia da semana
    a = ((12 - mes) / 10);
    b = ano - a;
    c = mes + (12 * a);
    d = b / 100;
    e = d / 4;
    f = 2 - d + e;
    g = (int) (365.25 * b);
    h = (int) (30.6001 * (c + 1));
    i = (int) ((f + g) + (h + dia) + 5);
    j = (int) (i % 7); //Resto de I por 7, onde 0=SAB, 1=DOM, 2=SEG, 3=TER, 4=QUA, 5=QUI, 6=SEX

    return j;
}

int percorreSemanas(agenda *compromisso, int n, int domingo, int dias_faltando, int dia, int mes, int ano) //domingo = Número correspondente ao domingo em relaçao ao dia da semana
{                                                                                                           //(se o dia da semana é domingo, domingo = 0)
    int i, j, found=0;
    int anobusca, mesbusca, diabusca;

    for(i=0; i<n; i++)
        {
            j = domingo;
            if((compromisso[i].data.ano == ano || compromisso[i].data.ano == ano+1 || compromisso[i].data.ano == ano-1) && (compromisso[i].data.mes == mes || compromisso[i].data.mes == mes+1 || compromisso[i].data.mes == mes-1))
            {
                while (j<= dias_faltando)
                {
                    diabusca = dia+j;
                    anobusca = ano;
                    mesbusca = mes;

                    if(diabusca > 29)      //virada de mês/ano pra frente
                    {
                        if(mesbusca == 2)
                        {
                            mesbusca++;
                            diabusca -= 29;
                        }

                        if((diabusca > 30) && (mesbusca == 4 || mesbusca == 6 || mesbusca == 9 || mesbusca == 11))
                        {
                            mesbusca++;
                            diabusca -= 30;
                        }

                        if(diabusca > 31 && mesbusca == 12)     //virada de ano
                        {
                            diabusca -= 31;
                            mesbusca = 1;
                            anobusca++;
                        }

                        if(diabusca > 31)
                        {
                            mesbusca++;
                            diabusca -= 31;
                        }
                    }

                    else if(diabusca < 1)       //virada de mês/ano pra trás
                    {
                        if(mes == 1)        //virada de ano
                         {
                             mesbusca = 12;
                             anobusca--;
                         }

                        else mesbusca = mes-1;

                        if((mes-1) == 1 || (mes-1) == 3 || (mes-1) == 5 || (mes-1) == 7 || (mes-1) == 8 || (mes-1) == 10)
                            diabusca = 31 + (dia+j);

                        else if(mes-1 == 2)
                            diabusca = 29 + (dia+j);

                        else diabusca = 30 + (dia+j);
                    }

                    if((compromisso[i].data.dia == diabusca) && (compromisso[i].data.mes = mesbusca) && (compromisso[i].data.ano == anobusca))
                    {
                        listar(compromisso, i, (i+1));
                        found++;
                    }

                    j++;
                }
            }

            if(found>0)
                break;
        }

    return found;
}

void listaPorSemana(agenda *compromisso, int n)
{
    int found, dia, mes, ano, dia_semana;

    dataDoSistema(&dia, &mes, &ano);

    dia_semana = getDiaDaSemana(dia, mes, ano);

    switch(dia_semana)
    {
    case 0:     //Sábado
        found = percorreSemanas(compromisso, n, -6, 0, dia, mes, ano);
    break;
    case 1:     //Domingo
        found = percorreSemanas(compromisso, n, 0, 6, dia, mes, ano);
    break;
    case 2:     //Segunda
        found = percorreSemanas(compromisso, n, -1, 5, dia, mes, ano);
    break;
    case 3:     //Terça
        found = percorreSemanas(compromisso, n, -2, 4, dia, mes, ano);
    break;
    case 4:     //Quarta
        found = percorreSemanas(compromisso, n, -3, 3, dia, mes, ano);
    break;
    case 5:     //Quinta
        found = percorreSemanas(compromisso, n, -4, 2, dia, mes, ano);
    break;
    case 6:     //Sexta
        found = percorreSemanas(compromisso, n, -5, 1, dia, mes, ano);
    break;
    default:
        printf("Erro ao retornar o dia da semana.\n\n");
        system("pause");
        found = -1;
    break;
    }

    if(!found)
        printf("Nenhum compromisso agendado para essa semana.");
}

void listaPorDia(agenda *compromisso, int n)
{
    int i, found=0, dia, mes, ano;

    dataDoSistema(&dia, &mes, &ano);

    for(i=0; i<n; i++)
    {
        if((compromisso[i].data.ano == ano) && (compromisso[i].data.mes == mes) && (compromisso[i].data.dia == dia))
        {
            listar(compromisso, i, i+1);
            found++;
        }

        else if((found > 0) && (compromisso[i].data.dia != dia))
            break;
    }

    if(!found)
        printf("Nenhum compromisso agendado para hoje.");


}

void listaPorMes(agenda *compromisso, int n)
{
    int i, found=0, dia, mes, ano;

    dataDoSistema(&dia, &mes, &ano);

    for(i=0; i<n; i++)
    {
        if((compromisso[i].data.ano == ano) && (compromisso[i].data.mes == mes))
        {
            listar(compromisso, i, i+1);
            found++;
        }

        else if((found > 0) && (compromisso[i].data.mes != mes))
            break;
    }

    if(!found)
        printf("Nenhum compromisso agendado para este mês.");
}

int comparaMes(char mes[])
{
    if(strcmp(mes, "Jan") == 0)
       return 1;

    if(strcmp(mes, "Feb") == 0)
        return 2;

    if(strcmp(mes, "Mar") == 0)
        return 3;

    if(strcmp(mes, "Apr") == 0)
        return 4;

    if(strcmp(mes, "May") == 0)
        return 5;

    if(strcmp(mes, "Jun") == 0)
        return 6;

    if(strcmp(mes, "Jul") == 0)
        return 7;

    if(strcmp(mes, "Aug") == 0)
        return 8;

    if(strcmp(mes, "Sep") == 0)
        return 9;

    if(strcmp(mes, "Oct") == 0)
        return 10;

    if(strcmp(mes, "Nov") == 0)
        return 11;

    if(strcmp(mes, "Dec") == 0)
        return 12;

    else return 0;
}

void dataDoSistema (int *dia, int *mes, int *ano)
{
    char strdate[12], strano[5], strmes[4], strdia[3];
    int i, j;

    strcpy(strdate, __DATE__);      //Data do sistema (string)

    for(i=0; i<4; i++)
    {
        strmes[i] = strdate[i];     //Pega mes (string)
    }
    strmes[3] = '\0';

    for(j=0; j<3; i++, j++)
    {
        strdia[j] = strdate[i];
    }
    strdia[2] = '\0';

    for(j=0, i=7; strdate[i] != '\0'; i++, j++)
    {
        strano[j] = strdate[i];     //Pega ano (string)
    }
    strano[4] = '\0';

    *ano = atoi(strano);     //Converte ano para inteiro
    *mes = comparaMes(strmes);     //Converte mes para inteiro
    *dia = atoi(strdia);

    return;
}

void trocaPosicao(agenda *compromisso, int old_index, int new_index)
{
    char str_aux[LEN];
    int aux;

    strcpy(str_aux, compromisso[old_index].titulo);
    strcpy(compromisso[old_index].titulo, compromisso[new_index].titulo);
    strcpy(compromisso[new_index].titulo, str_aux);

    strcpy(str_aux, compromisso[old_index].descricao);
    strcpy(compromisso[old_index].descricao, compromisso[new_index].descricao);
    strcpy(compromisso[new_index].descricao, str_aux);

    strcpy(str_aux, compromisso[old_index].local);
    strcpy(compromisso[old_index].local, compromisso[new_index].local);
    strcpy(compromisso[new_index].local, str_aux);

    aux = compromisso[old_index].data.dia;
    compromisso[old_index].data.dia = compromisso[new_index].data.dia;
    compromisso[new_index].data.dia = aux;

    aux = compromisso[old_index].data.mes;
    compromisso[old_index].data.mes = compromisso[new_index].data.mes;
    compromisso[new_index].data.mes = aux;

    aux = compromisso[old_index].data.ano;
    compromisso[old_index].data.ano = compromisso[new_index].data.ano;
    compromisso[new_index].data.ano = aux;

    aux = compromisso[old_index].horario.hora;
    compromisso[old_index].horario.hora = compromisso[new_index].horario.hora;
    compromisso[new_index].horario.hora = aux;

    aux = compromisso[old_index].horario.min;
    compromisso[old_index].horario.min = compromisso[new_index].horario.min;
    compromisso[new_index].horario.min = aux;

    aux = compromisso[old_index].alarme.hora;
    compromisso[old_index].alarme.hora = compromisso[new_index].alarme.hora;
    compromisso[new_index].alarme.hora = aux;

    aux = compromisso[old_index].alarme.min;
    compromisso[old_index].alarme.min = compromisso[new_index].alarme.min;
    compromisso[new_index].alarme.min = aux;
}

void ordemCronologica(agenda *compromisso, int n)
{
    int i, j=0, index, menor, menor_found;

    //Trata por ano
    for(i=1; i<n; i++)
    {
        menor = compromisso[i-1].data.ano;
        menor_found = 0;
        for(j=i; j<n; j++)
        {
            if(compromisso[j].data.ano < menor)
            {
                menor = compromisso[j].data.ano;
                index = j;
                menor_found++;
            }
        }

        if(!menor_found)
                index = i-1;

        trocaPosicao(compromisso, index, i-1);
    }

    //Trata por mês, em caso de anos iguais
    for(i=1; i<n; i++)
    {
        menor = compromisso[i-1].data.mes;
        menor_found = 0;
        for(j=i; j<n; j++)
        {
            if(compromisso[j].data.ano == compromisso[i-1].data.ano)
            {
                if(compromisso[j].data.mes < menor)
                {
                    menor = compromisso[j].data.mes;
                    index = j;
                    menor_found++;
                }
            }
        }

        if(!menor_found)
                index = i-1;

        trocaPosicao(compromisso, index, i-1);
    }

    //Trata por dia, em caso de ano e mês iguais
    for(i=1; i<n; i++)
    {
        menor = compromisso[i-1].data.dia;
        menor_found = 0;
        for(j=i; j<n; j++)
        {
            if((compromisso[j].data.ano == compromisso[i-1].data.ano) && (compromisso[j].data.mes == compromisso[i-1].data.mes))
            {
                if(compromisso[j].data.dia < menor)
                {
                    menor = compromisso[j].data.dia;
                    index = j;
                    menor_found++;
                }
            }
        }

        if(!menor_found)
                index = i-1;

        trocaPosicao(compromisso, index, i-1);
    }

    //Trata por hora, em caso de dia, mes e ano iguais
    for(i=1; i<n; i++)
    {
        menor = compromisso[i-1].horario.hora;
        menor_found = 0;
        for(j=i; j<n; j++)
        {
            if((compromisso[j].data.ano == compromisso[i-1].data.ano) && (compromisso[j].data.mes == compromisso[i-1].data.mes) && (compromisso[j].data.dia == compromisso[i-1].data.dia))
            {
                if(compromisso[j].horario.hora < menor)
                {
                    menor = compromisso[j].horario.hora;
                    index = j;
                    menor_found++;
                }
            }
        }

        if(!menor_found)
                index = i-1;

        trocaPosicao(compromisso, index, i-1);
    }

    //Trata por minuto, em caso de horas, dia, mes e ano iguais (Ufa!)
    for(i=1; i<n; i++)
    {
        menor = compromisso[i-1].horario.min;
        menor_found = 0;
        for(j=i; j<n; j++)
        {
            if((compromisso[j].data.ano == compromisso[i-1].data.ano) && (compromisso[j].data.mes == compromisso[i-1].data.mes) && (compromisso[j].data.dia == compromisso[i-1].data.dia) && (compromisso[j].horario.hora == compromisso[i-1].horario.hora))
            {
                if(compromisso[j].horario.min < menor)
                {
                    menor = compromisso[j].horario.min;
                    index = j;
                    menor_found++;
                }
            }
        }

        if(!menor_found)
                index = i-1;

        trocaPosicao(compromisso, index, i-1);
    }

    reescreveDados(compromisso, n);
}

int buscaDataHora(agenda *compromisso, int n)
{
    date busca_data;
    time busca_hora;
    int i, found=0, *result;

    result = malloc(sizeof(int));

    printf("Digite a data do compromisso (dd/mm/aaaa): ");
    scanf("%d/%d/%d", &busca_data.dia, &busca_data.mes, &busca_data.ano);
    printf("\nDigite a hora do compromisso (h:min): ");
    scanf("%d:%d", &busca_hora.hora, &busca_hora.min);

    for(i=0; i<n; i++)
    {
        if((busca_data.dia == compromisso[i].data.dia) && (busca_data.mes == compromisso[i].data.mes) && (busca_data.ano == compromisso[i].data.ano))
        {
            if((busca_hora.hora == compromisso[i].horario.hora) && (busca_hora.min == compromisso[i].horario.min))
            {
                result[found] = i;
                found++;
                result = (int *) realloc(result, (found+1)*sizeof(int));
                break;
            }
        }
    }

    if(found == 0)
    {
        printf("\n\nCompromisso nao encontrado.");
        return 0;
    }

    else if(found > 1)
    {
        printf("\n%d compromissos foram encontrados com a mesma data e hora:\n\n", found);
        for(i=0; i<found; i++)
        {
            printf("%d. %s", result[i]+1, compromisso[result[i]].titulo);
            printf("\nDescricao: %s", compromisso[result[i]].descricao);
            printf("\nData: %.2d/%.2d/%.2d", compromisso[result[i]].data.dia, compromisso[result[i]].data.mes, compromisso[result[i]].data.ano);
            printf("\nHora: %.2d:%.2d", compromisso[result[i]].horario.hora, compromisso[result[i]].horario.min);
            printf("\nLocal: %s", compromisso[result[i]].local);
            printf("\nHora de ativacao do alarme: %.2d:%.2d\n\n", compromisso[result[i]].alarme.hora, compromisso[result[i]].alarme.min);
        }
        return -1;
    }

    else
    {
        return result[0]+1; //retorna o indice do compromisso encontrado +1 (para nunca ser menor que 1 e assim ficar mais facil de tratar na função)
    }
}

int buscaPalavraChave(agenda *compromisso, int n)
{
    char busca_titulo[LEN/2];
    int i, j, k, found=0, *result;

    result = malloc(sizeof(int));

    fflush(stdin);
    printf("Digite palavra-chave do titulo ou descricao do compromisso: "); gets(busca_titulo);

    for(i=0; i<n; i++) //Percorre compromissos cadastrados
    {
        for(j=0; j<strlen(compromisso[i].titulo); j++) //Percorre letras do titulode cada compromisso
        {
            k = 0;
            while((busca_titulo[k] == compromisso[i].titulo[j+k]) && busca_titulo[k] != '\0')
                k++;

            if(k==strlen(busca_titulo))
            {
                result[found] = i;
                found++;
                result = (int *) realloc(result, (found+1)*sizeof(int));
                break;
            }
        }

        if(k<strlen(busca_titulo)) //se palavra-chave não está no titulo, busca na descrição
        {
            for(j=0; j<strlen(compromisso[i].descricao); j++) //Percorre letras da descricao do compromisso
            {
                k = 0;
                while((busca_titulo[k] == compromisso[i].descricao[j+k]) && busca_titulo[k] != '\0')
                    k++;

                if(k==strlen(busca_titulo))
                {
                    result[found] = i;
                    found++;
                    result = (int *) realloc(result, (found+1)*sizeof(int));
                    break;
                }
            }
        }
    }

    if(found==0)
    {
        printf("\n\nCompromisso nao encontrado.");
        return 0;
    }

    else if(found > 1)
    {
        printf("\n%d compromissos foram encontrados com a mesma palavra-chave:\n\n", found);
        for(i=0; i<found; i++)
        {
            printf("%d. %s", result[i]+1, compromisso[result[i]].titulo);
            printf("\nDescricao: %s", compromisso[result[i]].descricao);
            printf("\nData: %.2d/%.2d/%.2d", compromisso[result[i]].data.dia, compromisso[result[i]].data.mes, compromisso[result[i]].data.ano);
            printf("\nHora: %.2d:%.2d", compromisso[result[i]].horario.hora, compromisso[result[i]].horario.min);
            printf("\nLocal: %s", compromisso[result[i]].local);
            printf("\nHora de ativacao do alarme: %.2d:%.2d\n\n", compromisso[result[i]].alarme.hora, compromisso[result[i]].alarme.min);
        }
        return -1;
    }

    else
    {
        return result[0]+1; //retorna o indice do compromisso encontrado +1 (para nunca ser menor que 1 e assim ficar mais facil de tratar na função)
    }
}

void listar(agenda *compromisso, int inicio, int fim)
{
    int i;

    for(i=inicio; i<fim; i++)
    {
        printf("%d. %s", i+1, compromisso[i].titulo);
        printf("\nDescricao: %s", compromisso[i].descricao);
        printf("\nData: %.2d/%.2d/%.2d", compromisso[i].data.dia, compromisso[i].data.mes, compromisso[i].data.ano);
        printf("\nHora: %.2d:%.2d", compromisso[i].horario.hora, compromisso[i].horario.min);
        printf("\nLocal: %s", compromisso[i].local);
        printf("\nHora de ativacao do alarme: %.2d:%.2d\n\n\n", compromisso[i].alarme.hora, compromisso[i].alarme.min);
    }
}

void alterar(agenda *compromisso, int n)
{
    char resp, titulo_aux[LEN];
    int result, item_op, select, valido, dia_aux, mes_aux, ano_aux, hora_aux, min_aux;

    if(n==1)
    {
        select = 0;
    }

    else
    {
        printf("ALTERAR COMPROMISSO\n\n");
        result = buscaPalavraChave(compromisso, n);

        if(result<0)
        {
            printf("\nDigite o numero do compromisso que deseja alterar: ");
            do {
                scanf("%d", &select);
                select--;

                if(select<0 || select>n)
                    printf("\nOpcao invalida. Digite novamente: ");
            } while (select<0 || select>n);
        }

        else if(!result)
            return;

        else
            select = --result;  //se buscaPalavraChave encontra apenas um compromisso, retorna o índice do compromisso +1
                                //e aqui é feita a subtração

        system("cls");
    }

    printf("Selecione o item que deseja alterar:\n");
    do {
        item_op = menuItem();
        system("cls");

        switch(item_op)
        {
        case 1:
            strcpy(titulo_aux, compromisso[select].titulo); //copia o titulo original para uma variavel auxiliar antes de alterar

            printf("Digite o novo titulo: ");
            fflush(stdin);
            gets(compromisso[select].titulo);
            trataString(compromisso[select].titulo, LEN);

            valido = validaCompromisso(compromisso, select, n);     //valida a alteraçao
            if(!valido)
            {
                printf("\n\nNao foi possivel alterar o titulo.\nJa existe um compromisso com mesmo titulo, data e hora");
                strcpy(compromisso[select].titulo, titulo_aux);     //se nao for válido, o titulo volta a ser o original
            }
        break;
        case 2:
            printf("Digite a nova descricao: ");
            fflush(stdin);
            gets(compromisso[select].descricao);
            trataString(compromisso[select].descricao, LEN);
        break;
        case 3:
            dia_aux = compromisso[select].data.dia;
            mes_aux = compromisso[select].data.mes;
            ano_aux = compromisso[select].data.ano;

            printf("Digite a nova data (dd/mm/aaaa): ");
            do
            {
               scanf("%d/%d/%d", &compromisso[select].data.dia, &compromisso[select].data.mes, &compromisso[select].data.ano);
            }while(validaData(compromisso[select].data.dia, compromisso[select].data.mes, compromisso[select].data.ano) == 0);

            valido = validaCompromisso(compromisso, select, n);
            if(!valido)
            {
                printf("\n\nNao foi possivel alterar a data.\nJa existe um compromisso com mesmo titulo, data e hora");
                compromisso[select].data.dia = dia_aux;
                compromisso[select].data.mes = mes_aux;
                compromisso[select].data.ano = ano_aux;
            }
        break;
        case 4:
            hora_aux = compromisso[select].horario.hora;
            min_aux = compromisso[select].horario.min;

            printf("Digite o novo horario (hr:min): ");
            do
            {
                scanf("%d:%d", &compromisso[select].horario.hora, &compromisso[select].horario.min);
            }while((validaInput(compromisso[select].horario.hora, 0, 23, "Hora")==0) || (validaInput(compromisso[select].horario.min, 0, 59, "Hora")==0));

            valido = validaCompromisso(compromisso, select, n);
            if(!valido)
            {
                printf("\n\nNao foi possivel alterar a hora.\nJa existe um compromisso com mesmo titulo, data e hora");
                compromisso[select].horario.hora = hora_aux;
                compromisso[select].horario.min = min_aux;
            }
        break;
        case 5:
            printf("Digite o novo local: ");
            fflush(stdin);
            gets(compromisso[select].local);
            trataString(compromisso[select].local, LEN);
        break;
        case 6:
            printf("Digite a nova hora do alarme (hr:min): ");
            do
            {
                scanf("%d:%d", &compromisso[select].horario.hora, &compromisso[select].horario.min);
            }while((validaInput(compromisso[select].horario.hora, 0, 23, "Hora")==0) || (validaInput(compromisso[select].horario.min, 0, 59, "Hora")==0));
        break;
        case 7:
            printf("Alteracao cancelada.");
            return;
        default:
            printf("Opcao invalida.");
        break;
        }
        printf("\n\nDeseja fazer outra alteracao no mesmo compromisso? (y/n)\n");
        fflush(stdin);
        resp = getchar();

    }while((resp=='y' || resp=='Y'));

    reescreveDados(compromisso, n);
}

int cadastrar(agenda *compromisso, int n)
{
    printf("NOVO COMPROMISSO\n\n");
    fflush(stdin);
    printf("Titulo do compromisso: "); gets(compromisso[n].titulo);
    trataString(compromisso[n].titulo, LEN);

    fflush(stdin);
    printf("\nDescricao: "); gets(compromisso[n].descricao);
    trataString(compromisso[n].descricao, LEN);

    printf("\nData (dd/mm/aaaa): ");
    do {
        scanf("%d/%d/%d", &compromisso[n].data.dia, &compromisso[n].data.mes, &compromisso[n].data.ano);
    }while(validaData(compromisso[n].data.dia, compromisso[n].data.mes, compromisso[n].data.ano) == 0);

    printf("\nHora (h:min): ");
    do {
        scanf("%d:%d", &compromisso[n].horario.hora, &compromisso[n].horario.min);
    }while((validaInput(compromisso[n].horario.hora, 0, 23, "Hora")==0) || (validaInput(compromisso[n].horario.min, 0, 59, "Hora")==0));

    fflush(stdin);
    printf("\nLocal: "); gets(compromisso[n].local);
    trataString(compromisso[n].local, LEN);

    printf("\nHora de ativacao do alarme (h:min): ");
    do {
        scanf("%d:%d", &compromisso[n].alarme.hora, &compromisso[n].alarme.min);
    }while((validaInput(compromisso[n].alarme.hora, 0, 23, "Hora")==0) || (validaInput(compromisso[n].alarme.min, 0, 59, "Hora")==0));

    if(validaCompromisso(compromisso, n, n) == 0)
    {
        printf("\n\nNao foi possivel concluir o cadastro.\nJa existe um compromisso com mesmo titulo, data e hora.");
        return n;
    }

    else
    {
        escreveDados(compromisso, n);

        system("cls");
        printf("Compromisso cadastrado.");

        return ++n;
    }
}

int menuItem()
{
    int op;

    printf("\n1. Titulo");
    printf("\n2. Descricao");
    printf("\n3. Data");
    printf("\n4. Hora");
    printf("\n5. Local");
    printf("\n6. Hora de ativacao do alarme");
    printf("\n7. Cancelar alteracao");

    printf("\n\nOpcao: "); scanf("%d", &op);
    return op;
}

char menu()
{
    char op;

    printf("    || MENU ||\n");
    printf("\na. Cadastrar compromisso");
    printf("\nb. Alterar compromisso");
    printf("\nc. Buscar compromisso");
    printf("\nd. Visualizar compromissos");
    printf("\ne. Remover compromisso");
    printf("\nf. Encerrar programa");
    printf("\n\nDigite a opção: ");

    op = getch();
    fflush(stdin);
    system("cls");

    return op;
}

int persisteNum()
{
    FILE *cont_in;
    int *contagem, contador = 0;

    cont_in = fopen("agenda.bin", "rb");

    if(cont_in == NULL)
    {
        return 0;
    }

    contagem = malloc(sizeof(agenda));

    while((fread(contagem, sizeof(agenda), 1, cont_in)) == 1)
    {
        contador++;
    }

    free(contagem);

    return contador;
}

void persisteDados(agenda *compromisso, int n)
{
    agenda copia[n];
    FILE *in;
    int i;

    if((in = fopen("agenda.bin", "rb")) == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        exit(1);
    }

    fread(copia, sizeof(agenda), n, in);
    for(i=0; i<n; i++)
    {
        strcpy(compromisso[i].titulo, copia[i].titulo);
        strcpy(compromisso[i].descricao, copia[i].descricao);
        strcpy(compromisso[i].local, copia[i].local);

        compromisso[i].data.dia = copia[i].data.dia;
        compromisso[i].data.mes = copia[i].data.mes;
        compromisso[i].data.ano = copia[i].data.ano;

        compromisso[i].horario.hora = copia[i].horario.hora;
        compromisso[i].horario.min = copia[i].horario.min;

        compromisso[i].alarme.hora = copia[i].alarme.hora;
        compromisso[i].alarme.min = copia[i].alarme.min;
    }

    fclose(in);
}

void reescreveDados(agenda *compromisso, int n)     //Em caso de alteração ou remoção, reescreve tudo
{
    FILE *out;
    if((out = fopen("agenda.bin", "wb")) == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    fwrite(compromisso, sizeof(agenda), n, out);

    fclose(out);
}

void escreveDados(agenda *compromisso, int n)   //Adiciona um registro
{
    FILE *out;
    if((out = fopen("agenda.bin", "ab")) == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        exit(1);
    }

    fwrite(&compromisso[n], sizeof(agenda), 1, out);

    fclose(out);
}
