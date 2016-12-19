#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<limits.h>
#include<sys/time.h>
#include<sys/resource.h>


typedef struct DigitBitMapData{
        int pixels[19][28];
        int label;
}DigitBitMapData;

void extract_features(FILE * training_images, DigitBitMapData * curr);
int predict();
void build_digit_feature_data();
void test_classification();
void update_weights(int,int);
void initialize_weight_vector();
double get_time();

int TRAINING_SIZE;
DigitBitMapData * neighbors[5000];
