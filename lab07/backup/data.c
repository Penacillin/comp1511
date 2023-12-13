#include "data.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

double getSum(double digit_metrics[100][N_OF_METRICS], Metric metric)
{
	double sum = 0;
	for (int i = 0; i < 100; i++)
	{
		sum += digit_metrics[i][metric];
	}
	return sum;
}

double getAverage(double digit_metrics[100][N_OF_METRICS], Metric metric)
{
	return getSum(digit_metrics, metric) / 100;
}

double get_stddevS(double digit_metrics[100][N_OF_METRICS], Metric metric)
{
	double mean = getAverage(digit_metrics, metric);
	double square_difference_sum = 0;
	for (int i = 0; i < 100; i++)
	{
		square_difference_sum += (digit_metrics[i][metric] - mean)*(digit_metrics[i][metric] - mean);
	}
	square_difference_sum /= 98;
	return sqrt(square_difference_sum);
}

void read_stats_table(double digit_stats[10][N_OF_METRICS][2])
{
	int x;

	FILE *f = fopen("./stats.csv", "r");

	if (f == NULL)
	{
		fprintf(stderr, "Could not open stats file, exiting\n");
		exit(1);
	}

	for (int dig = 0; dig < 10; dig++)
	{
		fscanf(f, "%d,", &x);
		printf("%d,", x);
		for (int i = 0; i < N_OF_METRICS; i++)
		{
			fscanf(f, "%lf,", &(digit_stats[dig][i][0]));
			fscanf(f, "%lf,", &(digit_stats[dig][i][1]));

			printf(" %lf , %lf ", (digit_stats[dig][i][0]),
				(digit_stats[dig][i][1]));
		}
		printf("\n");
	}
	fclose(f);
}