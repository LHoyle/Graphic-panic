#pragma once

const int M = 16;
const int N = 12;
void InitMaze();

class Cell
{
public:
	Cell()
	{
		l = t = r = b = true;
		visited = false;
	}
	void Draw(int i, int j);

	bool l, t, r, b, visited;
};

class Maze
{
public:
	Maze();
	void Init();
	void RemoveWalls(int i, int j);
	void Draw();
	bool IsSafe(double x, double y, double radius);
	int GetStartX();


private:
	Cell mCells[M][N];
	int startx;
};