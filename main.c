//
//  main.c
//  minip
//
//  Created by Dasa Anand on Feb-April.
//  Copyright 2010 __ CG __. All rights reserved.
//	Made on Mac using openGL as base and xcode as compiler.



#ifdef __APPLE__ 
#include <GLUT/GLUT.h>
#include <OpenGL/OpenGL.h>
#include <alloca.h>

#else
#include <gl/glut.h>
#include <malloc.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "lib.h"
#include "transform.h"
#include "drawalgo.h"
#include "char.h"

int work_h,work_w,pop_x,pop_y,startx,starty;
int heightm,heightmax,heightl,starty_layer;
int widthm,widthmax,startx_layer;
int adder,i_startx,i_starty,adder_line_sub_x,adder_line_sub_y,i_startx_line_sub,i_starty_line_sub,i_maxy;
int check,line_type;
int xrnor,yrnor;
int color_no,selected,flag_started,flag_insert;
int main_window,draw_window,tools_window,status_window,color_window,sub_window,col_window,war1_window,layer_window,file_window,pop_window,anim_window;
int adder_poly_sub_x,adder_poly_sub_y,i_startx_poly_sub,i_starty_poly_sub,no_vertex,no;
int adder_char_sub_x,adder_char_sub_y,i_startx_char_sub,i_starty_char_sub,h,w,count;
int adder_circle_sub_x,adder_circle_sub_y,i_startx_circle_sub,i_starty_circle_sub,circle_type,rx,ry,r,rad;
int i_startx_ell_sub,i_starty_ell_sub,ell_type;
int adder_trans_sub_x,adder_trans_sub_y,i_startx_trans_sub,i_starty_trans_sub,startx,starty,adderx,addery;
int open,cho,layer_check,war,allign;
int layer_name_index,index2,file_name_index,openf;
int first,prob,fail,trans,yt1,yt2,dec,count_no,hold,tempdec,negtx,negty,temp_layer;
int col_x,col_y,col_startx,col_clicked,t1,col_starty,animate_col_flag;
int grid_flag,grid_clicked,save_lay_flag,save_lay_index[5],store_index,war_lay;
int store_index,pop_move,pop_check,yl,yh,hold;
int anim_window_activate,store_anim_index,img_anim_index,flag_scale,flag_trans,flag_rot,point,found_img,send;
int action_window,store_layer,action_key,name_index,name,anim_arbit,clipped,move,example;
float xwmin,ywmin,xwmax,ywmax,cou;
FILE *fp;

float xnor,ynor;

char tempch[10],asc_no[10],action[10][50];
char file_name[20]="untitled.df";
char icons[21][20]={"","Line","Free Hand","Polygon","Circle","Text","Create Layer","Edit Layer","Delete Layer","zoom in","zoom out","Undo","Redo","Paint","Grid","File","Select","Clipping","Viewing","Time Animate","Example"};
char icon_text[10][20]={"Icon selected:","Layer selected:"};

typedef unsigned int outcode;
enum { TOP=0x1, BOTTOM=0x2, RIGHT=0x4, LEFT=0x8 };

struct s1
{
	int x,y;
	int r;
}CP,temp,init,chCP,prev,mous,pass,store_pt,anim_scale_pt,pt,anim_arbit_pt;

struct s4 
{
	float x1,y1,x2,y2;
}store_anim[50][150];

struct s5 
{
	int con,no;
	char name[3];
}name_anim[30];


struct s3 rd,*ard,*head,*shift,*end[20],*next_layer,*start[20],*tempc,*store_tail,*prevp1,*prevp2,*prevp,*store,*store_temp,*store_redo,*cp,*ard1,*shift1;
struct color obj[14];
struct layer lay[20],*head_seg,*shift_seg,*ard_seg;
	
/**** char set pt ****/
void char_set(int x, int y)
{
	chCP.x=x;
	chCP.y=y;
}


/**** Convert ascii to num ****/
int asc_num(char ch)
{
	int i;
	for (i=48; i<=57; i++)
	{
		if (i==ch)
		{
			break;
		}
	}
	return i-48;
}


/**** Normalizing the coordinates ****/
void normalize (int x, int y)
{
	x-=startx;
	xnor=normalizeh(work_w,x);
	ynor=normalizeh(work_h,y);
}


/**** Reverse normalize the coordinates ****/
void rev_normalize (float x, float y)
{
	//xrnor=glutGet(GLUT_WINDOW_WIDTH);
	xrnor=work_w;
	xrnor*=x;
	xrnor+=startx;
	//xrnor+=glutGet(GLUT_WINDOW_X);
	//yrnor=glutGet(GLUT_WINDOW_HEIGHT);
	yrnor=work_h;
	yrnor*=y;
}



/**** draw from the file ****/
void draw(int op)
{
	int x1,y1;
	switch (op)
	{
		case 1:
			fscanf(fp, "%f %f %f %f",&rd.x1,&rd.y1,&rd.x2,&rd.y2);
			fscanf(fp, "%d %f",&rd.l_type,&rd.size);
			fscanf(fp, "%f %f %f",&rd.red,&rd.g,&rd.b);
			glColor3f(rd.red, rd.g, rd.b);
			rev_normalize(rd.x1, rd.y1);
			x1=xrnor;
			y1=yrnor;
			rev_normalize(rd.x2, rd.y2);
			draw_line(x1, y1, xrnor, yrnor, rd.l_type, rd.size);
			break;
			
		case 2:
			fscanf(fp, "%f %f %f",&rd.x1,&rd.y1,&rd.size);
			fscanf(fp, "%f %f %f",&rd.red,&rd.g,&rd.b);
			glColor3f(rd.red, rd.g, rd.b);
			rev_normalize(rd.x1, rd.y1);
			
			if (temp.x==0)
			{
				temp.x=xrnor;
				temp.y=yrnor;
				break;
			}
			draw_line(temp.x, temp.y, xrnor, yrnor, 1, rd.size);
			temp.x=xrnor;
			temp.y=yrnor;
			break;
			
		case 3:
			break;
			
		case 4:
			fscanf(fp, "%f %f %d %d %f",&rd.x1,&rd.y1,&rd.r,&rd.c_type,&rd.size);
			fscanf(fp, "%f %f %f",&rd.red,&rd.g,&rd.b);
			glColor3f(rd.red, rd.g, rd.b);
			rev_normalize(rd.x1, rd.y1);
			draw_circle(xrnor, yrnor, rd.r, rd.c_type, 1.0);
			break;
			
		case 5:
			fscanf(fp, "%d %d %d",&rd.h,&rd.w,&rd.ch);
			break;
			
		case 10:
			fscanf(fp, "%f %f %d %d %d %f ",&rd.x1,&rd.y1,&rd.rx,&rd.ry,&rd.c_type,&rd.size);
			fscanf(fp, "%f %f %f",&rd.red,&rd.g,&rd.b);
			glColor3f(rd.red, rd.g, rd.b);
			rev_normalize(rd.x1, rd.y1);
			draw_ellipse(xrnor, yrnor, rd.rx, rd.ry, rd.c_type);
			break;
			
		default:
			break;
	}
	
}	


/**** grid ****/
void grid()
{
	float x1,y1,x2,y2,size,r,g,b;
	int type;
	fp=fopen("grid.gd", "r");
	while (!feof(fp)!=0)
	{
		fscanf(fp, "%f %f %f %f",&x1,&y1,&x2,&y2);
		fscanf(fp, "%d %f",&type,&size);
		fscanf(fp, "%f %f %f",&r,&g,&b);
		glColor3f(r, g, b);
		rev_normalize(x1, y1);
		x1=xrnor;
		y1=yrnor;
		rev_normalize(x2, y2);
		draw_line(x1, y1, xrnor, yrnor, type, size);
	}
	fclose(fp);	
}



/**** Read from the display file ****/
void rePaint()
{
	glutSetWindow(draw_window);
	glClear(GL_COLOR_BUFFER_BIT);
	
	if (grid_flag==0)
	{
		grid();
	}
	
	fp=fopen(file_name, "r");
	temp.x=0;
	temp.y=0;
	
	while (!feof(fp)!=0)
	{
		fscanf(fp, "%d",&rd.op);
		draw(rd.op);
	}
	
	fclose(fp);
	//glFlush();
}	


/**** Undo ****/
void undo()
{	
	store_temp=store_redo;
	switch (end[selected]->op)
	{
		case 1:
			store_redo=end[selected];
			break;
			
		case 2:
			shift=start[selected];
			while (shift!=end[selected])
			{
				if (shift->op!=2 && shift->next->op==2)
				{
					store_redo=shift->next;
				}
				shift=shift->next;
			}
			break;
			
		case 3:
			shift=start[selected];
			while (shift!=end[selected])
			{
				if (shift->op==3)
				{
					store_redo=shift;
				}
				shift=shift->next;
			}
			break;

		case 4:
			store_redo=end[selected];
			break;

		case 5:
			shift=start[selected];
			while (shift!=end[selected])
			{
				if (shift->op==5)
				{
					store_redo=shift;
				}
				shift=shift->next;
			}

		default:
			break;
	}
	
	
	if (start[selected]==store_redo)
	{
		/*if (end[selected]->next!=NULL)
		{
			end[selected-1]->next=start[selected+1];
		}
		else
		{
			if (selected==0)
			{
				ard=NULL;
				head=NULL;
				start[selected]=NULL;
			}
			else
			{
				if (selected!=1)
				{
					if (end[selected-2]->next=start[selected+1])
					{
						end[selected-2]->next=start[selected+1];
					}
					else
					{
						end[selected-1]->next=NULL;
					}
				}
				else
				{
					end[selected-1]->next=NULL;
				}
			}
		}*/
	}
	else
	{
		shift=start[selected];
		while (shift->next!=store_redo)
		{
			shift=shift->next;
		}
		end[selected]=shift;
		
		if (start[selected+1]!=NULL)
		{
			end[selected]->next=start[selected+1];
		}
		else
		{
			end[selected]->next=NULL;
		}
	}
	
	if (store_temp!=NULL)
	{
		switch (store_redo->op)
		{
			case 1:
				store_redo->next=store_temp;
				break;
			case 2:
				prevp1=store_redo;
				do
				{
					store_redo=store_redo->next;
				}while (store_redo->next!=NULL); 
				store_redo->next=store_temp;
				prevp2=store_redo;
				store_redo=prevp1;
				break;
			case 3:
				prevp1=store_redo;
				do
				{
					store_redo=store_redo->next;
				}while (store_redo->op!=3);
				store_redo->next=store_temp;
				store_redo=prevp1;
				break;
			case 4:
				store_redo->next=store_temp;
				break;
			case 5:
				store_redo->next=store_temp;
				break;
	
			
			default:
				break;
		}
	}
	
	
	ard=end[selected];
	df_wr();
	rePaint();
}


/**** Redo ****/
void redo()
{
	if (store_redo!=NULL)
	{
		switch (store_redo->op) 
		{
			case 1:
				end[selected]->next=store_redo;
				break;
				
			case 2:
				end[selected]->next=store_redo;
				while (store_redo!=prevp2)
				{
					store_redo=store_redo->next;
				}
				//store_redo=store_redo->next;
				break;

			case 3:
				end[selected]->next=store_redo;
				store_redo=store_redo->next;
				while (store_redo->op!=3)
				{
					store_redo=store_redo->next;
				}
				
				break;

			case 4:
				end[selected]->next=store_redo;
				break;

			default:
				break;
		}
		
		
		end[selected]=store_redo;
		if (store_redo->next!=NULL)
		{
			store_redo=store_redo->next;
		}
		else
		{
			store_redo=NULL;
		}
		
		end[selected]->next=NULL;
		ard=end[selected];

		df_wr();
		rePaint();
	}
}



/**** Deselecting ****/
void deselect()
{
	int x1,y1;
	glutSetWindow(draw_window);

	shift=store;
	while (store_index>0)
	{
		switch (shift->op)
		{
			case 1:
				rev_normalize(shift->x1, shift->y1);
				x1=xrnor;
				y1=yrnor;
				rev_normalize(shift->x2, shift->y2);
				glColor3f(shift->red, shift->g, shift->b);
				draw_line(x1, y1, xrnor, yrnor, shift->l_type, shift->size);
				break;
			case 3:
				store_index++;
				break;
			case 4:
				rev_normalize(shift->x1, shift->y1);
				glColor3f(shift->red, shift->g, shift->b);
				draw_circle(xrnor, yrnor, shift->r, shift->c_type, shift->size);
				break;
			case 5:
				store_index++;
				break;

			case 10:
				rev_normalize(shift->x1, shift->y1);
				glColor3f(shift->red, shift->g, shift->b);
				draw_ellipse(xrnor, yrnor, shift->rx, shift->ry, shift->c_type);
				break;

			default:
				break;
		}
		store_index--;
		shift=shift->next;
	}
	store=NULL;
}	


/**** Selection ****/
void select(float x, float y)
{
	float x1,y1,x2,y2,tem,xtt,ytt;
	int xt,yt,found_line,found_poly,found_circle,found_char,t;
	
	found_line=found_poly=found_circle=0;

	deselect();
	
	shift=head;
	store_index=0;

	
	while (shift!=NULL)
	{
		x1=shift->x1;
		y1=shift->y1;
		x2=shift->x2;
		y2=shift->y2;
		
		switch (shift->op)
		{
			case 1:
				if (shift->x1>shift->x2)
				{
					tem=x1;
					x1=x2;
					x2=tem;
				}
				if (shift->y1>shift->y2)
				{
					tem=y1;
					y1=y2;
					y2=tem;
				}
				xtt=(y-y1)*(x2-x1)/(y2-y1)+x1;
				ytt=(x-x1)*(y2-y1)/(x2-x1)+y1;
				
				if (y>=ytt-0.01 && y<=ytt+0.01)
				{
					rev_normalize(shift->x1, shift->y1);
					xt=xrnor;
					yt=yrnor;
					rev_normalize(shift->x2, shift->y2);
					glColor3f(0.0, 0.0, 1.0);
					draw_line(xt, yt, xrnor, yrnor, shift->l_type, shift->size);
					store_index++;
					found_line=1;
				}
				else
				{
					if (x>=xtt-0.01 && x<=xtt+0.01)
					{
						rev_normalize(shift->x1, shift->y1);
						xt=xrnor;
						yt=yrnor;
						rev_normalize(shift->x2, shift->y2);
						glColor3f(0.0, 0.0, 1.0);
						draw_line(xt, yt, xrnor, yrnor, shift->l_type, shift->size);
						store_index++;
						found_line=1;
					}
				}
				break;
			case 3:
				prevp1=shift;
				shift=shift->next;
				while (shift->op!=3)
				{
					x1=shift->x1;
					y1=shift->y1;
					x2=shift->x2;
					y2=shift->y2;
					
					if (shift->x1>shift->x2)
					{
						tem=x1;
						x1=x2;
						x2=tem;
					}
					if (shift->y1>shift->y2)
					{
						tem=y1;
						y1=y2;
						y2=tem;
					}
					xtt=(y-y1)*(x2-x1)/(y2-y1)+x1;
					ytt=(x-x1)*(y2-y1)/(x2-x1)+y1;
					
					if (y>=ytt-0.01 && y<=ytt+0.01)
					{	
						found_poly=1;
						store=prevp1->next;

						while (store->op!=3)
						{
							rev_normalize(store->x1, store->y1);
							xt=xrnor;
							yt=yrnor;
							rev_normalize(store->x2, store->y2);
							glColor3f(0.0, 0.0, 1.0);
							draw_line(xt, yt, xrnor, yrnor, store->l_type, store->size);
							store_index++;
							store=store->next;
						}
						break;
					}
					else
					{
						if (x>=xtt-0.01 && x<=xtt+0.01)
						{
							found_poly=1;
							store=prevp1->next;

							while (store->op!=3)
							{
								rev_normalize(store->x1, store->y1);
								xt=xrnor;
								yt=yrnor;
								rev_normalize(store->x2, store->y2);
								glColor3f(0.0, 0.0, 1.0);
								draw_line(xt, yt, xrnor, yrnor, store->l_type, store->size);
								store_index++;
								store=store->next;
							}
							break;
						}
					}
					shift=shift->next;
				}
				break;
			case 4:
				rev_normalize(x, y);
				xt=xrnor;
				yt=yrnor;
				rev_normalize(shift->x1, shift->y1);
				
				if (xrnor>xt)
				{
					tem=xt;
					xt=xrnor;
					xrnor=tem;
					if (yrnor>yt)
					{
						tem=yt;
						yt=yrnor;
						yrnor=tem;
					}
				}
				t=sqrt(pow(xt-xrnor, 2)+pow(yt-yrnor, 2));
				
				if (shift->r-t>=0 && shift->r-t<=4)
				{
					glColor3f(0.0, 0.0, 1.0);
					rev_normalize(shift->x1, shift->y1);
					draw_circle(xrnor, yrnor, shift->r, shift->c_type, shift->size);
					store_index++;
					found_circle=1;
				}
				break;
			case 5:
				prevp1=shift;
				shift=shift->next;
				while (shift->op!=5)
				{
					if (shift->op==1)
					{
						x1=shift->x1;
						y1=shift->y1;
						x2=shift->x2;
						y2=shift->y2;
						
						if (shift->x1>shift->x2)
						{
							tem=x1;
							x1=x2;
							x2=tem;
						}
						if (shift->y1>shift->y2)
						{
							tem=y1;
							y1=y2;
							y2=tem;
						}
						xtt=(y-y1)*(x2-x1)/(y2-y1)+x1;
						ytt=(x-x1)*(y2-y1)/(x2-x1)+y1;
						
						if (y>=ytt-0.01 && y<=ytt+0.01)
						{	
							found_char=1;
							store=prevp1->next;
							
							while (store->op!=5)
							{
								if (store->op==1)
								{
									rev_normalize(store->x1, store->y1);
									xt=xrnor;
									yt=yrnor;
									rev_normalize(store->x2, store->y2);
									glColor3f(0.0, 0.0, 1.0);
									draw_line(xt, yt, xrnor, yrnor, store->l_type, store->size);
								}
								if (store->op==10)
								{
									rev_normalize(store->x1, store->y1);
									glColor3f(0.0, 0.0, 1.0);
									draw_ellipse(xrnor, yrnor, store->rx, store->ry, store->c_type);
								}
								store_index++;
								store=store->next;								
							}
							break;
						}
						else
						{
							if (x>=xtt-0.01 && x<=xtt+0.01)
							{
								found_char=1;
								store=prevp1->next;
								
								while (store->op!=5)
								{
									if (store->op==1)
									{
										rev_normalize(store->x1, store->y1);
										xt=xrnor;
										yt=yrnor;
										rev_normalize(store->x2, store->y2);
										glColor3f(0.0, 0.0, 1.0);
										draw_line(xt, yt, xrnor, yrnor, store->l_type, store->size);
									}
									if (store->op==10)
									{
										rev_normalize(store->x1, store->y1);
										glColor3f(0.0, 0.0, 1.0);
										draw_ellipse(xrnor, yrnor, store->rx, store->ry, store->c_type);
									}
									store_index++;
									store=store->next;

								}
								break;
							}
						}
					}
					shift=shift->next;
				}
				
				break;

				
			default:
				break;
		}
		
		if (found_line==1)
		{
			store=shift;
			break;
		}
		if (found_poly==1 || found_char==1)
		{
			store=prevp1;
			break;
		}
		if (found_circle==1)
		{
			store=shift;
			break;
		}
		
		shift=shift->next;
		store=NULL;
	}
	
	if (store!=NULL)
	{
		found_img=1;
	}
	else
	{
		found_img=0;
	}

	
}




/**** Character set generation ****/
void char_gen(char ch, int h, int w)
{
	int t,ret;
	ret=0;
		
	glPointSize(2.0);
	if (cho==1 && ch!=13 && ch!=8) 
	{
		active_write(check, chCP.x, chCP.y, h, w, -1, -1, -1, ch, -1, 1.0);
		ret=1;
	}
	t=draw_char(ch,h,w,chCP.x, chCP.y);
	if (ret==1) 
	{
		active_write(check, chCP.x, chCP.y, h, w, -1, -1, -1, ch, -1, 1.0);
	}

	switch (ch)
	{
		case 13:
			mous.y-=h+h/2;
			count=0;
			break;
		default:
			break;
	}
	
	if (t==1) 
	{
		count++;
	}
	if (t==2)
	{
		count--;
	}
	
	if (h >13) 
	{
		chCP.x=mous.x+count*4*w/3;
	}
	else
	{
		chCP.x=mous.x+count*3*w/2;
	}
	chCP.y=mous.y;
}



void lineto(GLint x,GLint y, int type, float size)
{
	if (temp.x!=0)
	{
		draw_line(temp.x, temp.y, x, y, type, size);

	}
	
	CP.x=x;
	CP.y=y;
	temp.x=x;
	temp.y=y;	
}


/**** Line Absolute ****/
void lineabs (int x1, int y1, int x2, int y2, float size, int type)
{
	draw_line(x1, y1, x2, y2, type, size);
	
}


/**** init size of icons for tool_window ****/
void init_size()
{
	adder=35; 
	i_startx=5; 
	i_starty=heightm-35;
}


/**** init size of icons for line sub_window ****/
void init_size_line_sub()
{
	adder_line_sub_x=70;
	adder_line_sub_y=20;
	i_startx_line_sub=10;
	i_starty_line_sub=heightm-100;
	i_maxy=i_starty_line_sub-(adder_line_sub_y*4);
	
}


/**** init size of icons for polygon sub_window ****/
void init_size_poly_sub()
{
	adder_poly_sub_x=45;
	adder_poly_sub_y=40;
	i_startx_poly_sub=20;
	i_starty_poly_sub=heightm-250;
}


/**** init size of icons for char size sub_window ****/
void init_size_char_sub()
{
	adder_char_sub_x=20;
	adder_char_sub_y=20;
	i_startx_char_sub=30;
	i_starty_char_sub=heightm-100;
}


/**** init size of icons for circle sub_window ****/
void init_size_circle_sub()
{
	adder_circle_sub_x=30;
	adder_circle_sub_y=30;
	i_startx_circle_sub=10;
	i_starty_circle_sub=heightm-100;
	
}

void init_size_ell_sub()
{
	adder_circle_sub_x=30;
	adder_circle_sub_y=30;
	i_startx_circle_sub=10;
	i_starty_ell_sub=heightm-340;
}


void init_size_trans_sub()
{
	i_startx_trans_sub=20;
	i_starty_trans_sub=heightm-100;
	adder_trans_sub_x=50;
	adder_trans_sub_y=80;
}

/**** Icon box for tools ***/
void icon_box_tool()
{
	glColor3f(1.0, 1.0, 1.0);
	draw_line(i_startx+16, i_starty+adder/2, i_startx+adder-17, i_starty+adder/2, 1, 30.0);
	glColor3f(0.7, 0.7, 0.7);
	draw_rect(i_startx+2, i_starty+3, i_startx+adder-3, i_starty+adder-4, 1, 3.0);
}


/**** Icon box for line sub window ****/
void icon_box_line_sub()
{
	glColor3f(1.0, 1.0, 1.0);	
	draw_line(i_startx_line_sub+8, i_starty_line_sub+adder_line_sub_y/2, i_startx_line_sub+adder_line_sub_x-5, i_starty_line_sub+adder_line_sub_y/2, 1, 19.0);
}

/**** Icon box for polygon sub window ****/
void icon_box_poly_sub()
{
	glColor3f(1.0, 1.0, 1.0);
	draw_line(i_startx_poly_sub+22, i_starty_poly_sub+adder_poly_sub_y-19, i_startx_poly_sub+adder_poly_sub_x-20, i_starty_poly_sub+adder_poly_sub_y-19, 1, 42.0);
	glColor3f(0.0, 0.0, 0.0);
	glFlush();

}


/**** Icon for circle sub window ****/
void icon_box_circle_sub()
{
	glColor3f(1.0, 1.0, 1.0);
	draw_line(i_startx_circle_sub+15, i_starty_circle_sub+adder_circle_sub_y/2, i_startx_circle_sub+adder_circle_sub_x-15, i_starty_circle_sub+adder_circle_sub_y/2, 1, 30.0);
	glFlush();	
}	


void icon_box_trans_sub()
{
	glColor3f(1.0, 1.0, 1.0);
	lineabs(i_startx_trans_sub, i_starty_trans_sub, i_startx_trans_sub+adder_trans_sub_x, i_starty_trans_sub, 30.0, 1);
}


/**** Icon box for color pallet ****/
void icon_color()
{
	int k=widthm;
	k+=250;
	draw_line(k-t1-10, i_starty+5, k-t1-8, i_starty+5, 1, 15.0);
	glColor3f(0.5, 0.5, 0.5);
	draw_rect(k-t1, i_starty+14, k-t1-16, i_starty-3, 1, 2.0);
}


/**** Icons for the tools ****/
void icon()
{
	int t,j,gx,gy,ty,tempx,tempy;

	/*** Line ****/
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	lineabs(i_startx+5, i_starty+5, i_startx+adder-5, i_starty+adder-5, 2.0, 1);
	
	/**** Free hand ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_line(i_startx+15, i_starty+17, i_startx+adder-12, i_starty+adder-10, 1, 5.0);
	draw_circle(i_startx+12, i_starty+13, 2, 0, 1.0);
	draw_circle(i_startx+14, i_starty+15, 1, 0, 3.0);

	draw_circle(i_startx+12, i_starty+13, 6, 0, 2.0);
	
	
	/**** Polygon ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	lineabs(i_startx+10, i_starty+5, i_startx+adder-10, i_starty+5, 2.0, 1);
	lineabs(i_startx+adder-10, i_starty+5, i_startx+adder-5, (i_starty+adder)-adder/2, 2.0, 1);
	lineabs(i_startx+adder-5, (i_starty+adder)-adder/2, i_startx+adder/2, i_starty+adder-5, 2.0, 1);
	lineabs(i_startx+adder/2, i_starty+adder-5, i_startx+5, (i_starty+adder)-adder/2, 2.0, 1);
	lineabs(i_startx+5, (i_starty+adder)-adder/2, i_startx+10, i_starty+5, 2.0, 1);
	
	
	/**** Circle ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_circle(i_startx+adder/2, i_starty+adder/2, adder/3, 0, 2.0);
	
	
	/**** Text ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	char_set(i_startx+12,i_starty+10);
	char_gen('t', 17, 10);
	
	
	/**** Create segment ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_rect(i_startx+7, i_starty+10, i_startx+23, i_starty+25, 1, 2.0);
	glColor3f(0.3, 0.8, 0.3);
	lineabs(i_startx+15, i_starty+20, i_startx+20, i_starty+15, 2.0, 1);
	lineabs(i_startx+20, i_starty+15, i_startx+28, i_starty+26, 2.0, 1);
	
	
	/**** Edit segment ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_rect(i_startx+7, i_starty+10, i_startx+23, i_starty+25, 1, 2.0);
	glColor3f(0.3, 0.3, 1.0);
	char_set(i_startx+13,i_starty+13);
	char_gen('t', 9, 12);
	
	
	/**** Delete segment ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_rect(i_startx+7, i_starty+10, i_startx+23, i_starty+25, 1, 2.0);
	glColor3f(0.9, 0.3, 0.3);
	lineabs(i_startx+15, i_starty+22, i_startx+27, i_starty+14, 2.0, 1);
	lineabs(i_startx+15, i_starty+14, i_startx+27, i_starty+22, 2.0, 1);
	t=i_startx;
	ty=i_starty;
	t1=t;
	col_startx=i_startx;
	col_starty=i_starty;
	
	
	/**** Zoom in ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_circle(i_startx+adder/2, i_starty+adder/2, adder/3, 0, 2.0);
	glColor3f(0.7, 0.7, 0.0);
	lineabs(i_startx+10, i_starty+adder/2, i_startx+adder-10, i_starty+adder/2, 2.0, 1);
	lineabs(i_startx+adder/2, i_starty+10, i_startx+adder/2, i_starty+23, 2.0, 1);
	
	/**** Zoom out ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_circle(i_startx+adder/2, i_starty+adder/2, adder/3, 0, 2.0);
	glColor3f(0.7, 0.0, 0.7);
	lineabs(i_startx+10, i_starty+adder/2, i_startx+adder-10, i_starty+adder/2, 2.0, 1);
	
	
	/**** Undo ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.3, 0.7, 0.7);
	draw_line(i_startx+10, i_starty+adder/2, i_startx+adder-8, i_starty+adder/2, 1, 2.0);
	draw_line(i_startx+10, i_starty+adder/2, i_startx+18, i_starty+adder/2+4, 1, 2.0);
	draw_line(i_startx+10, i_starty+adder/2, i_startx+18, i_starty+adder/2-4, 1, 2.0);

	
	/**** Redo ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.3, 0.7, 0.7);
	draw_line(i_startx+10, i_starty+adder/2, i_startx+adder-8, i_starty+adder/2, 1, 2.0);
	draw_line(i_startx+adder-8, i_starty+adder/2, i_startx+adder-18, i_starty+adder/2+4, 1, 2.0);
	draw_line(i_startx+adder-8, i_starty+adder/2, i_startx+adder-18, i_starty+adder/2-4, 1, 2.0);
	
	
	/**** Eraser ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.4, 0.4, 0.3);
	draw_rect(i_startx+20, i_starty+20, i_startx+adder-20, i_starty+adder-20, 1, 10.0);

	
	/**** Grid ****/
	i_startx+=adder+5;
	tempx=i_startx;
	tempy=i_starty;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	gx=i_startx+2;
	gy=i_starty;
	i_startx+=5;
	i_starty+=5;
	glColor3f(0.5, 0.0, 0.5);
	for (i=0; i<4; i++)
	{
		draw_line(i_startx+5, gy+10, i_startx+5, gy+adder-10, 1, 2.0);
		draw_line(gx+8, i_starty+5, gx+adder-12, i_starty+5, 1, 2.0);
		i_startx+=5;
		i_starty+=5;
	}
	
	
	/**** Menu ****/
	i_startx=tempx+adder+5;
	i_starty=tempy;
	icon_box_tool();
	glColor3f(0.5, 0.5, 0.6);
	draw_line(i_startx+10, i_starty+10, i_startx+adder-10, i_starty+10, 1, 2.0);
	draw_line(i_startx+adder-10, i_starty+10, i_startx+adder-10, i_starty+adder-13, 1, 2.0);
	draw_line( i_startx+adder-10, i_starty+adder-13, i_startx+adder-15, i_starty+adder-13, 1, 2.0);
	draw_line(i_startx+adder-15, i_starty+adder-13, i_startx+adder-15, i_starty+adder-8, 1, 2.0);
	draw_line(i_startx+adder-15, i_starty+adder-8, i_startx+10, i_starty+adder-8, 1, 2.0);
	draw_line( i_startx+10, i_starty+adder-8, i_startx+10, i_starty+10, 1, 2.0);
	
	/**** Selection ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_line(i_startx+adder/2-5, i_starty+10, i_startx+adder/2-5, i_starty+adder-10, 1, 2.0);
	draw_line(i_startx+adder/2-5, i_starty+adder-10, i_startx+adder/2+6, i_starty+14, 1, 2.0);
	draw_line(i_startx+adder/2+6, i_starty+14, i_startx+adder/2-1, i_starty+15, 1, 2.0);
	draw_line(i_startx+adder/2-1, i_starty+15, i_startx+adder/2-5, i_starty+10, 1, 2.0);
	draw_line(i_startx+adder/2-1, i_starty+15, i_startx+adder/2+2, i_starty+10, 1, 2.0);
	draw_line(i_startx+adder/2, i_starty+15, i_startx+adder/2+3, i_starty+10, 1, 2.0);

	
	/**** Clipping ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_rect(i_startx+7, i_starty+10, i_startx+23, i_starty+25, 1, 2.0);
	glColor3f(0.0, 0.5, 0.5);
	draw_line(i_startx+adder/2+6, i_starty+14, i_startx+adder/2-1, i_starty+15, 1, 2.0);
	draw_line(i_startx+adder/2-1, i_starty+15, i_startx+adder/2-5, i_starty+10, 1, 2.0);

	
	/**** Viewing ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_rect(i_startx+5, i_starty+8, i_startx+21, i_starty+23, 1, 2.0);
	draw_rect(i_startx+10, i_starty+12, i_startx+26, i_starty+28, 1, 2.0);
	
	/**** Time Animation ****/
	i_startx+=adder+5;
	icon_box_tool();
	glColor3f(0.0, 0.0, 0.0);
	draw_rect(i_startx+7, i_starty+10, i_startx+23, i_starty+25, 1, 2.0);
	glColor3f(0.8, 0.7, 0.8);
	char_set(i_startx+14,i_starty+13);
	char_gen('t', 9, 12);
	
	glColor3f(0.3, 0.3, 1.0);
	char_set(i_startx+9,i_starty+13);
	char_gen('t', 9, 12);
	glColor3f(0.3, 0.3, 0.3);
	char_set(i_startx+5,i_starty+13);
	char_gen('t', 9, 12);

	/**** Time Animation ****/
	i_startx+=adder+5;
	icon_box_tool();
	
	/**** Color pallet ****/
	i_starty=ty;

	for (j=13; j>=0; j--)
	{
		glColor3f(obj[j].r,obj[j].g,obj[j].b);
		icon_color();
		t1+=20;
		if (j==7)
		{
			t1=t;
			i_starty+=20;
		}
		
	}
	init_size();
	glFlush();

}




/**** Print no ****/
void print_no(int x, int y)
{
	int t1,t2,t3,t4;
	normalize(x,y);
	
	t1=(xnor*10);
	t1=t1%10;
	t2=(xnor*100);
	t2=t2%10;
	
	t3=(ynor*10);
	t3=t3%10;
	t4=(ynor*100);
	t4=t4%10;
	
	glutSetWindow(status_window);
	
	glColor3f(0.0, 0.0, 0.0);
	draw_line(110, heightm-50, 240, heightm-50, 1, 20.0);
	
	glColor3f(0.7, 0.7, 0.7);
	draw_char('x', 14, 9, 110, heightm-57);
	draw_char(':', 14, 9, 120, heightm-57);
	glColor3f(1.0, 0.0, 0.0);

	if (xnor>=0.995)
	{
		draw_char(49, 14, 9, 130, heightm-57);
		draw_char(48, 14, 9, 150, heightm-57);
		draw_char(48, 14, 9, 160, heightm-57);
	}
	else 
	{
		draw_char(48, 14, 9, 130, heightm-57);
		draw_char(48+t1, 14, 9, 150, heightm-57);
		draw_char(48+t2, 14, 9, 160, heightm-57);
	}
	draw_char(46, 14 ,8, 140, heightm-57);
	glColor3f(0.7, 0.7, 0.7);

	draw_char('y', 14, 9, 180, heightm-57);
	draw_char(':', 14, 9, 190, heightm-57);
	glColor3f(1.0, 0.0, 0.0);
	if (ynor>=0.994) 
	{
		draw_char(49, 14, 9, 200, heightm-57);
		draw_char(48, 14, 9, 220, heightm-57);
		draw_char(48, 14, 9, 230, heightm-57);
		
	}
	else 
	{
		draw_char(48, 14, 9, 200, heightm-57);
		draw_char(48+t3, 14, 9, 220, heightm-57);
		draw_char(48+t4, 14, 9, 230, heightm-57);
	}
	
	draw_char(46, 14 ,8, 210, heightm-57);
	glFlush();

}	



void init_seg()
{
	lay[selected].sx=1;
	lay[selected].sy=1;
	lay[selected].angleo=0;
	lay[selected].anglea=0;
	lay[selected].tx=0;
	lay[selected].ty=0;
	lay[selected].rot_arbit=0;
	lay[selected].clockwise=0;
	lay[selected].x=0;
	lay[selected].y=0;
}


void doTransform()
{
	if (shift!=NULL)
	{
		switch (shift->op)
		{
			case 1:
				if (lay[selected].rot_arbit!=1)
				{
					load_identity();
					scaling(lay[selected].sx,lay[selected].sy);
					rotation(lay[selected].angleo);
					translate(lay[selected].tx,lay[selected].ty);
					transform_matrix(shift->x1,shift->y1);
					
					load_identity();
					scaling(lay[selected].sx,lay[selected].sy);
					rotation(lay[selected].angleo);
					translate(lay[selected].tx,lay[selected].ty);
					transform_matrix(shift->x2,shift->y2);
					
				}
				else
				{
					normalize(lay[selected].x, lay[selected].y);
					load_identity();
					scaling(lay[selected].sx, lay[selected].sy);
					translate(-xnor, -ynor);
					rev_normalize(xnor, ynor);
					rotation(lay[selected].anglea);
					translate(lay[selected].tx, lay[selected].ty);
					translate(xnor, ynor);
					
					
					transform_matrix(shift->x1, shift->y1);
					transform_matrix(shift->x2, shift->y2);
					
					
					rev_normalize(xnor, ynor);
					lay[selected].x=xrnor;
					lay[selected].y=yrnor;
					
				}
				
				break;
				
			case 2:
				if (lay[selected].rot_arbit!=1)
				{
					load_identity();
					scaling(lay[selected].sx,lay[selected].sy);
					rotation(lay[selected].angleo);
					translate(lay[selected].tx,lay[selected].ty);
					transform_matrix(shift->x1,shift->y1);
				}
				else
				{
					normalize(lay[selected].x, lay[selected].y);
					
					load_identity();
					scaling(lay[selected].sx, lay[selected].sy);
					translate(-xnor, -ynor);
					rotation(lay[selected].anglea);
					translate(xnor, ynor);
					translate(lay[selected].tx, lay[selected].ty);
					transform_matrix(shift->x1, shift->y1);
					
					//xnor+=lay[selected].tx;
					//ynor+=lay[selected].ty;
					
					rev_normalize(xnor, ynor);
					lay[selected].x=xrnor;
					lay[selected].y=yrnor;				
				}
				
				break;
				
			case 4:
				if (lay[selected].rot_arbit!=1)
				{
					load_identity();
					shift->r=shift->r*lay[selected].sx;
					scaling(lay[selected].sx, lay[selected].sy);
					rotation(lay[selected].angleo);
					translate(lay[selected].tx,lay[selected].ty);
					transform_matrix(shift->x1,shift->y1);
					
				}
				
				else
				{				
					normalize(lay[selected].x, lay[selected].y);
					
					load_identity();
					shift->r=shift->r*lay[selected].sx;
					scaling(lay[selected].sx, lay[selected].sy);				
					translate(-xnor, -ynor);
					rotation(lay[selected].anglea);
					translate(xnor, ynor);
					translate(lay[selected].tx, lay[selected].ty);
					transform_matrix(shift->x1, shift->y1);
					
					
					//xnor+=lay[selected].tx;
					//ynor+=lay[selected].ty;
					
					
					rev_normalize(xnor, ynor);
					lay[selected].x=xrnor;
					lay[selected].y=yrnor;
				}			
				break;
				
			case 10:
				if (lay[selected].rot_arbit!=1) 
				{
					load_identity();
					shift->rx=shift->rx*lay[selected].sx;
					shift->ry=shift->ry*lay[selected].sy;
					scaling(lay[selected].sx, lay[selected].sy);		
					rotation(lay[selected].angleo);
					translate(lay[selected].tx, lay[selected].ty);
					transform_matrix(shift->x1, shift->y1);
				}
				else
				{
					normalize(lay[selected].x, lay[selected].y);
					
					
					load_identity();
					shift->rx=shift->rx*lay[selected].sx;
					shift->ry=shift->ry*lay[selected].sy;
					scaling(lay[selected].sx, lay[selected].sy);		
					translate(-xnor, -ynor);
					rotation(lay[selected].anglea);
					translate(xnor, ynor);
					translate(lay[selected].tx, lay[selected].ty);
					transform_matrix(shift->x1, shift->y1);
					
					
					//xnor+=lay[selected].tx;
					//ynor+=lay[selected].ty;
					
					rev_normalize(xnor, ynor);
					lay[selected].x=xrnor;
					lay[selected].y=yrnor;
					
				}
				
				break;
				
			default:
				break;
		}
		
	}
		
	glFlush();

}


/**** animate the scale of the figure ****/
void anim_scale (int pt,int x,int y)
{
	switch (store->op)
	{
			case 1:
				if (pt==1)
				{
					rev_normalize(store->x1, store->y1);
					draw_line(x, y, xrnor, yrnor, store->l_type, store->size);
					normalize(x, y);
					store_anim[store_anim_index][img_anim_index].x1=xrnor;
					store_anim[store_anim_index][img_anim_index].y1=yrnor;
				}
				else
				{
					rev_normalize(store->x2, store->y2);
					draw_line(xrnor, yrnor, x, y, store->l_type, store->size);
					normalize(x, y);
					store_anim[store_anim_index][img_anim_index].x2=xrnor;
					store_anim[store_anim_index][img_anim_index].y2=yrnor;					
				}
				
			
				break;
			default:
				break;
	}
	
}



/**** rePaint layerwise ****/
void lay_draw()
{
	int x1,y1;
	
	glutSetWindow(draw_window);
	if (shift1!=NULL)
	{
		switch (shift1->op)
		{
			case 1:
				rev_normalize(shift1->x1, shift1->y1);
				x1=xrnor;
				y1=yrnor;
				rev_normalize(shift1->x2, shift1->y2);
				if (animate_col_flag==1)
				{
					glColor3f(1.0, 1.0, 1.0);
				}
				else
				{
					glColor3f(shift1->red, shift1->g, shift1->b);
				}
				draw_line(x1, y1, xrnor, yrnor, shift1->l_type, shift1->size);
				break;
				
			case 2:
				rev_normalize(shift1->x1, shift1->y1);
				if (temp.x==0)
				{
					temp.x=xrnor;
					temp.y=yrnor;
					break;
				}
				
				if (animate_col_flag==1)
				{
					glColor3f(1.0, 1.0, 1.0);
				}
				else
				{
					glColor3f(shift1->red, shift1->g, shift1->b);
				}
				
				draw_line(temp.x, temp.y, xrnor, yrnor, 1, shift1->size);
				temp.x=xrnor;
				temp.y=yrnor;
				break;
				
			case 4:
				rev_normalize(shift1->x1, shift1->y1);
				if (animate_col_flag==1)
				{
					glColor3f(1.0, 1.0, 1.0);
				}
				else
				{
					glColor3f(shift1->red, shift1->g, shift1->b);
				}
				draw_circle(xrnor, yrnor, shift1->r, shift1->c_type, shift1->size);
				break;
				
			case 10:
				rev_normalize(shift1->x1, shift1->y1);
				if (animate_col_flag==1)
				{
					glColor3f(1.0, 1.0, 1.0);
				}
				else
				{
					glColor3f(shift1->red, shift1->g, shift1->b);
				}
				draw_ellipse(xrnor, yrnor, shift1->rx, shift1->ry, shift1->c_type);
				break;
				
				
			default:
				break;
		}
		
	}
	
		glFlush();

}


/**** layer wise drawing ****/
void lay_rePaint()
{
	shift1=start[selected];
	while (shift1!=end[selected] && shift1!=NULL)
	{
		lay_draw();
		shift1=shift1->next;
	}
	lay_draw();
	glFlush();

}


/**** Save for combine transformation ****/
void save()
{

	save_lay_index[store_index]=selected;
	if (negtx==1)
	{
		lay[selected].tx=-lay[selected].tx;
		
		negtx=0;
	}
	if (negty==1)
	{
		lay[selected].ty=-lay[selected].ty;
		negty=0;
	}
	store_index++;
	
}


/**** conti. transformation ****/
void cont_transform()
{
	float i,tx1,ty1,sx1,sy1,angleo1,anglea1;
	float n;
	int j,k;
	
	float tx[5],ty[5],sx[5],sy[5],angleo[5],anglea[5];
	
	
	if (negtx==1)
	{
		lay[selected].tx=-lay[selected].tx;
		negtx=0;
	}
	if (negty==1)
	{
		lay[selected].ty=-lay[selected].ty;
		negty=0;
	}
	
	seg_wr(0);
	j=selected;
	tx1=lay[selected].tx;
	ty1=lay[selected].ty;
	sx1=lay[selected].sx;
	sy1=lay[selected].sy;
	angleo1=lay[selected].angleo;
	anglea1=lay[selected].anglea;

	k=0;
	while (k<store_index)
	{
		selected=save_lay_index[k];
		seg_wr(0);
		tx[k]=lay[save_lay_index[k]].tx;
		ty[k]=lay[save_lay_index[k]].ty;
		sx[k]=lay[save_lay_index[k]].sx;
		sy[k]=lay[save_lay_index[k]].sy;
		angleo[k]=lay[save_lay_index[k]].angleo;
		anglea[k]=lay[save_lay_index[k]].anglea;
		k++;
	}
	
	selected=j;
	n=0.0;
	if (ty1==0.0)
	{
		n=tx1/0.01;
	}
	else
	{
		if (tx1==0.0)
		{
			n=ty1/0.01;
		}
		else
		{
			if (tx1>ty1 )
			{
				n=tx1/0.01;
			}
			if (ty1<tx1)
			{
				n=ty1/0.01;
			}
			
		}
		
	}
	
	if (n==0)
	{
		if (sy1==1.0 && sx1!=1.0)
		{
			if (sx1>1)
			{
				n=log(sx1)/log(1.1);
			}
			if (sx1<1)
			{
				n=log(sx1)/log(0.9);
			}
		}
		else
		{
			if (sx1==1.0 && sy1!=1.0)
			{
				if (sy1>1)
				{
					n=log(sy1)/log(1.1);
				}
				if (sx1<1)
				{
					n=log(sy1)/log(0.9);
					
				}
			}
			else
			{
				if (sx1>sy1)
				{
					if (sx1>1)
					{
						n=log(sx1)/log(1.1);
					}
					if (sx1<1)
					{
						n=log(sx1)/log(0.9);
					}
				}
				else
				{
					if (sy1>1)
					{
						n=log(sy1)/log(1.1);
					}
					if (sx1<1)
					{
						n=log(sy1)/log(0.9);
					}
				}
				
			}
		}
		if (n==0)
		{
			if (lay[selected].rot_arbit!=1)
			{
				n=angleo1/log(5);
			}
			else
			{
				n=anglea1/log(5);
			}
		}
	}
	
	
	if (n==0)
	{
		k=0;
		while (k<store_index)
		{
			if (n==0.0)
			{
				if (ty[k]==0.0)
				{
					n=tx[k]/0.01;
				}
				else
				{
					if (tx[k]==0.0)
					{
						n=ty[k]/0.01;
					}
					else
					{
						if (tx[k]>ty[k] )
						{
							n=tx[k]/0.01;
						}
						if (ty[k]<tx[k])
						{
							n=ty[k]/0.01;
						}
						
					}
					
				}
				
				if (n==0)
				{
					if (sy[k]==1.0 && sx[k]!=1.0)
					{
						if (sx[k]>1)
						{
							n=log(sx[k])/log(1.1);
						}
						if (sx[k]<1)
						{
							n=log(sx[k])/log(0.9);
						}
					}
					else
					{
						if (sx[k]==1.0 && sy[k]!=1.0)
						{
							if (sy[k]>1)
							{
								n=log(sy[k])/log(1.1);
							}
							if (sx[k]<1)
							{
								n=log(sy[k])/log(0.9);
								
							}
						}
						else
						{
							if (sx[k]>sy[k])
							{
								if (sx[k]>1)
								{
									n=log(sx[k])/log(1.1);
								}
								if (sx[k]<1)
								{
									n=log(sx[k])/log(0.9);
								}
							}
							else
							{
								if (sy[k]>1)
								{
									n=log(sy[k])/log(1.1);
								}
								if (sx[k]<1)
								{
									n=log(sy[k])/log(0.9);
								}
							}
							
						}
						
						
						
					}
					if (n==0)
					{
						if (lay[selected].rot_arbit!=1)
						{
							n=angleo[k]/log(5);
						}
						else
						{
							n=anglea[k]/log(5);
						}
					}
				}
			}
			if (n!=0.0)
			{
				break;
			}
			k++;
			
		}
		
	}
		
	
	if (n==0.0)
	{
		n=1;
	}
	if (n<0.0)
	{
		n=-n;
	}
	
	lay[selected].tx=tx1/n;
	lay[selected].ty=ty1/n;
	lay[selected].sx=pow(sx1,((double) 1/n));
	lay[selected].sy=pow(sy1, ((double) 1/n));
	lay[selected].angleo=pow(angleo1, ((double) 1/n));
	lay[selected].anglea=pow(anglea1, ((double) 1/n));
	
	
	
	k=0;
	while (k<store_index)
	{
		lay[save_lay_index[k]].tx=tx[k]/n;
		lay[save_lay_index[k]].ty=ty[k]/n;
		lay[save_lay_index[k]].sx=pow(sx[k],((double) 1/n));
		lay[save_lay_index[k]].sy=pow(sy[k], ((double) 1/n));
		lay[save_lay_index[k]].angleo=pow(angleo[k],((double) 1/n));
		lay[save_lay_index[k]].anglea=pow(anglea[k], ((double) 1/n));
		
		k++;
	}
				
	
	j=selected;
	
	
	for (i=1; i<=n; i=i+1.0)
	{
		selected=j;
		animate_col_flag=1;
		lay_rePaint();
		
		shift=start[selected];	
		while (shift!= end[selected])
		{
			doTransform();		
			shift=shift->next;
		}
		doTransform();
		animate_col_flag=0;
		lay_rePaint();
		
		k=0;
		while (k<store_index)
		{
			selected=save_lay_index[k];
			animate_col_flag=1;
			lay_rePaint();
			
			shift=start[selected];
			while (shift!=end[selected])
			{
				doTransform();
				shift=shift->next;
			}
			doTransform();
			animate_col_flag=0;
			lay_rePaint();
			k++;
		}		
		usleep(10000);
	}	
	
	k=0;
	while (k<store_index)
	{
		selected=save_lay_index[k];
		init_seg();
		k++;
	}
	store_index=0;
	selected=j;
	init_seg();
	df_wr();
	rePaint();
	
}
				  


/**** animation ****/
void animate()
{
	float i,tx,ty,sx,sy,angleo,anglea;
	float n;
	
	if (negtx==1)
	{
		lay[selected].tx=-lay[selected].tx;
		negtx=0;
	}
	if (negty==1)
	{
		lay[selected].ty=-lay[selected].ty;
		negty=0;
	}
	seg_wr(0);
	tx=lay[selected].tx;
	ty=lay[selected].ty;
	sx=lay[selected].sx;
	sy=lay[selected].sy;
	angleo=lay[selected].angleo;
	anglea=lay[selected].anglea;
	n=0.0;

	if (ty==0.0)
	{
		n=tx/0.01;
	}
	else
	{
		if (tx==0.0)
		{
			n=ty/0.01;
		}
		else
		{
			if (tx>ty )
			{
				n=tx/0.01;
			}
			if (ty<tx)
			{
				n=ty/0.01;
			}
			
		}

	}
	
	if (n==0)
	{
		if (sy==1.0 && sx!=1.0)
		{
			if (sx>1)
			{
				n=log(sx)/log(1.1);
			}
			if (sx<1)
			{
				n=log(sx)/log(0.9);
			}
		}
		else
		{
			if (sx==1.0 && sy!=1.0)
			{
				if (sy>1)
				{
					n=log(sy)/log(1.1);
				}
				if (sx<1)
				{
					n=log(sy)/log(0.9);
					
				}
			}
			else
			{
				if (sx>sy)
				{
					if (sx>1)
					{
						n=log(sx)/log(1.1);
					}
					if (sx<1)
					{
						n=log(sx)/log(0.9);
					}
				}
				else
				{
					if (sy>1)
					{
						n=log(sy)/log(1.1);
					}
					if (sx<1)
					{
						n=log(sy)/log(0.9);
					}
				}

			}
		}
		if (n==0)
		{
			if (lay[selected].rot_arbit!=1)
			{
				n=angleo/log(5);
			}
			else
			{
				n=anglea/log(5);
			}
		}
	}
	
	if (n==0)
	{
		n=1;
	}
	if (n<0)
	{
		n=-n;
	}
	
	
	
	lay[selected].tx=tx/n;
	lay[selected].ty=ty/n;
	lay[selected].sx=pow(sx,((double) 1/n));
	lay[selected].sy=pow(sy, ((double) 1/n));
	lay[selected].angleo=pow(angleo,((double) 1/n));
	lay[selected].anglea=pow(anglea, ((double) 1/n));
	
	
	for (i=1; i<=n; i=i+1.0)
	{
		animate_col_flag=1;
		lay_rePaint();
		
		shift=start[selected];	
		while (shift!= end[selected] && shift!=NULL)
		{
			doTransform();		
			shift=shift->next;
		}
		doTransform();
	
		animate_col_flag=0;
		lay_rePaint();
		usleep(10000);
	}	
	
	df_wr();
	rePaint();
	init_seg();	
}



/**** Zoom in ****/
void zoom_in()
{

}



/**** zoom out ****/
void zoom_out()
{
	
	
}


/**** Init for layer_window ****/
void init_layer_window()
{
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(200, heightm-200-heightm/2,widthm/2, heightm/2); 
    gluOrtho2D(200,200+widthm/2,heightm-200-heightm/2,heightm-200);
    glFlush();
}


void init_size_layer_window()
{
	startx = startx_layer+50;
	heightl=glutGet(GLUT_WINDOW_HEIGHT);
	starty = heightl+115;
	adderx = 50;
	addery = 30;
}



/**** create layer ****/
void create_layer()
{
	char ch_war[40]={"The layer -        - already exists "};
	char txt[3]={"ok"};
	int j;

	glColor3f(1.0,1.0,1.0);
	draw_line(widthm/2+80, starty_layer-20, widthm/2+125, starty_layer-20, 1, 30.0);
	
	init_size_layer_window();
	glColor3f(1.0, 1.0, 1.0);
	j=0;
	while (ch_war[j]!='\0')
	{
		char_set(startx-10+j*12, starty-8);
		char_gen(ch_war[j], 14, 9);
		j++;
	}
	glColor3f(1.0, 0.0, 0.0);
	j=0;
	
	while (lay[war_lay].layer_name[j]!='\0')
	{
		char_set(startx-10+j*12+150, starty-8);
		char_gen(lay[war_lay].layer_name[j], 14, 9);
		j++;
	}
	
	glColor3f(0.0, 0.0, 0.0);
	j=0;
	while (txt[j]!='\0')
	{
		char_set(widthm/2+90+j*12, 170);
		char_gen(txt[j], 14, 9);
		j++;
	}
	
	
	glColor3f(1.0, 0.0, 0.0);
	draw_line(widthm/2-130, starty_layer+120, widthm/2-60, starty_layer+120, 1, 5.0);
	draw_line(widthm/2-60, starty_layer+120, widthm/2-95, starty_layer+200, 1, 5.0);
	draw_line(widthm/2-95, starty_layer+200, widthm/2-130, starty_layer+120, 1, 5.0);
	
	glColor3f(1.0, 1.0, 1.0);
	draw_line(widthm/2-95, starty_layer+170, widthm/2-95, starty_layer+150, 1, 2.0);
	draw_circle(widthm/2-95, starty_layer+140, 5, 0, 2.0);
	
}



void icon_layer_window()
{
	glColor3f(1.0,1.0,1.0);
	draw_line(startx-15, starty, startx+adderx-15, starty, 1, 30.0);
	
}


/**** create for select layer_window ****/
void select_layer()
{
    int j,k;
	char txt[3]={"ok"};
	
    init_size_layer_window();
	
	for (j=0; j<=layer_name_index; j++)
	{
		icon_layer_window();
		k=0;
		glColor3f(0.0, 0.0, 0.0);
		while (lay[j].layer_name[k]!='\0')
		{
			char_set(startx-20+k*12, starty-8);
			char_gen(lay[j].layer_name[k], 14, 9);
			k++;
		}
		 startx+=adderx+50;
		if (startx>widthm/2+100)
		{
			init_size_layer_window();
			starty-=addery+10;
		}
	}
	
	glColor3f(1.0,1.0,1.0);
	draw_line(widthm/2+80, starty_layer-20, widthm/2+125, starty_layer-20, 1, 30.0);
	
	glColor3f(0.0, 0.0, 0.0);
	j=0;
	while (txt[j]!='\0')
	{
		char_set(widthm/2+90+j*12, 170);
		char_gen(txt[j], 14, 9);
		j++;
	}
	
	init_size_layer_window();
} 


/**** save as display func ****/
void save_as()
{
	int j,k;
	char txt[11]="File name:";
	char txt1[2][5]={"Save","Load"};
	init_size_layer_window();
	j=0;k=0;
	while (txt[j]!='\0')
	{
		char_set(startx-20+j*12, starty-8);
		char_gen(txt[j], 14, 9);
		j++;
	}
	startx+=j*12+20;
	icon_layer_window();
	
	glColor3f(1.0,1.0,1.0);
	draw_line(widthm/2+80, starty_layer-20, widthm/2+125, starty_layer-20, 1, 30.0);
	glColor3f(0.0, 0.0, 0.0);
	k=0;
	if (openf==1)
	{
		k=1;
	}
	j=0;
	while (txt1[k][j]!='\0')
	{
		char_set(widthm/2+80+j*12, 170);
		char_gen(txt1[k][j], 14, 9);
		j++;
	}
}



/**** Layer name contradiction ****/
void display_layer_war()
{
	glClear(GL_COLOR_BUFFER_BIT);
	create_layer();
	glFlush();
}


/**** Layer select ****/
void display_layer_window()
{
    glClear(GL_COLOR_BUFFER_BIT);
    select_layer();
    glFlush();
} 


/**** File save as ****/
void display_file_window()
{
	glClear(GL_COLOR_BUFFER_BIT);
	save_as();
	glFlush();
}


/**** Keyboard func for save window ****/
void myKey_file_window (char key)
{
	if (key!=46 && key!=13 && key!=44 && count<6)
	{
		glColor3f(1.0, 0.0, 0.0);
		char_gen(key, 13, 8);
		if (key != 8)
		{
			file_name[file_name_index++]=key;
		}
		else
		{
			file_name[--file_name_index]='\0';
		}
	}
//	glFlush();
}


void pop_function()
{
	switch (pop_check)
	{
		case 1://hold
			hold=1;
			break;
		case 2://cut
			cp=store;
			shift=head;
			while (shift->next!=store)
			{
				shift=shift->next;
			}

			if (cp->next!=NULL)
			{
				switch (cp->op)
				{
					case 1:
						shift->next=cp->next;
						break;
					case 3:
						prevp1=shift->next->next;
						while (prevp1->op!=3)
						{
							prevp1=prevp1->next;
						}
						shift->next=prevp1->next;
						break;
					case 4:
						shift->next=cp->next;
						break;
						
					default:
						break;
				}
			}
			else
			{
				shift->next=NULL;
				end[selected]=shift;
				ard=end[selected];
			}
			
			break;
		case 3://copy
			cp=store;
			break;
			
		case 4://paste
			shift=cp;
			ard1=malloc(sizeof(struct s3));
			ard1->next=NULL;
			ard1->op=shift->op;
			switch (shift->op)
			{
				case 1:
					ard1->x1=shift->x1;
					ard1->y1=shift->y1;
					ard1->x2=shift->x2;
					ard1->y2=shift->y2;
				
					ard1->l_type=shift->l_type;
					ard1->size=shift->size;
					ard1->red=shift->red;
					ard1->g=shift->g;
					ard1->b=shift->b;
					break;
				case 3:
					prevp1=ard1;
					ard1->next=malloc(sizeof(struct s3));
					ard1=ard1->next;
					ard1->next=NULL;
					shift=shift->next;
					while (shift->op!=3)
					{
						ard1->op=shift->op;
						ard1->x1=shift->x1;
						ard1->y1=shift->y1;
						ard1->x2=shift->x2;
						ard1->y2=shift->y2;
						ard1->l_type=shift->l_type;
						ard1->size=shift->size;
						ard1->red=shift->red;
						ard1->g=shift->g;
						ard1->b=shift->b;
						ard1->next=malloc(sizeof(struct s3));
						ard1=ard1->next;
						ard1->next=NULL;
						shift=shift->next;
					}
					ard1->op=shift->op;
					ard1=prevp1;
					break;

				case 4:
					ard1->x1=shift->x1;
					ard1->y1=shift->y1;
					ard1->r=shift->r;
					ard1->c_type=shift->c_type;
					ard1->size=shift->size;
					ard1->red=shift->red;
					ard1->g=shift->g;
					ard1->b=shift->b;
					break;

				default:
					break;
			}
		
			
			end[selected]->next=ard1;
			end[selected]=ard1;
			ard=end[selected];
			break;
			
		case 5://delete
			shift=head;
			while (shift->next!=store && shift->next!=NULL)
			{
				shift=shift->next;
			}
			if (shift->next==NULL)
			{
				shift=store;
			}
			
			switch (store->op)
			{
				case 1:
					shift->next=store->next;
					break;
				case 3:
					prevp1=store->next;
					while (prevp1->op!=3)
					{
						prevp1=prevp1->next;
					}
					shift->next=prevp1->next;
					break;
				case 4:
					shift->next=store->next;
					break;
				default:
					break;
			}
			
			store_index=0;
			
			break;
			
		default:
			break;
	}
	if (hold!=1)
	{
		df_wr();
		rePaint();
	}
	
}


void pop_text()
{
	char text[5][10]={"Hold","Cut","Copy","Paste","Delete"};
	int i,j;
	glColor3f(0.2, 0.2, 0.2);
	i=0;
	while (i<=4)
	{
		j=0;
		while (text[i][j]!='\0')
		{
			char_set(pop_x+17+j*11, pop_y+120-25*i);
			char_gen(text[i][j], 13, 9);
			j++;
		}
		i++;
	}
}

/**** init for pop_window ****/
void init_pop()
{
	glClearColor(0.9, 0.9, 0.9, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glViewport(pop_x, pop_y, 100, 150);
	gluOrtho2D(pop_x, pop_x+100, pop_y, pop_y+150);
    glFlush();
}

/**** Display for the popup menu ****/
void display_pop()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.5, 0.5, 0.5);
	draw_rect(pop_x+5, pop_y+5, pop_x+95, pop_y+145, 1, 3.0);
	pop_text();
	//rePaint();
	//glutSetWindow(pop_window);
	glFlush();
}

void myMouse_pop_window (int button, int state, int x, int y)
{
	int yl,yh,i;
	int max=glutGet(GLUT_WINDOW_HEIGHT);
	if (button==GLUT_LEFT_BUTTON) 
	{
		display_pop();
		yl=15;
		yh=31;
		for (i=1; i<=5; i++)
		{
			if (y>yl && y<yh && x>10 && x<100)
			{
				glPointSize(10.0);
				glColor3f(0.0, 0.0, 1.0);
				draw_line(pop_x+20, pop_y+max-yl-9, pop_x+80, pop_y+max-yl-9, 1, 20.0);
				pop_text();
				pop_check=i;
				pop_function();
				break;
			}
			else
			{
				yl+=25;
				yh+=25;
			}
		}
		usleep(200000);
		glutDestroyWindow(pop_window);
	}
	//rePaint();
}


void myMouse_pop_window_over (int x, int y)
{
	int i;
	int max=glutGet(GLUT_WINDOW_HEIGHT);
	
	if (pop_move==1)
	{
		glColor3f(0.9, 0.9, 0.9);
		draw_line(pop_x+20, pop_y+max-yl-9, pop_x+80, pop_y+max-yl-9, 1, 20.0);
		pop_text();
	}
	
	
	yl=15;
	yh=31;
	for (i=1; i<=5; i++)
	{
		
		if (y>yl && y<yh && x>10 && x<100)
		{	
			glPointSize(10.0);
			glColor3f(0.0, 0.0, 1.0);
			draw_line(pop_x+20, pop_y+max-yl-9, pop_x+80, pop_y+max-yl-9, 1, 20.0);
			pop_text();
			pop_move=1;
			break;
		}
		else
		{
			pop_move=0;
			yl+=25;
			yh+=25;
		}
	}
	
}


/**** init for store_anim ****/
void init_store_anim()
{
	/*int i,j;
	for (i=0; i<50; i++)
	{
		for (j=0; j<150; j++)
		{
			store_anim[i][j].sx=1;
			store_anim[i][j].sy=1;
			store_anim[i][j].angleo=0;
			store_anim[i][j].anglea=0;
			store_anim[i][j].tx=0;
			store_anim[i][j].ty=0;
			store_anim[i][j].rot_arbit=0;
			store_anim[i][j].clockwise=0;
			store_anim[i][j].x=0;
			store_anim[i][j].y=0;
		}
	}*/
	store_anim_index=0;
	flag_scale=0;
	flag_trans=0;
	flag_rot=0;
}


/**** rectangle in the animate window ****/
void rect_anim()
{
	int i;
	glColor3f(1.0, 1.0, 1.0);
	draw_line(125, 25, widthm-25, 25, 1, 40.0);
	glColor3f(0.0, 0.0, 0.0);
	draw_line(125, 25, widthm-24, 25, 1, 3.0);
	glColor3f(0.7, 0.7, 0.7);
	for (i=0; i<48; i++)
	{
		draw_line(125+22*i, 10, 125+22*i, 40, 1, 3.0);
	}
	
}


/**** init for animate window ****/
void init_anim_window()
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(100, 0, widthm-100, 50);		//view (x,y)(lower-left-corner),sizex,sizey
	gluOrtho2D(100, widthm, 0.0, 50);  // clipping left,right,bottom,top
	glFlush();
}

void display_anim_window()
{
	glClear(GL_COLOR_BUFFER_BIT);
	rect_anim();
	rePaint();
	glFlush();
}

/**** mouse function for animation window ****/
void myMouse_anim_window (int button, int state, int x, int y)
{
	int i,xi;
	
	if (button==GLUT_LEFT_BUTTON)
	{
		xi=25;
		for (i=0; i<50; i++)
		{
			if (x>=xi-10 && x<=xi+5)
			{
				glColor3f(1.0, 0.0, 0.0);
				draw_circle(125+22*i, 25, 5, 0, 2.0);
				store_anim_index=i;
				break;
			}
			else
			{
				xi+=25;
			}
		}
	}
	glFlush();
}



void layer_action_window()
{
	int i,j;
	char eg[10]={"Example"};
	
	glColor3f(0.8, 0.0, 0.0);
	draw_rect(22, heightm-38, 116, heightm-5, 1, 5.0);
	glColor3f(1.0, 0.0, 0.0);
	draw_line(40, heightm-20, 100, heightm-20, 1, 30.0);
	
	j=0;
	glColor3f(0.0, 0.0, 0.0);
	while (eg[j]!='\0')
	{
		char_set(40+10*j, heightm-27);
		char_gen(eg[j], 12, 8);
		j++;
	}
	glColor3f(1.0, 1.0, 1.0);
	draw_line(140, heightm-20, widthm-30, heightm-20, 1, 30.0);

	
	
	for (i=1; i<=layer_name_index+1; i++)
	{
		glColor3f(0.8, 0.0, 0.0);
		draw_rect(22, heightm-38-50*i, 116, heightm-5-50*i, 1, 5.0);
		glColor3f(1.0, 0.0, 0.0);
		draw_line(40, heightm-20-50*i, 100, heightm-20-50*i, 1, 30.0);
		
		j=0;
		glColor3f(0.0, 0.0, 0.0);
		while (lay[i-1].layer_name[j]!='\0')
		{
			char_set(40+10*j, heightm-27-50*i);
			char_gen(lay[i-1].layer_name[j], 12, 8);
			j++;
		}
		glColor3f(1.0, 1.0, 1.0);
		draw_line(140, heightm-20-50*i, widthm-30, heightm-20-50*i, 1, 30.0);
	}
	
	for (i=0; i<3; i++)
	{
		for (j=0; j<9; j++)
		{
			glColor3f(1.0, 1.0, 1.0);
			draw_line(30+120*j,20+40*i, 100+120*j, 20+40*i, 1, 30.0);
		}
	}
}

/**** init for action window ****/
void init_action_window()
{
	glClearColor(0.6, 0.6, 0.6, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, widthm, heightm);		//view (x,y)(lower-left-corner),sizex,sizey
	gluOrtho2D(0, widthm, 0.0, heightm);  // clipping left,right,bottom,top
	glFlush();
}
	
/**** display for the action file ****/
void display_action_window()
{
	glClear(GL_COLOR_BUFFER_BIT);
	layer_action_window();
	glFlush();
}


void myMouse_action_window (int button, int state, int x, int y)
{
	int i,j,y1,order,x2,y2;
	
	order=0;
	if (button==GLUT_LEFT_BUTTON)
	{
		glColor3f(0.8, 0.0, 0.0);
		draw_rect(22, heightm-38-50*(store_layer+1), 116, heightm-5-50*(store_layer+1), 1, 5.0);
		
		store_layer=-1;
		
		y1=75;
		for (i=1; i<=layer_name_index+1; i++)
		{
			if (y>=y1-25 && y<=y1+25)
			{
				glColor3f(0.8, 0.8, 0.0);
				draw_rect(22, heightm-38-50*i, 116, heightm-5-50*i, 1, 5.0);
				store_layer=i-1;
				
				chCP.x=140;
				chCP.y=heightm-20-50*i-12/2;
				mous.x=140;
				mous.y=heightm-20-50*i-12/2;
				count=0;
				name=0;
				break;
			}
			else
			{
				order=1;
				y1+=50;
				
			}
		}
		if (order==1)
		{
			y2=580;
			for (i=0; i<3; i++)
			{
				if (y>=y2 && y<=y2+30)
				{
					x2=17;
					for (j=0; j<9; j++)
					{
						if ((x>x2 && x<x2+120) && (y>y2 && y<y2+30))
						{
							chCP.x=30+120*j;
							chCP.y=heightm-y2-23;

							mous.x=chCP.x;
							mous.y=chCP.y;
							count=0;
							name=1;
							break;
						}
						else
						{
							x2+=120;
						}
					}
				}
				else
				{
					y2+=40;
				}
			}
		}
	}
	glFlush();
}


void myKey_action_window (int key)
{
	
	glColor3f(1.0, 0.0, 0.0);
	action_key=1;
	if (key!=13 && name==0)
	{
		action[store_layer][count]=key;
		char_gen(key,12,7);
		
		if (key=='x')
		{
			key=':';
			action[store_layer][count]=key;
			char_gen(key,12,7);
		}
		if (key=='a')
		{
			anim_arbit=1;
		}
		if (key=='p')
		{
			key=anim_arbit_pt.x/100+48;
			action[store_layer][count]=key;
			char_gen(key,12,7);
			key=(anim_arbit_pt.x/10)%10+48;
			action[store_layer][count]=key;
			char_gen(key,12,7);
			key=anim_arbit_pt.x%10+48;
			action[store_layer][count]=key;
			char_gen(key,12,7);
			
			key=',';
			action[store_layer][count]=key;
			char_gen(key,12,7);
			
			key=anim_arbit_pt.y/100+48;
			action[store_layer][count]=key;
			char_gen(key,12,7);
			key=(anim_arbit_pt.y/10)%10+48;
			action[store_layer][count]=key;
			char_gen(key,12,7);
			key=anim_arbit_pt.y%10+48;
			action[store_layer][count]=key;
			char_gen(key,12,7);
			anim_arbit=0;

		}
		if (key=='y')
		{
			key=':';
			action[store_layer][count]=key;
			char_gen(key,12,7);
		}

	}
	if (key!=13 && name==1)
	{
		if (key=='c')
		{
			name_anim[name_index-1].con=1;
		}
		else
		{
			if (key=='n')
			{
				name_anim[name_index-1].con=0;
			}
			else
			{
				name_anim[name_index].no=key-48;
				name_index++;
			}
		}
		char_gen(key,12,7);
	}
	
	glFlush();
}


void action_init()
{
	int i,j;
	name_index=0;
	for (i=0; i<layer_name_index; i++)
	{
		j=0;
		while (action[i][j]='\0')
		{
			action[i][j]='\0';
			j++;
		}
		lay[i].sx=1;
		lay[i].sy=1;
		lay[i].angleo=0;
		lay[i].anglea=0;
		lay[i].tx=0;
		lay[i].ty=0;
		lay[i].rot_arbit=0;
		lay[i].clockwise=0;
		lay[i].x=0;
		lay[i].y=0;
	}
}



/**** animation function ****/
void create_action()
{
	/*int i,j,n,x,y;
	float a,b,c,d;
	n=10;
	
	for (i=0; i<=0; i++)
	{
		shift=head;
		j=0;
		n=10;
		while (shift!=NULL)
		{
			while (n>=0)
			{
				switch (shift->op==1)
				{
					case 1:
						glColor3f(1.0, 1.0, 1.0);
						rev_normalize(shift->x1, shift->y1);
						x=xrnor;y=yrnor;
						rev_normalize(shift->x2, shift->y2);
						draw_line(x, y, xrnor, yrnor, shift->l_type, shift->size);
						
						
						a=store_anim[i][j].x1-shift->x1;
						b=store_anim[i][j].y1-shift->y1;
						c=store_anim[i][j].x2-shift->x2;
						d=store_anim[i][j].y2-shift->y2;
						load_identity();
						translate(a/10, b/10);
						transform_matrix(shift->x1, shift->y1);
						load_identity();
						translate(c/10, b/10);
						transform_matrix(shift->x2, shift->y2);
						glColor3f(shift->red, shift->g, shift->b);
						draw_line(x, y, xrnor, yrnor, shift->l_type, shift->size);

						break;
					default:
						break;
				}
				n--;
			}
			
			j++;
			shift=shift->next;
		}
		
	}*/
	glutDestroyWindow(action_window);

	action_init();
	glutInitWindowPosition(widthm, heightm);
	glutInitWindowSize(widthm, heightm);
	action_window=glutCreateWindow("Animation");
	init_action_window();
	glutDisplayFunc(display_action_window);
	glutMouseFunc(myMouse_action_window);
	glutKeyboardFunc(myKey_action_window);
	
	
}


void extract(int i)
{
	int j;
	j=0;
	//printf("\n%s",action[i]);
	//printf("\n%d %d",i,name_anim[i].no-1);
	while (action[name_anim[i].no-1][j]!=')')
	{
		switch (action[name_anim[i].no-1][j])
		{
			case 't':
				j++;
				if (action[name_anim[i].no-1][j]=='x')
				{
					if (action[name_anim[i].no-1][j+2]=='-')
					{
						j++;
					}
					j=j+4;
					lay[name_anim[i].no-1].tx=0.01*asc_num(action[name_anim[i].no-1][j+1])+0.1*asc_num(action[name_anim[i].no-1][j]);
					if (action[name_anim[i].no-1][j-3]=='-')
					{
						lay[name_anim[i].no-1].tx=-lay[name_anim[i].no-1].tx;
					}
					j++;
					//printf("\n%s \t%f",lay[name_anim[i].no-1].layer_name,lay[name_anim[i].no-1].tx);
				}
				if (action[name_anim[i].no-1][j]=='y')
				{
					if (action[name_anim[i].no-1][j+2]=='-')
					{
						j++;
					}
					
					j=j+4;
					lay[name_anim[i].no-1].ty=0.01*asc_num(action[name_anim[i].no-1][j+1])+0.1*asc_num(action[name_anim[i].no-1][j]);
					if (action[name_anim[i].no-1][j-3]=='-')
					{
						lay[name_anim[i].no-1].ty=-lay[name_anim[i].no-1].ty;
					}
					j++;
					//printf("\n%s \t%f",lay[name_anim[i].no-1].layer_name,lay[name_anim[i].no-1].ty);
				}
				break;
				
			case 's':
				j++;
				if (action[name_anim[i].no-1][j]=='x')
				{
					j=j+2;
					lay[name_anim[i].no-1].sx=asc_num(action[name_anim[i].no-1][j]);
					j=j+2;
					lay[name_anim[i].no-1].sx+=0.01*asc_num(action[name_anim[i].no-1][j+1])+0.1*asc_num(action[name_anim[i].no-1][j]);
					//printf("\n%s \t%f",lay[name_anim[i].no-1].layer_name,lay[name_anim[i].no-1].sx);
				}
				if (action[name_anim[i].no-1][j]=='y')
				{
					j=j+2;
					lay[name_anim[i].no-1].sy=asc_num(action[name_anim[i].no-1][j]);
					j=j+2;
					lay[name_anim[i].no-1].sy+=0.01*asc_num(action[name_anim[i].no-1][j+1])+0.1*asc_num(action[name_anim[i].no-1][j]);
					//printf("\n%s \t%f",lay[name_anim[i].no-1].layer_name,lay[name_anim[i].no-1].sx);
				}
				break;
			
			case 'a':
				lay[name_anim[i].no-1].rot_arbit=1;
				j=j+2;
				if (action[name_anim[i].no-1][j]=='c')
				{
					lay[name_anim[i].no-1].clockwise=1;
				}
				else
				{
					lay[name_anim[i].no-1].clockwise=0;
				}
				j++;

				lay[name_anim[i].no-1].anglea=asc_num(action[name_anim[i].no-1][j+1])+10*asc_num(action[name_anim[i].no-1][j]);
				j=j+4;
				
				lay[name_anim[i].no-1].x=100*asc_num(action[name_anim[i].no-1][j])+10*asc_num(action[name_anim[i].no-1][j+1])+asc_num(action[name_anim[i].no-1][j+2]);
				j=j+4;
				lay[name_anim[i].no-1].y=100*asc_num(action[name_anim[i].no-1][j])+10*asc_num(action[name_anim[i].no-1][j+1])+asc_num(action[name_anim[i].no-1][j+2]);

				
				//printf("\n%f \t%d %d",lay[name_anim[i].no-1].anglea,lay[name_anim[i].no-1].x,lay[name_anim[i].no-1].y);

				
				break;

			default:
				break;
		}
		j++;	
	}
	lay[name_anim[i].no-1].tx=lay[name_anim[i].no-1].tx/10;
	lay[name_anim[i].no-1].ty=lay[name_anim[i].no-1].ty/10;
	lay[name_anim[i].no-1].sx=pow(lay[name_anim[i].no-1].sx, 0.1);
	lay[name_anim[i].no-1].sy=pow(lay[name_anim[i].no-1].sy, 0.1);
	//lay[name_anim[i].no-1].anglea=pow(lay[name_anim[i].no-1].anglea, 0.1);
	lay[name_anim[i].no-1].anglea=5;
	
}


void anim(int k,int j)
{
	int n,i;
	
	for (n=0; n<=10; n++)
	{
		for(i=k;i<=j;i++)
		{
			selected=name_anim[i].no-1;
			animate_col_flag=1;
			lay_rePaint();
			
			shift=start[selected];	
			while (shift!= end[selected])
			{
				doTransform();		
				shift=shift->next;
			}
			doTransform();
			animate_col_flag=0;
			lay_rePaint();
			

		}
		usleep(100000);
	}
	df_wr();
	rePaint();
	action_init();
}


/**** clear animation value ****/
void perform_action()
{
	
	int i,j,k,l,swap;
	int tem;

	
	if (example==1)
	{
		fp=fopen("action.af", "r");
		fscanf(fp, "%s",action[0]);
		fclose(fp);
		printf("\n%s\n",action[0]);
	}
	
	else
	{
		fp=fopen("action.af", "w");
		for (i=0; i<name_index; i++)
		{
			fprintf(fp, "%s\n",action[name_anim[i].no-1]);
		}
		fclose(fp);
	}

	
	usleep(100000);

	
	i=0;
	
	while (i<name_index)
	{
		
		swap=0;
		extract(i);

		j=i;
		while (name_anim[i].con==1)
		{		
			i++;
			extract(i);
		}
		usleep(100000);
		tem=name_index;
		anim(j,i);
		name_index=tem;
		
		
		
		i=j;
		
		//printf("\n%s",action[name_anim[i].no-1]);

		//while (name_anim[i].con==1) 
		//{
			k=0;l=0;
			while (action[name_anim[i].no-1][k]!=')') 
			{
				k++;
			}
			k++;
		
			while (action[name_anim[i].no-1][k]!='\0')
			{
				action[name_anim[i].no-1][l]=action[name_anim[i].no-1][k];
				action[name_anim[i].no-1][k]='\0';
				l++;k++;
				swap=1;
			}
			//printf("\n%s",action[name_anim[i].no-1]);
			
		if (swap==1)
		{
			extract(i);
			i--;
		}
			
	//	}
		
		
		
		
		
	//	usleep(10000);
		//anim(j,i);
		
		/*if (i<name_index)
		{
			i++;
			extract(i);
			usleep(10000);
			tem=name_index;
			anim(i,i);
			name_index=tem;

		}*/
		
		
		
		/*k=0;l=0;
		while (action[name_anim[i].no-1][k]!=')') 
		{
			k++;
		}
		k++;
		while (action[name_anim[i].no-1][k]!='\0')
		{
			action[name_anim[i].no-1][l]=action[name_anim[i].no-1][k];
			l++;k++;
			printf("called");
		}
		extract(i);
		//usleep(10000);
		anim(i,i);*/
		i++;
	}
	
	glutDestroyWindow(anim_window);
}


void action_reset()
{
	glutDestroyWindow(action_window);
	create_action();
}


int calcode (float x,float y)
{
	int code =0;
	
	if(y> ywmax)
		code |=TOP;
	else if( y<ywmin)
		code |= BOTTOM;
	else if(x > xwmax)
		code |= RIGHT;
	else if ( x< xwmin)
		code |= LEFT;
	
	return(code);
}


/**** clipping ****/
void clip()
{
	float x0,y0,x1,y1;
	outcode code0,code1,codeout;
	int accept = 0, done=0;
	
	x0=shift1->x1;
	x1=shift1->x2;
	y0=shift1->y1;
	y1=shift1->y2;
	
	code0 = calcode(x0,y0);
	code1 = calcode(x1,y1);
		
	
	do{
		
		if(!(code0 | code1))
		{ 
			accept =1;
			done =1;
		}
		else
			if(code0 & code1) 
			{
				done = 1; 
			}
			else
			{
				float x,y;
				codeout = code0 ? code0 : code1;
				if(codeout & TOP)
				{
					x = x0 + (x1-x0)*(ywmax-y0)/(y1-y0);
					y = ywmax;
				}
				else
					if( codeout & BOTTOM)
					{
						x = x0 + (x1-x0)*(ywmin-y0)/(y1-y0);
						y = ywmin;
					}
					else
						if ( codeout & RIGHT)
						{
							y = y0+(y1-y0)*(xwmax-x0)/(x1-x0);
							x = xwmax;
						}
						else
						{
							y = y0 + (y1-y0)*(xwmin-x0)/(x1-x0);
							x = xwmin;
						}
				if( codeout == code0)
				{
					x0 = x; y0 = y;
					code0=calcode(x0,y0);
				}
				else
				{
					x1 = x; y1 = y;
					code1 = calcode(x1,y1);
				}
			}
	} while( done == 0);
	
	if(accept) 
	{
		if (shift1->x1!=x0 || shift1->x2!=x1 || shift1->y1!=y0 || shift1->y2!=y1)
		{
			clipped=1;
		}
		else
		{
			clipped=0;
		}

		shift1->x1=x0;
		shift1->x2=x1;
		shift1->y1=y0;
		shift1->y2=y1;
	}	
	else
	{		
		if (shift1==head)
		{
			head=head->next;
		}
		else
		{
			shift=head;
			while (shift->next!=shift1)
			{
				shift=shift->next;
			}
			if (shift1==ard)
			{
				shift->next=NULL;
				ard=shift;
				end[selected]=ard;
			}
			else
			{
				shift->next=shift1->next;
			}
		 }		
	}
	df_wr();
	
}



/**** Create sub window ****/
void create_sub_window(int n)
{
	char create_layer[3][20]={"Name:","Create","Clear"};
	char trans_layer[9][20]={"Select layer","Scale x:","Scale y:","Rotate O:","Rotate A:","Trans x:","Trans y:","Save","Animate"};
	char del_layer[1][10]={"Delete"};
	char menu[2][10]={"Save","Load"};
	char grid[3][12]={"Allign:","Active","Deactive"};
	char sel[2][7]={"Unhold","Clear"};
	char view[2][5]={"Map","Move"};
	char anim[3][6]={"Action","Anim","Reset"};
	int j,k;

	
	
	if (anim_window_activate==1)
	{
		//work_h-=100;
		glutDestroyWindow(anim_window);
		anim_window_activate=0;
		/*if (n!=19)
		{
			rePaint();
		}*/
	}
		

	glutSetWindow(sub_window);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
	
	switch (n)
	{
		case 1:
			if (anim_window_activate==1)
			{
				glutDestroyWindow(anim_window);
				anim_window_activate=0;
			}
			
			init_size_line_sub();
			icon_box_line_sub();
			
			glColor3f(0.0, 0.0, 1.0);
			draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
			
			
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_line_sub+5, i_starty_line_sub+10, i_startx_line_sub+adder_line_sub_x-5, i_starty_line_sub+10, 2.0, 1);
			
			i_starty_line_sub-=25;
			icon_box_line_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_line_sub+5, i_starty_line_sub+10, i_startx_line_sub+adder_line_sub_x-5, i_starty_line_sub+10, 2.0, 2);
			
						
			i_starty_line_sub-=25;
			icon_box_line_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_line_sub+5, i_starty_line_sub+10, i_startx_line_sub+adder_line_sub_x-5, i_starty_line_sub+10, 2.0, 3);
			
			i_starty_line_sub-=25;
			icon_box_line_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_line_sub+5, i_starty_line_sub+10, i_startx_line_sub+adder_line_sub_x-5, i_starty_line_sub+10, 2.0, 4);
			
			init_size_line_sub();
			line_type=1;
			break;
			
			
		case 3:
			init_size_line_sub();
			icon_box_line_sub();
			
			glColor3f(0.0, 0.0, 1.0);
			draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
			
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_line_sub+5, i_starty_line_sub+10, i_startx_line_sub+adder_line_sub_x-5, i_starty_line_sub+10, 2.0, 1);
			
			
			i_starty_line_sub-=25;
			icon_box_line_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_line_sub+5, i_starty_line_sub+10, i_startx_line_sub+adder_line_sub_x-5, i_starty_line_sub+10, 2.0, 2);
			
			i_starty_line_sub-=25;
			icon_box_line_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_line_sub+5, i_starty_line_sub+10, i_startx_line_sub+adder_line_sub_x-5, i_starty_line_sub+10, 2.0, 3);
			
			i_starty_line_sub-=25;
			icon_box_line_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_line_sub+5, i_starty_line_sub+10, i_startx_line_sub+adder_line_sub_x-5, i_starty_line_sub+10, 2.0, 4);
			
			init_size_line_sub();
			line_type=1;
			init_size_poly_sub();
			icon_box_poly_sub();
			
			glColor3f(0.0, 0.0, 1.0);
			draw_rect(i_startx_poly_sub+1, i_starty_poly_sub+adder_poly_sub_y, i_startx_poly_sub+adder_poly_sub_x, i_starty_poly_sub+1, 1, 3.0);
			
			
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_poly_sub+5, i_starty_poly_sub+5, i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+5, 2.0, 1);
			lineabs(i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+5, i_startx_poly_sub+(adder_poly_sub_x/1.9), i_starty_poly_sub+adder_poly_sub_y-5, 2.0, 1);
			lineabs(i_startx_poly_sub+(adder_poly_sub_x/1.9), i_starty_poly_sub+adder_poly_sub_y-5, i_startx_poly_sub+5, i_starty_poly_sub+5, 2.0, 1);
			
			
			i_starty_poly_sub-=45;
			icon_box_poly_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_poly_sub+5, i_starty_poly_sub+5, i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+5, 2.0, 1);
			lineabs(i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+5, i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+adder_poly_sub_y-5, 2.0, 1);
			lineabs(i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+adder_poly_sub_y-5, i_startx_poly_sub+5, i_starty_poly_sub+adder_poly_sub_y-5, 2.0, 1);
			lineabs(i_startx_poly_sub+5, i_starty_poly_sub+adder_poly_sub_y-5, i_startx_poly_sub+5, i_starty_poly_sub+5, 2.0, 1);
			
			i_starty_poly_sub-=45;
			icon_box_poly_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_poly_sub+5, i_starty_poly_sub+5, i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+5, 2.0, 1);
			lineabs(i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+5, i_startx_poly_sub+adder_poly_sub_x-10, i_starty_poly_sub+adder_poly_sub_y-5, 2.0, 1);
			lineabs(i_startx_poly_sub+adder_poly_sub_x-10, i_starty_poly_sub+adder_poly_sub_y-5, i_startx_poly_sub+10, i_starty_poly_sub+adder_poly_sub_y-5, 2.0, 1);
			lineabs(i_startx_poly_sub+10, i_starty_poly_sub+adder_poly_sub_y-5, i_startx_poly_sub+5, i_starty_poly_sub+5, 2.0, 1);
			
			i_starty_poly_sub-=45;
			icon_box_poly_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_poly_sub+12, i_starty_poly_sub+5, i_startx_poly_sub+adder_poly_sub_x-12, i_starty_poly_sub+5, 2.0, 1);
			lineabs(i_startx_poly_sub+adder_poly_sub_x-12, i_starty_poly_sub+5, i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+(adder_poly_sub_y/1.7), 2.0, 1);
			lineabs(i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+(adder_poly_sub_y/1.7), i_startx_poly_sub+(adder_poly_sub_x/1.9), i_starty_poly_sub+adder_poly_sub_y-5, 2.0, 1);
			lineabs(i_startx_poly_sub+(adder_poly_sub_x/1.9), i_starty_poly_sub+adder_poly_sub_y-5, i_startx_poly_sub+6, i_starty_poly_sub+(adder_poly_sub_y/1.7), 2.0, 1);
			lineabs(i_startx_poly_sub+6, i_starty_poly_sub+(adder_poly_sub_y/1.7), i_startx_poly_sub+12, i_starty_poly_sub+5, 2.0, 1);
			
			
			i_starty_poly_sub-=45;
			icon_box_poly_sub();
			glColor3f(0.0, 0.0, 0.0);
			lineabs(i_startx_poly_sub+(adder_poly_sub_x/1.9), i_starty_poly_sub+5, i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+13, 2.0, 1);
			lineabs(i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+13, i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+28, 2.0, 1);
			lineabs(i_startx_poly_sub+adder_poly_sub_x-5, i_starty_poly_sub+28, i_startx_poly_sub+(adder_poly_sub_x/1.9), i_starty_poly_sub+adder_poly_sub_y-5, 2.0, 1);
			lineabs(i_startx_poly_sub+(adder_poly_sub_x/1.9), i_starty_poly_sub+adder_poly_sub_y-5, i_startx_poly_sub+5, i_starty_poly_sub+28, 2.0, 1);
			lineabs(i_startx_poly_sub+5, i_starty_poly_sub+28, i_startx_poly_sub+5, i_starty_poly_sub+13, 2.0, 1);
			lineabs(i_startx_poly_sub+5, i_starty_poly_sub+13, i_startx_poly_sub+(adder_poly_sub_x/1.9), i_starty_poly_sub+5, 2.0, 1);
			
			i_starty_poly_sub-=45;
			icon_box_poly_sub();
			glColor3f(0.0, 0.0, 0.0);
			char_set(i_startx_poly_sub+12, i_starty_poly_sub+10);
			char_gen('N', 24, 17);
			init_size_poly_sub();
			break;
			
		case 4:
			init_size_circle_sub();
			
			i_startx_circle_sub+=0.60*adder_circle_sub_x;
			icon_box_circle_sub();
			
			circle_type=0;
			glColor3f(0.0, 0.0, 0.0);
			draw_circle(i_startx_circle_sub+adder_circle_sub_x/2, i_starty_circle_sub+adder_circle_sub_y/2, adder_circle_sub_x/3, circle_type, 2.0);
			
			glColor3f(0.0, 0.0, 1.0);
			draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 2.0);
			
			
			i_startx_circle_sub-=0.60*adder_circle_sub_x;
			i_starty_circle_sub-=adder_circle_sub_y+10;
			icon_box_circle_sub();
			circle_type=1;
			glColor3f(0.0, 0.0, 0.0);
			draw_circle(i_startx_circle_sub+adder_circle_sub_x/2, i_starty_circle_sub+adder_circle_sub_y/2, adder_circle_sub_x/3, circle_type, 2.0);
			
			
			i_startx_circle_sub+=adder_circle_sub_x+10;
			icon_box_circle_sub();
			circle_type=5;
			glColor3f(0.0, 0.0, 0.0);
			draw_circle(i_startx_circle_sub+adder_circle_sub_x/2, i_starty_circle_sub+adder_circle_sub_y/2, adder_circle_sub_x/3, circle_type, 2.0);
			
			
			
			i_startx_circle_sub-=adder_circle_sub_x+10;
			i_starty_circle_sub-=adder_circle_sub_y+10;
			icon_box_circle_sub();
			circle_type=2;
			glColor3f(0.0, 0.0, 0.0);
			draw_circle(i_startx_circle_sub+adder_circle_sub_x/2, i_starty_circle_sub+adder_circle_sub_y/2, adder_circle_sub_x/3, circle_type, 2.0);
			
			
			i_startx_circle_sub+=adder_circle_sub_x+10;
			icon_box_circle_sub();
			circle_type=6;
			glColor3f(0.0, 0.0, 0.0);
			draw_circle(i_startx_circle_sub+adder_circle_sub_x/2, i_starty_circle_sub+adder_circle_sub_y/2, adder_circle_sub_x/3, circle_type, 2.0);
			
			
			i_startx_circle_sub-=adder_circle_sub_x+10;
			i_starty_circle_sub-=adder_circle_sub_y+10;
			icon_box_circle_sub();
			circle_type=3;
			glColor3f(0.0, 0.0, 0.0);
			draw_circle(i_startx_circle_sub+adder_circle_sub_x/2, i_starty_circle_sub+adder_circle_sub_y/2, adder_circle_sub_x/3, circle_type, 2.0);
			
			i_startx_circle_sub+=adder_circle_sub_x+10;
			icon_box_circle_sub();
			circle_type=7;
			glColor3f(0.0, 0.0, 0.0);
			draw_circle(i_startx_circle_sub+adder_circle_sub_x/2, i_starty_circle_sub+adder_circle_sub_y/2, adder_circle_sub_x/3, circle_type, 2.0);
			
			i_startx_circle_sub-=adder_circle_sub_x+10;
			i_starty_circle_sub-=adder_circle_sub_y+10;
			icon_box_circle_sub();
			circle_type=4;
			glColor3f(0.0, 0.0, 0.0);
			draw_circle(i_startx_circle_sub+adder_circle_sub_x/2, i_starty_circle_sub+adder_circle_sub_y/2, adder_circle_sub_x/3, circle_type, 2.0);
			
			i_startx_circle_sub+=adder_circle_sub_x+10;
			icon_box_circle_sub();
			circle_type=8;
			glColor3f(0.0, 0.0, 0.0);
			draw_circle(i_startx_circle_sub+adder_circle_sub_x/2, i_starty_circle_sub+adder_circle_sub_y/2, adder_circle_sub_x/3, circle_type, 2.0);
			circle_type=0;
			
			break;
			
			
		case 5:
			
			init_size_char_sub();
			glColor3f(1.0, 1.0, 1.0);
			draw_line(i_startx_char_sub+11, i_starty_char_sub+adder_char_sub_y/2+1, i_startx_char_sub+adder_char_sub_x-9, i_starty_char_sub+adder_char_sub_y/2+1, 1, 22.0);
			glColor3f(0.0, 0.0, 0.0);
			char_set(i_startx_char_sub+6, i_starty_char_sub+4);
			char_gen('A',13,8);
			
			glColor3f(0.0, 0.0, 1.0);
			draw_rect(i_startx_char_sub+1, i_starty_char_sub+adder_char_sub_y+1, i_startx_char_sub+adder_char_sub_x, i_starty_char_sub+1, 1, 3.0);
			
			
			i_starty_char_sub-=60;
			i_startx_char_sub-=3;
			adder_char_sub_x+=6;
			adder_char_sub_y+=6;
			glColor3f(1.0, 1.0, 1.0);
			draw_line(i_startx_char_sub+14, i_starty_char_sub+adder_char_sub_y/2+11, i_startx_char_sub+adder_char_sub_x-12, i_starty_char_sub+adder_char_sub_y/2+11, 1, 28.0);
			glColor3f(0.0, 0.0, 0.0);
			char_set(i_startx_char_sub+8, i_starty_char_sub+15);
			char_gen('A', 17,10);
			
			i_starty_char_sub-=60;
			i_startx_char_sub-=3;
			adder_char_sub_x+=2;
			adder_char_sub_y+=6;
			glColor3f(1.0, 1.0, 1.0);
			draw_line(i_startx_char_sub+17, i_starty_char_sub+adder_char_sub_y/2+11, i_startx_char_sub+adder_char_sub_x-12, i_starty_char_sub+adder_char_sub_y/2+11, 1, 33.0);
			glColor3f(0.0, 0.0, 0.0);
			char_set(i_startx_char_sub+9, i_starty_char_sub+13);
			char_gen('A', 24,14);
			
			i_starty_char_sub-=60;
			i_startx_char_sub-=3;
			adder_char_sub_x+=6;
			adder_char_sub_y+=6;
			glColor3f(1.0, 1.0, 1.0);
			draw_line(i_startx_char_sub+20, i_starty_char_sub+adder_char_sub_y/2+11, i_startx_char_sub+adder_char_sub_x-14, i_starty_char_sub+adder_char_sub_y/2+11, 1, 40.0);
			glColor3f(0.0, 0.0, 0.0);
			char_set(i_startx_char_sub+10, i_starty_char_sub+16);
			char_gen('A', 26,18);
			init_size_char_sub();
			break;
			
		case 6:
			glColor3f(0.7, 0.7, 0.7);
			j=0;
			while (create_layer[0][j]!='\0')
			{
				char_set(10+13*j, heightm-80);
				char_gen(create_layer[0][j], 13, 8);
				j++;
			}
			glColor3f(1.0, 1.0, 1.0);
			lineabs(10, heightm-100, 80, heightm-100, 30.0, 1);
			lineabs(20, heightm-140, 60, heightm-140, 25.0, 1);
			lineabs(20, heightm-180, 60, heightm-180, 25.0, 1);
			
			glColor3f(0.0, 0.0, 0.0);
			j=0;
			while (create_layer[1][j]!='\0')
			{
				char_set(13+10*j, heightm-147);
				char_gen(create_layer[1][j], 13, 8);
				j++;
			}
			j=0;
			while (create_layer[2][j]!='\0')
			{
				char_set(17+10*j, heightm-187);
				char_gen(create_layer[2][j], 13, 8);
				j++;
			}
			break;
			
		case 7:
			init_size_trans_sub();
			icon_box_trans_sub();
			
			glColor3f(0.0, 0.0, 0.0);
			j=0;
			while (trans_layer[0][j]!='\0')
			{
				char_set(17+10*j, i_starty_trans_sub-5);
				char_gen(trans_layer[0][j], 13, 8);
				j++;
			}
			i_starty_trans_sub-=adder_trans_sub_y;
			for (k=1; k<=8; k++)
			{
				glColor3f(0.0, 0.0, 0.0);
				icon_box_trans_sub();
				j=0;
				if (k<=6)
				{
					glColor3f(0.7, 0.7, 0.7);
					while (trans_layer[k][j]!='\0')
					{
						char_set(10+10*j, i_starty_trans_sub+20);
						char_gen(trans_layer[k][j], 13, 8);
						j++;
					}
					if (k<=5)
					{
						i_starty_trans_sub-=adder_trans_sub_y;
					}
					else
					{
						i_starty_trans_sub-=adder_trans_sub_y-30;
					}
				}
				else
				{
					glColor3f(0.0, 0.0, 0.0);
					while (trans_layer[k][j]!='\0')
					{
						char_set(10+10*j, i_starty_trans_sub-10);
						char_gen(trans_layer[k][j], 13, 8);
						j++;
					}
					i_starty_trans_sub-=adder_trans_sub_y-30;
				}
			}
			init_size_trans_sub();
			break;
			
		case 8:
			init_size_trans_sub();
			icon_box_trans_sub();
			glColor3f(0.0, 0.0, 0.0);
			j=0;
			while (trans_layer[0][j]!='\0')
			{
				char_set(17+10*j, i_starty_trans_sub-5);
				char_gen(trans_layer[0][j], 13, 8);
				j++;
			}
			i_starty_trans_sub-=adder_trans_sub_y;
			icon_box_trans_sub();
			glColor3f(0.0, 0.0, 0.0);
			j=0;
			while (del_layer[0][j]!='\0')
			{
				char_set(17+10*j, i_starty_trans_sub-5);
				char_gen(del_layer[0][j], 13, 8);
				j++;
			}
			break;

		case 9:
			zoom_in();
			break;
		
		case 10:
			zoom_out();
			break;

		case 11:
			undo();
			break;

		case 12:
			redo();
			break;
	
		case 13:
			temp.x=0;
			temp.y=0;
			break;
			
		case 14:
			init_size_trans_sub();

			glColor3f(0.7, 0.7, 0.7);
			k=0;
			while (grid[0][k]!='\0')
			{
				char_set(10+11*k, i_starty_trans_sub+25);
				char_gen(grid[0][k], 13, 8);
				k++;
			}
			
			glColor3f(0.0, 0.0, 0.0);
			for (j=1; j<=2; j++)
			{
				icon_box_trans_sub();
				glColor3f(0.0, 0.0, 0.0);
				k=0;
				while (grid[j][k]!='\0')
				{
					char_set(12+9*k, i_starty_trans_sub-5);
					char_gen(grid[j][k], 13, 8);
					k++;
				}
				i_starty_trans_sub-=adder_trans_sub_y;
			}
			init_size_trans_sub();
			
			grid_clicked++;
			if (grid_clicked%2==0)
			{
				grid_flag=1;
			}
			else
			{
				grid_flag=0;
			}
			rePaint();

			break;

		case 15:
			init_size_trans_sub();
			glColor3f(0.0, 0.0, 0.0);
			for (j=0; j<=1; j++)
			{
				icon_box_trans_sub();
				glColor3f(0.0, 0.0, 0.0);
				k=0;
				while (menu[j][k]!='\0')
				{
					char_set(17+13*k, i_starty_trans_sub-5);
					char_gen(menu[j][k], 13, 8);
					k++;
				}
				i_starty_trans_sub-=adder_trans_sub_y;
			}
			init_size_trans_sub();
			break;
	
		case 16:
			init_size_trans_sub();
			glColor3f(0.0, 0.0, 0.0);
			for (j=0; j<=1; j++)
			{
				icon_box_trans_sub();
				glColor3f(0.0, 0.0, 0.0);
				k=0;
				while (sel[j][k]!='\0')
				{
					char_set(14+12*k, i_starty_trans_sub-5);
					char_gen(sel[j][k], 13, 8);
					k++;
				}
				i_starty_trans_sub-=adder_trans_sub_y;
			}
			init_size_trans_sub();
			break;

			
		case 18:
			init_size_trans_sub();
			glColor3f(0.0, 0.0, 0.0);
			for (j=0; j<=1; j++)
			{
				icon_box_trans_sub();
				glColor3f(0.0, 0.0, 0.0);
				k=0;
				while (view[j][k]!='\0')
				{
					char_set(17+12*k, i_starty_trans_sub-5);
					char_gen(view[j][k], 13, 8);
					k++;
				}
				i_starty_trans_sub-=adder_trans_sub_y;
			}
			init_size_trans_sub();
			break;

		case 19:
			init_size_trans_sub();
			glColor3f(0.0, 0.0, 0.0);
			for (j=0; j<=2; j++)
			{
				icon_box_trans_sub();
				glColor3f(0.0, 0.0, 0.0);
				k=0;
				while (anim[j][k]!='\0')
				{
					char_set(17+12*k, i_starty_trans_sub-5);
					char_gen(anim[j][k], 13, 8);
					k++;
				}
				i_starty_trans_sub-=adder_trans_sub_y;
			}
			init_size_trans_sub();
			init_store_anim();
			break;
			
		case 20:
			glutSetWindow(draw_window);

			example=1;
			/*shift=head;
			shift->size=3.0;
			for (j=0; j<=12; j++)
			{
				
			}
			df_wr();*/
			
			
			//rePaint();
			break;

			
		default:
			break;
	}
	
	glFlush();	
}



void myMouse_draw_window (int button, int state, int x, int y)
{
	int in;
	
	float xd,yd,i,xd1,t,difx,dify;
	
	glutSetWindow(draw_window);
	x=glutGet(GLUT_WINDOW_X)+x;
	y=glutGet(GLUT_WINDOW_HEIGHT)-y;
	
	if (allign==1)
	{
		normalize(x, y);
		xd1=0.02;
		for (i=1; i<=50; i++)
		{
			if (xnor>xd1-0.02 && xnor<=xd1)
			{
				xd=xd1-xnor;
				
				if (xd<=0.01) 
				{
					xnor=xd1;
				}
				else
				{
					xnor=xd1-0.02;
				}
			}
			if (ynor>xd1-0.02 && ynor<=xd1)
			{
				
				yd=xd1-ynor;
				
				if (yd<=0.01) 
				{
					ynor=xd1;
				}
				else
				{
					ynor=xd1-0.02;
				}
			}
			xd1+=0.02;
		}
		
		rev_normalize(xnor, ynor);
		x=xrnor;
		y=yrnor;
	}
	
	
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		if (lay[selected].rot_arbit==1)
		{
			lay[selected].x=x;
			lay[selected].y=y;
		}
		
		glColor3f(obj[color_no].r, obj[color_no].g, obj[color_no].b);
		
		if (line_type!=2 && line_type!=3 && line_type!=4)
		{
			line_type=1;
		}	
		
		CP.x=x;
		CP.y=y;
		switch (check) 
		{
			case 1:
				
				if (temp.x!=0)
				{
					lineabs(temp.x, temp.y, CP.x, CP.y, 1.0, line_type);
					active_write(1, temp.x, temp.y, CP.x, CP.y, -1, -1, line_type, -1, -1, 1.0);
					pass.x=0;
				}

				temp.x=CP.x;
				temp.y=CP.y;

				break;
				
				
			case 2:
				temp.x=CP.x;
				temp.y=CP.y;
				active_write(2, temp.x, temp.y, -1, -1, -1, -1, 1, -1, -1, 1.0);
				break;
				
			case 3:
				if (no_vertex==-1)
				{
					if (temp.x==0) 
					{
						init.x=CP.x;
						init.y=CP.y;
						temp.x=CP.x;
						temp.y=CP.y;
						in=1;
					}
					
					if (first==1)
					{
						active_write(check, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
						first=0;
					}
					
					lineabs(temp.x, temp.y, CP.x, CP.y, 1.0, line_type);
					if (in!=1)
					{
						active_write(1, temp.x, temp.y, CP.x, CP.y, -1, -1, line_type, -1, -1, 1.0);
						in=0;
					}
					temp.x=CP.x;
					temp.y=CP.y;

				}
				else
				{
					if (no_vertex==2)
					{
						if (no==1) 
						{
							draw_rect(temp.x, temp.y, x, y, line_type, 1.0);
							active_write(3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
							active_write(1, temp.x, temp.y, x, temp.y, -1, -1, line_type, -1, -1, 1.0);
							active_write(1, x, temp.y, x, y, -1, -1, line_type, -1, -1, 1.0);
							active_write(1, x, y, temp.x, y, -1, -1, line_type, -1, -1, 1.0);
							active_write(1, temp.x, y, temp.x, temp.y, -1, -1, line_type, -1, -1, 1.0);
							active_write(3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
							no=no_vertex;
							pass.x=0;
							temp.x=0;
							break;
						}
						temp.x=x;
						temp.y=y;
						no--;
						break;
					}
					
					if (first==1)
					{
						active_write(check, -1, -1, -1, -1, -1, -1, -1, no_vertex, -1, -1);
						first=0;
					}
					
					
					if (temp.x==0) 
					{
						init.x=CP.x;
						init.y=CP.y;
						temp.x=CP.x;
						temp.y=CP.y;
						in=1;
					}
					no--;
					
					lineabs(temp.x, temp.y, CP.x, CP.y, 1.0, line_type);
					if (in!=1)
					{
						active_write(1, temp.x, temp.y, CP.x, CP.y, -1, -1, line_type, -1, -1, 1.0);
						in=0;
					}
					
					temp.x=CP.x;
					temp.y=CP.y;
					if (no==0)
					{
						lineabs(CP.x, CP.y, init.x, init.y, 1.0, line_type);
						active_write(1, CP.x, CP.y, init.x, init.y, -1, -1, line_type, -1, -1, 1.0);
						active_write(3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
						no=no_vertex;
						temp.x=0;
						temp.y=0;
						first=1;
						pass.x=0;
					}
					
				}
				break;
				
			case 4:
				if (rad==0) 
				{
					temp.x=x;
					temp.y=y;
					rad=1;
					break;
				}
				
				if (x<temp.x) 
				{
					rx=temp.x-x;
				}
				else
				{
					rx=x-temp.x;
				}
				
				if (y<temp.y)
				{
					ry=temp.y-y;
				}
				else
				{
					ry=y-temp.y;
				}
				
				r=sqrt(pow(rx, 2)+pow(ry, 2));
				draw_circle(temp.x, temp.y, r, circle_type, 1.0);
				active_write(check, -1, -1, -1, -1, temp.x, temp.y, -1, r, circle_type, 1.0);
				pass.x=0;
				rad=0;
				break;
				
			case 5:
				chCP.x=x;
				chCP.y=y-h/2;
				mous.x=x;
				mous.y=y-h/2;
				count=0;
				break;
				
			case 16:
				glutDestroyWindow(pop_window);
				//rePaint();
				store_pt.x=x;
				store_pt.y=y;
				normalize(x, y);
				if (hold==0)
				{
					select(xnor,ynor);
				}
				break;
				
			case 17:
				if (temp.x==0)
				{
					temp.x=x;
					temp.y=y;
				}
				else
				{
					
					/*xwmin=x;
					ywmin=y;
					xwmax=temp.x;
					ywmax=temp.y;*/
					
					normalize(x, y);
					xwmin=xnor;
					ywmin=ynor;
					normalize(temp.x, temp.y);
					xwmax=xnor;
					ywmax=ynor;
					
					if (xwmin>xwmax) 
					{
						t=xwmax;
						xwmax=xwmin;
						xwmin=t;
					}
					if (ywmin>ywmax)
					{
						t=ywmax;
						ywmax=ywmin;
						ywmin=t;
					}
					
					shift1=head;
					prevp2=NULL;
					while (shift1!=NULL)
					{
						switch (shift1->op)
						{
							case 1:
								clip();
								if (prevp2!=NULL && clipped==1)
								{
									prevp1=head;
									
									if (prevp2==head)
									{
										head=head->next;
									}
									else
									{
										while (prevp1->next!=prevp2)
										{
											prevp1=prevp1->next;
										}
										prevp1->next=prevp2->next;
									}
									
									while (prevp1->next->op!=3)
									{
										prevp1=prevp1->next;
									}
									prevp1->next=prevp1->next->next;
									prevp2=NULL;
								}
								
								break;
								
							case 3:
								prevp2=shift1;
								break;

							default:
								break;
						}
						
						shift1=shift1->next;
					}
					df_wr();
					rePaint();
					rev_normalize(xwmin, ywmin);
					x=xrnor;y=yrnor;
					rev_normalize(xwmax, ywmax);
					
					glColor3f(0.9, 0.9, 0.9);
					draw_rect(x, y, xrnor, yrnor, 1, 2.0);
					temp.x=0;
				}
				break;
				
			case 18:
				if (move==1)
				{
					if (temp.x==0)
					{
						temp.x=x;
						temp.y=y;
					}
					else
					{
						//glClear(GL_COLOR_BUFFER_BIT);
						glColor3f(0.9, 0.9, 0.9);
						draw_rect(temp.x, temp.y, x, y, 1, 2.0);
						
						normalize(temp.x, y);
						difx=xnor-xwmin;
						dify=ynor-ywmin;
						printf("\n%f %f",difx,dify);
						
						normalize(x, y);
						xwmin=xnor;
						ywmin=ynor;
						normalize(temp.x, temp.y);
						xwmax=xnor;
						ywmax=ynor;
						
						if (xwmin>xwmax) 
						{
							t=xwmax;
							xwmax=xwmin;
							xwmin=t;
						}
						if (ywmin>ywmax)
						{
							t=ywmax;
							ywmax=ywmin;
							ywmin=t;
						}
						
						
						for (i=0; i<=layer_name_index; i++)
						{
							selected=i;
							init_seg();
							lay[selected].tx=difx;
							lay[selected].ty=dify;
							
							animate();
							
						}
						
						
						shift1=head;
						prevp2=NULL;
						while (shift1!=NULL)
						{
							switch (shift1->op)
							{
								case 1:
									clip();
									if (prevp2!=NULL && clipped==1)
									{
										prevp1=head;
										
										if (prevp2==head)
										{
											head=head->next;
										}
										else
										{
											while (prevp1->next!=prevp2)
											{
												prevp1=prevp1->next;
											}
											prevp1->next=prevp2->next;
										}
										
										while (prevp1->next->op!=3)
										{
											prevp1=prevp1->next;
										}
										prevp1->next=prevp1->next->next;
										prevp2=NULL;
									}
									
									break;
									
								case 3:
									prevp2=shift1;
									break;
									
								default:
									break;
							}
							
							shift1=shift1->next;
						}
						df_wr();
						rePaint();
						rev_normalize(xwmin, ywmin);
						x=xrnor;y=yrnor;
						rev_normalize(xwmax, ywmax);
						glColor3f(0.9, 0.9, 0.9);
						draw_rect(x, y, xrnor, yrnor, 1, 2.0);
						temp.x=0;
						
					}

				}
				break;
	
			case 19:
				/*store_pt.x=x;
				store_pt.y=y;
				normalize(x, y);
				select(xnor, ynor);

				if (flag_scale==1 && found_img==1)
				{
					shift=head;
					img_anim_index=0;
					while (shift!=store)
					{
						shift=shift->next;
						img_anim_index++;
					}
					printf("\n%d",store->op);
				}*/
				if (anim_arbit==1)
				{
					anim_arbit_pt.x=x;
					anim_arbit_pt.y=y;
				}
				
				break;

			default:
				break;
		}
		
		if (check==1 || check==3 || check==4)
		{
			print_no(x, y);
		}
		else
		{
			glutSetWindow(status_window);
			glColor3f(0.0, 0.0, 0.0);
			draw_line(110, heightm-50, 240, heightm-50, 1, 20.0);
		}
	}
	
	
	if (button==GLUT_RIGHT_BUTTON && state==GLUT_DOWN)
	{
		switch (check)
		{
			case 1:
				temp.x=x;
				temp.y=y;
				break;
				
			case 3:
				if (no_vertex==-1 && init.x !=0)
				{
					lineabs(temp.x, temp.y, init.x, init.y, 1.0, line_type);
					active_write(1, temp.x, temp.y, init.x, init.y, -1, -1, line_type, -1, -1, 1.0);
					active_write(3, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1);
					no=no_vertex;
					temp.x=0;
					temp.y=0;
					init.x=0;
					first=1;
				}
				break;
				
			case 16:
				//rePaint();
				glutDestroyWindow(pop_window);
				
				pop_x=x;
				pop_y=heightm-y+40;

				if (pop_y>=heightm-150)
				{
					pop_y-=150;
				}
				glutInitWindowPosition(pop_x, pop_y);
				glutInitWindowSize(100, 150);
				pop_window=glutCreateWindow("menu");
				//pop_window=glutCreateSubWindow(main_window, pop_x, pop_y, 100, 150);
				init_pop();
				glutDisplayFunc(display_pop);
				glutMouseFunc(myMouse_pop_window);
				glutPassiveMotionFunc(myMouse_pop_window_over);
				break;
	
			default:
				break;
		}
	}
	glFlush();

}



void myMouse_tools_window (int button, int state, int x, int y)
{
	int j;
	//glutDestroyWindow(pop_window);
	if (store_index>0 && hold==0)
	{
		deselect();
		glutSetWindow(tools_window);
	}
	
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		
		if (check!=0)
		{
			glColor3f(0.7, 0.7, 0.7);
			draw_rect(i_startx+2, i_starty+3, i_startx+adder-3, i_starty+adder-4, 1, 3.0);
		}
			
		
		
		init_size();
		glColor3f(0.0, 0.0, 1.0);
		
		for (j=1; j<=20; j++)
		{
			if ((x<i_startx+adder)&&(x>i_startx))
			{
				draw_rect(i_startx+2, i_starty+3, i_startx+adder-3, i_starty+adder-4, 1, 3.0);
				create_sub_window(j);
				check=j;
				break;
			}
			else
			{
				i_startx+=adder+5;
			}

		}
		
		col_clicked=0;	
		int k=widthm+150; 
		
		glColor3f(0.5, 0.5, 0.5);
		draw_rect(col_x-35, col_y,col_x-20, col_y-17, 1, 2.0);
		
		int t=col_startx;
		
		for (j=0; j<=13; j++)
		{
			if (heightm-y>i_starty && heightm-y<i_starty+20)
			{
				if (x>k-col_startx-35 && x<k-col_startx-20)
				{
					color_no=7+j;
					if (color_no==13)
					{
						glColor3f(0.0, 0.0, 0.0);
					}
					else
					{
						glColor3f(1.0, 1.0, 1.0);
					}
					draw_rect(k-col_startx-35, i_starty+14, k-col_startx-20, i_starty-3, 1, 2.0);
					col_x=k-col_startx;
					col_y=i_starty+14;
					col_clicked=1;
					check=0;
					create_sub_window(0);
					break;
				}
				else
				{
					col_startx-=20;
				}
				
			}
			if (heightm-y>i_starty+20 && heightm-y<i_starty+40)
			{
				if (x>k-col_startx-35 && x<k-col_startx-20)
				{
					color_no=j;
					glColor3f(1.0, 1.0, 1.0);
					draw_rect(k-col_startx-35, i_starty+34, k-col_startx-20, i_starty+17, 1, 2.0);
					col_x=k-col_startx;
					col_y=i_starty+34;
					col_clicked=1;
					check=0;
					create_sub_window(0);
					break;
				}
				else
				{
					col_startx-=20;
				}
			}
		}
		
		col_startx=t;
	
		no_vertex=3;
		no=no_vertex;
		line_type=0xffff;
		temp.x=0;
		temp.y=0;
		count=0;
		
		glutSetWindow(status_window);
		glColor3f(0.0, 0.0, 0.0);
		draw_line(400, heightm-50, 525, heightm-50, 1, 20.0);
		glColor3f(1.0, 0.0, 0.0);
		j=0;
		if (check!=0)
		{
			while (icons[check][j]!='\0')
			{
				draw_char(icons[check][j], 14, 9, 400+j*10, heightm-57);
				j++;
			}
		}
		if (check==0)
		{
			
		}
		glColor3f(0.0, 0.0, 0.0);
		
	}
	glFlush();

}



void myMouse_layer_warning(int button, int state, int x, int y)
{
	
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		x+=startx_layer;
		y=starty_layer+heightl-y;
		if (x>widthm/2+65 && x<widthm/2+140 && y<starty_layer+50 && y>starty_layer+15)
		{
			glColor3f(0.0, 0.0, 1.0);
			draw_rect(widthm/2+65, starty_layer-5, widthm/2+140, starty_layer-35, 1, 2.0);
			glutDestroyWindow(war1_window);
			war=0;
		}
		
	}
	glFlush();	
}


void myMouse_layer_window(int button, int state, int x, int y)
{
	
    if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {

		if (fail == 0)
		{
			glColor3f(1.0, 1.0, 1.0);
			draw_rect(startx-30, starty-15, startx+adderx, starty+15, 1, 2.0);
		}
	
		init_size_layer_window();
		glColor3f(0.0, 0.0, 1.0);
		int j;
		x+=startx_layer;
		y=starty_layer+heightl-y;
		
		for (selected=0; selected<=layer_name_index; selected++)
		{
			if (x>startx-30 && x<startx+adderx && y>starty+30 && y<starty+70)
			{
				draw_rect(startx-30, starty-15, startx+adderx, starty+15, 1, 2.0);
				fail=0;
				temp_layer=selected;
				prob=0;
				break;
			}
			else
			{
				startx+=adderx+50;
				fail=1;
			}
			if (startx>widthm/2+100)
			{
				init_size_layer_window();
				starty-=addery+10;
			}

		}
		
		if (x>widthm/2+65 && x<widthm/2+140 && y<starty_layer+50 && y>starty_layer+15)
		{
			glColor3f(0.0, 0.0, 1.0);
			draw_rect(widthm/2+65, starty_layer-5, widthm/2+140, starty_layer-35, 1, 2.0);
			prob=1;
			glutDestroyWindow(layer_window);
			selected=temp_layer;
			flag_insert=1;
			flag_started=0;
			if (selected!=0 && start[selected+1]!=NULL)
			{
				end[selected]->next=start[selected+1];
			}
			
			ard=end[selected];			
		}
		
		if (prob!=1)
		{
			glutSetWindow(status_window);
			glColor3f(0.0, 0.0, 0.0);
			draw_line(700, heightm-50, 790, heightm-50, 1, 20.0);
			
			glColor3f(1.0, 0.0, 0.0);
			j=0;
			while (lay[selected].layer_name[j]!='\0')
			{
				draw_char(lay[selected].layer_name[j], 13, 8, 700+10*j, heightm-57);
				j++;
			}
		}	
    }  
	glFlush();
}


void myMouse_file_window (int button, int state, int x, int y)
{
	int j;
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		x+=startx_layer;
		y=starty_layer+heightl-y;
		glColor3f(0.0, 0.0, 1.0);
		if (x>widthm/2+65 && x<widthm/2+140 && y<starty_layer+50 && y>starty_layer+15)
		{
			draw_rect(widthm/2+65, starty_layer-5, widthm/2+140, starty_layer-35, 1, 2.0);
			glutDestroyWindow(file_window);
			strcat(file_name,".df");
			if (openf==1)
			{
				rePaint();
			}
			//main_window=glutCreateWindow(file_name);

		}
		init_size_layer_window();
		startx+=140;
		glColor3f(0.0, 0.0, 1.0);
		if (x>startx-30 && x<startx+adderx && y>starty+30 && y<starty+70)
		{
			draw_rect(startx-30, starty-15, startx+adderx, starty+15, 1, 2.0);
			chCP.x=startx-25;
			chCP.y=starty-5;
			mous.x=chCP.x;
			mous.y=chCP.y;
			file_name_index=0;
			count=0;
			j=0;
			while (file_name[j]!='\0')
			{
				file_name[j]='\0';
				j++;
			}
		}
	}
	glFlush();
}



void myMouse_sub_window (int button, int state, int x, int y)
{
	int j,k,flag,l;
	
	if (button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		y=heightm-60-y;
		switch (check)
		{
			case 1:
				
				glColor3f(1.0, 1.0, 1.0);
				
				draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y-1, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+2, 1, 3.0);
				
				init_size_line_sub();
				glColor3f(0.0, 0.0, 1.0);
				
				if (y<i_starty_line_sub+adder_line_sub_y && y>i_starty_line_sub)
				{
					draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
					line_type=1;
				}
				else
				{
					i_starty_line_sub-=25;
					if (y<i_starty_line_sub+adder_line_sub_y && y>i_starty_line_sub)
					{
						draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
						line_type=2;
					}
					
					else 
					{
						i_starty_line_sub-=25;
						if (y<i_starty_line_sub+adder_line_sub_y && y>i_starty_line_sub)
						{
							draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
							line_type=3;
						}
						else 
						{
							i_starty_line_sub-=25;
							if (y<i_starty_line_sub+adder_line_sub_y && y>i_starty_line_sub)
							{
								draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
								line_type=4;
							}
						}
					}
				}
				break;
				
			case 3:
				if (y>i_maxy) 
				{
					glColor3f(1.0, 1.0, 1.0);
					
					draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
					
					
					init_size_line_sub();
					glColor3f(0.0, 0.0, 1.0);
					
					if (y<i_starty_line_sub+adder_line_sub_y && y>i_starty_line_sub)
					{
						draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
						line_type=1;
					}
					else
					{
						i_starty_line_sub-=25;
						if (y<i_starty_line_sub+adder_line_sub_y && y>i_starty_line_sub)
						{
							draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
							line_type=2;
						}
						
						else 
						{
							i_starty_line_sub-=25;
							if (y<i_starty_line_sub+adder_line_sub_y && y>i_starty_line_sub)
							{
								draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
								line_type=3;
							}
							else 
							{
								i_starty_line_sub-=25;
								if (y<i_starty_line_sub+adder_line_sub_y && y>i_starty_line_sub)
								{
									draw_rect(i_startx_line_sub, i_starty_line_sub+adder_line_sub_y, i_startx_line_sub+adder_line_sub_x+3, i_starty_line_sub+1, 1, 3.0);
									line_type=4;
								}
							}
						}
						
					}
				}
				else
				{
					glColor3f(1.0, 1.0, 1.0);
					draw_rect(i_startx_poly_sub+1, i_starty_poly_sub+adder_poly_sub_y, i_startx_poly_sub+adder_poly_sub_x, i_starty_poly_sub+1,1, 3.0);
					
					init_size_poly_sub();
					glColor3f(0.0, 0.0, 1.0);
					if (y<i_starty_poly_sub+adder_poly_sub_y && y>i_starty_poly_sub)
					{
						draw_rect(i_startx_poly_sub+1, i_starty_poly_sub+adder_poly_sub_y, i_startx_poly_sub+adder_poly_sub_x, i_starty_poly_sub+1,1, 3.0);
						no_vertex=3;
					}
					else 
					{
						i_starty_poly_sub-=45;
						if (y<i_starty_poly_sub+adder_poly_sub_y && y>i_starty_poly_sub)
						{
							draw_rect(i_startx_poly_sub+1, i_starty_poly_sub+adder_poly_sub_y, i_startx_poly_sub+adder_poly_sub_x, i_starty_poly_sub+1,1, 3.0);
							no_vertex=2;
						}
						else
						{
							i_starty_poly_sub-=45;
							if (y<i_starty_poly_sub+adder_poly_sub_y && y>i_starty_poly_sub)
							{
								draw_rect(i_startx_poly_sub+1, i_starty_poly_sub+adder_poly_sub_y, i_startx_poly_sub+adder_poly_sub_x, i_starty_poly_sub+1,1, 3.0);
								no_vertex=4;
							}
							else
							{
								i_starty_poly_sub-=45;
								if (y<i_starty_poly_sub+adder_poly_sub_y && y>i_starty_poly_sub)
								{
									draw_rect(i_startx_poly_sub+1, i_starty_poly_sub+adder_poly_sub_y, i_startx_poly_sub+adder_poly_sub_x, i_starty_poly_sub+1,1, 3.0);
									no_vertex=5;
								}
								
								else 
								{
									i_starty_poly_sub-=45;
									if (y<i_starty_poly_sub+adder_poly_sub_y && y>i_starty_poly_sub)
									{
										draw_rect(i_startx_poly_sub+1, i_starty_poly_sub+adder_poly_sub_y, i_startx_poly_sub+adder_poly_sub_x, i_starty_poly_sub+1,1, 3.0);
										no_vertex=6;
									}
									else
									{
										i_starty_poly_sub-=45;
										if (y<i_starty_poly_sub+adder_poly_sub_y && y>i_starty_poly_sub)
										{
											draw_rect(i_startx_poly_sub+1, i_starty_poly_sub+adder_poly_sub_y, i_startx_poly_sub+adder_poly_sub_x, i_starty_poly_sub+1,1, 3.0);
											no_vertex=-1;
										}
									}
								}
							}
						}
					}
					
					no=no_vertex;
					temp.x=0;
					temp.y=0;
					
				}
				break;
				
				
			case 4:
				if (circle_type==0)
				{
					init_size_circle_sub();
					i_startx_circle_sub+=0.60*adder_circle_sub_x;
					glColor3f(0.0, 0.0, 0.0);
					draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
				}
				else  
				{
					glColor3f(0.0, 0.0, 0.0);
					draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
				}
				
				init_size_circle_sub();
				i_startx_circle_sub+=0.60*adder_circle_sub_x;
				if ((y>i_starty_circle_sub && y<i_starty_circle_sub+adder_circle_sub_y)&&(x>i_startx_circle_sub && x<i_startx_circle_sub+adder_circle_sub_x))
				{
					glColor3f(0.0, 0.0, 1.0);
					draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
					circle_type=0;
				}
				else
				{
					i_startx_circle_sub-=0.60*adder_circle_sub_x;
					i_starty_circle_sub-=adder_circle_sub_y+10;
					if ((y>i_starty_circle_sub && y<i_starty_circle_sub+adder_circle_sub_y)&&(x>i_startx_circle_sub && x<i_startx_circle_sub+adder_circle_sub_x)) 
					{
						glColor3f(0.0, 0.0, 1.0);
						draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
						circle_type=1;
					}
					else
					{
						i_startx_circle_sub+=adder_circle_sub_x+10;
						if ((y>i_starty_circle_sub && y<i_starty_circle_sub+adder_circle_sub_y)&&(x>i_startx_circle_sub && x<i_startx_circle_sub+adder_circle_sub_x)) 
						{
							glColor3f(0.0, 0.0, 1.0);
							draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
							circle_type=5;
						}
						
						else
						{
							i_startx_circle_sub-=adder_circle_sub_x+10;
							i_starty_circle_sub-=adder_circle_sub_y+10;
							if ((y>i_starty_circle_sub && y<i_starty_circle_sub+adder_circle_sub_y)&&(x>i_startx_circle_sub && x<i_startx_circle_sub+adder_circle_sub_x)) 
							{
								glColor3f(0.0, 0.0, 1.0);
								draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
								circle_type=2;
							}
							else 
							{
								i_startx_circle_sub+=adder_circle_sub_x+10;
								if ((y>i_starty_circle_sub && y<i_starty_circle_sub+adder_circle_sub_y)&&(x>i_startx_circle_sub && x<i_startx_circle_sub+adder_circle_sub_x)) 
								{
									glColor3f(0.0, 0.0, 1.0);
									draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
									circle_type=6;
								}
								else 
								{
									i_startx_circle_sub-=adder_circle_sub_x+10;
									i_starty_circle_sub-=adder_circle_sub_y+10;
									if ((y>i_starty_circle_sub && y<i_starty_circle_sub+adder_circle_sub_y)&&(x>i_startx_circle_sub && x<i_startx_circle_sub+adder_circle_sub_x)) 
									{
										glColor3f(0.0, 0.0, 1.0);
										draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
										circle_type=3;
									}
									else
									{
										i_startx_circle_sub+=adder_circle_sub_x+10;
										if ((y>i_starty_circle_sub && y<i_starty_circle_sub+adder_circle_sub_y)&&(x>i_startx_circle_sub && x<i_startx_circle_sub+adder_circle_sub_x)) 
										{
											glColor3f(0.0, 0.0, 1.0);
											draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
											circle_type=7;
										}
										else 
										{
											i_startx_circle_sub-=adder_circle_sub_x+10;
											i_starty_circle_sub-=adder_circle_sub_y+10;
											if ((y>i_starty_circle_sub && y<i_starty_circle_sub+adder_circle_sub_y)&&(x>i_startx_circle_sub && x<i_startx_circle_sub+adder_circle_sub_x)) 
											{
												glColor3f(0.0, 0.0, 1.0);
												draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
												circle_type=4;
											}
											else 
											{
												i_startx_circle_sub+=adder_circle_sub_x+10;
												if ((y>i_starty_circle_sub && y<i_starty_circle_sub+adder_circle_sub_y)&&(x>i_startx_circle_sub && x<i_startx_circle_sub+adder_circle_sub_x)) 
												{
													glColor3f(0.0, 0.0, 1.0);
													draw_rect(i_startx_circle_sub+1, i_starty_circle_sub+adder_circle_sub_y, i_startx_circle_sub+adder_circle_sub_x, i_starty_circle_sub+1, 1, 3.0);
													circle_type=8;
												}
											}
										}
									}
								}
							}
						}
					}
				}
				break;
				
				
			case 5:
				
				glColor3f(1.0, 1.0, 1.0);
				draw_rect(i_startx_char_sub+1, i_starty_char_sub+adder_char_sub_y, i_startx_char_sub+adder_char_sub_x, i_starty_char_sub+1, 1, 3.0);
				
				
				init_size_char_sub();
				glColor3f(0.0, 0.0, 1.0);
				if (y<i_starty_char_sub+adder_char_sub_y && y>i_starty_char_sub)
				{
					draw_rect(i_startx_char_sub+1, i_starty_char_sub+adder_char_sub_y, i_startx_char_sub+adder_char_sub_x, i_starty_char_sub+1, 1, 3.0);
					h=13;
					w=8;
				}
				else 
				{
					i_starty_char_sub-=50;
					i_startx_char_sub-=3;
					adder_char_sub_x+=6;
					adder_char_sub_y+=6;
					
					if (y<i_starty_char_sub+adder_char_sub_y && y>i_starty_char_sub)
					{
						draw_rect(i_startx_char_sub+1, i_starty_char_sub+adder_char_sub_y, i_startx_char_sub+adder_char_sub_x, i_starty_char_sub+1, 1, 3.0);
						h=17;
						w=10;
					}
					else
					{
						i_starty_char_sub-=60;
						i_startx_char_sub-=3;
						adder_char_sub_x+=6;
						adder_char_sub_y+=6;
						if (y<i_starty_char_sub+adder_char_sub_y && y>i_starty_char_sub)
						{
							draw_rect(i_startx_char_sub+1, i_starty_char_sub+adder_char_sub_y, i_startx_char_sub+adder_char_sub_x, i_starty_char_sub+1, 1, 3.0);
							h=24;
							w=14;
						}
						
						else 
						{
							i_starty_char_sub-=60;
							i_startx_char_sub-=3;
							adder_char_sub_x+=6;
							adder_char_sub_y+=6;
							if (y<i_starty_char_sub+adder_char_sub_y && y>i_starty_char_sub)
							{
								draw_rect(i_startx_char_sub+1, i_starty_char_sub+adder_char_sub_y, i_startx_char_sub+adder_char_sub_x, i_starty_char_sub+1, 1, 3.0);
								h=32;
								w=18;
							}
						}
					}
				}
				
				break;
				
			case 6:
				
				if (y<heightm-85 && y>heightm-115) 
				{
					glColor3f(1.0, 1.0, 1.0);
					draw_rect(9, heightm-128, 73, heightm-152, 1, 2.0);
					draw_rect(9, heightm-168, 73, heightm-192, 1, 2.0);
					lineabs(10, heightm-100, 80, heightm-100, 30.0, 1);
					glColor3f(0.0, 0.0, 1.0);
					draw_rect(1, heightm-115, 95, heightm-85, 1, 2.0);
					
					index2=0;
					layer_check=1;
					chCP.x=5;
					chCP.y=heightm-110;
					mous.x=5;
					mous.y=heightm-110;
					count=0;
					layer_name_index++;
				}
				else
				{
					if (y<heightm-128 && y>heightm-152)
					{
						glColor3f(1.0, 1.0, 1.0);
						draw_rect(1, heightm-115, 95, heightm-85, 1, 2.0);
						draw_rect(9, heightm-168, 73, heightm-192, 1, 2.0);
						glColor3f(0.0, 0.0, 1.0);
						draw_rect(9, heightm-128, 73, heightm-152, 1, 2.0);
						layer_check=2;
						
						create_sub_window(6);
						j=0;
						while (j<=layer_name_index-1)
						{
							
							k=strcmp(lay[j].layer_name, lay[layer_name_index].layer_name);
							if (k==0)
							{
								war_lay=j;
								glutInitWindowSize(widthm/2, heightm/2);
								glutInitWindowPosition(200, 200);
								war1_window=glutCreateWindow("Warning");
								init_layer_window();
								glutDisplayFunc(display_layer_war);
								glutMouseFunc(myMouse_layer_warning);
								startx_layer=glutGet(GLUT_WINDOW_X);
								starty_layer=glutGet(GLUT_WINDOW_Y);
								
								l=0;
								while (lay[layer_name_index].layer_name[l]!='\0') 
								{
									lay[layer_name_index].layer_name[l]='\0';
									l++;

								}
								layer_name_index--;
								war=1;
							}
							
							j++;
						}
						if (war == 0)
						{
							glutSetWindow(status_window);
							glColor3f(0.0, 0.0, 0.0);
							draw_line(700, heightm-50, 770, heightm-50, 1, 20.0);
							
							glColor3f(1.0, 0.0, 0.0);
						
							flag_started=1;
							flag_insert=0;
						
							
							selected=layer_name_index;
							
							j=0;
							while (lay[layer_name_index].layer_name[j]!='\0')
							{
								draw_char(lay[layer_name_index].layer_name[j], 13, 8, 700+10*j, heightm-57);
								j++;
								
							}
							glColor3f(0.0, 0.0, 0.0);
							war=0;
							init_seg();
							seg_wr(1);
						}
						
					}
					else
					{
						if (y<heightm-168 && y>heightm-192)
						{
							glColor3f(1.0, 1.0, 1.0);
							draw_rect(1, heightm-115, 95, heightm-85, 1, 2.0);
							draw_rect(9, heightm-128, 73, heightm-152, 1, 2.0);
							lineabs(10, heightm-100, 80, heightm-100, 30.0, 1);
							glColor3f(0.0, 0.0, 1.0);
							draw_rect(9, heightm-168, 73, heightm-192, 1, 2.0);
							if (layer_check==1)
							{
								layer_name_index--;
							}
							
							layer_check=3;
							
						}
						else
						{
							glColor3f(1.0, 1.0, 1.0);
							draw_rect(1, heightm-115, 95, heightm-85, 1, 2.0);
							draw_rect(9, heightm-128, 73, heightm-152, 1, 2.0);
							draw_rect(9, heightm-168, 73, heightm-192, 1, 2.0);
							if (layer_check==1)
							{
								layer_name_index--;
							}
							layer_check=0;
						}
						
					}
					
				}
				
				break;
				
				
			case 7:
				dec=0;
				count_no=0;
				glColor3f(1.0, 1.0, 1.0);
				draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
				
				init_size_trans_sub();
				glColor3f(0.0, 0.0, 1.0);
				
				if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
				{
					
					draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
					
                    glutInitWindowSize(widthm/2, heightm/2);
					glutInitWindowPosition(200, 200);
					layer_window=glutCreateWindow("Select Layer");
					init_layer_window();
					glutDisplayFunc(display_layer_window);
					glutMouseFunc(myMouse_layer_window);
					startx_layer=glutGet(GLUT_WINDOW_X);
					starty_layer=glutGet(GLUT_WINDOW_Y);
					
				}
				else
				{
					for (k=1; k<=6; k++)
					{
						
						i_starty_trans_sub-=adder_trans_sub_y;
						if (y>i_starty_trans_sub-13 && y<i_starty_trans_sub+13)
						{
							icon_box_trans_sub();
							glColor3f(0.0, 0.0, 1.0);
							draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
							trans=k;
							
							if (flag==0)
							{
								glColor3f(1.0, 1.0, 1.0);
								draw_rect(i_startx_trans_sub-14, yt1-10, i_startx_trans_sub+adder_trans_sub_x+14, yt2, 1, 2.0);
							}
							flag=1;
							
							break;
						}
						flag=0;
						
					}
					
					chCP.x=10;
					chCP.y=i_starty_trans_sub-5;
					mous.x=10;
					mous.y=i_starty_trans_sub-5;
					count=0;
					
					if (trans==4)
					{
						lay[selected].rot_arbit=1;
					}

					
				}

				
				if (flag!=1)
				{
					glColor3f(1.0, 1.0, 1.0);
					draw_rect(i_startx_trans_sub-14, yt1-10, i_startx_trans_sub+adder_trans_sub_x+14, yt2, 1, 2.0);
					
					yt1=i_starty_trans_sub-25;
					yt2=i_starty_trans_sub-adder_trans_sub_y+15;
					if (y<yt1 && y>yt2)
					{
						
						glColor3f(0.0, 0.0, 1.0);
						draw_rect(i_startx_trans_sub-14, yt1-10, i_startx_trans_sub+adder_trans_sub_x+14, yt2, 1, 2.0);
						flag=0;
						trans=7;
						save();
						save_lay_flag=1;
						create_sub_window(7);
						
					}
					else
					{
						glColor3f(1.0, 1.0, 1.0);
						draw_rect(i_startx_trans_sub-14, yt1-10, i_startx_trans_sub+adder_trans_sub_x+14, yt2, 1, 2.0);

						yt1-=50;
						yt2-=50;
						if (y<yt1 && y>yt2)
						{
							
							glColor3f(0.0, 0.0, 1.0);
							draw_rect(i_startx_trans_sub-14, yt1-10, i_startx_trans_sub+adder_trans_sub_x+14, yt2, 1, 2.0);
							flag=0;
							trans=8;
							
							if (save_lay_flag==1)
							{
								cont_transform();
								save_lay_flag=0;
							}
							else
							{
								animate();
								save_lay_flag=0;
							}
							create_sub_window(7);
							
						}
						else
						{
							flag=2;
						}

					}

				}
									
				glColor3f(0.0, 0.0, 0.0);
				draw_line(0, 0, 100, 0, 1, 2.0);
				break;
				
				
			case 8:
				glColor3f(1.0, 1.0, 1.0);
				draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
				
				init_size_trans_sub();
				glColor3f(0.0, 0.0, 1.0);
				
				if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
				{
					
					draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
					
                    glutInitWindowSize(widthm/2, heightm/2);
					glutInitWindowPosition(200, 200);
					layer_window=glutCreateWindow("Select Layer");
					init_layer_window();
					glutDisplayFunc(display_layer_window);
					glutMouseFunc(myMouse_layer_window);
					startx_layer=glutGet(GLUT_WINDOW_X);
					starty_layer=glutGet(GLUT_WINDOW_Y);
					
				}
				else
				{
					i_starty_trans_sub-=adder_trans_sub_y;
					if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
					{
						
						draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
						
						if (end[selected]->next!=NULL)
						{
							end[selected-1]->next=start[selected+1];
						}
						else
						{
							end[selected-1]->next=NULL;
						}
	
						j=selected;
						while (j<layer_name_index)
						{
							k=0;
							while (lay[j+1].layer_name[k]!='\0')
							{
								lay[j].layer_name[k]=lay[j+1].layer_name[k];
								k++;
							}
							lay[j].layer_name[k]='\0';
							j++;
							
						}
						
						selected--;
						layer_name_index--;
						ard=end[selected];
			
						glutSetWindow(status_window);
						glColor3f(0.0, 0.0, 0.0);
						draw_line(700, heightm-50, 750, heightm-50, 1, 20.0);
						
						glColor3f(1.0, 0.0, 0.0);
						j=0;
						while (lay[selected].layer_name[j]!='\0')
						{
							draw_char(lay[selected].layer_name[j], 13, 8, 700+10*j, heightm-57);
							j++;
							
						}
						
					}	
					
				}
				df_wr();
				rePaint();
				break;
	
				
		case 14:
				glColor3f(1.0, 1.0, 1.0);
				draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
				
				init_size_trans_sub();
				glColor3f(0.0, 0.0, 1.0);
				
				if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
				{
					draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
					allign=1;
				}
				else
				{
					i_starty_trans_sub-=adder_trans_sub_y;
					if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
					{
						draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
						allign=0;
					}
				}

			break;
		
				
		case 15:
				glColor3f(1.0, 1.0, 1.0);
				draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
				init_size_trans_sub();
				glColor3f(0.0, 0.0, 1.0);
				
				if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
				{
					draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
					openf=0;
					glutInitWindowSize(widthm/2, heightm/2);
					glutInitWindowPosition(200, 200);
					file_window=glutCreateWindow("Save As...");
					init_layer_window();
					glutDisplayFunc(display_file_window);
					glutMouseFunc(myMouse_file_window);
					glutKeyboardFunc(myKey_file_window);
					startx_layer=glutGet(GLUT_WINDOW_X);
					starty_layer=glutGet(GLUT_WINDOW_Y);
				}
				else
				{
					i_starty_trans_sub-=adder_trans_sub_y;
					if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
					{
						draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
						openf=1;
						glutInitWindowSize(widthm/2, heightm/2);
						glutInitWindowPosition(200, 200);
						file_window=glutCreateWindow("Open File");
						init_layer_window();
						glutDisplayFunc(display_file_window);
						glutMouseFunc(myMouse_file_window);
						glutKeyboardFunc(myKey_file_window);
						startx_layer=glutGet(GLUT_WINDOW_X);
						starty_layer=glutGet(GLUT_WINDOW_Y);
					}
				}
				break;
				
			case 16:
				glColor3f(1.0, 1.0, 1.0);
				draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
				
				init_size_trans_sub();
				glColor3f(0.0, 0.0, 1.0);
				if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
				{
					draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
					hold=0;
					deselect();
				}
				else
				{
					i_starty_trans_sub-=adder_trans_sub_y;
					if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
					{
						draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
						cp=NULL;
						store=NULL;
					}
				}
				break;
	

			case 18:
				glColor3f(1.0, 1.0, 1.0);
				draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
				
				init_size_trans_sub();
				glColor3f(0.0, 0.0, 1.0);
				if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
				{
					draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
				}
				else
				{
					i_starty_trans_sub-=adder_trans_sub_y;
					if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
					{
						draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
						move=1;
					}
				}
				break;
				
			case 19:
				glColor3f(1.0, 1.0, 1.0);
				draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
				
				flag_scale=flag_trans=flag_rot=0;
				init_size_trans_sub();
				glColor3f(0.0, 0.0, 1.0);
				for (i=0; i<=2; i++)
				{
					if (y>i_starty_trans_sub-14 && y<i_starty_trans_sub+14)
					{
						draw_rect(i_startx_trans_sub-14, i_starty_trans_sub-14, i_startx_trans_sub+adder_trans_sub_x+14, i_starty_trans_sub+14, 1, 2.0);
						break;
					}
					else
					{
						i_starty_trans_sub-=adder_trans_sub_y;
					}
				}
				
				switch (i)
				{
					case 0:
						create_action();
						break;
					case 1:
						perform_action();
						break;
					case 2:
						action_init();
						break;
				}
				break;
				
			default:
				break;
		}
	}
	glFlush();

}


void my_Mouse_drag (int x, int y)
{
	int count_index;
	x=glutGet(GLUT_WINDOW_X)+x;
	y=glutGet(GLUT_WINDOW_HEIGHT)-y;
	
	switch (check)
	{
		case 2:
			lineto(x, y, 1, 1);
			active_write(2, temp.x, temp.y, -1, -1, -1, -1, 1, -1, -1, 1.0);
			break;
		case 13:
			lineto(x, y, 1, 10.0);
			active_write(2, temp.x, temp.y, -1, -1, -1, -1, 1, -1, -1, 10.0);
			break;
		case 16:
			count_index=store_index;
			while (count_index>0)
			{
				
				
				count_index--;
			}
			break;

		default:
			break;
	}
	glFlush();

}


void passive (int x, int y)
{
	x=glutGet(GLUT_WINDOW_X)+x;
	y=glutGet(GLUT_WINDOW_HEIGHT)-y;
	
	switch (check)
	{
		case 1:
			if (pass.x!=0)
			{
				glColor3f(1.0, 1.0, 1.0);
				draw_line(temp.x, temp.y, pass.x, pass.y, line_type, 1.0);
				//rePaint();
			}
			glColor3f(obj[color_no].r, obj[color_no].g, obj[color_no].b);
			draw_line(temp.x, temp.y, x, y, line_type, 1.0);
			//rePaint();
			pass.x=x;
			pass.y=y;

			break;
			
		case 3:
			if (temp.x!=0)
			{
				if (no_vertex==2)
				{
					if (pass.x!=0)
					{
						glColor3f(1.0, 1.0, 1.0);
						draw_rect(temp.x, temp.y, pass.x, pass.y, line_type, 1.0);
					}
					glColor3f(obj[color_no].r, obj[color_no].g, obj[color_no].b);
					draw_rect(temp.x, temp.y, x, y, line_type, 1.0);
				}
				else
				{
					if (pass.x!=0)
					{
						glColor3f(1.0, 1.0, 1.0);
						draw_line(temp.x, temp.y, pass.x, pass.y, line_type, 1.0);
						if (no==1)
						{			
							glColor3f(1.0, 1.0, 1.0);
							draw_line(init.x, init.y, pass.x, pass.y, line_type, 1.0);
						}
					}
					glColor3f(obj[color_no].r, obj[color_no].g, obj[color_no].b);
					draw_line(temp.x, temp.y, x, y, line_type, 1.0);
					
					if (no==1)
					{
						glColor3f(obj[color_no].r, obj[color_no].g, obj[color_no].b);
						draw_line(init.x, init.y, pass.x, pass.y, line_type, 1.0);
					}
				}

				pass.x=x;
				pass.y=y;
			}
			break;

		case 4:
			if (rad==1)
			{
				if (pass.x!=0)
				{
					glColor3f(1.0, 1.0, 1.0);
					draw_circle(temp.x, temp.y, pass.x, circle_type, 1.0);
				}
				
				if (x<temp.x) 
				{
					rx=temp.x-x;
				}
				else
				{
					rx=x-temp.x;
				}
				
				if (y<temp.y)
				{
					ry=temp.y-y;
				}
				else
				{
					ry=y-temp.y;
				}
				
				r=sqrt(pow(rx, 2)+pow(ry, 2));
				glColor3f(obj[color_no].r, obj[color_no].g, obj[color_no].b);
				draw_circle(temp.x, temp.y, r, circle_type, 1.0);
				pass.x=r;
			}
			break;

		case 17:
			if (temp.x!=0)
			{
				glColor3f(0.0, 0.0, 1.0);
				draw_rect(temp.x, temp.y, x, y, 1, 2.0);
			}
			break;
			
		case 19:
			if (send==1)
			{
				if (flag_scale==1)
				{
					//switch (store->op)
					//{
					//	case 1:
							if (point==1)
							{
								if (store->x1<=store->x2)
								{
									anim_scale(1,x,y);
								}
								else
								{
									if (store->y1<=store->y2)
									{
										anim_scale(1,x,y);
									}
									else
									{
										anim_scale(2,x,y);
									}
								}
							}
							if (point==2)
							{
								if (store->x1>=store->x2)
								{
									anim_scale(1,x,y);
								}
								else
								{
									if (store->y1>=store->y2)
									{
										anim_scale(1,x,y);
									}
									else
									{
										anim_scale(2,x,y);
									}
								}
							}
					//		break;
					//	default:
					//		break;
					//}
				}
			}
			
			break;

		default:
			break;
	}
	glFlush();
}

void myKey_draw_window (char key)
{
	action_key=0;
	if (check==5)
	{
		cho=1;
		glColor3f(obj[color_no].r, obj[color_no].g, obj[color_no].b);
		char_gen(key,h,w);
	}
	if (check==19)
	{
		if (key=='1')
		{
			point=1;
			send=1;
		}
		else
		{
			if (key=='2')
			{
				point=2;
				send=1;
			}
			else
			{
				send=0;
			}
		}
	}
	
	if (key==27)
	{
		create_sub_window(0);
		check=0;
		glutSetWindow(tools_window);
		glColor3f(1.0, 1.0, 1.0);
		draw_rect(i_startx+1, i_starty+adder-4, i_startx+adder-4, i_starty+3, 1, 3.0);

	}
	glFlush();

}


void myKey_sub_window (char key)
{
	int n,j;
	if (check==6 && layer_check==1)
	{
		if (chCP.x<=80 && key!=13)
		{
			
			glColor3f(0.0, 0.0, 1.0);
			char_gen(key, 13, 8);
			if (key != 8)
			{
				lay[layer_name_index].layer_name[index2++]=key;
				
			}
			else
			{
				lay[layer_name_index].layer_name[--index2]='\0';
			}
		}
	}
	if (check == 7)
	{
		if (((key<=57 && key>=48 ) || key==46 || key==45 || key==99 || key==97) && chCP.x<=80)
		{
			glColor3f(0.0, 0.0, 1.0);
			char_gen(key, 13, 8);
			if (trans==4 && (key==97 || key==99) )
			{
				if (key==99)
				{
					lay[selected].clockwise=1;
				}
				if (key==97)
				{
					lay[selected].clockwise=0;
				}
			}
			else
			{
				if (key == 45)
				{
					if (trans==5)
					{
						negtx=1;
					}
					if (trans == 6)
					{
						negty=1;
					}
				}	
				else
				{
					if (key != 46)
					{
						count_no++;
						switch (trans)
						{
							case 1:
								asc_no[count_no]=key;
								j=count_no;
								
								if (dec==0)
								{
									lay[selected].sx=0;
									hold=j;
									while (j>0)
									{
										n=asc_num(asc_no[j]);
										lay[selected].sx+=n*pow(10, count_no-j);
										j--;
									}
									tempdec=lay[selected].sx;
								}
								else
								{
									lay[selected].sx=tempdec;
									while (j>hold)
									{
										n=asc_num(asc_no[j]);
										lay[selected].sx+=n*pow(0.1, j-hold);
										j--;
									}
									
								}
								
								break;
								
							case 2:
								asc_no[count_no]=key;
								j=count_no;
								
								if (dec==0)
								{
									lay[selected].sy=0;
									hold=j;
									while (j>0)
									{
										n=asc_num(asc_no[j]);
										lay[selected].sy+=n*pow(10, count_no-j);
										j--;
									}
									tempdec=lay[selected].sy;
								}
								else
								{
									lay[selected].sy=tempdec;
									while (j>hold)
									{
										n=asc_num(asc_no[j]);
										lay[selected].sy+=n*pow(0.1, j-hold);
										j--;
									}
								}
								break;
								
							case 3:
								asc_no[count]=key;
								j=count;
								
								lay[selected].angleo=0;
								while (j>0)
								{
									n=asc_num(asc_no[j]);
									lay[selected].angleo+=n*pow(10, count-j);
									j--;
								}
								
								break;
								
							case 4:
								asc_no[count_no]=key;
								j=count_no;
								
								lay[selected].anglea=0;
								while (j>0)
								{
									n=asc_num(asc_no[j]);
									lay[selected].anglea+=n*pow(10, count_no-j);
									j--;
								}
								break;
								
							case 5:
								asc_no[count_no]=key;
								j=count_no;
								
								if (dec==0)
								{
									lay[selected].tx=0;
									hold=j;
									while (j>0)
									{
										n=asc_num(asc_no[j]);
										lay[selected].tx+=n*pow(10, count_no-j);
										j--;
									}
									tempdec=lay[selected].tx;
								}
								else
								{
									lay[selected].tx=tempdec;
									while (j>hold)
									{
										n=asc_num(asc_no[j]);
										lay[selected].tx+=n*pow(0.1, j-hold);
										j--;
									}
									
								}
								break;
								
							case 6:
								asc_no[count_no]=key;
								j=count_no;
								
								if (dec==0)
								{
									lay[selected].ty=0;
									hold=j;
									while (j>0)
									{
										n=asc_num(asc_no[j]);
										lay[selected].ty+=n*pow(10, count_no-j);
										j--;
									}
									tempdec=lay[selected].ty;
								}
								else
								{
									lay[selected].ty=tempdec;
									while (j>hold)
									{
										n=asc_num(asc_no[j]);
										lay[selected].ty+=n*pow(0.1, j-hold);
										j--;
									}
									
								}
								break;								
							default:
								break;
						}
						
						
					}
					else
					{
						dec=1;
					}
				}
			}	
		}
	}
	glFlush();

}


void entry_status (int state)
{
	if (state==GLUT_ENTERED) 
	{
		glutSetCursor(GLUT_CURSOR_TEXT);
		
	}
	if (state==GLUT_LEFT)
	{
		glutSetCursor(GLUT_CURSOR_INHERIT);
	}
}




void entry_tool (int state)
{
	if (state==GLUT_ENTERED) 
	{
		glutSetCursor(GLUT_CURSOR_INHERIT);
	}
}


void entry_draw (int state)
{
	if (state==GLUT_ENTERED)
	{
		switch (check)
		{
			case 1:
				glutSetCursor(GLUT_CURSOR_INHERIT);
				break;
			case 2:
				glutSetCursor(GLUT_CURSOR_DESTROY);
				break;
				
			case 3:
				glutSetCursor(GLUT_CURSOR_CROSSHAIR);
				break;
			case 5:
				glutSetCursor(GLUT_CURSOR_TEXT);
				break;
				
			default:
				break;
		}
		
	}
	else 
	{
		glutSetCursor(GLUT_CURSOR_INHERIT);
	}
	
}

/**** display for main_window ****/

void display_main()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}


/**** display for draw_window ****/
void display_draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glFlush();

}


/**** display for tools_window ****/

void display_tool()
{
	glClear(GL_COLOR_BUFFER_BIT);
	init_size();
	icon();
	glFlush();

}


/**** display for status_window ****/
void display_status (void)
{
	int j,k;
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.7, 0.7, 0.7);
	for (k=0; k<=1; k++)
	{
		j=0;
		while (icon_text[k][j]!='\0')
		{
			draw_char(icon_text[k][j], 14, 9, 250+j*10+290*k, heightm-57);
			j++;
		}
	}

	glColor3f(1.0, 0.0, 0.0);
	j=0;
	while (lay[0].layer_name[j]!='\0')
	{
		draw_char(lay[0].layer_name[j], 14, 9, 700+j*10, heightm-57);
		j++;
		
	}
	
	glFlush();

}


/**** display for sub_window ****/
void display_sub (void)
{
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.0, 0.0, 0.0);
	glFlush();

}



/***** init for main_window *****/
void init_main (void)
{		
	glClearColor(1.0, 1.0, 1.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(100, 0, widthm-100, heightm-60);		//view (x,y)(lower-left-corner),sizex,sizey
	gluOrtho2D(100, widthm, 0.0, heightm-60);  // clipping left,right,bottom,top
	glFlush();

}


/**** init for tools_window ****/
void init_tools (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, heightm-40, widthm, 40);
	gluOrtho2D(0.0, widthm, heightm-40, heightm);
	glFlush();
}


/**** init for status_window ****/
void init_status (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, heightm-60, widthm, 20);
	gluOrtho2D(0.0, widthm, heightm-60, heightm-40);
	glFlush();
}

/**** init for sub_window ****/
void init_sub (void)
{
	glClearColor(0.0, 0.0, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, 100, heightm-60);
	gluOrtho2D(0, 100, 0, heightm-60);
	glFlush();
}



/**** Set colors ****/
void color_init()
{
	obj[0].r = 0.0;
	obj[0].g = 0.0;      
	obj[0].b = 0.0;
	
	obj[1].r = 0.7;
	obj[1].g = 0.7;      
	obj[1].b = 0.7;
	
	obj[2].r = 0.5;
	obj[2].g = 0.0;      
	obj[2].b = 0.5;
	
	obj[3].r = 0.2;
	obj[3].g = 0.0;      
	obj[3].b = 0.6;
	
	obj[4].r = 0.0;
	obj[4].g = 0.0;      
	obj[4].b = 1.0;
	
	obj[5].r = 0.0;
	obj[5].g = 0.5;      
	obj[5].b = 0.0;
	
	obj[6].r = 0.0;
	obj[6].g = 1.0;      
	obj[6].b = 0.0;
	
	obj[7].r = 0.8;
	obj[7].g = 0.7;      
	obj[7].b = 0.4;
	
	obj[8].r = 0.4;
	obj[8].g = 0.2;      
	obj[8].b = 0.0;
	
	obj[9].r = 1.0;
	obj[9].g = 0.5;      
	obj[9].b = 0.5;
	
	obj[10].r = 1.0;
	obj[10].g = 0.0;      
	obj[10].b = 0.0;
	
	obj[11].r = 1.0;
	obj[11].g = 0.5;      
	obj[11].b = 0.0;
	
	obj[12].r = 1.0;
	obj[12].g = 1.0;      
	obj[12].b = 0.5;
	
	obj[13].r = 1.0;
	obj[13].g = 1.0;      
	obj[13].b = 1.0;
	
	
} 

/**** Variables init ****/
void var_init()
{
	heightm=glutGet(GLUT_SCREEN_HEIGHT)-100;
	widthm=glutGet(GLUT_SCREEN_WIDTH)-100;
	
	heightmax=glutGet(GLUT_SCREEN_HEIGHT);
	widthmax=glutGet(GLUT_SCREEN_WIDTH);
	temp.x=0;
	temp.y=0;
	line_type=1;
	check=0;
	no_vertex=3;
	no=no_vertex;
	h=13;
	w=8;
	rad=0;
	circle_type=0;
	first=1;
	open=0;
	cho=0;
	layer_name_index=0;
	index2=0;
	lay[0].layer_name[0]='b';
	lay[0].layer_name[1]='g';
	layer_check=0;
	war=0;
	selected=0;
	negtx=0;
	negty=0;
	flag_started=1;
	color_no=0;
	col_clicked=0;
	grid_flag=1;
	grid_clicked=0;
	save_lay_flag=0;
	store_index=0;
	allign=0;
	pop_check=0;
	hold=0;
	anim_window_activate=0;
	anim_arbit=0;
	cou=0;
	fp=fopen(file_name, "w");
	fclose(fp);
	color_init(); 
	init_seg();
	seg_wr(1);
}	


int main (int argc, char ** argv) 
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	var_init();

	/**** main_window ****/
	glutInitWindowSize(widthm, heightm);
	glutInitWindowPosition(0, 0);
	main_window=glutCreateWindow("MiniProject");
	init_main();
	glutDisplayFunc(display_main);
	
	
	/**** draw_window ****/
	draw_window=glutCreateSubWindow(main_window, 100, 60, widthm-100, heightm-60);
	init_main();
	glutDisplayFunc(display_draw);
	work_h=glutGet(GLUT_WINDOW_HEIGHT);
	work_w=glutGet(GLUT_WINDOW_WIDTH);
	startx=100;
	starty=glutGet(GLUT_WINDOW_Y);
	//printf("\n%d %d",starty,startx);
	glutEntryFunc(entry_draw);
	glutMouseFunc(myMouse_draw_window);
	glutKeyboardFunc(myKey_draw_window);
	glutMotionFunc(my_Mouse_drag);
	//glutPassiveMotionFunc(passive);
	
	/**** tools_window ****/
	tools_window=glutCreateSubWindow(main_window, 0, 0, widthm, 40);
	init_tools();
	glutDisplayFunc(display_tool);
	glutMouseFunc(myMouse_tools_window);
	glutEntryFunc(entry_tool);
	
	/**** status_window ****/
	status_window=glutCreateSubWindow(main_window, 0, 40, widthm, 20);
	init_status();
	glutDisplayFunc(display_status);
	glutEntryFunc(entry_status);
	
	
	/**** sub_window ****/
	sub_window=glutCreateSubWindow(main_window, 0, 60, 100, heightm-60);
	init_sub();
	glutDisplayFunc(display_sub);
	glutMouseFunc(myMouse_sub_window);
	//hacker();
	glutKeyboardFunc(myKey_sub_window);
	
	glutMainLoop();
    return 0;
}
