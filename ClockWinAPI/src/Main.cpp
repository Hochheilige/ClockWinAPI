#include "Clock.h"
#include <future>

#define PI 3.14159265358979323846

int main() {
	Window wnd, wnd1;
	Clock<Rect> clock_rect(Rect({ 100, 400 }, { 400, 100 },
								StandartColors::GREEN, StandartColors::MAGENTA,
								PenStyle::SOLID, 10, BrushStyle::SOLID));
	clock_rect.Draw(wnd.GetDeviceContext());

	Clock<Circle> clock_circle(Circle({ 500, 400 }, { 800, 100 },
									  StandartColors::RED, StandartColors::CYAN,
									  PenStyle::SOLID, 7, BrushStyle::SOLID));
	clock_circle.Draw(wnd1.GetDeviceContext());

	std::vector<std::future<void>> futures;
	futures.push_back(std::async([&]() {
		clock_rect.Manipulate(wnd.GetDeviceContext());
								 })
	);
	futures.push_back(std::async([&]() {
		clock_circle.Manipulate(wnd1.GetDeviceContext()); 
								 })
	);
}
