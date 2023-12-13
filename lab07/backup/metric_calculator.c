#include "metric_calculator.h"
#include "utilities.h"
#include <stdio.h>
#include <math.h>



int digit_by_metric_prob(double digit_summary[10][N_OF_METRICS][2], double digit_metrics[N_OF_METRICS])
{
	// create array to store points for each metric for each digit
	// The digit that has the most points at the end has the highest chance of 
	// being the digit
	double prob_points[10][N_OF_METRICS];
	zero_2D_double_array(10, N_OF_METRICS, prob_points);

	// Calculate z score for each metric for each digit
	double z = 0;
	for (int dig = 0; dig < 10; dig++)
	{
		for (int i = 0; i < N_OF_METRICS; i++)
		{
			// if SD is 0, and the x = mean, then its still 0
			if (digit_summary[dig][i][1] == 0.0f && digit_metrics[i] == digit_summary[dig][i][0])
			{
				z = 0;
			}
			// else if SD is 0, its infinity
			else if (digit_summary[dig][i][1] == 0)
			{
				z = METRIC_INF;
			}
			// else calculate z = (x - mean)/SD
			else
			{
				z = (digit_metrics[i] - digit_summary[dig][i][0]) / digit_summary[dig][i][1];
			}
			prob_points[dig][i] = fabs(z);
		}
	}

	for (int dig = 0; dig < 10; dig++)
	{
		for (int i = 0; i < N_OF_METRICS; i++)
		{
		
			printf("%lf, ", prob_points[dig][i]);
		}
		printf("\n");
	}

	// Sum up all the z scores for each digit
	double sum_z[10] = { 0.0 };
	for(int i = 0; i < 10;i++)
	{
		for (int j = 0; j < N_OF_METRICS; j++)
		{
			if (j == mhorBalance)
				sum_z[i] += prob_points[i][j] * 1.0;
			else if(j == mmaxVertical)
				sum_z[i] += prob_points[i][j] * 1.0;
			else if(j == mtallness)
				sum_z[i] += prob_points[i][j] * 1.0;
			else if (j == mmaxDiffVertBot)
				sum_z[i] += prob_points[i][j] * 1.0;
			else
				sum_z[i] += prob_points[i][j];
		}
	}
	for (int i = 0; i < 10; i++)
	{
		printf("%lf, ", sum_z[i]);		
	}
	printf("\n");

	// Find lowest z score, this is the guess for the digit
	double min_z = sum_z[0];
	double min_z2 = sum_z[0];
	int guess = 0;
	int guess2 = 0;
	for (int i = 1; i < 10; i++)
	{
		if (sum_z[i] < min_z)
		{
			min_z2 = min_z;
			min_z = sum_z[i];
			guess2 = guess;
			guess = i;
		}
		if (sum_z[i] < min_z2)
		{
			min_z2 = sum_z[i];
			guess2 = i;
		}
	}

	if (guess == 2 && guess2 == 1)
	{
		prob_points[1][mmaxDiffVertBot] *= 3;
		prob_points[2][mmaxDiffVertBot] *= 3;
	}

	return guess;
}