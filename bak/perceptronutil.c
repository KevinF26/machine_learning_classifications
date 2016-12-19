#include"perceptron.h"

void initialize_weight_vector()
{
	int i,j;
	for(i=0;i<10;i++)
	{
		classes[i].max_width_weight=rand()%10 * pow(-1,rand());
		classes[i].min_width_weight=rand()%10 * pow(-1,rand());
		classes[i].avg_width_weight=rand()%10 * pow(-1,rand());
		classes[i].max_height_weight=rand()%10 * pow(-1,rand());
                classes[i].min_height_weight=rand()%10 * pow(-1,rand());
                classes[i].avg_height_weight=rand()%10 * pow(-1,rand());
		for(j=0;j<19;j++)
		{
			classes[i].rows[j].num_on_weight=rand()%10 * pow(-1,rand());
			classes[i].rows[j].num_on_sets_weight=rand()%10 * pow(-1,rand());
			classes[i].rows[j].width_weight=rand()%10 * pow(-1,rand());
		}
		for(j=0;j<28;j++)
		{
			classes[i].columns[j].num_on_weight=rand()%10 * pow(-1,rand());
			classes[i].columns[j].num_on_sets_weight=rand()%10 * pow(-1,rand());
			classes[i].columns[j].height_weight=rand()%10 * pow(-1,rand());
		}
	}
}

int predict()
{
	int i,j;
	int guess=-1;
	long long highestactivation=LLONG_MIN;
	long long activations[10]={0};

	for(i=0;i<10;i++)
	{
		activations[i]+=classes[i].bias;
		activations[i]+=classes[i].max_width_weight*curr.max_width;
		activations[i]+=classes[i].min_width_weight*curr.min_width;
		activations[i]+=classes[i].avg_width_weight*curr.avg_width;
		activations[i]+=classes[i].max_height_weight*curr.max_height;
                activations[i]+=classes[i].min_height_weight*curr.min_height;
                activations[i]+=classes[i].avg_height_weight*curr.avg_height;
		for(j=0;j<19;j++)
		{
			activations[i]+=classes[i].rows[j].num_on_weight * curr.rows[j].num_on;
			activations[i]+=classes[i].rows[j].num_on_sets_weight * curr.rows[j].num_on_sets;
			activations[i]+=classes[i].rows[j].width_weight * curr.rows[j].width;
		}
		for(j=0;j<28;j++)
		{
			activations[i]+=classes[i].columns[j].num_on_weight * curr.columns[j].num_on;
                        activations[i]+=classes[i].columns[j].num_on_sets_weight * curr.columns[j].num_on_sets;
                        activations[i]+=classes[i].columns[j].height_weight * curr.columns[j].height;
		}
	}
	printf("BREAK\n\n");
	for(i=0;i<10;i++)
	{
		printf("activation for %d is %lld\n",i,activations[i]);
		if(activations[i]>highestactivation)
		{
			highestactivation=activations[i];
			guess=i;
		}
	}
	printf("guess is %d,correct was %d\n",guess,curr.label);
	return guess;
	
}

void update_weights(int guessed,int correct)
{
	int i,j;
	
	classes[guessed].bias--;
	classes[guessed].max_width_weight-=curr.max_width;
	classes[guessed].min_width_weight-=curr.min_width;
	classes[guessed].avg_width_weight-=curr.avg_width;
	classes[guessed].max_height_weight-=curr.max_height;
        classes[guessed].min_height_weight-=curr.min_height;
        classes[guessed].avg_height_weight-=curr.avg_height;
	for(i=0;i<19;i++)
	{
		classes[guessed].rows[i].num_on_weight-=curr.rows[i].num_on;
		classes[guessed].rows[i].num_on_sets_weight-=curr.rows[i].num_on_sets;
		classes[guessed].rows[i].width_weight-=curr.rows[i].width;
	}
	for(i=0;i<28;i++)
	{
		classes[guessed].columns[i].num_on_weight-=curr.columns[i].num_on;
		classes[guessed].columns[i].num_on_sets_weight-=curr.columns[i].num_on_sets;
		classes[guessed].columns[i].height_weight-=curr.columns[i].height;
	}

	classes[correct].bias++;
        classes[correct].max_width_weight+=curr.max_width;
        classes[correct].min_width_weight+=curr.min_width;
        classes[correct].avg_width_weight+=curr.avg_width;
        classes[correct].max_height_weight+=curr.max_height;
        classes[correct].min_height_weight+=curr.min_height;
        classes[correct].avg_height_weight+=curr.avg_height;
        for(i=0;i<19;i++)
        {
                classes[correct].rows[i].num_on_weight+=curr.rows[i].num_on;
                classes[correct].rows[i].num_on_sets_weight+=curr.rows[i].num_on_sets;
                classes[correct].rows[i].width_weight+=curr.rows[i].width;
        }
        for(i=0;i<28;i++)
        {
                classes[correct].columns[i].num_on_weight+=curr.columns[i].num_on;
                classes[correct].columns[i].num_on_sets_weight+=curr.columns[i].num_on_sets;
                classes[correct].columns[i].height_weight+=curr.columns[i].height;
        }

}

void extract_features(FILE * imagesfd)
{
	int i,j,k;
	char * image_line=NULL;
	size_t image_len=0;
	ssize_t image_read;
	char whitespace;
	int prev;
	int minindex,maxindex;
	int minwidth=28,maxwidth=0;
	int widthsum;
	int num_on_line;
	int num_sets_line;
	int minheight,maxheight,heightsum;
	//strip whitespace
	whitespace=1;
	while(whitespace)
	{
		image_read=getline(&image_line,&image_len,imagesfd);
		for(i=0;i<strlen(image_line);i++)
		{
			if(!isspace(image_line[i]))
			{
				whitespace=0;
				break;
			}
		}
	}
	//populate points grid
	for(i=0;i<19;i++)
	{
		image_read=getline(&image_line,&image_len,imagesfd);
		if(image_read==-1)
		{
			break;
		}

		for(j=0;j<28;j++)
		{
			if(image_line[j]=='+' || image_line[j]=='#')
			{
				curr.pixels[i][j]=1;
			}
			else
			{
				curr.pixels[i][j]=0;
			}
		}
	}
	
	//populate row data
	widthsum=0;
	maxwidth=0;
	minwidth=28;
	for(i=0;i<19;i++)
	{
		num_on_line=0;
		num_sets_line=0;
		minindex=0;
		maxindex=0;
		prev=0;
		for(j=0;j<28;j++)
		{
			if(curr.pixels[i][j]==1)
			{
				if(minindex==0)
					minindex=j;
				maxindex=j;
				num_on_line++;
				if(prev==0)
				{
					prev=1;
					num_sets_line++;
				}
			}
			else
			{
				prev=0;
			}
		}
		widthsum+=maxindex-minindex;
		if(maxindex==0)
			curr.rows[i].width=0;
		else
			curr.rows[i].width=maxindex-minindex;
		if(maxindex>=1 && (maxindex-minindex)<minwidth)
			minwidth=maxindex-minindex;
		if((maxindex-minindex)>maxwidth)
			maxwidth=maxindex-minindex;
		curr.rows[i].num_on=num_on_line;
		curr.rows[i].num_on_sets=num_sets_line%4;
	}
	curr.avg_width=(int)widthsum/19;
	curr.max_width=maxwidth;
	curr.min_width=minwidth;


	//populate column data
	heightsum=0;
	maxheight=0;
	minheight=19;
	for(i=0;i<28;i++)
	{
		num_on_line=0;
		num_sets_line=0;
		minindex=0;
		maxindex=0;
		prev=0;
		for(j=0;j<19;j++)
		{
			if(curr.pixels[j][i]==1)
			{
				if(minindex==0)
					minindex=j;
				maxindex=j;
				num_on_line++;
				if(prev==0)
				{
					prev=1;
					num_sets_line++;
				}
			}
			else
			{
				prev=0;
			}
		}
		heightsum+=maxindex-minindex;
		if(maxindex==0)
			curr.columns[i].height=0;
		else
			curr.columns[i].height=maxindex-minindex;
		if((maxindex-minindex)!=0 && (maxindex-minindex)<minheight)
			minheight=maxindex-minindex;
		if((maxindex-minindex)>maxheight)
			maxheight=maxindex-minindex;
		curr.columns[i].num_on=num_on_line;
		curr.columns[i].num_on_sets=num_sets_line%4;
	}
	curr.avg_height=(int)heightsum/28;
	curr.max_height=maxheight;
	curr.min_height=minheight;

}
