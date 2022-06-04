/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#pragma once

#include "pch.h"
#include "Application.h"

extern AppGUI::Application* AppGUI::CreateApplication();

int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PWSTR pCmdLine, int nCmdShow)
{
#ifdef _DEBUG

	AllocConsole();

	SetConsoleTitle(L"Debug Console");
	
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stderr, "CONOUT$", "w", stderr);
	
#else
	
	if (__argc > 1) {
		for(int i = 1; i < __argc; i++) {
			int j = 0;
			while (__argv[i][j] != '\0') { __argv[i][j] = tolower(__argv[i][j]); }
			if (strcmp(__argv[i], "--debug") == 0 || strcmp(__argv[i], "-d") == 0) {
				FILE* o;
				FILE* e;
				
				freopen_s(&o, "debug.txt", "w", stdout);
				freopen_s(&e, "error.txt", "w", stderr);
			}
		}
	}

#endif

	std::cout << std::endl << "Welcome to Debug mode" << std::endl << std::endl;

	auto app = AppGUI::CreateApplication();
	app->Run();
	delete app;
}