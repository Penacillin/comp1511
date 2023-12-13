#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "metrics.h"
#include "preprocessors.h"
#include "readers.h"
#include "utilities.h"
#include "data.h"
#include "metric_calculator.h"

#define MAP_HEIGHT box_height
#define MAP_WIDTH box_width

double sumHorBalance = 0;
double sumVerBalance = 0;
double sumTallness = 0;
double sumHoleSize = 0;
double sumHoles = 0;

int single_stats = 0;

int digit(int height, int width, int pixels[height][width], double digit_stats[N_OF_METRICS])
{
	int  start_row, start_column, box_width, box_height;
	
	// Basic metric variables
	double horBalance, verBalance, tallness, hole_size_fraction = 0, density, 
		average_width, middle_left_density, bot_right_density,
		vert_pos_of_hole = 0, sd_of_hor_balance, mean_three_width,
		mean_dist_from_left_topthird, hor_bal_top;

	int holes = 0;
	double max_vertical = 0, max_horizontal = 0;;

	// Transfer bounded box into "box_pixels"
	get_bounding_box(height, width, pixels, &start_row, &start_column, &box_height, &box_width);
	int box_pixels[box_height][box_width];
	copy_pixels(height, width, pixels, start_row, start_column, box_height, box_width, box_pixels);

	// Arrays for islands
	// NOTE: island 0 means not part of an island, therefore islands are 1 indexed
	int island_markings[MAP_HEIGHT][MAP_WIDTH];
	zero_2D_array(MAP_HEIGHT, MAP_WIDTH, island_markings);
	
	Island islands[MAX_NUM_OF_ISLANDS];
	
	int num_of_islands = 0;

	// Calculate metrics
	horBalance = get_horizontal_balance(box_height, box_width, box_pixels);
	verBalance = get_vertical_balance(box_height, box_width, box_pixels);
	tallness = get_tallness(box_height, box_width);
	density = get_density(box_height, box_width, box_pixels);
	max_vertical = get_max_vertical(box_height, box_width, box_pixels);
	average_width = get_average_width(box_height, box_width, box_pixels);
	max_horizontal = get_max_horizontal(box_height, box_width, box_pixels);
	middle_left_density = get_middle_left_density(box_height, box_width, box_pixels);
	bot_right_density = get_bottom_right_density(box_height, box_width, box_pixels);
	sd_of_hor_balance = get_SD_hor_bal(box_height, box_width, box_pixels);
	mean_three_width = get_mean_width_of_three(box_height, box_width, box_pixels);
	mean_dist_from_left_topthird = get_SD_dist_from_left_first_third(box_height, box_width, box_pixels);
	hor_bal_top = get_hor_bal_top(box_height, box_width, box_pixels);



	// Fill out island information
	fill_out_islands(MAP_HEIGHT, MAP_WIDTH, box_pixels, 
		island_markings, islands, &num_of_islands);

	// variable to indicate the island number of a hole
	int island_indicator_of_hole[8] = { 0 };

	// Count number of holes (i.e. isolated islands)
	for (int i = 1; i <= num_of_islands; i++)
	{
		// if it's isolated and its white, it's a hole... i think
		if (islands[i].is_isolated && islands[i].color == 0)
		{
			holes++;
			hole_size_fraction += islands[i].size;
			island_indicator_of_hole[holes-1] = i;
			//printf("hole island is %d\n", i);
		}
	}

	for (int i = 0; i < holes; i++)
	{
		vert_pos_of_hole += get_vert_pos_of_island(MAP_HEIGHT, MAP_WIDTH, island_markings, island_indicator_of_hole[i]);
	}
	if(holes != 0)
		vert_pos_of_hole /= holes;

	// calculate fraction of hole compared to bounding box
	hole_size_fraction /= MAP_HEIGHT*MAP_WIDTH;

	// put details into digit stats
	digit_stats[mhorBalance] = horBalance;
	digit_stats[mverBalance] = verBalance;
	digit_stats[mtallness] = tallness;
	digit_stats[mhole_size_fraction] = hole_size_fraction;
	digit_stats[mholes] = holes;
	digit_stats[mdensity] = density;
	digit_stats[mmaxVertical] = max_vertical;
	digit_stats[mmaxHorizontal] = max_horizontal;
	digit_stats[maverageWidth] = average_width;
	digit_stats[mmidLeftDensity] = middle_left_density;
	digit_stats[mbotRightDensity] = bot_right_density;
	digit_stats[mvertPosOfHole] = vert_pos_of_hole;
	digit_stats[msdHorBalance] = sd_of_hor_balance;
	digit_stats[mmeanWidthOfThree] = mean_three_width;
	digit_stats[mhorBalTop] = hor_bal_top;

	//print_plain(box_height, box_width, box_pixels);

	digit_stats[msteepestFallTopLeft] = get_max_fall_top_left(box_height, box_width, box_pixels);
	digit_stats[msteepestFallBotRight] = get_max_fall_bot_right(box_height, box_width, box_pixels);
	//digit_stats[msmoothnessMidLeft] = get_smoothness_mid_left(box_height, box_width, box_pixels);
	digit_stats[msteepestFallMidLeft] = get_max_fall_mid_left(box_height, box_width, box_pixels);
	digit_stats[mbotHorBalance] = get_bot_horizontal_balance(box_height, box_width, box_pixels);
	digit_stats[mdeepestLeftBotRight] = get_deepest_left_bot_right(box_height, box_width, box_pixels);
	digit_stats[mvertsBot] = get_verts_bot(box_height, box_width, box_pixels);
	digit_stats[mmaxDiffVertBot] = get_max_diff_vert(box_height, box_width, box_pixels);
	digit_stats[mSDgradBotLeft] = get_SD_grad_bot_left(box_height, box_width, box_pixels);
	digit_stats[mSDgradBotRight] = get_SD_grad_bot_right(box_height, box_width, box_pixels);
	digit_stats[mdeltaTR] = get_largest_delta_TR(box_height, box_width, box_pixels);
	
	if (single_stats)
	{
		printf("\nMetrics for :\n");
		print_image(box_height, box_width, box_pixels);
		printf("Horizontal Balance: %lf\n", horBalance);
		printf("Vertical Balance  : %lf\n", verBalance);
		printf("Tallness          : %lf\n", tallness);
		printf("Number of holes   : %d\n", holes);
		printf("hole size fraction: %lf\n", hole_size_fraction);
		printf("density           : %lf\n", density);
		printf("max Vertical      : %lf\n", max_vertical);
		printf("max horizontal	  : %lf\n", max_horizontal);
		printf("average width     : %lf\n", average_width);
		printf("middleleeft dens  : %lf\n", middle_left_density);
		printf("bot right   dens  : %lf\n", bot_right_density);
		printf("islands (%d) :\n", num_of_islands);
		printf("vert pos of hole  : %lf\n", digit_stats[mvertPosOfHole]);
		printf("SD of hor balance : %lf\n", digit_stats[msdHorBalance]);
		printf("mean width of 3 x : %lf\n", digit_stats[mmeanWidthOfThree]);
		printf("   hor bal top    : %lf\n", digit_stats[mhorBalTop]);
		printf("steepst top left  : %lf\n", digit_stats[msteepestFallTopLeft]);
		printf("steepst bot righ  : %lf\n", digit_stats[msteepestFallBotRight]);
		//printf("smoothnes mid left: %lf\n", digit_stats[msmoothnessMidLeft]);
		printf("steepst mid left  : %lf\n", digit_stats[msteepestFallMidLeft]);
		printf("bot hor balance   : %lf\n", digit_stats[mbotHorBalance]);
		printf("deepest bot rig   : %lf\n", digit_stats[mdeepestLeftBotRight]);
		printf("vertical line sbot: %lf\n", digit_stats[mvertsBot]);
		printf("max diff vert bot : %lf\n", digit_stats[mmaxDiffVertBot]);
		printf("SD grad bot left  : %lf\n", digit_stats[mSDgradBotLeft]);
		printf("steepest bot right: %lf\n", digit_stats[mSDgradBotRight]);
		//print_plain(MAP_HEIGHT, MAP_WIDTH, island_markings);
		printf("\n");
	}
	
	/*
	if (holes != 1)
	{
		fprintf(stderr, "fuck");
		int xxx;
		scanf("%d", &xxx);
	}
	*/

	

	return 3;
}

int getStatsFor(int dig, double digit_stat[100][N_OF_METRICS])
{
	int height, width;
	char filename[30] = { 0 };

	for (int i = 0; i <= 99; i++)
	{
		strcpy(filename, "./digit/"); // ./digit/
		sprintf(filename + 8, "%d", dig); // .digit/x
		strcpy(filename + 9, "_"); // ./digit/x_
		sprintf(filename + 10, "%02d", i); // ./digit/x_xx
		strcat(filename, ".pbm"); // ./digit/x_xx.pbm

		//printf("filename is %s\n", filename);

		if (get_pbm_dimensions(filename, &height, &width) != 1) {
			return 1;
		}

		int pixels[height][width];
		if (read_pbm(filename, height, width, pixels)) {
			digit(height, width, pixels, digit_stat[i]);
		}
	}
	
	printf("\nAVERAGE Metrics for %d :\n", dig);
	//print_image(box_height, box_width, box_pixels);
	printf("Horizontal Balance (%lf) : %.8lf\n", sumHorBalance, getAverage(digit_stat, mhorBalance));
	printf("Vertical Balance  : %lf\n", getAverage(digit_stat, mverBalance));
	printf("Tallness          : %lf\n", getAverage(digit_stat, mtallness));
	printf("Number of holes   : %lf\n", getAverage(digit_stat, mholes));
	printf("hole size fraction: %lf\n", getAverage(digit_stat, mhole_size_fraction));
	printf("desnity           : %lf\n", getAverage(digit_stat, mdensity));
	printf("max vertical	  : %lf\n",  getAverage(digit_stat, mmaxVertical));
	printf("max horizontal	  : %lf\n", getAverage(digit_stat, mmaxHorizontal));
	printf("average width	  : %lf\n", getAverage(digit_stat, maverageWidth));
	printf("middleleeft dens  : %lf\n", getAverage(digit_stat, mmidLeftDensity));
	printf("bot right   dens  : %lf\n", getAverage(digit_stat, mbotRightDensity));
	printf("vert pos of hole  : %lf\n", getAverage(digit_stat, mvertPosOfHole));
	printf("SD of hor balance : %lf\n", getAverage(digit_stat, msdHorBalance));
	printf("mean width of 3 x : %lf\n", getAverage(digit_stat, mmeanWidthOfThree));
	printf("   hor bal top    : %lf\n", getAverage(digit_stat, mhorBalTop));
	printf("steepst top left  : %lf\n", getAverage(digit_stat, msteepestFallTopLeft));
	printf("steepst bot righ  : %lf\n", getAverage(digit_stat, msteepestFallBotRight));
	//printf("smoothness mid  l : %lf\n", getAverage(digit_stat, msmoothnessMidLeft));
	printf("steepst mid left  : %lf\n", getAverage(digit_stat, msteepestFallMidLeft));
	printf("bot hor balance   : %lf\n", getAverage(digit_stat, mbotHorBalance));
	printf("deepest left bot r: %lf\n", getAverage(digit_stat, mdeepestLeftBotRight));
	printf("vertical lines bot: %lf\n", getAverage(digit_stat, mvertsBot));
	printf("max vert diff bot : %lf\n", getAverage(digit_stat, mmaxDiffVertBot));
	printf("SD bot left grad  : %lf\n", getAverage(digit_stat, mSDgradBotLeft));
	printf("SD bot right grad : %lf\n", getAverage(digit_stat, mSDgradBotRight));
	printf("top right big delt: %lf\n", getAverage(digit_stat, mdeltaTR));
	printf("\n");
	

	return 0;
}

void create_summary_csv()
{
	FILE* stats;
	stats = fopen("./stats.csv", "w");
	double digitsStats[10][100][N_OF_METRICS];
	for (int digit = 0; digit <= 9; digit++)
	{
		
		getStatsFor(digit, digitsStats[digit]);
		fprintf(stats, "%d,", digit);

		for (int i = 0; i < N_OF_METRICS; i++)
		{
			fprintf(stats, "%lf,%lf,",
				getAverage(digitsStats[digit], i),
				get_stddevS(digitsStats[digit], i)
			);
		}
		fprintf(stats, "\n");
	}
}

int main(int argc, char *argv[]) {


	char filename[30];
	int height, width;

	if (argc < 2) {
		fprintf(stderr, "Usage: %s <image-file>\n", argv[0]);
		return 1;
	}

	if (argv[1][0] == 'c')
	{
		create_summary_csv();
		return 0;
	}

	double digit_summary[10][N_OF_METRICS][2];
	read_stats_table(digit_summary);
	double digit_stat[N_OF_METRICS];

	if (mstrlen(argv[1]) > 2)
	{
		single_stats = 1;
		strcpy(filename, argv[1]);

		printf("filename is %s\n", filename);

		if (get_pbm_dimensions(filename, &height, &width) != 1) {
			return 1;
		}

		int pixels[height][width];
		if (read_pbm(filename, height, width, pixels)) {
			digit(height, width, pixels, digit_stat);
		}
		int guess = digit_by_metric_prob(digit_summary, digit_stat);
		printf("guess: %d\n", guess); 
		
		return 0;
	}	
	
			
	int fucks = 0;
	int dig = atoi(argv[1]);
	for (int i = 0; i <= 99; i++)
	{
		strcpy(filename, "./digit/"); // ../../digit/
		sprintf(filename + 8, "%d", dig); // ../../digit/x
		strcpy(filename + 9, "_"); // ../../digit/x_
		sprintf(filename + 10, "%02d", i); // ../../digit/x_xx
		strcat(filename, ".pbm"); // ../../digit/x_xx.pbm

		printf("filename is %s\n", filename);

		if (get_pbm_dimensions(filename, &height, &width) != 1) {
			return 1;
		}

		int pixels[height][width];
		if (read_pbm(filename, height, width, pixels)) {
			digit(height, width, pixels, digit_stat);
		}
		int guess = digit_by_metric_prob(digit_summary, digit_stat);
		printf("guess: %d\n", guess);
		//sint xxx = 0;
		if (guess != dig)
		{
			fucks++;
			printf("fuck\n");
			//scanf("%d", &xxx);
		}
	}
	printf("fucks :%d\n", fucks);

	return 0;
}
