//
//  transform.h
//  minip
//
//  Created by Dasa Anand on Feb-April.
//  Copyright 2010 __ CG __. All rights reserved.
//	Made on Mac using openGL as base and xcode as compiler.

//#define angc 0.02685329252
#define angc 0.01745329252
struct layer lay[20];
extern int selected;
extern struct s3 *shift;
float H[3][3],xnor,ynor;

void load_identity()
{
	int i,j;
	for (i=0; i<=2; i++)
	{
		for (j=0; j<=2; j++)
		{
			if (i==j)
			{
				H[i][j]=1;
			}
			else
			{
				H[i][j]=0;
			}
		}
	}
}



void scaling(float sx, float sy)
{
	int i;
	for (i=0; i<=2; i++)
	{
		H[i][0]*=sx;
		H[i][1]*=sy;
	}
}



void rotation(float angle)
{
		
	angle=angle*angc;
	int i;
	float c,s,tempx;
	c=cos(angle);
	s=sin(angle);
	if (lay[selected].clockwise==1)
	{
		s=-s;
	}
	
	for (i=0; i<=2; i++)
	{
		tempx=H[i][0]*c-H[i][1]*s;
		H[i][1]=H[i][0]*s+H[i][1]*c;
		H[i][0]=tempx;
	}
	
}


void translate(float tx, float ty)
{
	H[2][0]=H[2][0]+tx;
	H[2][1]=H[2][1]+ty;
}



void transform_matrix(float x, float y)
{
	int flag;
	float tempx;
	
	flag=0;
	if (x==shift->x1 && y==shift->y1)
	{
		flag=1;
	}
	if (x==shift->x2 && y==shift->y2)
	{
		flag=2;
	}
	
	tempx=x*H[0][0]+y*H[1][0]+H[2][0];
	y=x*H[0][1]+y*H[1][1]+H[2][1];
	x=tempx;
	
	if (flag==1)
	{
		shift->x1=x;
		shift->y1=y;
	}
	if (flag==2)
	{
		shift->x2=x;
		shift->y2=y;
	}	
	
	
}
