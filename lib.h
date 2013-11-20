//
//  lib.c
//  minip
//
//  Created by Dasa Anand on Feb-April.
//  Copyright 2010 __ CG __. All rights reserved.
//	Made on Mac using openGL as base and xcode as compiler.


/*
 *	 op-code		parameters
 * 1.line abs	x1	y1	x2	y2	linetype size	col
 * 2.freehand	x1	y1	size	col
 * 3.polygon	 
 1			x1	y2	x1	y2	linetype size
 1
 1 ...
 3
 *4.circle		x	y	r	circle_type	col
 * 5.text	h w 
 1 ...
 1 ...
 10 ..
 5
 *10.ellipse	x1	x2	xc	yc	c_type	col
 */


extern int color_no,selected,flag_insert,flag_started,layer_name_index;

FILE *fp;

struct s3 
{
	int op,l_type,c_type,text,r,rx,ry,h,w,ch,n;
	float x1,y1,x2,y2,size;
	float red,g,b;
	struct s3 *next; 
};


struct color
{
    float r,g,b;
};

struct layer 
{
	char layer_name[10];
	float sx,sy;
	float tx,ty;
	float angleo,anglea;
	int clockwise;
	int x,y;
	int rot_arbit;
	int pt;
	struct layer *next_seg;
};


extern struct layer lay[20],*head_seg,*shift_seg,*ard_seg;
extern struct color obj[14];
extern struct s3 rd,*ard,*head,*shift,*end[20],*next_layer,*start[20],*tempc,*store_tail,*prevp1,*prevp2,*store,*store_redo;
extern char file_name[20];


float normalizeh(float max, int var)
{
	max=var/max;
	return max;
}



/**** write using active display file ****/
void df_wr()
{
	
	fp=fopen(file_name,"w");
	shift=head;
	while (shift!= NULL)
	{
		switch (shift->op)
		{
			case 1:
				fprintf(fp, "%d ",shift->op);
				fprintf(fp, "%f %f %f %f %d %f ",shift->x1,shift->y1,shift->x2,shift->y2,shift->l_type,shift->size);
				break;
				
			case 2:
				fprintf(fp, "%d ",shift->op);
				fprintf(fp, "%f %f %f ",shift->x1,shift->y1,shift->size);
				break;
				
			case 3:
				fprintf(fp, "%d\n",shift->op);
				break;
				
			case 4:
				fprintf(fp, "%d ",shift->op);
				fprintf(fp, "%f %f %d %d %f ",shift->x1,shift->y1,shift->r,shift->c_type,shift->size);
				break;
				
			case 5:
				fprintf(fp, "%d ",shift->op);
				fprintf(fp, "%d %d %d\n",shift->h,shift->w,shift->ch);
				break;
			
			case 10:
				fprintf(fp, "%d ",shift->op);
				fprintf(fp, "%f %f %d %d %d %f ",shift->x1,shift->y1,shift->rx,shift->ry,shift->c_type,shift->size);
				break;

				
			default:
				break;
		}
		if (shift->op !=3 && shift->op !=5)
		{
			fprintf(fp, "%f %f %f\n",shift->red,shift->g,shift->b);
		}
		
		shift=shift->next;
		
	}
	
	fclose(fp);
}




/**** Active display file generation ****/
void active_write(int a, int x1, int y1, int x2, int y2, int xc, int yc, int ltype, int n, int ctype, float s)
{
	float work_h,work_w;
	work_h=glutGet(GLUT_SCREEN_HEIGHT)-160;
	work_w=glutGet(GLUT_SCREEN_WIDTH)-200;

	if (ard==NULL)
	{
		ard=malloc(sizeof(struct s3));
		head=ard;
	}
	else
	{
		ard->next=malloc(sizeof(struct s3));
		ard=ard->next;
	}
	ard->op=a;
	
	switch (a)
	{
		case 1:
			ard->x1=normalizeh(work_w, x1-100);
			ard->y1=normalizeh(work_h, y1);
			ard->x2=normalizeh(work_w, x2-100);
			ard->y2=normalizeh(work_h, y2);
			ard->l_type=ltype;
			ard->size=s;
			break;
			
		case 2:
			ard->x1=normalizeh(work_w, x1-100);
			ard->y1=normalizeh(work_h, y1);
			ard->size=s;
			break;
			
		case 3:
			break;
			
		case 4:
			ard->x1=normalizeh(work_w, xc-100);
			ard->y1=normalizeh(work_h, yc);
			ard->r=n;
			ard->c_type=ctype;
			ard->size=s;
			break;
			
		case 5:
			ard->h=x2;
			ard->w=y2;
			ard->ch=n;
			break;
			
		case 10:
			ard->x1=normalizeh(work_w, x1-100);
			ard->y1=normalizeh(work_h, y1);
			ard->rx=x2;
			ard->ry=y2;
			ard->c_type=ctype;
			ard->size=s;
			break;

			
		default:
			break;
	}
	
	if (a!=3)
	{
		ard->red=obj[color_no].r;
		ard->g=obj[color_no].g;
		ard->b=obj[color_no].b;
	}
	
	ard->next=NULL;
	end[selected]=ard;
	
	
	if (flag_started==1)
	{
		start[selected]=ard;
		if (selected != 0)
		{
			end[selected-1]->next=start[selected];
		}
		else
		{
			head=ard;
		}
		flag_started=0;
	}
	
	if (flag_insert==1)
	{
		if (start[selected+1]==NULL)
		{
			end[selected]->next=NULL;
		}
		else
		{
			end[selected]->next=start[selected+1];

		}

	}
	df_wr();	
}



/**** generation of segment table ****/
void seg_wr(int created)
{

	int j;
	if (created==1)
	{
		if (selected==0)
		{
			ard_seg=malloc(sizeof(struct layer));
			head_seg=ard_seg;
		}
		else
		{
			ard_seg->next_seg=malloc(sizeof(struct layer));
			ard_seg=ard_seg->next_seg;
		}	
		ard_seg->next_seg=NULL;
	}
	else
	{
		shift_seg=head_seg;
		for (j=1; j<selected; j++)
		{
			shift_seg=shift_seg->next_seg;
		}
		
		if (selected==0)
		{
			ard_seg=head_seg;
		}
		else
		{
			ard_seg=shift_seg->next_seg;
		}

	}

	ard_seg->sx=lay[selected].sx;
	ard_seg->sy=lay[selected].sy;
	ard_seg->tx=lay[selected].tx;
	ard_seg->ty=lay[selected].ty;
	ard_seg->angleo=lay[selected].angleo;
	ard_seg->anglea=lay[selected].anglea;
	ard_seg->clockwise=lay[selected].clockwise;
	ard_seg->x=lay[selected].x;
	ard_seg->y=lay[selected].y;
	ard_seg->rot_arbit=lay[selected].rot_arbit;
	
	fp=fopen("segement_table.tbl", "w");
	fprintf(fp, "Name\tsx\t\tsy\t\ttx\t\tty\t\tangleo\t\tanglea\t\tclockwise\tx\ty\tarbit\n");
	shift_seg=head_seg;
	j=0;
	while (j<=layer_name_index)
	{
		fprintf(fp, "%s\t%f\t%f\t%f\t%f\t%f\t%f\t%d\t\t%d\t%d\t%d\n",lay[j].layer_name,shift_seg->sx,shift_seg->sy,shift_seg->tx,shift_seg->ty,shift_seg->angleo,shift_seg->anglea,shift_seg->clockwise,shift_seg->x,shift_seg->y,shift_seg->rot_arbit);
		
		if (shift_seg->next_seg==NULL)
		{
			break;
		}
		
		shift_seg=shift_seg->next_seg;
		j++;
	}
	fclose(fp);
}