#include "Figures.h"

Line::Color::Color(StandartColors color) {
	switch (color) {
		case StandartColors::WHITE:
		{
			red = green = blue = 255;
			break;
		}
		case StandartColors::BLACK:
		{
			red = green = blue = 0;
			break;
		}
		case StandartColors::RED:
		{
			red = 255;
			green = blue = 0;
			break;
		}
		case StandartColors::GREEN: {
			green = 255;
			red = blue = 0;
			break;
		}
		case StandartColors::BLUE: {
			blue = 255;
			red = green = 0;
			break;
		}
		case StandartColors::YELLOW: {
			red = green = 255;
			blue = 0;
			break;
		}
		case StandartColors::CYAN: {
			green = blue = 255;
			red = 0;
			break;
		}
		case StandartColors::MAGENTA: {
			red = blue = 255;
			green = 0;
			break;
		}
		default: {
			red = green = blue = 0;
			break;
		}	
	}
}

Line::Line() : entry(Point()), destination(Point(1, 0)), color() {
	pen = CreatePen(static_cast<int>(Style::SOLID), 1, RGB(color.red, color.green, color.blue));
}

Line::Line(const Point& ent, const Point& dest, Style style, uint32_t width, StandartColors clr)
	: entry(ent), destination(dest), color(clr) {
	pen = CreatePen(static_cast<int>(style), width, RGB(color.red, color.green, color.blue));
}

Line::Line(const Point& ent, const Point& dest, Style style, uint32_t width, uint16_t r, uint16_t g, uint16_t b) 
	: entry(ent), destination(dest), color(r, g, b) {
	pen = CreatePen(static_cast<int>(style), width, RGB(color.red, color.green, color.blue));
}

Line::~Line() {
	DeleteObject(pen);
}

void Line::Select(const HDC& hdc) {
	SetPen();
	SelectObject(hdc, pen);
}

void Line::Draw(const HDC& hdc) const {
	SelectObject(hdc, pen);
	MoveToEx(hdc, entry.x, entry.y, NULL);
	LineTo(hdc, destination.x, destination.y);
}

void Line::SetEntryPoint(const Point& point) {
	entry = point;
}

void Line::SetDestPoint(const Point& point) {
	destination = point;
}

void Line::SetPoints(const Point& ent, const Point& dest) {
	entry = ent;
	destination = dest;
}

void Line::SetColor(StandartColors clr) {
	color = Color(clr);
}

void Line::SetPen(Style style, uint32_t width, StandartColors clr) {
	color = Color(clr);
	SetPen(style, width);
}

void Line::SetPen(Style style, uint32_t width) {
	pen = CreatePen(static_cast<int>(style), width, RGB(color.red, color.green, color.blue));
}

void Line::SetPen() {
	pen = CreatePen(static_cast<int>(Style::SOLID), 1, RGB(color.red, color.green, color.blue));
}

Triangle::Triangle() {
	vertexes[0] = {0, 0};
	vertexes[1] = {1, 0};
	vertexes[2] = {0, 1};
	line = Line();
	Line::Color tmp = Line::Color(StandartColors::WHITE);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

Triangle::Triangle(StandartColors color) {
	vertexes[0] = { 0, 0 };
	vertexes[1] = { 1, 0 };
	vertexes[2] = { 0, 1 };
	line = Line();
	line.SetColor(color);
	Line::Color tmp = Line::Color(color);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

Triangle::Triangle(Line::Point* const v, StandartColors color) : vertexes(v){
	line = Line();
	line.SetPoints(vertexes[0], vertexes[1]);
	line.SetColor(color);
	Line::Color tmp = Line::Color(color);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

Triangle::Triangle(const Line::Point& v1, const Line::Point& v2, const Line::Point& v3, StandartColors color) {
	vertexes[0] = v1;
	vertexes[1] = v2;
	vertexes[2] = v3;
	line = Line();
	line.SetPoints(vertexes[0], vertexes[1]);
	line.SetColor(color);
	Line::Color tmp = Line::Color(color);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

Triangle::~Triangle() {
	delete[] vertexes;
	DeleteObject(brush);
}

void Triangle::Draw(const HDC& hdc) {
	POINT points[3] = {
		{vertexes[0].x, vertexes[0].y},
		{vertexes[1].x, vertexes[1].y},
		{vertexes[2].x, vertexes[2].y},
	};
	line.Bind(hdc);
	SelectObject(hdc, brush);
	Polygon(hdc, points, 3);
}

void Triangle::SetLine(Style style, uint32_t width, StandartColors clr) {
	line.SetPen(style, width, clr);
}

void Triangle::SetLine(Style style, uint32_t width) {
	line.SetPen(style, width);
}

void Triangle::SetColor(StandartColors color) {
	line.SetColor(color);	
	Line::Color tmp = Line::Color(color);
	brush = CreateSolidBrush(RGB(tmp.red, tmp.green, tmp.blue));
}

void Triangle::SetVertexes(Line::Point* const v) {
	vertexes = v;
}

void Triangle::SetVertexes(const Line::Point& v1, const Line::Point& v2, const Line::Point& v3) {
	vertexes[0] = v1;
	vertexes[1] = v2;
	vertexes[2] = v3;
}

