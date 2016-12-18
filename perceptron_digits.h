#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<limits.h>



typedef struct WeightVector{
	int bias;
	int pixel_weights[19][28];
}WeightVector;

typedef struct DigitBitMapData{
        int pixels[19][28];
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
