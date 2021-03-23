/*Parallel Hierarchical One-Dimensional Search for motion estimation*/
/*Initial algorithm - Used for simulation and profiling             */

#include <sys/time.h>

#include <stdio.h>
#include <stdlib.h>

#define N 144     /*Frame dimension for QCIF format*/
#define M 176     /*Frame dimension for QCIF format*/
//#define B 16      /*Block size*/
#define p 7       /*Search space. Restricted in a [-p,p] region around the
                    original location of the block.*/
int Bx,By;


#define FOR_LOOP_S(s)                                                           \
    min1 = 255*Bx*By;                                                             \
    min2 = 255*Bx*By;                                                             \
    FOR_LOOP_I(-s);                                                             \
    FOR_LOOP_I(0);                                                              \
    FOR_LOOP_I(s);                                                              \
    array_x += bestx;                                                           \
    array_y += besty;


#define FOR_LOOP_I(i)                                                           \
    distx = 0;                                                                  \
    disty = 0;                                                                  \
    for(k=0; k<Bx; k++)                                                          \
    {                                                                           \
        for(l=0; l<By; l++)                                                      \
        {                                                                       \
            p1 = current[Bx*x+k][By*y+l];                                         \
            if((Bx*x + array_x + i + k) < 0 ||                                   \
            (Bx*x + array_x + i + k) > (N-1) ||                                  \
            (By*y + array_y + l) < 0 ||                                          \
            (By*y + array_y + l) > (M-1))                                        \
            {                                                                   \
                p2 = 0;                                                         \
            } else {                                                            \
                p2 = previous[Bx*x+array_x+i+k][By*y+array_y+l];                  \
            }                                                                   \
            if((Bx*x + array_x + k) <0 ||                                        \
            (Bx*x + array_x + k) > (N-1) ||                                      \
            (By*y + array_y + i + l) < 0 ||                                      \
            (By*y + array_y + i + l) > (M-1))                                    \
            {                                                                   \
                q2 = 0;                                                         \
            } else {                                                            \
                q2 = previous[Bx*x+array_x+k][By*y+array_y+i+l];                  \
            }                                                                   \
            distx += abs(p1-p2);                                                \
            disty += abs(p1-q2);                                                \
        }                                                                       \
    }                                                                           \
    if(distx < min1)                                                            \
    {                                                                           \
        min1 = distx;                                                           \
        bestx = i;                                                              \
    }                                                                           \
    if(disty < min2)                                                            \
    {                                                                           \
        min2 = disty;                                                           \
        besty = i;                                                              \
    }  

void read_sequence(int current[N][M], int previous[N][M])
{ 
	FILE *picture0, *picture1;
	int i, j;

	if((picture0=fopen("akiyo0.y","rb")) == NULL)
	{
		printf("Previous frame doesn't exist.\n");
		exit(-1);
	}

	if((picture1=fopen("akiyo1.y","rb")) == NULL) 
	{
		printf("Current frame doesn't exist.\n");
		exit(-1);
	}

  /*Input for the previous frame*/
  for(i=0; i<N; i++)
  {
    for(j=0; j<M; j++)
    {
      previous[i][j] = fgetc(picture0);
    }
  }

	/*Input for the current frame*/
	for(i=0; i<N; i++)
  {
		for(j=0; j<M; j++)
    {
			current[i][j] = fgetc(picture1);
    }
  }

	fclose(picture0);
	fclose(picture1);
}


void phods_motion_estimation(int current[N][M], int previous[N][M],
    int vectors_x[N/Bx][M/By],int vectors_y[N/Bx][M/By])
{
  int x, y, i, j, k, l, p1, p2, q2, distx, disty, S, min1, min2, bestx, besty;

  distx = 0;
  disty = 0;

  /*Initialize the vector motion matrices*/
  for(i=0; i<N/Bx; i++)
  {
    for(j=0; j<M/By; j++)
    {
      vectors_x[i][j] = 0;
      vectors_y[i][j] = 0;
    }
  }

  /*For all blocks in the current frame*/
  for(x=0; x<N/Bx; x++)
  {
      for(y=0; y<M/By; y++)
      {
          int array_x = vectors_x[x][y];
          int array_y = vectors_y[x][y];
          FOR_LOOP_S(4);
          FOR_LOOP_S(2);
          FOR_LOOP_S(1);
      }
  }
}



int main( int argc, char *argv[] )
{
   
  if (argc == 1)
  {
    Bx = 16;
    By = 16;
  }
  else if (argc == 3)
  {
    Bx = atoi(argv[1]);
    By = atoi(argv[1]);
  }
  else
  {
    printf("Usage: ./phods_v4_2d block_size_x block_size_y\n");
    exit(1);
  }
  double time;
  struct timeval ts,tf;

  int current[N][M], previous[N][M], motion_vectors_x[N/Bx][M/By],motion_vectors_y[N/Bx][M/By], i, j;
  read_sequence(current,previous);

  gettimeofday(&ts, NULL);


  phods_motion_estimation(current,previous,motion_vectors_x,motion_vectors_y);
  gettimeofday(&tf,NULL);


  time=(tf.tv_sec-ts.tv_sec)+(tf.tv_usec-ts.tv_usec) * 0.000001;
  printf("%lf\n", time);
  return 0;

}
