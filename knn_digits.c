#include"knn_digits.h"

int main(int argc, char * argv[])
{
	double t1,t2;
	TRAINING_SIZE=5000;
        if(argc>1)
        {
                TRAINING_SIZE=atoi(argv[1]);
                if(TRAINING_SIZE<0)
                {
                        printf("negative number entered for training size\n");
                        exit(-1);
                }
                if(TRAINING_SIZE>5000)
                {
                        printf("max training size is 5000\n");
                        exit(-1);
                }
        }

	t1=get_time();
	build_digit_feature_data();
	test_classification();
	t2=get_time();
	printf("elapsed time=%fs\n",t2-t1);	
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
	printf("success rate=%.4g%%\n",(float)numcorrect*100/(numcorrect+numincorrect));
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
