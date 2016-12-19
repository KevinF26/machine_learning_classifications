#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<limits.h>

typedef struct row_weight{
	int num_on_weight;
	int num_on_sets_weight;
	int width_weight;
}row_weight;

typedef struct column_weight{
	int num_on_weight;
	int num_on_sets_weight;
	int height_weight;
}column_weight;

typedef struct WeightVector{
	int bias;
	row_weight rows[19];
	column_weight columns[28];
	int max_width_weight;
	int min_width_weight;
	int avg_width_weight;
	int max_height_weight;
	int min_height_weight;
	int avg_height_weight;
}WeightVector;

typedef struct row{
        int num_on;
        int num_on_sets;
        int width;
}row;

typedef struct column{
        int num_on;
        int num_on_sets;
        int height;
}column;

typedef struct DigitBitMapData{
        char pixels[19][28];
        row rows[19];
        column columns[28];
        int max_width;
        int min_width;
        int avg_width;
        int max_height;
        int min_height;
        int avg_height;
        int label;
}DigitBitMapData;

void extract_features(FILE * training_images);
int predict();
void build_digit_feature_data();
void test_classification();
void update_weights(int,int);
void initialize_weight_vector();
#define NUM_ON 0
#define NUM_SETS_ON 1
#define LINE_WIDTH 2

DigitBitMapData curr;

WeightVector classes[10];
