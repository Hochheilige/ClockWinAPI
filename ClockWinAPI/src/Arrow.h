#pragma once

#include "WinAPIWrapper.h"

class Arrow {
public:
	Arrow();
	Arrow(const Line line);
	Arrow(const Point start, const Point finish, const PenStyle style = PenStyle::SOLID,
		  const int32_t width = 1, const StandartColors color = StandartColors::WHITE);
	Arrow(const Point start, const Point finish, const PenStyle style = PenStyle::SOLID,
		  const int32_t width = 1, const Color color = Color());
	
	void Draw(const HDC hdc);
	void Move(const HDC hdc, const double angle);
	inline void SetColor(const Color color) { arrow.SetColor(color); }
	inline void SetColor(const StandartColors color) { arrow.SetColor(color); }


	PenStyle GetStyle() const { return arrow.GetStyle(); }
	Color GetColor() const { return arrow.GetColor(); }
private:
	Line arrow;
	int32_t length;
};

