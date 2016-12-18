#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<limits.h>
#define TRAINING_SIZE 450


typedef struct FaceBitMapData{
        int pixels[66][60];
        int label;
}FaceBitMapData;

void extract_features(FILE * training_images, FaceBitMapData * curr);
int predict();
void build_face_feature_data();
void test_classification();
void update_weights(int,int);
void initialize_weight_vector();



FaceBitMapData * neighbors[TRAINING_SIZE];
