/*==================================================================================================
 PROGRAMMER:			Thomas Kroll, Nathan Kroll
 COURSE:				CSC 525/625
 MODIFIED BY:			Thomas Kroll, kroll001
 LAST MODIFIED DATE:	9/26/2016
 DESCRIPTION:			
 NOTE:					N/A
 FILES:					project1.cpp, (projProject.sln, ...)
 IDE/COMPILER:			MicroSoft Visual Studio 2013
 INSTRUCTION FOR COMPILATION AND EXECUTION:
	1.		Double click on myCPPproj.sln	to OPEN the project
	2.		Press Ctrl+F7					to COMPILE
	3.		Press Ctrl+Shift+B				to BUILD (COMPILE+LINK)
	4.		Press Ctrl+F5					to EXECUTE
==================================================================================================*/
#include <iostream>
#include <GL/glut.h>				// include GLUT library


//***********************************************************************************
// GLOBALS: for user controlled text to display.
GLubyte bitmap[] = {
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00,
	0x00, 0xE0, 0x00, 0x00,
	0x01, 0xF8, 0xC0, 0x00,
	0x00, 0x3F, 0xC0, 0x00,
	0x18, 0x00, 0x40, 0x00,
	0x3E, 0x00, 0x40, 0x00,
	0x1F, 0xC0, 0xC0, 0x00,
	0x03, 0xE0, 0xC0, 0x00,
	0x00, 0x60, 0xC0, 0x00,
	0x00, 0x61, 0x80, 0x00,
	0x00, 0x61, 0x80, 0x00,
	0x00, 0x61, 0x00, 0x00,
	0x00, 0x43, 0x00, 0x00,
	0x00, 0x43, 0x00, 0x00,
	0x00, 0x46, 0x00, 0x00,
	0x00, 0xCE, 0x00, 0x00,
	0x00, 0xCE, 0x00, 0x00,
	0x00, 0xCE, 0x00, 0x00,
	0x00, 0xCE, 0x00, 0x00,
	0x00, 0xCE, 0x00, 0x00,
	0x00, 0xEE, 0x00, 0x00,
	0x00, 0xFE, 0x00, 0x00,
	0x00, 0xFE, 0x10, 0x00,
	0x00, 0xFE, 0x70, 0x00,
	0x00, 0xFF, 0xC0, 0x00,
	0x01, 0xFF, 0x80, 0x00,
	0x01, 0xFF, 0xF0, 0x00,
	0x01, 0xFC, 0x0F, 0x00,
	0x01, 0xFC, 0x03, 0x00,
	0x01, 0xFC, 0x06, 0x00,
	0x01, 0xFC, 0x0C, 0x00,
	0x01, 0xFC, 0x18, 0x00,
	0x01, 0xFC, 0x30, 0x00,
	0x00, 0xFC, 0x60, 0x00,
	0x00, 0xFE, 0xE0, 0x00,
	0x00, 0xFF, 0xC0, 0x00,
	0x00, 0xFF, 0x80, 0x00,
	0x01, 0xFF, 0x00, 0x00,
	0x03, 0xFE, 0x00, 0x00,
	0x07, 0x80, 0x00, 0x00,
	0x07, 0x1C, 0x00, 0x00,
	0x0C, 0x3F, 0x00, 0x00,
	0x1C, 0x3F, 0x80, 0x00,
	0x18, 0x3F, 0xC0, 0x00,
	0x19, 0xFF, 0xE0, 0x00,
	0x30, 0x3F, 0xF0, 0x00,
	0x30, 0x1F, 0xF0, 0x00,
	0x30, 0x0F, 0xF0, 0x00,
	0x30, 0x0F, 0xF0, 0x00,
	0x3E, 0x07, 0xF0, 0x00,
	0x0F, 0xFB, 0xF0, 0x00,
	0x00, 0x19, 0xF0, 0x00,
	0x00, 0x08, 0x40, 0x00,
	0x00, 0x0F, 0x04, 0x00,
	0x00, 0x0F, 0x00, 0x00,
	0x00, 0x00, 0x01, 0xC0,
	0x00, 0x00, 0x00, 0x40,
	0x00, 0x00, 0x00, 0x20,
	0x00, 0x00, 0x00, 0xC0,
	0x00, 0x00, 0x00, 0x00,
};

float slope(int top1, int top2, int bottom1, int bottom2){
	return float(top2 - top1) / (bottom2 - bottom1);

}

int getY(float m, int x, int x1, int y1){
	return int((m*(x - x1)) + y1);
}

int getX(float m, int y, int y1, int x1){
	return int(((y - y1) / m) + x1);
}

void drawLine(int x1, int y1, int x2, int y2){
	float m = slope(y1, y2, x1, x2);
	glBegin(GL_POINTS);
	if (m < 1 && m > -1){
		if (x1 < x2){
			for (int x = x1; x < x2; x++){
				glVertex2i(x, getY(m, x, x1, y1));
			}
		}
		else if (x1 == x2 && y1 < y2){
			for (int y = y1; y < y2; y++){
				glVertex2i(x1, y);
			}
		}
		else if (x1 == x2 && y1 > y2){
			for (int y = y2; y < y1; y++){
				glVertex2i(x1, y);
			}
		}
		else{
			for (int x = x2; x < x1; x++){
				glVertex2i(x, getY(m, x, x1, y1));
			}
		}
	}
	else{
		if (y1 < y2){
			for (int y = y1; y < y2; y++){
				glVertex2i(getX(m, y, y1, x1), y);
			}
		}
		else if (y1 == y2 && x1 < x2){
			for (int x = x1; x < x2; x++){
				glVertex2i(x, y1);
			}
		}
		else if (y1 == y2 && x1 > x2){
			for (int x = x2; x < x1; x++){
				glVertex2i(x, y1);
			}
		}
		else{
			for (int y = y2; y < y1; y++){
				glVertex2i(getX(m, y, y1, x1), y);
			}
		}
	}
	glEnd();
}

void displayBitmap(){
	glColor3f(0.9, 0.0, 0.6);
	glRasterPos2i(0, 0);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
	glBitmap(27, 65, 0, 0, 0, 0, bitmap);
}

void drawGrid()
{ // Draw the Coordinate Grid.
 glPointSize(1);		// change point size back to 1
 glColor3f(0, 0, 0);
 glRasterPos2i(152, 0);
 glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'X');
 glRasterPos2i(0, 152);
 glutBitmapCharacter(GLUT_BITMAP_8_BY_13, 'Y');
 glBegin(GL_POINTS);	// use points to form X-/Y-axes
   glColor3f(0, 0, 0);  // change drawing color to black

   for (int x=-150; x<=150; x++) // draw X-axis
     glVertex2i(x, 0);
   for (int y=-150; y<=150; y++) // draw Y-axis
     glVertex2i(0, y);
 glEnd();
}

//***********************************************************************************
void myInit()
{glClearColor(1, 1, 1, 0);			// specify a background clor: white 
 gluOrtho2D(-200, 200, -200, 200);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{glClear(GL_COLOR_BUFFER_BIT);	// draw the background
 drawGrid();
 displayBitmap();
 glFlush(); // flush out the buffer contents
}


//***********************************************************************************
int main()
{
    //====================================================================//
    // These lines are only here so I can work on this at home
    // since the only c++ compiler available to me is g++
    int argc = 1;
    char *argv[1] = {(char*)"Something"};
    glutInit(&argc, argv);
    //====================================================================//

    glutInitWindowSize(400, 400);				// specify a window size
    glutInitWindowPosition(100, 0);			// specify a window position
    glutCreateWindow("Text Display");			// create a titled window

    myInit();									// setting up



    glutDisplayFunc(myDisplayCallback);		// register a callback


    glutMainLoop();							// get into an infinite loop
}
