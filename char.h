//
//  char.h
//  minip
//
//  Created by Dasa Anand on Feb-April.
//  Copyright 2010 __ CG __. All rights reserved.
//	Made on Mac using openGL as base and xcode as compiler.


extern int cho,action_key;
int i=0;

struct s2
{
	int x,y;
}cha,pre[10];

char st[10];


/*** Char move to ****/
void char_move_to(int x, int y)
{
	cha.x+=x;
	cha.y+=y;
}



/**** Char line to ****/
void char_line_to(int x, int y)
{
	
	draw_line(cha.x, cha.y, cha.x+x, cha.y+y, 1, 2.0);
	if (cho==1)
	{
		active_write(1, cha.x, cha.y, cha.x+x, cha.y+y, -1, -1, 1, -1, -1, 2.0);
	}
	cha.x+=x;
	cha.y+=y;
}




int draw_char(char ch, int h, int w, int x, int y)
{
	int re;
	cha.x=x;
	cha.y=y;																																					
	
	switch (toupper(ch))
	{
		case '1':
			char_line_to(w, 0);
			char_move_to(-w/2, 0);
			char_line_to(0, h);
			char_line_to(-w/4, -h/4);
			break;
			
		case '2':
			char_line_to(w, 0);
			char_move_to(-w/2, 2*h/3);
			draw_ellipse(cha.x, cha.y, w/2, 0.45*h, 3);
			char_move_to(-w/2, -2*h/3);
			char_line_to(w, 2*h/3);
			break;
			
		case '3':
			char_move_to(0, h);
			char_line_to(w, 0);
			char_line_to(-0.5*w, -0.42*h);
			char_move_to(0, -0.35*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.3*h, 2);
			draw_ellipse(cha.x, cha.y, w/2, 0.3*h, 7);
			break;
			
		case '4':
			char_move_to(0.75*w, -1);
			char_line_to(0, h+1);
			char_line_to(-0.75*w, -0.75*h);
			char_line_to(w, 0);
			break;
			
		case '5':
			char_move_to(w, h);
			char_line_to(-w, 0);
			char_line_to(0, -0.40*h);
			char_move_to(w/2, -0.39*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.4*h, 2);
			draw_ellipse(cha.x, cha.y, w/2, 0.4*h, 7);
			char_move_to(-w/2, 0.4*h);
			char_line_to(0.4*w, 0);
			break;
			
		case '6':
			char_move_to(0, h-1);
			char_line_to(0, -0.6*h);
			char_move_to(0, -0.4*h);
			char_move_to(w/2, 0.3*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.4*h, 0);
			char_move_to(0, 0.6*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.15*h, 3);
			
			break;
			
			
		case '7':
			char_move_to(w/3, 0);
			char_line_to(2*w/3, h);
			char_line_to(-w+3, 0);
			break;
			
		case '8':
			char_move_to(w/2, 0.30*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.30*h, 0);
			char_move_to(0, 0.57*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.25*h, 0);
			break;
			
		case '9':
			char_move_to(w/2, 0.75*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.4*h, 0);
			char_move_to(-w/2, -0.6*h);
			char_move_to(w, 0);
			char_line_to(0, 0.7*h);
			char_move_to(-w/2, -0.7*h);
			draw_ellipse(cha.x, cha.y, 0.4*w, 0.15*h, 4);
			break;
			
		case '0':
			char_move_to(w/2, h/2+1);
			draw_ellipse(cha.x, cha.y-1, w/2, h/2+1, 0);
			char_move_to(-w/2, -h/2-2);
			char_move_to(0.3*w, 0.29*h);
			char_line_to(0.5*w, 0.8*h);
			break;
			
		case 'A':
			char_line_to(0, 0.8*h);
			char_move_to(w, 0);
			char_line_to(0, -0.8*h);
			char_move_to(-w, 0.4*h);
			char_line_to(w, 0);
			char_move_to(-w/2, 0.5*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.2*h, 3);
			break;
			
		case 'B':
			char_line_to(w-4, 0);
			char_move_to(-w+4, 0);
			char_line_to(0, h);
			char_line_to(w-4, 0);
			char_move_to(-w+4, -h/2);
			char_line_to(w-7, 0);
			char_move_to(-w/2+5, 0.25*h);
			draw_ellipse(cha.x, cha.y, w/2+1, 0.28*h, 2);
			char_move_to(0, -0.55*h);
			draw_ellipse(cha.x, cha.y, w/2+1, 0.25*h, 2);
			break;
			
		case 'C':
			char_move_to(w/2, 0);
			char_line_to(-w/2+8, 0);
			char_move_to(0, h);
			char_line_to(w/2-8, 0);
			char_move_to(0, -h/2);
			draw_ellipse(cha.x, cha.y, w/2, h/2, 1);
			break;
			
		case 'D':
			char_line_to(0, h);
			char_move_to(w/2, -h/2);
			draw_ellipse(cha.x, cha.y, w/2, h/2, 2);
			char_move_to(0, h/2);
			char_line_to(-w/2, 0);
			char_move_to(0, -h);
			char_line_to(w/2, 0);
			break;
			
		case 'E':
			char_line_to(w, 0);
			char_move_to(-w, 0);
			char_line_to(0, h);
			char_line_to(w, 0);
			char_move_to(-w, -h/2);
			char_line_to(w, 0);
			break;
			
		case 'F':
			char_line_to(0, h);
			char_line_to(w, 0);
			char_move_to(-w, -h/2);
			char_line_to(w, 0);
			break;
			
		case 'G':
			char_move_to(w/2, 0);
			char_line_to(-w/2+8, 0);
			char_move_to(0, h);
			char_line_to(w/2-8, 0);
			char_move_to(0, -h/2);
			draw_ellipse(cha.x, cha.y, w/2, h/2, 1);
			char_line_to(5, 0);
			char_line_to(0, -h/2);
			char_line_to(-2, 0);
			break;
			
		case 'H':
			char_line_to(0, h);
			char_move_to(w, 0);
			char_line_to(0, -h);
			char_move_to(0, h/2);
			char_line_to(-w, 0);
			break;
			
		case 'I':
			char_line_to(w, 0);
			char_move_to(0, h);
			char_line_to(-w, 0);
			char_move_to(w/2, 0);
			char_line_to(0, -h);
			break;
			
		case 'J':
			char_move_to(0.8*w, 2);
			char_line_to(0, h-2);
			char_line_to(-0.5*w, 0);
			char_move_to(0, -0.95*h);
			draw_ellipse(cha.x+1, cha.y, 0.35*w, 0.1*h, 4);
			break;
			
		case 'K':
			char_line_to(0, h);
			char_move_to(0, -h/2);
			char_line_to(w, h/2);
			char_move_to(-w+4, -h/2);
			char_line_to(w-4, -h/2);
			break;
			
		case 'L':
			char_line_to(0, h);
			char_move_to(0, -h);
			char_line_to(w, 0);
			break;
			
		case 'M':
			char_line_to(0, h);
			char_line_to(w/2, -0.50*h);
			char_line_to(w/2, 0.50*h);
			char_line_to(0, -h);
			break;
			
		case 'N':
			char_line_to(0, h);
			char_line_to(w, -h);
			char_line_to(0, h);
			break;
			
		case 'O':
			char_move_to(w/2, h/2+1);
			draw_ellipse(cha.x, cha.y-1, w/2, h/2+1, 0);
			break;
			
		case 'P':
			char_line_to(0, h);
			char_line_to(w-4, 0);
			char_move_to(-w+4, -h/2);
			char_line_to(w-7, 0);
			char_move_to(-w/2+5, 0.25*h);
			draw_ellipse(cha.x, cha.y, w/2+1, 0.28*h, 2);
			break;
			
		case 'Q':
			char_move_to(w/2, h/2+1);
			draw_ellipse(cha.x, cha.y-1, w/2, h/2+1, 0);
			char_move_to(0, -0.3*h);
			char_line_to(0.4*w, -0.3*h);
			break;
			
		case 'R':
			char_line_to(0, h);
			char_line_to(w-4, 0);
			char_move_to(-w+4, -h/2);
			char_line_to(w-7, 0);
			char_move_to(-w/2+5, 0.25*h);
			draw_ellipse(cha.x, cha.y, w/2+1, 0.28*h, 2);
			char_move_to(0, -0.3*h);
			char_line_to(0.6*w, -0.51*h);
			break;
			
		case 'S':
			char_move_to(w/2, 0.25*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.30*h, 2);
			draw_ellipse(cha.x, cha.y, w/2, 0.30*h, 7);
			char_move_to(0, 0.6*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.25*h, 1);
			draw_ellipse(cha.x, cha.y, w/2, 0.25*h, 5);
			break;
			
		case 'T':
			char_move_to(0, h);
			char_line_to(w, 0);
			char_move_to(-w/2, 0);
			char_line_to(0, -h);
			break;
			
		case 'U':
			char_move_to(0, h);
			char_line_to(0, -0.9*h);
			char_move_to(w, 0);
			char_line_to(0, 0.9*h);
			char_move_to(-w/2, -0.9*h);
			draw_ellipse(cha.x, cha.y, w/2, 0.15*h, 4);
			break;
			
		case 'V':
			char_move_to(0, h);
			char_line_to(w/2, -h);
			char_line_to(w/2, h);
			break;
			
		case 'W':
			char_move_to(0, h);
			char_line_to(0.20*w, -h);
			char_line_to(0.30*w, 0.60*h);
			char_line_to(0.30*w, -0.60*h);
			char_line_to(0.20*w, h);
			break;
			
		case 'X':
			char_move_to(0, h);
			char_line_to(w, -h);
			char_move_to(0, h);
			char_line_to(-w, -h);
			break;
			
		case 'Y':
			char_move_to(0, h);
			char_line_to(w/2, -h/2);
			char_line_to(w/2, h/2);
			char_move_to(-w/2, -h/2);
			char_line_to(0, -(h+1)/2);
			break;
			
		case 'Z':
			char_move_to(0, h);
			char_line_to(w, 0);
			char_line_to(-w, -h);
			char_line_to(w, 0);
			break;
			
		case ' ':
			break;
			
		case '.':
			draw_ellipse(cha.x+2, cha.y, 1, 1, 0);
			break;
			
		case 8:
			glColor3f(0.0, 0.0, 0.0);
			if (action_key==1)
			{
				glColor3f(1.0, 1.0, 1.0);
			}
			re=draw_char(st[(i-1)%10], h, w, pre[(i-1)%10].x, pre[(i-1)%10].y); 
			i-=2;
			return 2;
			break;
			
		case 13:
			return -1;
			break;
			
		case 45:
			char_move_to(0, h/2);
			char_line_to(w, 0);
			break;
			
			
			
		case ',':
			char_move_to(5, 0);
			char_line_to(-3, -3);
			break;
			
		case ':':
			char_move_to(5, 0.2*h);
			draw_ellipse(cha.x, cha.y, 1, 1, 0);
			char_move_to(0, h/2);
			draw_ellipse(cha.x, cha.y, 1, 1, 0);
			break;
		
		case '(':
			char_move_to(w/2, h/2);
			draw_ellipse(cha.x, cha.y, w/2, h/2+2, 1);
			break;
	
		case ')':
			char_move_to(w/2, h/2);
			draw_ellipse(cha.x, cha.y, w/2, h/2+2, 2);
			break;

			
		default:
			return -1;
			
	}
	st[i%10]=ch;
	pre[i%10].x=x;
	pre[i%10].y=y;
	cho=0;
	i++;
	return 1;
	
}
