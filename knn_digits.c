#include"knn_digits.h"

int main(int argc, char * argv[])
{
	build_digit_feature_data();
	test_classification();
}


void test_classification()
{
	DigitBitMapData * curr;
	int guess;
	int numcorrect=0;
	int numincorrect=0;
	FILE * test_images;
	FILE * test_labels;
	char * label_line=NULL;
        size_t label_len=0;
        ssize_t label_read;
	//these fopen commands are unique to my directory structure
	//folder hosting the executable should contain directories for digitdata and facedata
	test_images=fopen("./digitdata/testimages","r");
	if(test_images==NULL)
		exit(EXIT_FAILURE);
	test_labels=fopen("./digitdata/testlabels","r");
	if(test_labels==NULL)
		exit(EXIT_FAILURE);

	curr=malloc(sizeof(DigitBitMapData));

	while((label_read=getline(&label_line, &label_len, test_labels)) !=-1) 
	{
		memset(curr,0,sizeof(DigitBitMapData));
		curr->label=label_line[0]-48;
		extract_features(test_images,curr);
		guess=predict(curr);
		//printf("guess=%d,correct=%d\n",guess,curr.label);
		if(guess==curr->label)
		{
			numcorrect++;
		}
		else
		{
			numincorrect++;
		}
	}
	int i;
	printf("numcorrect=%d,numincorrect=%d\n",numcorrect,numincorrect);
}

void build_digit_feature_data()
{
	DigitBitMapData * curr;
	int num_training_instances=0;
	FILE * training_images;
	FILE * training_labels;
	char * label_line=NULL;
        size_t label_len=0;
        ssize_t label_read;
	int guess=-1;	
	//these fopen commands are unique to my directory structure
	//folder hosting the executable should contain directories for digitdata and facedata
	training_images=fopen("./digitdata/trainingimages","r");
	if(training_images==NULL)
		exit(EXIT_FAILURE);
	training_labels=fopen("./digitdata/traininglabels","r");
	if(training_labels==NULL)
		exit(EXIT_FAILURE);

	int i;
	//while((label_read=getline(&label_line, &label_len, training_labels)) !=-1) 
	for(i=0;i<TRAINING_SIZE;i++)
	{
		curr=malloc(sizeof(DigitBitMapData));
		label_read=getline(&label_line, &label_len, training_labels);
		num_training_instances++;
		curr->label=label_line[0]-48;
		extract_features(training_images,curr);
		neighbors[i]=curr;
	}

}
