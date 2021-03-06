#ifndef __Round__ROBIN__
#define __Round__ROBIN__

#include "./Process.h"
#include "./SortingFunction.h"
#include "./PrintTable.h"

void rr_calculate_all_time(Process *p, int len)
{
	int i;
	int total_waiting_time = 0;
	int total_turnaround_time = 0;
	int total_response_time = 0;
	int total_return_time = 0;

	for (i = 0; i < len; i++)
	{
		p[i].waiting_time = p[i].turnaround_time - p[i].burst;
		p[i].return_time = p[i].arrive_time + p[i].burst + p[i].waiting_time;

		total_waiting_time += p[i].waiting_time;
		total_turnaround_time += p[i].turnaround_time;
		total_response_time += p[i].response_time;
		total_return_time += p[i].return_time;
	}

	printf("\n\tTempo médio de espera     : %-2.2lf\n", (double)total_waiting_time / (double)len);
	printf("\tTempo médio de turnaround  : %-2.2lf\n", (double)total_turnaround_time / (double)len);
	printf("\tTempo médio de resposta    : %-2.2lf\n", (double)total_response_time / (double)len);
	printf("\tTempo médio de retorno     : %-2.2lf\n\n", (double)total_return_time / (double)len);
}

void rr_calculate_waiting_time(Process *p, int len, Quantum q)
{
	int i;

	int curr_time = 0;

	int *remain_burst_time = (int *)malloc(sizeof(int) * len);

	int *calc_response_time = (int *)malloc(sizeof(int) * len);

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;

		calc_response_time[i] = FALSE;
	}

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{

			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (calc_response_time[i] == FALSE)
				{
					p[i].response_time = curr_time - p[i].arrive_time;

					calc_response_time[i] = TRUE;
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;

					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];

					p[i].waiting_time = curr_time - p[i].burst;

					remain_burst_time[i] = 0;
				}
			}
		}

		if (check == TRUE)
			break;
	}

	free(remain_burst_time);
}

void rr_calculate_turnaround_time(Process *p, int len)
{
	int i;

	for (i = 0; i < len; i++)
		p[i].turnaround_time = p[i].burst + p[i].waiting_time - p[i].arrive_time;
}

void rr_print_gantt_chart(Process *p, int len, Quantum q)
{
	int i, j;

	int curr_time = 0, total_burst_time = 0;

	int temp_total_burst_time = 0;

	int *remain_burst_time = (int *)malloc(sizeof(int) * len);

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;

		total_burst_time += p[i].burst;
	}

	printf("\t");

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf(" ");
					for (j = 0; j < remain_burst_time[i]; j++)
						printf("--");
				}

				else
				{
					printf(" ");
					for (j = 0; j <= q; j++)
						printf("--");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}
			}
		}

		if (check == TRUE)
			break;
	}

	printf(" \n\t");

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
	}

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf("|");

					if (remain_burst_time[i] != 1)
					{
						for (j = 0; j <= remain_burst_time[i] / 2; j++)
							printf(" ");

						printf("%2s", p[i].id);

						for (j = 0; j <= remain_burst_time[i] / 2; j++)
							printf(" ");
					}

					else
						printf("%2s", p[i].id);
				}

				else
				{
					printf("|");

					for (j = 0; j < q; j++)
						printf(" ");

					printf("%2s", p[i].id);

					for (j = 0; j < q; j++)
						printf(" ");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}
			}
		}

		if (check == TRUE)
			break;
	}

	printf("|\n\t");

	for (i = 0; i < len; i++)
	{
		remain_burst_time[i] = p[i].burst;
	}

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf(" ");
					for (j = 0; j < remain_burst_time[i]; j++)
						printf("--");
				}

				else
				{
					printf(" ");
					for (j = 0; j <= q; j++)
						printf("--");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}
			}
		}

		if (check == TRUE)
			break;
	}

	printf("\n\t");

	for (i = 0; i < len; i++)
		remain_burst_time[i] = p[i].burst;

	curr_time = 0;

	while (TRUE)
	{
		int check = TRUE;

		for (i = 0; i < len; i++)
		{
			if (remain_burst_time[i] > 0)
			{
				check = FALSE;

				if (remain_burst_time[i] < q)
				{
					printf("%-2d", curr_time);

					for (j = 0; j < remain_burst_time[i] - 1; j++)
						printf("  ");

					printf(" ");
				}

				else
				{
					printf("%-2d", curr_time);

					for (j = 0; j < q; j++)
						printf("  ");

					printf(" ");
				}

				if (remain_burst_time[i] > q)
				{
					curr_time += q;
					remain_burst_time[i] -= q;
				}

				else
				{
					curr_time += remain_burst_time[i];
					p[i].waiting_time = curr_time - p[i].burst;
					remain_burst_time[i] = 0;
				}
			}
		}

		if (check == TRUE)
			break;
	}

	printf("%-3d\n", total_burst_time);

	printf("\n");

	free(remain_burst_time);
}

void RR(Process *p, int len, Quantum quantum)
{
	printf("\tImplementação do Round Robin( Quantum : %d )\n\n", quantum);

	// inicializa o processo
	process_init(p, len);

	// ordena os processos por ordem de chegada
	merge_sort_by_arrive_time(p, 0, len);

	// calcula tempo de espera
	rr_calculate_waiting_time(p, len, quantum);

	// calcula turnaround
	rr_calculate_turnaround_time(p, len);

	// função que imprime gráfico de gantt
	rr_print_gantt_chart(p, len, quantum);

	// função que calcula e imprime os tempos médios
	rr_calculate_all_time(p, len);

	// função que imprime a tabela dos processos
	print_table(p, len);
}

#endif
