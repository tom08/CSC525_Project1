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
#include <cmath>
#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include <time.h>
#include <GL/glut.h>				// include GLUT library


//***********************************************************************************
// GLOBALS: for user controlled text to display.
GLubyte bitmap[256];
//Pixel Map
GLfloat picture[675][900][3];
// Window dimentions
int windowX = 900;
int windowY = 676;

class Pixel {
public:
	Pixel(int x, int y) {
		xPos = x;
		yPos = y;
	}

	Pixel(int x, int y, float color[]) {
		xPos = x;
		yPos = y;
		red = color[0];
		green = color[1];
		blue = color[2];
	}

	Pixel(int x, int y, float r, float g, float b) {
		xPos = x;
		yPos = y;
		red = r;
		green = g;
		blue = b;
	}

	void setXPos(int x) {
		xPos = x;
	}

	int getXPos() {
		return xPos;
	}

	void setYPos(int y) {
		yPos = y;
	}

	int getYPos() {
		return yPos;
	}

	int* getPosArray() {
		int pointArray[2];
		pointArray[0] = xPos;
		pointArray[1] = yPos;
		return pointArray;
	}

	void setRed(float r) {
		red = r;
	}

	float getRed() {
		return red;
	}

	void setGreen(float g) {
		green = g;
	}

	float getGreen() {
		return green;
	}

	void setBlue(float b) {
		blue = b;
	}

	float getBlue() {
		return blue;
	}

	float* getColorArray() {
		float colorArray[3];
		colorArray[0] = red;
		colorArray[1] = green;
		colorArray[2] = blue;
		return colorArray;
	}

	std::string getPosAsString() {
		return "[" + std::to_string(xPos) + "," + std::to_string(yPos) + "]";
	}

	std::string getColorAsString() {
		return std::to_string(red) + " " + std::to_string(green) + " " + std::to_string(blue);
	}

private:
	int xPos;
	int yPos;
	float red;
	float green;
	float blue;
};

int getRandomCoord(int max, int min) {
	return rand() % max + min;
}

// GLOBALS: for user controlled text to display.
//10 - A, 11 - B, 12 - C, 13 - D, 14 - E, 15 - F
GLubyte tinyTree[] = {
	0x00, 0x00, 0x00,  //1
	0x00, 0x00, 0x00,  //2
	0x07, 0xc0, 0x00, //3
	0x01, 0xc0, 0x00, //4
	0x00, 0x80, 0x00, //5
	0x00, 0xc0, 0x00, //6
	0x00, 0x40, 0x00, //7
	0x00, 0x40, 0x00, //8
	0x00, 0x60, 0x00, //9
	0x00, 0x38, 0x00, //10
	0x00, 0x28, 0x00, //11
	0x00, 0xe8, 0x00, //12
	0x00, 0xff, 0x00, //13
	0x0f, 0xf7, 0xf8, //14
	0x0f, 0xff, 0xf8, //15
	0x0f, 0xff, 0xfe, //16
	0x07, 0xff, 0xfe, //17
	0x0f, 0xff, 0xfe, //18
	0x0f, 0xff, 0xfc, //19
	0x1f, 0xff, 0xfe, //20
	0x1f, 0xff, 0xfe, //21
	0x0f, 0xff, 0xf8, //22
	0x03, 0xff, 0xf8, //23
	0x01, 0xbf, 0xd0  //24
};


//Lines
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
//

void drawPixelMap() {
	glRasterPos2i(-(windowX / 2), -(windowY / 2));
	glDrawPixels(900, 675, GL_RGB, GL_FLOAT, picture);
}


//Characters
void drawChar(int aChar, bool smallText = false) {
	if (smallText) {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, aChar);
	}
	else {
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, aChar);
	}
}

//Mulitple characters - text
void drawText(std::string text) {
	glColor3f(.7, .5, .3);

	glRasterPos2i(-200, 30);
	for (int i = 0; i < text.length(); i++) {
		drawChar(text[i]);
	}
}

//Polygon
void drawPolygon(std::vector<Pixel> points, bool usePointColor = false) {

	glEnable(GL_POLYGON_STIPPLE);
	glPolygonStipple(tinyTree);
	glBegin(GL_POLYGON);
	glColor3f(0, .5, 1);
	for (int i = 0; i < points.size(); i++) {
		if (usePointColor) {
			glColor3fv(points.at(i).getColorArray());
		}
		glVertex2iv(points.at(i).getPosArray());
	}
	glEnd();

}

//Circle
float convertToRadians(int degree) {
	float pi = 3.14159265359;
	return degree * pi / 180;
}

void drawCircle(int radius, int xInit = 0, int yInit = 0) {
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int deg = 0; deg <= 360; deg++) {
		float rad = convertToRadians(deg);
		float xPos = xInit + radius * cos(rad);
		float yPos = yInit - radius * sin(rad);
		glColor3f(0, 1, 0);
		glVertex2f(xPos, yPos);

	}
	glEnd();
}


//Bitmap
void displayBitmap(){
	glColor3f(0, .9, 0);
	glRasterPos2i(getRandomCoord(windowX, -(windowX / 2)), getRandomCoord(windowY, -(windowY / 2)));
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBitmap(24, 24, 0, 0, 0, 0, tinyTree);
}

void drawTinyTrees() {
	srand(time(NULL));
	for (int i = 0; i < 5; i++) {
		displayBitmap();
	}
}

void drawCoordinateSystem() {
	glPointSize(1);		// change point size back to 1

	glBegin(GL_POINTS);	// use points to form X-/Y-axes
	glColor3f(0, 0, 0);			 // change drawing color to black
	for (int x = -150; x <= 150; x++) // draw X-axis
		glVertex2i(x, 0);
	for (int y = -150; y <= 150; y++) // draw Y-axis
		glVertex2i(0, y);
	glEnd();
	glRasterPos2i(5, 140);
	drawChar('Y', true);
	glRasterPos2i(140, 5);
	drawChar('X', true);
}

void read_pixel_map(){
    std::string fname;
    // TODO:  REMOVE THIS WHEN WE TURN IN THE PROJECT.
    // replace with correct path to execute on Trace.
#ifdef WINDOWS
    fname = "C:\\School\\CSC525\\Project 1\\CSC525_Project1\\pixel_map.txt";
#else
    fname = "pixel_map.txt";
#endif
    std::fstream fin;
    fin.open(fname);
    float r, g, b;
    int y = 0;
    int x = 0;
    if(fin.is_open()){
        while(fin >> r){
            fin >> g;
            fin >> b;
            picture[y][x][0] = r;
            picture[y][x][1] = g;
            picture[y][x][2] = b;
            x++;
            if(x == 900){
                x = 0;
                y++;
            }
        }
    }
}

//***********************************************************************************
void myInit()
{glClearColor(1, 1, 1, 0);			// specify a background clor: white 
 int x = windowX / 2;
 int y = windowY / 2;
 gluOrtho2D(-x, x, -y, y);  // specify a viewing area
}

//***********************************************************************************
void myDisplayCallback()
{
    glClear(GL_COLOR_BUFFER_BIT);	// draw the background
    drawPixelMap();
    drawTinyTrees();
    glFlush(); // flush out the buffer contents
}


//***********************************************************************************
int main()
{
    //====================================================================//
    // These lines are only here so I (Thomas) can work on this at home
    // since the only c++ compiler available to me is g++
    // (Visual Studio and Linux don't play well together)
    int argc = 1;
    char *argv[1] = {(char*)"Something"};
    glutInit(&argc, argv);
    //====================================================================//

    glutInitWindowSize(windowX, windowY);				// specify a window size
    glutInitWindowPosition(100, 0);			// specify a window position
    glutCreateWindow("Text Display");			// create a titled window

    myInit();									// setting up
    read_pixel_map();


    glutDisplayFunc(myDisplayCallback);		// register a callback


    glutMainLoop();							// get into an infinite loop
}
