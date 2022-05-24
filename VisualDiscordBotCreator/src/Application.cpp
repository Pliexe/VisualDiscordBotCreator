/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#include <iostream>
#include <Windows.h>

#include <ApplicationGUI.h>

class VisualBotCreator : public AppGUI::Application
{
public:
	VisualBotCreator() {
		
	}
};

AppGUI::Application* AppGUI::CreateApplication()
{
	return new VisualBotCreator();
}