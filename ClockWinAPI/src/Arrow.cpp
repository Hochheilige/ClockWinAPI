#include "Arrow.h"

Arrow::Arrow() {
	arrow = Line();
	length = arrow.GetLength();
}

Arrow::Arrow(const Line line) {
	arrow = Line(line);
	length = arrow.GetLength();
}

Arrow::Arrow(const Point start, const Point finish, const PenStyle style, const int32_t width, const StandartColors color) {
	arrow = Line(start, finish, style, width, color);
	length = arrow.GetLength();
}

Arrow::Arrow(const Point start, const Point finish, const PenStyle style, const int32_t width, const Color color) {
	arrow = Line(start, finish, style, width, color);
	length = arrow.GetLength();
}

void Arrow::Draw(const HDC hdc) {
	arrow.Draw(hdc);
}

void Arrow::Move(const HDC hdc, const double angle) {
	Point old_dest = arrow.GetEntry();
	int32_t x = old_dest.x + length * cos(angle);
	int32_t y = old_dest.y + length * sin(angle);
	arrow.SetDestination({ x, y });
	Draw(hdc);
}
