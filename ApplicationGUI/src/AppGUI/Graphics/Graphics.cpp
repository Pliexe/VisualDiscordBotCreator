/* Copyright (c) 2022 Szabadi László Zsolt
 * You should have received a copy of the GNU AGPL v3.0 license with
 * this file. If not, please write to: pliexe, or visit : https://github.com/Pliexe/VisualDiscordBotCreator/blob/master/LICENSE
 */
#include "Graphics.h"

namespace AppGUI {
	Graphics::Graphics()
	{
		factory = NULL;
		renderTarget = NULL;
		writeFactory = NULL;
	}
	Graphics::~Graphics()
	{
		if (factory) factory->Release();
		if (renderTarget) renderTarget->Release();
		if(writeFactory) writeFactory->Release();
	}
	bool Graphics::Init(HWND hWnd)
	{
		if (D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &factory) != S_OK) return false;
		
		RECT rect;
		GetClientRect(hWnd, &rect);
		
		if(factory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(hWnd, D2D1::SizeU(rect.right, rect.bottom)),
			&renderTarget
		) != S_OK) return false;

		if (DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(writeFactory), reinterpret_cast<IUnknown**>(&writeFactory)) != S_OK) return false;
		
		return true;
	}

	void Graphics::Resize(int width, int height)
	{
		if (renderTarget != NULL)
		{
			renderTarget->Resize(D2D1::SizeU(width, height));
		}
	}
}