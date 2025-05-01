#pragma once
#include "Maze.h"
class Rat
{
public:
	Rat();
	~Rat(); 
	void Init(double x, double y, double degrees);
	void ScurryForward(double DT, Maze & prison);
	void SpinLeft(double DT);
	void SpinRight(double DT);
	void Draw();



	double GetX() 
	{ 
		return mX;
	}
	double GetY() 
	{ 
		return mY;
	}
	double GetDY(double DT) {
		double radians = mDegrees / 180 * 3.1415926; 
		double dy = sin(radians) * speed * DT;
		return dy;
	}
	double GetDX(double DT) {
		double radians = mDegrees / 180 * 3.1415926;
		double dx = cos(radians) * speed * DT;
		return dx;
	}

private:
	double mDegrees;
	double mX;
	double mY;
	double speed;
};

