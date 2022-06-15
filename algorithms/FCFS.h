#ifndef __FIRST__COME__FIRST__SERVED__
#define __FIRST__COME__FIRST__SERVED__


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

//função da saída do gráfico gantt  
void fcfs_print_gantt_chart(Process *p, int len)
{
    int i, j;
    printf("\t ");
    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");

        printf(" ");
    }

    printf("\n\t|");


    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");

        printf("%s", p[i].id);

        for (j = 0; j < p[i].burst - 1; j++)
            printf(" ");

        printf("|");
    }

    printf("\n\t ");

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("--");

        printf(" ");
    }

    printf("\n\t");


    printf("0");

    for (i = 0; i < len; i++)
    {
        for (j = 0; j < p[i].burst; j++)
            printf("  ");

        if (p[i].return_time > 9)
            printf("\b");

        printf("%d", p[i].return_time);

    }

    printf("\n");
}

//função do algoritmo FCFS | p = matriz da estrutura | len = numero de processos

void FCFS(Process *p, int len)
{   
    int i;
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;
    int total_return_time = 0;

    //inicializa o processo com a função process_init
    process_init(p, len);


    //chamada da função que ordena os processos por ordem de chegada
    merge_sort_by_arrive_time(p, 0, len);

    p[0].return_time = p[0].burst - p[0].arrive_time; //ok
	p[0].response_time = p[0].return_time - p[0].burst; //ok
	p[0].waiting_time = p[0].response_time;             // ok
	p[0].turnaround_time = p[0].waiting_time + p[0].burst; // ok

	for(i = 1; i < len; i++){
		p[i].return_time = p[i].burst + p[i-1].return_time;
		p[i].response_time = p[i].return_time - (p[i].burst + p[i].arrive_time);
		p[i].waiting_time = p[i].response_time;
		p[i].turnaround_time = p[i].response_time + p[i].burst;
	}

	for(i = 0; i < len; i++){
		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
		total_return_time += p[i].return_time;
	}
    
    printf("\tExemplo do FCFS:\n\n");
    //chamada da função que mostra a saída do gráfico de gantt
    fcfs_print_gantt_chart(p, len);

    //Saídas OBS: copiado do exemplo PPS
    //Tempo médio de espera | Tempo médio Turnaround | Tempo médio de resposta
	printf("\n\tTempo médio de espera     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tTempo médio de turnaround  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tTempo médio de resposta    : %-2.2lf\n", (double)total_response_time / (double)len);
	printf("\tTempo médio de retorno     : %-2.2lf\n\n", (double)total_return_time/ (double)len);

    //função que imprime a tabela de dados
    print_table(p, len);

}

#endif
