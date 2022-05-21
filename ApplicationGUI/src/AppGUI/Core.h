#pragma once

#ifdef APPGUI_BUILD_DLL
#define GUI_API __declspec(dllexport)
#else
#define GUI_API __declspec(dllimport)
#endif