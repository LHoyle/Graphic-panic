#include <cmath>
#include "rat.h"
#include "glut.h"
#include "graphics.h"
#include "Maze.h"
Rat::Rat()
{
	mX = 0;
	mY = 0;
	mDegrees = 0;
	//Init(x, y, degrees);
}

Rat::~Rat()
{
}

void Rat::Init(double x, double y, double degrees) {
	mX = x;
	mY = y;
	mDegrees = degrees;
	speed = 1.1;
}
void Rat::ScurryForward(double DT, Maze& prison){
	double radians = mDegrees / 180 * 3.1415926;
	
	double dx = cos(radians) * speed * DT;
	double dy = sin(radians) * speed * DT;
	double newX = mX + dx;
	double newY = mY + dy;
	double RatsRadius = .4;
	if (prison.IsSafe(newX, newY, RatsRadius)) {
		mX = newX;
		mY = newY;
	}
	else if (prison.IsSafe(mX, newY, RatsRadius)) {
		mY = newY;
	}
	else if (prison.IsSafe(newX, mY, RatsRadius)) {
		mX = newX;
	}
	//Draw();
}

void Rat::SpinLeft(double DT) {
	double speed = 150;
	mDegrees += speed * DT;


}
void Rat::SpinRight(double DT) {
	double speed = 150;
	mDegrees = mDegrees - (speed * DT);
}
void Rat::Draw() {
	if (current_view == rat_view)
	{
		return; // drawing yourself in rat view looks bad.
	}

	
	glPushMatrix();
	glTranslated(mX, mY, 0);
	glRotated(mDegrees, 0, 0, 1);
	
	glColor3d(1, 0, 0);
	DrawTriangle(.4, 0, -.2, -.2, -.2, .2);
	DrawCircle(.2, -.1, .09);
	DrawCircle(.2, .1, .09);

	glColor3d(0, 0, 0);
	DrawText(0, 0, "rat");

	glColor3d(1, 1, 1);
	glPopMatrix();
}