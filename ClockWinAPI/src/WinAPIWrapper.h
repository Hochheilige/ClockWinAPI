#pragma once

#include <cstdint>
#include <cmath>
#include <vector>

#include <Windows.h>

class Window {
public:
	Window() {
		GetStdHandle(STD_OUTPUT_HANDLE);
		GetConsoleScreenBufferInfo(hStdout, &csbi);
		hWindow = GetConsoleWindow();
		hDeviceContext = GetDC(hWindow);
	}
	~Window() {
		ReleaseDC(hWindow, hDeviceContext);
	}

	inline HANDLE GetHandle() { return hStdout; }
	inline CONSOLE_SCREEN_BUFFER_INFO GetScreenBufferInfo() { return csbi; }
	inline HWND GetWindow() { return hWindow; }
	inline HDC GetDeviceContext() { return hDeviceContext; }
private:
	HANDLE hStdout;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HWND hWindow;
	HDC hDeviceContext;
};

enum class PenStyle {
	SOLID,
	DASH,
	DOT,
	DASHDOT,
	DASHDOTDOT,
	INVISIBLE,
	INSIDEFRAME
};

enum class BrushStyle {
	SOLID,
	HATCH,
	PATTERN
};

enum class HatchTypes {
	HORIZONTAL,
	VERTICAL,
	FDIAGONAL, // from left top to right bottom
	BDIAGONAL, // from left bottom to right top
	CROSS,
	DIAGCROSS,
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

struct Point {
	int32_t x, y;

	Point() : x(0), y(0) {}
	Point(const int32_t x_coord, const int32_t y_coord)
		: x(x_coord), y(y_coord) {
	}
	Point(const Point& point) : x(point.x), y(point.y) {}
};

struct Color {
	uint16_t red, green, blue;

	Color() : red(255), green(255), blue(255) {}
	Color(const uint16_t r, const uint16_t g, const uint16_t b) : red(r), green(g), blue(b) {}
	explicit Color(const StandartColors color) {
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
			case StandartColors::GREEN:
			{
				green = 255;
				red = blue = 0;
				break;
			}
			case StandartColors::BLUE:
			{
				blue = 255;
				red = green = 0;
				break;
			}
			case StandartColors::YELLOW:
			{
				red = green = 255;
				blue = 0;
				break;
			}
			case StandartColors::CYAN:
			{
				green = blue = 255;
				red = 0;
				break;
			}
			case StandartColors::MAGENTA:
			{
				red = blue = 255;
				green = 0;
				break;
			}
			default:
			{
				red = green = blue = 0;
				break;
			}
		}
	}

	COLORREF GetColorRef() const {
		return RGB(red, green, blue);
	};
};

class Pen {
public:
	Pen() : style(PenStyle::SOLID), width(1), color(Color()) {
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	Pen(const PenStyle st, const int32_t w, const Color clr)
		: style(st), width(w), color(clr) {
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	Pen(const PenStyle st, const int32_t w, const StandartColors clr)
		: style(st), width(w), color(clr) {
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	void SetStyle(const PenStyle st) {
		style = st;
		DeleteObject(pen);
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	void SetWidth(const int32_t w) {
		width = w;
		DeleteObject(pen);
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	void SetColor(const Color clr) {
		color = clr;
		DeleteObject(pen);
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	void SetColor(const StandartColors clr) {
		color = Color(clr);
		DeleteObject(pen);
		pen = CreatePen(static_cast<int>(style), width, color.GetColorRef());
	}

	void Select(const HDC hdc) const {
		if (pen)
			SelectObject(hdc, pen);
	}

	PenStyle GetStyle() const { return style; }
	Color GetColor() const { return color; }
private:
	HPEN pen;
	PenStyle style;
	int32_t width;
	Color color;
};

class Brush {
public:
	Brush() {
		style = BrushStyle::SOLID;
		color = Color();
		hatch = HatchTypes::HORIZONTAL;
		bitmap = nullptr;
		brush = CreateSolidBrush(color.GetColorRef());
	}

	Brush(const BrushStyle st, const Color clr,
		  const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
		  const HBITMAP bm = nullptr) {
		style = st;
		color = clr;
		hatch = hatch_type;
		bitmap = bm;
		SelectStyle();
	}

	Brush(const BrushStyle st, const StandartColors clr,
		  const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
		  const HBITMAP bm = nullptr) {
		style = st;
		color = Color(clr);
		hatch = hatch_type;
		bitmap = bm;
		SelectStyle();
	}

	void SetBrushStyle(const BrushStyle st,
					   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
					   const HBITMAP bm = nullptr) {
		style = st;
		hatch = hatch_type;
		bitmap = bm;
		DeleteObject(brush);
		SelectStyle();
	}

	void SetHatch(const HatchTypes hatch_type) {
		hatch = hatch_type;
		DeleteObject(brush);
		SelectStyle();
	}

	void SetColor(const Color clr) {
		color = clr;
		DeleteObject(brush);
		SelectStyle();
	}

	void SetColor(const StandartColors clr) {
		color = Color(clr);
		DeleteObject(brush);
		SelectStyle();
	}

	void SetBitmap(const HBITMAP bm) {
		bitmap = bm;
		DeleteObject(brush);
		SelectStyle();
	}

	void Select(const HDC hdc) {
		if (brush)
			SelectObject(hdc, brush);
	}

	Color GetColor() { return color; }
private:
	HBRUSH brush;
	BrushStyle style;
	Color color;
	HatchTypes hatch;
	HBITMAP bitmap;

	void SelectStyle() {
		switch (style) {
			case BrushStyle::SOLID:
			{
				brush = CreateSolidBrush(color.GetColorRef());
				break;
			}
			case BrushStyle::HATCH:
			{
				brush = CreateHatchBrush(static_cast<int>(hatch), color.GetColorRef());
				break;
			}
			case BrushStyle::PATTERN:
			{
				brush = CreatePatternBrush(bitmap);
				break;
			}
		}
	}
};

class Line {
public:
	Line()
		: entry({ 0, 0 }),
		destination({ 1,1 }),
		pen(Pen()) {
	}

	Line(const Point start, const Point finish, Pen pn)
		: entry(start), destination(finish), pen(pn) {
	}

	Line(const Point start, const Point finish, const PenStyle style = PenStyle::SOLID,
		 const int32_t width = 1, const StandartColors color = StandartColors::WHITE)
		: entry(start), destination(finish),
		pen({ style, width, color }) {
	}

	Line(const Point start, const Point finish, const PenStyle style = PenStyle::SOLID,
		 const int32_t width = 1, const Color color = Color())
		: entry(start), destination(finish),
		pen({ style, width, color }) {
	}

	void Draw(const HDC hdc) const {
		SelectObject(hdc, GetStockObject(NULL_PEN));
		MoveToEx(hdc, entry.x, entry.y, nullptr);
		pen.Select(hdc);
		LineTo(hdc, destination.x, destination.y);
	}

	void SetCoord(const Point start, const Point finish) {
		entry = start;
		destination = finish;
	}

	inline void SetEntry(const Point start) { entry = start; }
	inline void SetDestination(const Point finish) { destination = finish; }
	inline void SetColor(const Color color) { pen.SetColor(color); }
	inline void SetColor(const StandartColors color) { pen.SetColor(color); }
	inline void SetStyle(const PenStyle style) { pen.SetStyle(style); }
	inline void SetWidth(const int32_t width) { pen.SetWidth(width); }
	inline int32_t GetLength() {
		return sqrt(
			pow((destination.x - entry.x), 2) +
			pow((destination.y - entry.y), 2)
		);
	}
	inline Point GetEntry() { return { entry.x, entry.y }; }
	inline Point GetDestination() { return { destination.x, destination.y }; }
	Color GetColor() const { return pen.GetColor(); }
	PenStyle GetStyle() const { return pen.GetStyle(); }
private:
	Point entry, destination;
	Pen pen;
};

class Figure {
public:
	virtual void Draw(const HDC hdc) = 0;
	virtual void SetColor(const Color color) = 0;
	virtual void SetColor(const StandartColors color) = 0;
	inline void SetContourColor(const Color color) { pen.SetColor(color); }
	inline void SetContourColor(const StandartColors color) { pen.SetColor(color); }
	inline void SetContourStyle(const PenStyle style) { pen.SetStyle(style); }
	inline void SetContourWidth(const int32_t width) { pen.SetWidth(width); }
	inline void SetFillColor(const Color color) { brush.SetColor(color); }
	inline void SetFillColor(const StandartColors color) { brush.SetColor(color); }
	inline void SetFillStyle(const BrushStyle style,
							 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
							 const HBITMAP bm = nullptr) {
		brush.SetBrushStyle(style);
	}
	inline void SetFillHatch(const HatchTypes hatch_type) { brush.SetBrushStyle(BrushStyle::HATCH, hatch_type); }
	Point GetCentre() {
		return {
			vertexes[0].x + (vertexes[1].x - vertexes[0].x) / 2,
			vertexes[0].y + (vertexes[1].y - vertexes[0].y) / 2
		};
	}

	std::vector<Point> GetPoints() { return vertexes; }

	Color GetContourColor() { return pen.GetColor(); }
	Color GetFillColor() { return brush.GetColor(); }

protected:
	std::vector<Point> vertexes;
	Pen pen;
	Brush brush;
};

class Triangle : public Figure {
public:
	Triangle() {
		vertexes = {
			{ 100, 0   },
			{ 0  , 100 },
			{ 100, 100 }
		};
		pen = Pen();
		brush = Brush();
	}

	Triangle(const Point v1, const Point v2, const Point v3,
			 const Color inner = Color(), const Color contour = Color(),
			 const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
			 const BrushStyle brush_style = BrushStyle::SOLID,
			 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
			 const HBITMAP bm = nullptr) {
		vertexes = { v1, v2, v3 };
		pen = Pen(pen_style, width, contour);
		brush = Brush(brush_style, inner, hatch_type, bm);
	}

	Triangle(const Point v1, const Point v2, const Point v3,
			 const StandartColors inner = StandartColors::WHITE,
			 const StandartColors contour = StandartColors::WHITE,
			 const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
			 const BrushStyle brush_style = BrushStyle::SOLID,
			 const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
			 const HBITMAP bm = nullptr) {
		vertexes = { v1, v2, v3 };
		pen = Pen(pen_style, width, contour);
		brush = Brush(brush_style, inner, hatch_type, bm);
	}

	void Draw(const HDC hdc) {
		pen.Select(hdc);
		brush.Select(hdc);
		POINT* points = new POINT[3]{
			{ vertexes[0].x, vertexes[0].y },
			{ vertexes[1].x, vertexes[1].y },
			{ vertexes[2].x, vertexes[2].x }
		};
		Polygon(hdc, points, 3);
	}

	void SetVertexes(const Point v1, const Point v2, const Point v3) {
		vertexes[0] = v1;
		vertexes[1] = v2;
		vertexes[2] = v3;
	}

	void SetColor(const Color color) {
		pen.SetColor(color);
		brush.SetColor(color);
	}

	void SetColor(const StandartColors color) {
		pen.SetColor(color);
		brush.SetColor(color);
	}

};

class Rect : public Figure {
public:
	Rect() {
		vertexes = {
			{0, 0},
			{100, 100}
		};
		pen = Pen();
		brush = Brush();
	}

	Rect(const Point left_top, const Point right_bottom,
			   const Color inner = Color(), const Color contour = Color(),
			   const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
			   const BrushStyle brush_style = BrushStyle::SOLID,
			   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
			   const HBITMAP bm = nullptr) {
		vertexes = {
			left_top,
			right_bottom
		};
		pen = Pen(pen_style, width, contour);
		brush = Brush(brush_style, inner, hatch_type, bm);
	}

	Rect(const Point left_top, const Point right_bottom,
			   const StandartColors inner = StandartColors::WHITE,
			   const StandartColors contour = StandartColors::WHITE,
			   const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
			   const BrushStyle brush_style = BrushStyle::SOLID,
			   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
			   const HBITMAP bm = nullptr) {
		vertexes = {
			left_top,
			right_bottom
		};
		pen = Pen(pen_style, width, contour);
		brush = Brush(brush_style, inner, hatch_type, bm);
	}

	void Draw(const HDC hdc) {
		pen.Select(hdc);
		brush.Select(hdc);
		Rectangle(hdc, vertexes[0].x, vertexes[0].y, vertexes[1].x, vertexes[1].y);
	}

	void SetVertexes(const Point left_top, const Point right_bottom) {
		vertexes[0] = left_top;
		vertexes[1] = right_bottom;
	}

	void SetColor(const Color color) {
		pen.SetColor(color);
		brush.SetColor(color);
	}

	void SetColor(const StandartColors color) {
		pen.SetColor(color);
		brush.SetColor(color);
	}
};

class Circle : public Figure {
public:
	Circle() {
		vertexes = {
			{0, 0},
			{100, 100}
		};
		pen = Pen();
		brush = Brush();
	}

	Circle(const Point left_top, const Point right_bottom,
				   const Color inner = Color(), const Color contour = Color(),
				   const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
				   const BrushStyle brush_style = BrushStyle::SOLID,
				   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
				   const HBITMAP bm = nullptr) {
		vertexes = {
			left_top,
			right_bottom
		};
		pen = Pen(pen_style, width, contour);
		brush = Brush(brush_style, inner, hatch_type, bm);
	}

	Circle(const Point left_top, const Point right_bottom,
				   const StandartColors inner = StandartColors::WHITE,
				   const StandartColors contour = StandartColors::WHITE,
				   const PenStyle pen_style = PenStyle::SOLID, const int32_t width = 1,
				   const BrushStyle brush_style = BrushStyle::SOLID,
				   const HatchTypes hatch_type = HatchTypes::HORIZONTAL,
				   const HBITMAP bm = nullptr) {
		vertexes = {
			left_top,
			right_bottom
		};
		pen = Pen(pen_style, width, contour);
		brush = Brush(brush_style, inner, hatch_type, bm);
	}

	void Draw(const HDC hdc) {
		pen.Select(hdc);
		brush.Select(hdc);
		Ellipse(hdc, vertexes[0].x, vertexes[0].y, vertexes[1].x, vertexes[1].y);
	}

	void SetColor(const Color color) {
		pen.SetColor(color);
		brush.SetColor(color);
	}

	void SetColor(const StandartColors color) {
		pen.SetColor(color);
		brush.SetColor(color);
	}

	void SetVertexes(const Point left_top, const Point right_bottom) {
		vertexes[0] = left_top;
		vertexes[1] = right_bottom;
	}
};