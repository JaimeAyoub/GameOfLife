#include "LeminGame.h"

LeminGame appGame;

int main()
{
	appGame.SetWindowsDimensions(960, 720);
	appGame.SetWindowName(L"AutomataC");
	appGame.StartApplication();

	return 0;
}