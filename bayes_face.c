#include"bayes_face.h"

int main(int argc, char * argv[])
{
	build_face_feature_data();
	test_classification();
}


void test_classification()
{
	int guess;
	int numcorrect=0;
	int numincorrect=0;
	FaceBitMapData curr;
	FILE * test_images;
	FILE * test_labels;
	char * label_line=NULL;
        size_t label_len=0;
        ssize_t label_read;
	//these fopen commands are unique to my directory structure
	//folder hosting the executable should contain directories for facedata and facedata
	test_images=fopen("./facedata/facedatatest","r");
	if(test_images==NULL)
		exit(EXIT_FAILURE);
	test_labels=fopen("./facedata/facedatatestlabels","r");
	if(test_labels==NULL)
		exit(EXIT_FAILURE);

	while((label_read=getline(&label_line, &label_len, test_labels)) !=-1) 
	{
		memset(&curr,0,sizeof(FaceBitMapData));
		curr.label=label_line[0]-48;
		extract_features(test_images);
		guess=predict();
		//printf("guess=%d,correct=%d\n",guess,curr.label);
		if(guess==curr.label)
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

void build_face_feature_data()
{
	int num_training_instances=0;
	FILE * training_images;
	FILE * training_labels;
	char * label_line=NULL;
        size_t label_len=0;
        ssize_t label_read;	
	//these fopen commands are unique to my directory structure
	//folder hosting the executable should contain directories for facedata and facedata
	training_images=fopen("./facedata/facedatatrain","r");
	if(training_images==NULL)
		exit(EXIT_FAILURE);
	training_labels=fopen("./facedata/facedatatrainlabels","r");
	if(training_labels==NULL)
		exit(EXIT_FAILURE);

	while((label_read=getline(&label_line, &label_len, training_labels)) !=-1) 
	{
		num_training_instances++;
		memset(&curr,0,sizeof(FaceBitMapData));
		curr.label=label_line[0]-48;
		extract_features(training_images);
		add_features();
	}
	calculate_likelyhoods(num_training_instances);

}
