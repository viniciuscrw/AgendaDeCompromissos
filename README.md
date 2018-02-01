# AgendaDeCompromissos
Pequeno projeto para aprendizado de programção em linguagem C, implementando uma Agenda de Compromissos em modo texto, feito para a disciplina de Linguagem de Programação 1.

Alguns dos recursos da linguagem que são trabalhados no projeto:
- Estruturas (struct)
- Ponteiros e alocação dinâmica de memória
- Manipulaçao de arquivos
- Ordenação de array


Segue a proposta do projeto:
_________________

Implemente uma agenda de compromissos que permita ao usuário realizar as seguintes operações:
* Cadastrar compromissos
* Alterar compromissos
* Remover compromissos

Cada compromisso deve conter as seguintes informações mínimas:
* Hora
* Data
* Título
* Onde
* Descrição
* Horário de ativação do alarme

Restrições do Projeto
* Lembre-se que cada compromisso deve ser único (para isso, comparamos uma chave tripla: hora, data e título do compromisso);
* A agenda deve ser mantida num arquivo no disco;
* Deve ser apresentado ao usuário um menu de opções que permita que ele manipule a agenda de forma fácil e objetiva;
* Cada uma das funcionalidades deve ser implementada em funções separadas do programa principal (ex: cadastrar, remover, alterar, buscar, etc.);
* Deve ser possível a visualização pelo usuário da agenda de várias formas: compromissos do dia, de uma semana, de um mês ou em ordem cronológica dos compromissos cadastrados;
* Deve ser permitido procurar na agenda: por uma palavra chave na descrição ou no título, ou por uma data e hora específicas;
* Deve permitir ao usuário limpar o arquivo, retirando os compromissos passados quando ele desejar (deve ser uma opção do tipo remover_anteriores que remove do arquivo todos os compromissos já passados até o momento da execução). É possível ainda remover um compromisso que ainda não tenha passado;
* O seu calendário não deve ter restrição à data (desde que ser válida, qualquer data pode ser usada para agendar compromissos, (por exemplo 24 de agosto de 4050) nem à quantidade de compromissos agendados. A única restrição é o tamanho da memória disponível no seu computador.
* Mais de um compromisso pode ser a cadastrado ao mesmo tempo. Dessa forma, use alocação dinâmica de memória para os registros de compromissos num vetor antes de gravá-los no disco.
