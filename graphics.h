#pragma once
void DrawTriangle(double x1, double y1, double x2, double y2, double x3, double y3);
void DrawRectangle(double x1, double y1, double x2, double y2);
void DrawCircle(double x1, double y1, double radius);
void DrawText(double x, double y, const char* string);

enum viewtype { top_view, perspective_view, rat_view };
extern viewtype current_view;


void SetTopView(int w, int h);

void SetPerspectiveView(int w, int h);

double GetDeltaTime();