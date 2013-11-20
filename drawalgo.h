//
//  drawalgo.h
//  minip
//
//  Created by Dasa Anand on Feb-April.
//  Copyright 2010 __MyCompanyName__. All rights reserved.
//	Made on Mac using openGL as base and xcode as compiler.

int cho;

void put_pixel(int x,int y)
{
	glBegin(GL_POINTS);
	glVertex2i(x, y);
	glEnd();
}


int diff(int x2, int x1)
{
	if (x2>x1)
	{
		return x2-x1;
	}
	else
	{
		return x1-x2;
	}
}

int sign(int x2, int x1)
{
	if (x2>x1)
	{
		return 1;
	}
	else 
	{
		return -1;
	}
}


void draw_line( int x1, int y1, int x2, int y2, int type, float size)
{
	int x,y,dx,dy,d,s1,s2,t,inter,count,i;
	count=0;
	dx=diff(x2,x1);
	dy=diff(y2,y1);
	s1=sign(x2,x1);
	s2=sign(y2,y1);
	
	glPointSize(size);
	
	x=x1;
	y=y1;
	if (dy>dx)
	{
		t=dx;
		dx=dy;
		dy=t;
		inter=1;
	}
	else 
	{
		inter=0;
	}
	
	
	d=2*dy-dx;
	put_pixel(x, y);
	for (i=1; i<=dx; i++)
	{
		if (d>=0)
		{
			if (inter==1)
			{
				x+=s1;
			}
			else 
			{
				y+=s2;
			}
			d+=2*(dy-dx);
		}
		else 
		{
			d+=2*dy;
		}
		if (inter==1)
		{
			y+=s2;
		}
		else 
		{
			x+=s1;
		}
		
		count++;
		
		switch (type) 
		{
			case 1://solid
				put_pixel(x, y);
				break;
				
			case 2://dotted
				if (count%5==0)
				{
					put_pixel(x, y);
				}
				break;
				
			case 3://dashed
				if (count%6!=0 && count%7!=0 && count%8!=0 && count%9!=0 )
				{
					put_pixel(x, y);
					
				}
				if (count%9==0)
				{
					count=0;
				}
				break;
				
			case 4://dash_dot
				if (count%6!=0 && count%7!=0 && count%8!=0 && count%10!=0 && count%11!=0 && count%12!=0 && count%13!=0)
				{
					put_pixel(x, y);
				}
				if (count%13==0)
				{
					count=0;
				}
				break;
				
				
			default:
				
				break;
		}
		
	}
	glFlush();
}




void plot_circle(int xc, int yc, int x, int y, int type)
{
	switch (type) 
	{
		case 0://full circle
			put_pixel(xc+x, yc+y);
			put_pixel(xc-x, yc+y);
			put_pixel(xc+x, yc-y);
			put_pixel(xc-x, yc-y);
			put_pixel(xc+y,yc+x);
			put_pixel(xc-y,yc+x);
			put_pixel(xc+y,yc-x);
			put_pixel(xc-y,yc-x);
			break;
			
		case 1://left half
			put_pixel(xc-x, yc-y);
			put_pixel(xc-y, yc-x);
			put_pixel(xc-y, yc+x);
			put_pixel(xc-x, yc+y);
			break;
			
		case 2://right half
			put_pixel(xc+x, yc+y);
			put_pixel(xc+y, yc+x);
			put_pixel(xc+y, yc-x);
			put_pixel(xc+x, yc-y);
			break;
			
		case 3://top half
			put_pixel(xc+x, yc+y);
			put_pixel(xc+y, yc+x);
			put_pixel(xc-y, yc+x);
			put_pixel(xc-x, yc+y);
			break;
			
		case 4://bottom half
			put_pixel(xc-x, yc-y);
			put_pixel(xc-y, yc-x);
			put_pixel(xc+y, yc-x);
			put_pixel(xc+x, yc-y);
			break;
			
		case 5://right top 1/4th
			put_pixel(xc+x, yc+y);
			put_pixel(xc+y, yc+x);
			break;
			
		case 6://right bottom
			put_pixel(xc+x, yc-y);
			put_pixel(xc+y, yc-x);
			break;
			
		case 7://left bottom
			put_pixel(xc-x, yc-y);
			put_pixel(xc-y, yc-x);
			break;
			
		case 8://left top
			put_pixel(xc-x, yc+y);
			put_pixel(xc-y, yc+x);
			break;
			
		default:
			break;
	}
	
}





void draw_circle( int xc, int yc, int r, int type, float size)
{
	int x,y,p;
	
	x=0;
	y=r;
	glPointSize(size);
	plot_circle(xc,yc,x,y,type);
	p=1-r;
	while (x<y)
	{
		if (p<0)
		{
			x++;
			p+=2*x+1;
		}
		else 
		{
			x++;
			y--;
			p+=2*(x-y)+1;
		}
		plot_circle(xc,yc,x,y,type);
	}
}




void draw_rect( int x1, int y1, int x2, int y2, int line_type, float size)
{
	draw_line(x1, y1, x2, y1, line_type, size);
	draw_line(x2, y1, x2, y2, line_type, size);
	draw_line(x2, y2, x1, y2, line_type, size);
	draw_line(x1, y2, x1, y1, line_type, size);
}




void plot_ellipse( int xc, int yc, int x, int y, int type)
{
	switch (type) 
	{
		case 0:
			put_pixel(xc+x, yc+y);
			put_pixel(xc-x, yc+y);
			put_pixel(xc+x, yc-y);
			put_pixel(xc-x, yc-y);
			break;
			
		case 5://right upper
			put_pixel(xc+x, yc+y);
			break;
			
		case 6://right lower
			put_pixel(xc+x, yc-y);
			break;
			
		case 7://left lower
			put_pixel(xc-x, yc-y);
			break;
			
		case 8://left upper
			put_pixel(xc-x, yc+y);
			break;
			
		case 3://top half
			put_pixel(xc+x, yc+y);
			put_pixel(xc-x, yc+y);
			break;
			
		case 1://left half
			put_pixel(xc-x, yc+y);
			put_pixel(xc-x, yc-y);
			break;
			
		case 2://right half
			put_pixel(xc+x, yc+y);
			put_pixel(xc+x, yc-y);
			break;
			
		case 4://bottom half
			put_pixel(xc+x, yc-y);
			put_pixel(xc-x, yc-y);
			break;
			
			
		default:
			break;
	}
	
	
}



void draw_ellipse( int xc, int yc, int a, int b, int type)
{
	if (cho==1)
	{
		active_write(10, xc, yc, a, b, -1, -1, -1, -1, type, 2.0);
	}
	
	double d2,d1;
	int x=0;
	int y=b;
	
	d1=b*b-a*a*b+0.25*a*a;
	glPointSize(2.0);
	plot_ellipse(xc, yc, x, y, type);
	while (a*a*(y-0.5)>b*b*(x+1))
	{
		if (d1<0)
		{
			d1+=b*b*(2*x+3);
		}
		else
		{
			d1+=b*b*(2*x+3)+a*a*(-2*y+2);
			y--;
		}
		x++;
		plot_ellipse(xc, yc, x, y, type);
	}
	d2=b*b*(x+0.5)*(x+0.5)+a*a*(y-1)*(y-1)-a*a*b*b;
	while (y>0)
	{
		if (d2<0)
		{
			d2+=b*b*(2*x+2)+a*a*(-2*y+3);
			x++;
		}
		else
		{
			d2+=a*a*(-2*y+3);
		}
		y--;
		plot_ellipse(xc, yc, x, y, type);		
	}
}
	

float distance (float x1, float y1, float x2, float y2)
{
	float d;
	d=sqrt(pow(x2-x1, 2)+pow(y2-y1, 2));
	return d;
}
	