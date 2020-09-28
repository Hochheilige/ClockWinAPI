#pragma once

#include <mutex>

#include "Arrow.h"
#include "Time.h"

#define PI 3.14159265358979323846

template<class Form>
class Clock {
public:
	Clock() : sec_angle(-PI / 2), min_angle(-PI / 2), hrs_angle(-PI / 2) {
		form = {
			{ 0, 200 }, { 200, 0 },
			StandartColors::WHITE, StandartColors::BLACK,
			PenStyle::SOLID, 5
		};
		Point centre = form.GetCentre();
		hours = { centre, { 100, 50 }, PenStyle::SOLID, 3, StandartColors::BLACK };
		minutes = { centre, { 100, 30 }, PenStyle::SOLID, 2, StandartColors::BLACK };
		seconds = { centre, { 100, 10 }, PenStyle::SOLID, 1, StandartColors::BLACK };
		time = Time();
	}

	Clock(const Form figure) : sec_angle(-PI / 2), min_angle(-PI / 2 + PI / 16), hrs_angle(-PI / 2 + PI / 8) {
		form = Form(figure);
		Point centre = form.GetCentre();
		int32_t y = form.GetPoints()[0].y - centre.y;
		int32_t y_hours = centre.y - y * 0.5;
		int32_t y_minutes = centre.y - y * 0.7;
		int32_t y_seconds = centre.y - y * 0.9;
		hours = { centre, { centre.x, y_hours }, PenStyle::SOLID, 3, form.GetContourColor() };
		minutes = {centre, Point(centre.x, y_minutes), PenStyle::SOLID, 2, form.GetContourColor()};
		seconds = {centre, Point(centre.x, y_seconds), PenStyle::SOLID, 1, form.GetContourColor()};
		time = Time();
	}
	
	void Draw(const HDC hdc) {
		form.Draw(hdc);
		hours.Draw(hdc);
		minutes.Draw(hdc);
		seconds.Draw(hdc);
	}
	
	void Manipulate(const HDC hdc) {
		while (true) {
			time.Increase();
			seconds.Move(hdc, sec_angle);
			Sleep(1000);
			seconds.SetColor(form.GetFillColor());
			seconds.Move(hdc, sec_angle);
			seconds.SetColor(form.GetContourColor());
			if (!time.GetSeconds()) {
				minutes.SetColor(form.GetFillColor());
				minutes.Move(hdc, min_angle);
				min_angle += PI / 30;
				minutes.SetColor(form.GetContourColor());
				minutes.Move(hdc, min_angle);
			} else
				minutes.Draw(hdc);
			if (!time.GetMinutes() && !time.GetSeconds()) {
				hours.SetColor(form.GetFillColor());
				hours.Move(hdc, hrs_angle);
				hrs_angle += PI / 12;
				hours.SetColor(form.GetContourColor());
				hours.Move(hdc, hrs_angle);
			} else
				hours.Draw(hdc);

			sec_angle += PI / 30;
		}
	}
private:
	Form form;
	Arrow hours, minutes;
	Arrow seconds;
	Time time;
	double sec_angle, min_angle, hrs_angle;
};