#pragma once

#include "pch.h"
#include "Application.h"

extern AppGUI::Application* AppGUI::CreateApplication();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
	auto app = AppGUI::CreateApplication();
	app->Run();
	delete app;
}