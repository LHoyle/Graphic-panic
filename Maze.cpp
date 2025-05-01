#include <vector>
#include <iostream>
using namespace std;

#include "glut.h"
#include "Maze.h"
#include "graphics.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#if WIN32
#include "glut.h"
#elif (__APPLE__) // Apple
#include <GLUT/glut.h>
#else // Linux
#include <GL/freeglut.h>
#endif


// Textures
const int num_textures = 3;
unsigned int texName[num_textures];

void Cell::Draw(int i, int j)
{

	if (current_view == top_view)
	{
		if (l)
		{
			glBegin(GL_LINES);
			glVertex2d(i, j);
			glVertex2d(i, j + 1);
			glEnd();
		}
		if (b)
		{
			glBegin(GL_LINES);
			glVertex2d(i, j);
			glVertex2d(i + 1, j);
			glEnd();
		}
		if (r)
		{
			glBegin(GL_LINES);
			glVertex2d(i + 1, j);
			glVertex2d(i + 1, j + 1);
			glEnd();
		}
		if (t)
		{
			glBegin(GL_LINES);
			glVertex2d(i, j + 1);
			glVertex2d(i + 1, j + 1);
			glEnd();
		}
	}
	else {
		
		//be a problem child
		if (l)
		{
			unsigned char r = ((i * 7992037450 + j * 2349812154192874) % 256);
			unsigned char g = ((i * 79283592257450 + j * 236984192874) % 256);
			unsigned char b = ((i * 79282542037450 + j * 234981492874) % 256);
			
			
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texName[0]);
			glBegin(GL_QUADS);
			/*
			glVertex3d(i, j,0);
			glVertex3d(i, j + 1,0);
			glVertex3d(i, j + 1,1);
			glVertex3d(i, j,1);
			*/
			glTexCoord2f(0, 1); glVertex3d(i, j, 0);
			glTexCoord2f(1, 1); glVertex3d(i, j + 1, 0);
			glTexCoord2f(1, 0); glVertex3d(i, j + 1, 1);
			glTexCoord2f(0, 0); glVertex3d(i, j, 1);
			
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		if (b==true && j==0)
		{
			unsigned char r = ((i * 79283592037450 + j * 2349854192874) % 256);
			unsigned char g = ((i * 79292257450 + j * 2349256984192874) % 256);
			unsigned char b = ((i * 79282542037450 + j * 2349812392874) % 256); 

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texName[1]);
			glBegin(GL_QUADS);
			glTexCoord3f(0, 3,0);glVertex3d(i, j,0);
			glTexCoord3f(3, 3,0);glVertex3d(i + 1, j,0);
			glTexCoord3f(3, 0,1);glVertex3d(i + 1, j,1);
			glTexCoord3f(0, 0,1);glVertex3d(i, j,1);
			
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		if (r)
		{
			/*unsigned char r = ((i * 79283592 + j * 2349812154192874) % 256);
			unsigned char g = ((i * 792835922 + j * 234925698419287) % 256);
			unsigned char b = ((i * 792825420 + j * 234981235649287) % 256);
			glColor3ub(r, g, b); */

			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texName[0]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 1);glVertex3d(i + 1, j,0);
			glTexCoord2f(1, 1);glVertex3d(i + 1, j + 1,0);
			glTexCoord2f(1, 0);glVertex3d(i + 1, j + 1,1);
			glTexCoord2f(0, 0);glVertex3d(i + 1, j,1);
			
			glEnd();
			glDisable(GL_TEXTURE_2D);
		}
		if (t)
		{
			unsigned char r = ((i * 79283592037450 + j * 2349812154192874) % 256);
			unsigned char g = ((i * 79283592257450 + j * 2349256984192874) % 256);
			unsigned char b = ((i * 79282542037450 + j * 2349812356492874) % 256);
			glColor3ub(r, g, b);
			
			
			glEnable(GL_TEXTURE_2D);
			glBindTexture(GL_TEXTURE_2D, texName[2]);
			glBegin(GL_QUADS);
			glTexCoord2f(0, 3); glVertex3d(i, j + 1, 0);
			glTexCoord2f(1, 3); glVertex3d(i + 1, j + 1, 0);
			glTexCoord2f(1, 0); glVertex3d(i + 1, j + 1, 1);
			glTexCoord2f(0, 0); glVertex3d(i, j + 1, 1);
			glEnd(); 
			glDisable(GL_TEXTURE_2D);
			
		}
		
	}

}

Maze::Maze()
{
	startx = 0;
	//Init();
	
}

void Maze::Init()
{
	RemoveWalls(0, 0);
	//startx = 0;
	// Knock out 1 bottom wall and 1 top wall
	startx = rand() % M;
	mCells[startx][0].b = false;
	mCells[rand() % M][N-1].t = false;
}

void Maze::RemoveWalls(int i, int j)
{
	mCells[i][j].visited = true;
	enum class direction { LEFT, UP, RIGHT, DOWN };

	while (true)
	{
		std::vector<direction> move;

		// Can we go left?
		if (i - 1 >= 0 && !mCells[i - 1][j].visited)
			move.push_back(direction::LEFT);
		// Can we go UP?
		if (j + 1 < N && !mCells[i][j + 1].visited)
			move.push_back(direction::UP);
		// Can we go right?
		if (i + 1 < M && !mCells[i + 1][j].visited)
			move.push_back(direction::RIGHT);
		// Can we go DOWN?
		if (j - 1 >= 0 && !mCells[i][j - 1].visited)
			move.push_back(direction::DOWN);

		if (move.size() == 0)
			return; // no possible moves forward

		int r = rand() % move.size();

		if (move[r] == direction::LEFT)
		{
			mCells[i][j].l = false;
			mCells[i - 1][j].r = false;
			RemoveWalls(i - 1, j);
		}
		else if (move[r] == direction::RIGHT)
		{
			mCells[i][j].r = false;
			mCells[i + 1][j].l = false;
			RemoveWalls(i + 1, j);
		}
		else if (move[r] == direction::UP)
		{
			mCells[i][j].t = false;
			mCells[i][j + 1].b = false;
			RemoveWalls(i, j + 1);
		}
		else // if (move[r] == direction::DOWN)
		{
			mCells[i][j].b = false;
			mCells[i][j - 1].t = false;
			RemoveWalls(i, j - 1);
		}

		// repeat for other 3 directions
	}
}

void Maze::Draw()
{
	if (current_view == top_view)
	{
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				mCells[i][j].Draw(i, j);
	}
	else
	{
		// draw walls as GL_QUADS
		// figure out a way to draw each wall in a different color. (you don't have to save the color of the wall)
		// figure out a way to prevent two co-planar wall from 'bleeding' on top of each other when drawing.
		for (int i = 0; i < M; i++)
			for (int j = 0; j < N; j++)
				mCells[i][j].Draw(i, j);
	}

	
}
int Maze::GetStartX() {
	return startx;
}

bool Maze::IsSafe(double x, double y, double radius) {
	//check right wall of current cell
	//we made all cells one big on purpose. 
	int cellX = (int)x;
	int cellY = (int)y;
	double offsetX = x-cellX;
	double offsetY = y - cellY;
	if (Maze::mCells[cellX][cellY].l && offsetX - radius <= 0) {

		//left
		return false;
	}
	if (Maze::mCells[cellX][cellY].t && offsetY + radius >= 1.0) {
		
		//top
		return false;
	}
	if (Maze::mCells[cellX][cellY].r && offsetX + radius >= 1.0) {
		//right
		return false;
	}
	if (Maze::mCells[cellX][cellY].b && offsetY - radius <= 0) {
		//bottom
		return false;
	}
	//we can never go in a corner. so we need to make a case so it doens't happen
	//check right bottom corner
	if (offsetX + radius >= 1.0 && offsetY - radius <= 0) {
		return false;
	}
	//now we need to check for the others as well
	if (offsetX - radius <= 0 && offsetY - radius <= 0) {
		return false;
	}
	if (offsetX + radius >= 1.0 && offsetY + radius >= 1.0) {
		return false;
	}
	if (offsetX - radius <= 0 && offsetY + radius >= 1.0) {
		return false;
	}


	//we also have an array out of bounds case for trrying to get outside the maze
	return true;
}

void InitMaze() {
	const char max_file_size = 100;
	char imageFiles[num_textures][max_file_size] = { "catacombes_no_Watermark.jpg", "skull_textture.jpg","steel.jpg"};

	glGenTextures(num_textures, texName);
	std::cout << imageFiles;
	for (int i = 0; i < num_textures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, texName[i]);
		glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
		glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width, height, nrChannels;
		unsigned char* data = stbi_load(imageFiles[i], &width, &height, &nrChannels, 0);
		if (data)
		{
			gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGB, width, height, GL_RGB, GL_UNSIGNED_BYTE, data);
			// NOTE: If the above command doesn't work, try it this way:
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
				//glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);
	}

}