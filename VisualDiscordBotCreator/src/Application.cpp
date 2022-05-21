/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE.txt
 */
#include <iostream>
#include <Windows.h>

#include <ApplicationGUI.h>

class VisualBotCreator : public AppGUI::Application
{
public:
	void Run() {
		MessageBox(nullptr, L"Test", L"Window ey", MB_OK);
	}
};

AppGUI::Application* AppGUI::CreateApplication()
{
	return new VisualBotCreator();
}