#ifndef DATA_H
#define DATA_H

typedef struct DigitMetrics DigitMetrics;
struct DigitMetrics {
	double horBalance;
	double verBalance;
	double tallness;
	double hole_size_fraction;
	int holes;
};

#define N_OF_METRICS 25

typedef enum Metric Metric;
enum Metric
{
	mhorBalance,
	mverBalance,
	mtallness,
	mhole_size_fraction,
	mholes,
	mdensity,
	mmaxVertical,
	mmaxHorizontal,
	maverageWidth,
	mmidLeftDensity,
	mbotRightDensity,
	mvertPosOfHole,
	msdHorBalance,
	mmeanWidthOfThree,
	mhorBalTop,
	msteepestFallTopLeft,
	msteepestFallBotRight,
	msteepestFallMidLeft,
	mbotHorBalance,
	mdeepestLeftBotRight,
	mvertsBot,
	mmaxDiffVertBot,
	mSDgradBotLeft,
	mSDgradBotRight,
	mdeltaTR
	//msmoothnessMidLeft,
	//leftchecks
};

double getSum(double digit_metrics[100][N_OF_METRICS], Metric metric);
double getAverage(double digit_metrics[100][N_OF_METRICS], Metric metric);
double get_stddevS(double digit_metrics[100][N_OF_METRICS], Metric metric);

void read_stats_table(double digit_stats[10][N_OF_METRICS][2]);

#endif
