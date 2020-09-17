#pragma once

#include <cstdint>
#include <vector>

#include "Window.h"

enum class Style {
	SOLID,
	DASH, 
	DOT,
	DASHDOT,
	DASHDOTDOT,
	INVISIBLE,
	INSIDEFRAME
};

enum class StandartColors {
	WHITE,
	BLACK,
	RED, 
	GREEN,
	BLUE,
	YELLOW,
	CYAN,
	MAGENTA
};

class Line {
public:
	struct Point {
		int32_t x, y;

		Point() : x(0), y(0) {}
		Point(const uint32_t x_coord, const uint32_t y_coord)
			: x(x_coord), y(y_coord) {}
		Point(const Point& point) : x(point.x), y(point.y) {}
	};

	struct Color {
		uint16_t red, green, blue;

		Color() : red(0), green(0), blue(0) {}
		Color(uint16_t r, uint16_t g, uint16_t b) : red(r), green(g), blue(b) {}
		explicit Color(StandartColors color);
	};

	Line();
	Line(const Point& ent, const Point& dest, Style style, uint32_t width, StandartColors clr);
	Line(const Point& ent, const Point& dest, Style style, uint32_t width, uint16_t r, uint16_t g, uint16_t b);
	~Line();

	void Select(const HDC& hdc);
	void Draw(const HDC& hdc) const;
	void SetEntryPoint(const Point& point);
	void SetDestPoint(const Point& point);
	void SetPoints(const Point& ent, const Point& dest);
	void SetColor(StandartColors clr);
	void SetPen(Style style, uint32_t width, StandartColors clr);
	void SetPen(Style style, uint32_t width);
	void SetPen();

private:
	Point entry, destination;
	HPEN pen;
	Color color;
};

class Figure {
public:
	virtual void Draw(const HDC& hdc) = 0;
	virtual void SetLine(Style style, uint32_t width, StandartColors clr) = 0;
	virtual void SetLine(Style style, uint32_t width) = 0;
	virtual void SetColor(StandartColors color) = 0;
protected:
	Line line;
};

class Triangle : public Figure {
public:
	Triangle();
	Triangle(StandartColors color);
	Triangle(Line::Point* const v, StandartColors color = StandartColors::WHITE);
	Triangle(const Line::Point& v1, const Line::Point& v2, const Line::Point& v3, StandartColors color = StandartColors::WHITE);
	~Triangle();

	void Draw(const HDC& hdc) override;
	void SetLine(Style style, uint32_t width, StandartColors clr) override;
	void SetLine(Style style, uint32_t width) override;
	void SetColor(StandartColors color) override;
	void SetVertexes(Line::Point* const v);
	void SetVertexes(const Line::Point& v1, const Line::Point& v2, const Line::Point& v3);
	
private:
	Line::Point* vertexes = new Line::Point[3]();
	HBRUSH brush;
};

class Rect : public Figure {
public:

private:
	Line::Point* vertexes = new Line::Point[2]();
};

class Circle : public Figure {
public:

private:
	Line::Point* centre = new Line::Point();
	uint32_t radius;
};

