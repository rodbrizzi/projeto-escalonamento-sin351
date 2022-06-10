#ifndef __SHORTEST__JOB__FIRST__
#define __SHORTEST__JOB__FIRST__


#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"


void sjf_calculate_time(Process *p, int len)
{
	int i, j;

	int curr_time = 0;

	int min = 0;



	p[0].completed = TRUE;
	p[0].return_time = p[0].burst;
	p[0].turnaround_time = p[0].burst - p[0].arrive_time;
	p[0].waiting_time = 0;
	
	curr_time = p[0].burst;



	for(i = 1; i < len; i++)
	{

		for (j = 1; j < len; j++)
		{

			if (p[j].completed == TRUE)
				continue;

			else
			{
				min = j;

				break;

			}
		}


		for (j = 1; j < len; j++)
		{

			if ((p[j].completed == FALSE)
					&& (p[j].arrive_time <= curr_time)
						&& (p[j].burst < p[min].burst))
			{
				min = j;

			}
		}

		p[min].waiting_time = curr_time - p[min].arrive_time;

		p[min].completed = TRUE;


		curr_time += p[min].burst;


		p[min].return_time = curr_time;

		p[min].turnaround_time = p[min].return_time - p[min].arrive_time;

	}
}


void sjf_print_gantt_chart(Process *p, int len)
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

		if (p[i].turnaround_time > 9)
			printf("\b");

		printf("%d", p[i].return_time);
	}

	printf("\n");
}


void SJF(Process *p, int len){
    printf("SJF - Implememtar e devolver no final, o tempo de espera, tempo de retorno e o tempo de resposta");

}

#endif
