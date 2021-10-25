/* CSE 20311
 * Jonathan Nguyen
 * fractals.c
 */

#include "gfx.h"
#include <stdio.h>
#include <math.h>

void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3 );
void shrinkSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void spiralSquare(int x, int y, double size, double theta);
void circularLace(int x, int y, int radius);
void snowflake(int x, int y, int len);
void tree(int x, int y, double len, double theta);
void fern(int x, int y, double len, double theta);
void spiralSpiral(int x, int y, int radius, double theta); 
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3 );
void drawSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);

int main() {
	char c;
  int width = 700, height = 700, mrgn = 20, i;

  gfx_open(width, height, "Main");
  while(1) {
    if (gfx_event_waiting()) {
			c = gfx_wait();
			gfx_clear();
			switch (c) {
				case 'q':
					return 0;
				case '1':
					sierpinski(mrgn, mrgn, width-mrgn, mrgn, width/2, height-mrgn);
					break;
				case '2':
					shrinkSquare(width/4, height/4, 3*width/4, height/4, 3*width/4, 3*height/4, width/4, 3*height/4);
					break;
				case '3':
					spiralSquare(width/2, height/2, 1.5, 0);
					break;
				case '4':
					circularLace(width/2, height/2, height/3);
					break;
				case '5':
					snowflake(width/2, height/2, height/3);
					break;
				case '6':
					gfx_line(width/2, height - height/20, width/2, height - height/20 - height/3);
					tree(width/2, height - height/20 - height/3, height/5, 13*M_PI/10);
					break;
				case '7':
					gfx_line(width/2, height - height/20, width/2, height - height/20 - height*6/11);
					fern(width/2, height - height/20 - height*6/11, height*6/33.0, 4*M_PI/3);
					break;
				case '8':
					spiralSpiral(width/2, height/2, height*2/3, 0);
					break;
				default:
					printf("Please enter valid input\n");
					break;
			}
		}
	}
}

// Sierpinski's triangle
void sierpinski( int x1, int y1, int x2, int y2, int x3, int y3 ) {
  if( abs(x2-x1) < 5 ) return;
  drawTriangle( x1, y1, x2, y2, x3, y3 );
  sierpinski( x1, y1, (x1+x2)/2, (y1+y2)/2, (x1+x3)/2, (y1+y3)/2 );
  sierpinski( (x1+x2)/2, (y1+y2)/2, x2, y2, (x2+x3)/2, (y2+y3)/2 );
  sierpinski( (x1+x3)/2, (y1+y3)/2, (x2+x3)/2, (y2+y3)/2, x3, y3 );
}

// Shrinking square
void shrinkSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	double dif = (abs(x1-x2))*0.22;

	if (dif < 0.5) return;
	drawSquare(x1, y1, x2, y2, x3, y3, x4, y4);
	shrinkSquare(x1-dif, y1-dif, x1+dif, y1-dif, x1+dif, y1+dif, x1-dif, y1+dif);
	shrinkSquare(x2-dif, y2-dif, x2+dif, y2-dif, x2+dif, y2+dif, x2-dif, y2+dif);
	shrinkSquare(x3-dif, y3-dif, x3+dif, y3-dif, x3+dif, y3+dif, x3-dif, y3+dif);
	shrinkSquare(x4-dif, y4-dif, x4+dif, y4-dif, x4+dif, y4+dif, x4-dif, y4+dif);
}

// Spiral of squares
void spiralSquare(int x, int y, double size, double theta) {
	double a = 1, b = 0.2, scale = 1.057, xd = x+a*cos(-theta)*exp(b*theta), yd = y+a*sin(-theta)*exp(b*theta);

	if (theta > 10*M_PI) return;
	if (size > 2) drawSquare(xd, yd, xd+size, yd, xd+size, yd+size, xd, yd+size);
	else drawSquare(xd, yd, xd, yd, xd, yd, xd, yd);
	spiralSquare(x, y, pow(size, scale), theta+(2*M_PI/10));
}

// Circular lace
void circularLace(int x, int y, int radius) {
	double theta = M_PI/3, i;

	if (radius < 1) return;
	gfx_circle(x, y, radius);
	for (i = 0; i < 6; i++) 
		circularLace(x + radius*cos(theta*i), y + radius*sin(theta*i), radius/3);
}

// Snowflake
void snowflake(int x, int y, int len) {
	double theta = M_PI*2/5, i;

	if (len < 1) return;
	for (i = 0; i < 5; i++)
		gfx_line(x, y, x + len*cos(theta*i), y + len*sin(theta*i));
	for (i = 0; i < 5; i++) 
		snowflake(x + len*cos(theta*i), y + len*sin(theta*i), len/3);
}

// Tree
void tree(int x, int y, double len, double theta) {
	double angle = 2*M_PI/5, dif = M_PI/5;
	
	if (len < 1) return;
	gfx_line(x, y, x + len*cos(theta), y + len*sin(theta));
	gfx_line(x, y, x + len*cos(theta+angle), y + len*sin(theta+angle));
	tree(x + len*cos(theta), y + len*sin(theta), len*2/3, theta-dif);
	tree(x + len*cos(theta+angle), y + len*sin(theta+angle), len*2/3, theta+angle-dif);
}

// Fern
void fern(int x, int y, double len, double theta) {
	double angle = 2*M_PI/6, dif = M_PI/6, seg = len*3/4, i, xi, yi;

	if (len < 3) return;
	for (i = 0; i < 4; i++) {
		xi = x - (seg*i*cos(theta-11*M_PI/6));
		yi = y - (seg*i*sin(theta-11*M_PI/6));
		gfx_line(xi, yi, xi+len*cos(theta), yi+len*sin(theta));
		gfx_line(xi, yi, xi+len*cos(theta+angle), yi+len*sin(theta+angle));
		fern(xi+len*cos(theta), yi+len*sin(theta), len/3, theta-dif);
		fern(xi+len*cos(theta+angle), yi+len*sin(theta+angle), len/3, theta+angle-dif);
	}
}	

// Spiral of spiral
void spiralSpiral(int x, int y, int radius, double theta) {
 	int xlocal = x + radius*cos(theta), ylocal = y + radius*sin(theta);
	
	if (radius < 2) return;
 	gfx_point(x + radius*cos(theta), y + radius*sin(theta));
	spiralSpiral(xlocal, ylocal, radius * .25, theta + M_PI/10);
	spiralSpiral(x, y, radius * .97, theta + M_PI/10);
}

void drawTriangle( int x1, int y1, int x2, int y2, int x3, int y3 ) {
  gfx_line(x1, y1, x2, y2);
  gfx_line(x2, y2, x3, y3);
  gfx_line(x3, y3, x1, y1);
}

void drawSquare(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	gfx_line(x1, y1, x2, y2);
	gfx_line(x2, y2, x3, y3);
	gfx_line(x3, y3, x4, y4);
	gfx_line(x4, y4, x1, y1);
}


