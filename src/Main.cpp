#include "Time.h"
#include "Figures.h"

int main() {
	//time_t now = time(0);
	//tm time;
	//localtime_s(&time, &now);

	//Time timer(&time);
	//
	//for (int i = 0; i < 100; ++i) {
	//	timer.PrintCurrentTimeStd();
	//	timer.Increase();
	//	Sleep(1000);
	//}
	Window wnd;
	Triangle tr({ 100, 100 }, { 200, 100 }, { 100, 200 });
	tr.SetColor(StandartColors::GREEN);
	tr.Draw(wnd.hDeviceContext);
	
}