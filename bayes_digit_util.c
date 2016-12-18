#include"bayes_digit.h"

int predict()
{
	int i,j;
	int guess=-1;
	double highestProbability=-INFINITY;
	double probabilities[10];
	for(i=0;i<10;i++)
	{
		probabilities[i]=log(training_feats[i].likelyhood);
		
		probabilities[i]+=log(training_feats[i].max_width_likelyhoods[curr.max_width]);
		probabilities[i]+=log(training_feats[i].min_width_likelyhoods[curr.min_width]);
		//probabilities[i]+=log(training_feats[i].avg_width_likelyhoods[curr.avg_width]);
		probabilities[i]+=log(training_feats[i].max_height_likelyhoods[curr.max_height]);
		probabilities[i]+=log(training_feats[i].min_height_likelyhoods[curr.min_height]);
		//probabilities[i]+=log(training_feats[i].avg_height_likelyhoods[curr.avg_height]);

		for(j=0;j<19;j++)
        	{
			probabilities[i]+=log(training_feats[i].rows[j].num_on_likelyhoods[curr.rows[j].num_on]);
			probabilities[i]+=log(training_feats[i].rows[j].num_on_sets_likelyhoods[curr.rows[j].num_on_sets%10]);
			probabilities[i]+=log(training_feats[i].rows[j].width_likelyhoods[curr.rows[j].width]);
		}
		for(j=0;j<28;j++)
        	{
			probabilities[i]+=log(training_feats[i].columns[j].num_on_likelyhoods[curr.columns[j].num_on]);
			probabilities[i]+=log(training_feats[i].columns[j].num_on_sets_likelyhoods[curr.columns[j].num_on_sets%10]);
		//	probabilities[i]+=log(training_feats[i].columns[j].height_likelyhoods[curr.columns[j].height]);
		}
	}
	for(i=0;i<10;i++)
	{
		if(probabilities[i]>highestProbability)
		{
			highestProbability=probabilities[i];
			guess=i;
		}
	}
	return guess;
	
}

void add_features()
{
	int i;
	training_feats[curr.label].total_training_instances++;
	training_feats[curr.label].max_width[curr.max_width]++;
	training_feats[curr.label].min_width[curr.min_width]++;
	training_feats[curr.label].avg_width[curr.avg_width]++;
	training_feats[curr.label].max_height[curr.max_height]++;
	training_feats[curr.label].min_height[curr.min_height]++;
	training_feats[curr.label].avg_height[curr.avg_height]++;

	for(i=0;i<19;i++)
	{
		training_feats[curr.label].rows[i].num_on[curr.rows[i].num_on]++;
		training_feats[curr.label].rows[i].num_on_sets[curr.rows[i].num_on_sets]++;
		training_feats[curr.label].rows[i].width[curr.rows[i].width]++;
	}

	for(i=0;i<28;i++)
	{
		training_feats[curr.label].columns[i].num_on[curr.columns[i].num_on]++;
		training_feats[curr.label].columns[i].num_on_sets[curr.columns[i].num_on_sets]++;
		training_feats[curr.label].columns[i].height[curr.columns[i].height]++;
	}

}

void calculate_likelyhoods(int num_training_instances)
{
	int i,j,k;
	for(i=0;i<10;i++)
	{
		training_feats[i].likelyhood=((double)training_feats[i].total_training_instances/num_training_instances);
		for(j=0;j<28;j++)
		{
			training_feats[i].min_width_likelyhoods[j]=((double)(training_feats[i].min_width[j]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE));
			training_feats[i].max_width_likelyhoods[j]=((double)(training_feats[i].max_width[j]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE));
			training_feats[i].avg_width_likelyhoods[j]=((double)(training_feats[i].avg_width[j]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE));
		}
		for(j=0;j<19;j++)
		{
			training_feats[i].min_height_likelyhoods[j]=((double)(training_feats[i].min_height[j]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE));
			training_feats[i].max_height_likelyhoods[j]=((double)(training_feats[i].max_height[j]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE));
			training_feats[i].avg_height_likelyhoods[j]=((double)(training_feats[i].avg_height[j]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE));
		}
		for(j=0;j<19;j++)
		{
			DigitRowFeats * tempRow=&training_feats[i].rows[j];
			for(k=0;k<4;k++)
			{
				tempRow->num_on_sets_likelyhoods[k]=(double)(tempRow->num_on_sets[k]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE);
			}
			for(k=0;k<28;k++)
			{
				tempRow->num_on_likelyhoods[k]=(double)(tempRow->num_on[k]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE);
				tempRow->width_likelyhoods[k]=(double)(tempRow->width[k]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE);
			}
		}
		for(j=0;j<28;j++)
		{
			DigitColumnFeats * tempColumn=&training_feats[i].columns[j];
			for(k=0;k<4;k++)
			{
				tempColumn->num_on_sets_likelyhoods[k]=(double)(tempColumn->num_on_sets[k]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE);
			}
			for(k=0;k<19;k++)
			{
				tempColumn->num_on_likelyhoods[k]=(double)(tempColumn->num_on[k]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE);
				tempColumn->height_likelyhoods[k]=(double)(tempColumn->height[k]+LAPLACE)/(training_feats[i].total_training_instances+LAPLACE);
			}
		}
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
		image_read=getline(&image_line,&image_len,imagesfd);
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
