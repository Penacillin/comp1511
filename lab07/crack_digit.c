#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "metrics.h"
#include "preprocessors.h"
#include "readers.h"
#include "utilities.h"
#include "data.h"
#include "metric_calculator.h"

int main(int argc, char *argv[]) {


	char filename[30];
	int height, width;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
		return 1;
	}

	// if argument is "c", create statistics
	if (argv[1][0] == 'c')
	{
		create_summary_csv();
		return 0;
	}

	double digit_summary[10][N_OF_METRICS][2];
	read_stats_table(digit_summary);
	double digit_stat[N_OF_METRICS];
	double prob_points[10][N_OF_METRICS];

	// if a filename is inputted, try crack
	if (mstrlen(argv[1]) > 2)
	{
		strcpy(filename, argv[1]);
		//printf("CRACKING\n");
		//printf("CRACKING filename is %s\n", filename);

		if (get_pbm_dimensions(filename, &height, &width) != 1) {
			return 1;
		}

		int pixels[height][width];
		if (read_pbm(filename, height, width, pixels)) {
			digit(height, width, pixels, digit_stat);
		}
		if(argc > 2)
			print_digit_metrics(height, width, pixels, digit_stat);

		int guess = digit_by_metric_prob(digit_summary, digit_stat, prob_points);
		printf("%d\n", guess);
		
		return 0;
	}	

	// if a single digit is inputted, crack every file under that digit
	int fucks = 0;
	int dig = atoi(argv[1]);
	for (int i = 0; i <= 99; i++)
	{
		strcpy(filename, "./digit/"); // ../../digit/
		sprintf(filename + 8, "%d", dig); // ../../digit/x
		strcpy(filename + 9, "_"); // ../../digit/x_
		sprintf(filename + 10, "%02d", i); // ../../digit/x_xx
		strcat(filename, ".pbm"); // ../../digit/x_xx.pbm

		printf("STATS filename is %s\n", filename);

		if (get_pbm_dimensions(filename, &height, &width) != 1) {
			return 1;
		}

		int pixels[height][width];
		if (read_pbm(filename, height, width, pixels)) {
			digit(height, width, pixels, digit_stat);
		}
		
		int guess = digit_by_metric_prob(digit_summary, digit_stat, prob_points);
		
		//sint xxx = 0;
		if (guess != dig)
		{
			fucks++;
			printf("fuck\n");
			if (argc > 2)
			{
				print_digit_metrics(height, width, pixels, digit_stat);
				print_plain_double(10, N_OF_METRICS, prob_points);
			}
			//scanf("%d", &xxx);
		}
		printf("guess: %d\n", guess);
	}
	printf("fucks :%d\n", fucks);

	return 0;
}
