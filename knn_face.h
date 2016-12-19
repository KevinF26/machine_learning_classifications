#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include<limits.h>
#include<sys/time.h>
#include<sys/resource.h>

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
double get_time();


FaceBitMapData * neighbors[450];
int TRAINING_SIZE;
