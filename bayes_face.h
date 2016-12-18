#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
	
typedef struct FaceRowFeats{
	int num_on[60];
	int num_on_sets[10];
	double num_on_likelyhoods[60];
	double num_on_sets_likelyhoods[10];
	int width[60];
	double width_likelyhoods[60];
}FaceRowFeats;

typedef struct FaceColumnFeats{
	int num_on[66];
	int num_on_sets[10];
	double num_on_likelyhoods[66];
	double num_on_sets_likelyhoods[10];
	int height[66];
	double height_likelyhoods[66];
}FaceColumnFeats;

typedef struct FaceFeatureStore{
	FaceRowFeats rows[66];
	FaceColumnFeats columns[60];
	int max_width[60];
	int min_width[60];
	int avg_width[60];
	int max_height[66];
	int min_height[66];
	int avg_height[66];
	double max_width_likelyhoods[60];
	double min_width_likelyhoods[60];
	double avg_width_likelyhoods[60];
	double max_height_likelyhoods[66];
    double min_height_likelyhoods[66];
    double avg_height_likelyhoods[66];
	int total_training_instances;
	double likelyhood;
}FaceFeatureStore;

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

typedef struct FaceBitMapData{
	char pixels[66][60];
	row rows[66];
	column columns[60];
	int max_width;
	int min_width;
	int avg_width;
	int max_height;
	int min_height;
	int avg_height;
	int label;
}FaceBitMapData;	

//forward declarations
void build_face_feature_data();
void test_classification();
void print_heatmap();
void print_heatmapof(int val);
void calculate_likelyhoods();
void add_features();
void extract_features(FILE * training_images);
int predict();

#define LAPLACE 1
#define NUM_ON 0
#define NUM_SETS_ON 1
#define LINE_WIDTH 2

//global struct of features for each of faces 0-1
FaceFeatureStore training_feats[2];
FaceBitMapData curr;
