#include "metrics.h"
#include "utilities.h"
#include <stdio.h>
#include <math.h>


double get_vertical_balance(int height, int width, int pixels[height][width])
{
	int row_sum = 0;
	int n_black_pixels = 0;

	for (int i = 0; i < height; i++)
	{
		int currRowSum = 0;
		for (int j = 0; j < width; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				currRowSum++;
				n_black_pixels++;
			}
		}
		// after found sum of black pixels in current column, add to total
		row_sum += currRowSum * i;
	}

	return ((double)row_sum / n_black_pixels + 0.5) / height;
}

double get_horizontal_balance(int height, int width, int pixels[height][width])
{
	int column_sum = 0;
	int n_black_pixels = 0;

	for (int i = 0; i < width; i++)
	{
		int currColumnSum = 0;
		for (int j = 0; j < height; j++)
		{
			if (pixels[j][i])
			{
				// if pixel is black
				currColumnSum++;
				n_black_pixels++;
			}
		}
		// after found sum of black pixels in current column, add to total
		column_sum += currColumnSum * i;
	}

	return ((double)column_sum / n_black_pixels + 0.5) / width;
}

double get_tallness(int height, int width)
{
	return (double)height / width;
}

double get_density(int height, int width, int pixels[height][width])
{
	int n_black_pixels = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				n_black_pixels++;
			}
		}
	}
	//printf("num of black pixels:%d, sqare: %d\n", n_black_pixels, height*width);
	return (double) n_black_pixels / (height*width);
}

double get_max_vertical(int height, int width, int pixels[height][width])
{

	int max = 0;

	for (int i = 0; i < width; i++)
	{
		int curr_col_sum = 0;
		for (int j = 0; j < height; j++)
		{
			if (pixels[j][i])
			{
				// if pixel is black
				curr_col_sum++;
			}
		}
		if (curr_col_sum > max)
			max = curr_col_sum;
	}

	return (double) max / height;
}

double get_max_horizontal(int height, int width, int pixels[height][width])
{

	int max = 0;

	for (int i = 0; i < height; i++)
	{
		int curr_row_sum = 0;
		for (int j = 0; j < width; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				curr_row_sum++;
			}
		}
		if (curr_row_sum > max)
			max = curr_row_sum;
	}

	return (double) max / width;
}

double get_average_width(int height, int width, int pixels[height][width])
{
	double sum_width = 0;
	
	int left_side = 0;
	int right_side = 0;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				left_side = j;
				j = width;
			}
		}
		for (int j = width-1; j >= 0; j--)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				right_side = j;
				j = -1;
			}
		}

		sum_width += right_side - left_side;
	}

	return sum_width / height / width;
}

double get_density_within_bounds(int y, int height, int x, int width, int pixels[height][width])
{
	int n_black_pixels = 0;

	for (int i = y; i < height + y; i++)
	{
		for (int j = x; j < width + x; j++)
		{
			if (pixels[i][j])
			{
				// if pixel is black
				n_black_pixels++;
			}
		}
	}
	//printf("num of black pixels:%d, sqare: %d\n", n_black_pixels, height*width);
	return (double)n_black_pixels / (height*width);
}

// Return density of the rectangle 1/3 up from the bottom left and halfway across
// the image
double get_middle_left_density(int height, int width, int pixels[height][width])
{
	return get_density_within_bounds(height / 3, height / 3, 0, width / 2, pixels);
}

// Return density of rectangle 1/3 from bottom right and halway across
double get_bottom_right_density(int height, int width, int pixels[height][width])
{
	return get_density_within_bounds(0, height / 3, width / 2, width / 2, pixels);
}

double get_bot_horizontal_balance(int height, int width, int pixels[height][width])
{

	int column_sum = 0;
	int n_black_pixels = 0;

	for (int i = 0; i < width; i++)
	{
		int currColumnSum = 0;
		for (int j = 0; j < height / 2; j++)
		{
			if (pixels[j][i])
			{
				// if pixel is black
				currColumnSum++;
				n_black_pixels++;
			}
		}
		// after found sum of black pixels in current column, add to total
		column_sum += currColumnSum * i;
	}

	return ((double)column_sum / n_black_pixels + 0.5) / width;
}

int next_check(int x, int y, int direction, int *nx, int *ny)
{
	switch (direction)
	{
	case 0:
		*nx = x - 1;
		*ny = y - 1;
		break;
	case 1:
		*nx = x - 1;
		*ny = y - 1;
		break;
	case 2:
		*nx = x - 1;
		*ny = y + 1;
		break;
	case 3:
		*nx = x - 1;
		*ny = y + 1;
		break;
	case 4:
		*nx = x + 1;
		*ny = y + 1;
		break;
	}
	// TODO: Continue tracing paths on left side to find next check position
	// Check if it's different for left and right
	// fuck it probs is


	return 42;
}

//
int left_turns(int height, int width, int pixels[height][width])
{
	int x = 0;
	//int y = 0;
	//int direction = 0;

	for (int i = 0; i < width; i++)
	{
		if (pixels[0][i])
		{
			x = i;
			i = width;
		}
	}

	for (int i = 0; i < width; i++)
	{
		if (pixels[1][i])
		{
			// TODO: Think about whether to check for bounds here or in function
		}
	}
	return 0;
}

// Gets the vertical position of hte midpoint of a given island  (as a ratio of height)
double get_vert_pos_of_island(int height, int width, int island[height][width], int indi)
{
	int bot = 0;
	int top = 0;
	// Check its an existant island
	if (indi == 0)
		return 0;

	// Search for bottom of island
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (island[y][x] == indi)
			{
				bot = y;
				x = width;
				y = height;
			}
		}
	}

	// Search for top of island
	for (int y = bot + 1; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (island[y][x] == indi)
			{
				top = y;
			}
		}
	}

	// return its height as a fraction of picture height
	return (double)(top + bot) / 2 / height;
}

// Gets the standard deviation of the horizontal balance
double get_SD_hor_bal(int height, int width, int pixels[height][width])
{
	double mean = 0;
	double values[height];

	for (int y = 0; y < height; y++)
	{
		int curr_row = 0;
		int n_pixels = 0;
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				curr_row += x;
				n_pixels++;
			}
		}
		values[y] = ((double)curr_row / n_pixels + 0.5) / width;
		mean += values[y];
	}
	mean /= height;
	double square_difference_sum = 0;
	for (int i = 0; i < height; i++)
	{
		square_difference_sum += (values[i] - mean)*(values[i] - mean);
	}
	square_difference_sum /= height - 1;
	return sqrt(square_difference_sum);
}

// Gets how far from the left side the number has 3 strokes
double get_mean_width_of_three(int height, int width, int pixels[height][width])
{
	int threes = 0;
	int black = 0;
	int swaps = 0;
	for (int x = 0; x < width; x++)
	{
		black = pixels[0][x];
		swaps = 0;
		for (int y = 1; y < height; y++)
		{
			if (pixels[y][x] && !black)
			{
				black = 1;
				swaps++;
			}
			if (!(pixels[y][x]) && black)
			{
				black = 0;
				swaps++;
			}
		}
		if (swaps == 6)
		{
			return (double)x / width;
			threes++;
		}
	}

	return (double)threes / width;
}

#define LEFT_DIST_TOP (height - (height / 5))
#define LEFT_DIST_BOT (2 * height / 3)

double get_SD_dist_from_left_first_third(int height, int width, int pixels[height][width])
{
	double mean = 0;
	int values[(LEFT_DIST_TOP - LEFT_DIST_BOT) + 1];

	for (int y = LEFT_DIST_TOP; y > LEFT_DIST_BOT; y--)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				mean += x;
				values[LEFT_DIST_TOP - y] = x;
				x = width;
			}
		}
	}
	
	mean /= (LEFT_DIST_TOP - LEFT_DIST_BOT) / width;
	double square_difference_sum = 0;
	
	for (int i = 0; i < LEFT_DIST_TOP - LEFT_DIST_BOT; i++)
	{
		square_difference_sum += (values[i] - mean)*(values[i] - mean);
	}
	square_difference_sum /= (LEFT_DIST_TOP - LEFT_DIST_BOT) - 1;
	
	return sqrt(square_difference_sum);
}

// Gets the standard deviation of the horizontal balance
double get_hor_bal_top(int height, int width, int pixels[height][width])
{
	double mean = 0;
	double values[LEFT_DIST_TOP - LEFT_DIST_BOT];

	for (int y = LEFT_DIST_TOP; y > LEFT_DIST_BOT; y--)
	{
		int curr_row = 0;
		int n_pixels = 0;
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				curr_row += x;
				n_pixels++;
			}
		}
		values[LEFT_DIST_TOP - y] = ((double)curr_row / n_pixels + 0.5) / width;
		mean += values[LEFT_DIST_TOP - y];
	}
	mean /= LEFT_DIST_TOP - LEFT_DIST_BOT;
	
	return mean;
}

double get_longest_vert_top(int height, int width, int pixels[height][width])
{
	int longest = 0;
	int index = 0;
	for (int x = 0; x < width; x++)
	{
		int curr = 0;
		for (int y = height - 1; y > height / 3; y++)
		{
			if (pixels[y][x])
			{
				curr++;
			}
			else
			{
				if (curr > longest)
					longest = curr;
				curr = 0;
			}
		}
	}

	return index / width;
}

double get_max_fall_top_left(int height, int width, int pixels[height][width])
{
	int y1 = 0, y2 = 0, x1 = 0, x2 = 0;
	int counter = 0;
	double sum = 0;

	// Get first pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[height-1][x])
		{
			x2 = x;
			y2 = height - 1;

			x = width;
		}
	}
	// Get second pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[height - 2][x])
		{
			y1 = height - 2;
			x1 = x;

			x = width;
		}
	}
	if ((double)(x1 - x2) / (y1 - y2) < 0)
	{
		sum += (double)(x1 - x2) / (y1 - y2);
		counter++;
	}

	for (int y = height - 3; y > 2 * height / 3; y--)
	{
		for (int x = 0; x < width; x++)
		{	
			if (pixels[y][x]) {
				x2 = x1;
				y2 = y1;
				x1 = x;
				y1 = y;
				if ((double)(x1 - x2) / (y1 - y2) < 0)
				{
					sum += (double)(x1 - x2) / (y1 - y2);
					counter++;
				}
				x = width;
			}
		}
		
	}
	if (counter > 0)
		return sum /= counter;
	else
		return 0;
}

double get_max_fall_bot_right(int height, int width, int pixels[height][width])
{
	int y1 = 0, y2 = 0, x1 = 0, x2 = 0;
	int counter = 0;
	double sum = 0;

	// Get first pixel
	for (int x = width; x > 0; x--)
	{
		if (pixels[0][x])
		{
			x2 = x;
			y2 = 0;

			x = 0;
		}
	}
	// Get second pixel
	for (int x = width  - 1; x > 0; x--)
	{
		if (pixels[1][x])
		{
			y1 = 1;
			x1 = x;

			x = 0;
		}
	}
	if ((double)(x1 - x2) / (y1 - y2) < 0)
	{
		sum += (double)(x1 - x2) / (y1 - y2);
		counter++;
	}

	for (int y = 2; y < height / 3; y++)
	{
		for (int x = width - 1; x > 0; x--)
		{
			if (pixels[y][x]) {
				x2 = x1;
				y2 = y1;
				x1 = x;
				y1 = y;
				if ((double)(x1 - x2) / (y1 - y2) < 0)
				{
					sum += (double)(x1 - x2) / (y1 - y2);
					counter++;
				}
				x = 0;
			}
		}

	}
	if (counter > 0)
		return sum /= counter;
	else
		return 0;
}

double get_max_fall_mid_left(int height, int width, int pixels[height][width])
{
	int y1 = 0, y2 = 0, x1 = 0, x2 = 0;
	int counter = 0;
	double sum = 0;

	// Get first pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[height / 3][x])
		{
			x2 = x;
			y2 = height / 3;

			x = width;
		}
	}
	// Get second pixel
	for (int x = 0; x < width; x++)
	{
		if (pixels[height / 3 + 1][x])
		{
			y1 = height / 3 + 1;
			x1 = x;

			x = width;
		}
	}
	if ((double)(x1 - x2) / (y1 - y2) < 0)
	{
		sum += (double)(x1 - x2) / (y1 - y2);
		counter++;
	}

	for (int y = height / 3 + 2; y < 2 * height / 3; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x]) {
				x2 = x1;
				y2 = y1;
				x1 = x;
				y1 = y;
				if ((double)(x1 - x2) / (y1 - y2) < 0)
				{
					sum += (double)(x1 - x2) / (y1 - y2);
					counter++;
				}
				x = width;
			}
		}

	}
	if (counter > 0)
		return sum /= counter;
	else
		return 0;
}

double get_smoothness_mid_left(int height, int width, int pixels[height][width])
{
	int N = height / 3;
	double grads[N];

	for (int y = 2 * height / 3; y > height / 3 + 1; y--)
	{
		int y1, y2, x1, x2;

		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				y1 = y;
				x1 = x;

				x = width;
			}
		}

		for (int x = 0; x < width; x++)
		{
			if (pixels[y - 1][x])
			{
				y2 = y - 1;
				x2 = x;

				x = width;
			}
		}	
		grads[2 * height / 3 - y] = (double)(x1 - x2) / (y1 - y2);
		//printf("grad is %lf", grads[2 * height / 3 - y]);
		int x;
		//scanf("%d", &x);
	}

	// Calculate SD
	double mean = 0;
	for (int i = 0; i < N; i++)
	{
		mean += grads[i];
	}

	mean /= N;

	double square_difference_sum = 0;
	for (int i = 0; i < N; i++)
	{
		square_difference_sum += (grads[i] - mean)*(grads[i] - mean);
	}
	square_difference_sum /= N;

	return sqrt(square_difference_sum);

}

double vert_line_follower(int height, int width, int pixels[height][width])
{
	for (int y = 0; y < height - 1; y++)
	{
		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{

			}
		}
	}
	return 42;
}

double get_deepest_left_bot_right(int height, int width, int pixels[height][width])
{
	int deepest = 200;

	for (int y = height / 10; y < height / 3; y++)
	{
		for (int x = width - 1; x > 0; x--)
		{
			if (pixels[y][x]) {
				if (y < deepest)
					deepest = x;

				x = 0;
			}
		}

	}
	return (double) deepest / width;
}

// gets the number of vertical strokes in the bottom half of the image
double get_verts_bot(int height, int width, int pixels[height][width])
{
	double swaps = 0;
	int color = 0;
	for (int y = height / 8; y < height / 3; y++)
	{
		color = pixels[y][0];
		for (int x = 1; x < width; x++)
		{
			if (pixels[y][x] != color) {
				swaps++;
				color = pixels[y][x];
			}
		}

	}
	return swaps / (height / 3 - height / 8);
}

// get max change in bottom vertical line in the bottom half of image
double get_max_diff_vert(int height, int width, int pixels[height][width])
{
	int longest = 0;
	int shortest = 200;
	int previous = 0;
	for (int x = 0; x < width; x++)
	{
		int y = 0;
		while (pixels[y][x] == 0 && y < height / 3) y++;
		
		int len = 0;
		if (y != height / 3)
		{
			while (pixels[y][x] == 1)
			{
				y++;
				len++;
			}

			if (len > longest)
				longest = len;
			if (len < shortest)
				shortest = len;
		}
	}

	return (double)(longest-shortest) / height;

}

double get_SD_grad_bot_left(int height, int width, int pixels[height][width])
{
	int N = height / 3;
	double grads[N];

	for (int y = 0; y < N; y++)
	{
		int y1, y2, x1, x2;

		for (int x = 0; x < width; x++)
		{
			if (pixels[y][x])
			{
				y1 = y;
				x1 = x;

				x = width;
			}
		}

		for (int x = 0; x < width; x++)
		{
			if (pixels[y + 1][x])
			{
				y2 = y - 1;
				x2 = x;

				x = width;
			}
		}
		grads[y] = (double)(x1 - x2) / (y1 - y2);
		//printf("grad is %lf", grads[2 * height / 3 - y]);
		int x;
		//scanf("%d", &x);
	}

	// Calculate SD
	double mean = 0;
	for (int i = 0; i < N; i++)
	{
		mean += grads[i];
	}

	mean /= N;
	double square_difference_sum = 0;
	for (int i = 0; i < N; i++)
	{
		square_difference_sum += (grads[i] - mean)*(grads[i] - mean);
	}
	square_difference_sum /= N;

	return sqrt(square_difference_sum);
}

double get_SD_grad_bot_right(int height, int width, int pixels[height][width])
{
	int N = height / 3;
	double grads[N];

	int tallest = 0;
	int shortest = 0;
	int y1 = 0;

	// find tallest
	for (int y = 0; y < N; y++)
	{
		int x = width - 1;
		while (pixels[y][x] == 0) x--;

		if (x > tallest)
		{
			tallest = x;
			y1 = y;
		}
	}	
	shortest = tallest;
	// find shortest above  tallest
	for (int y = y1; y < N; y++)
	{
		int x = width - 1;
		while (pixels[y][x] == 0) x--;

		if (x < shortest)
			shortest = x;
	}
	//printf("tallest shortest %d %d %lf\n", tallest, shortest, (double)(tallest - shortest) / width);
	return (double)(tallest - shortest) / width;

}

double get_largest_delta_TR(int height, int width, int pixels[height][width])
{
	int N = height / 3;
	double grads[N];

	int tallest = 0;
	int shortest = 0;
	int y1 = 0;

	// find tallest
	for (int y = height - 1; y > 2 * height / 3; y--)
	{
		int x = width - 1;
		while (pixels[y][x] == 0) x--;

		if (x > tallest)
		{
			tallest = x;
			y1 = y;
		}
	}
	shortest = tallest;
	// find shortest above  tallest
	for (int y = y1; y > 2 * height / 3; y--)
	{
		int x = width - 1;
		while (pixels[y][x] == 0) x--;

		if (x < shortest)
			shortest = x;
	}
	//printf("tallest shortest %d %d %lf\n", tallest, shortest, (double)(tallest - shortest) / width);
	return (double)(tallest - shortest) / width;

}

//double get_dist_from_left_for_