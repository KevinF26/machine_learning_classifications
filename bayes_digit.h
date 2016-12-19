#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<sys/time.h>
#include<sys/resource.h>
	
typedef struct DigitRowFeats{
	int num_on[28];
	int num_on_sets[4];
	double num_on_likelyhoods[28];
	double num_on_sets_likelyhoods[4];
	int width[28];
	double width_likelyhoods[28];
}DigitRowFeats;

typedef struct DigitColumnFeats{
	int num_on[19];
	int num_on_sets[4];
	double num_on_likelyhoods[19];
	double num_on_sets_likelyhoods[4];
	int height[19];
	double height_likelyhoods[19];
}DigitColumnFeats;

typedef struct DigitFeatureStore{
	DigitRowFeats rows[19];
	DigitColumnFeats columns[28];
	int max_width[28];
	int min_width[28];
	int avg_width[28];
	int max_height[19];
	int min_height[19];
	int avg_height[19];
	double max_width_likelyhoods[28];
	double min_width_likelyhoods[28];
	double avg_width_likelyhoods[28];
	double max_height_likelyhoods[19];
    double min_height_likelyhoods[19];
    double avg_height_likelyhoods[19];
	int total_training_instances;
	double likelyhood;
}DigitFeatureStore;

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

//forward declarations
void build_digit_feature_data();
void test_classification();
void print_heatmap();
void print_heatmapof(int val);
void calculate_likelyhoods();
void add_features();
void extract_features(FILE * training_images);
int predict();
double get_time();
int training_size;

#define LAPLACE 1
#define NUM_ON 0
#define NUM_SETS_ON 1
#define LINE_WIDTH 2

//global struct of features for each of digits 0-9
DigitFeatureStore training_feats[10];
DigitBitMapData curr;
