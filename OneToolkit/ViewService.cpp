﻿#include "pch.h"
#include "OneToolkit.h"
#include "ViewService.h"
#include "ViewServiceDesktop.h"
#include "ViewServiceUniversal.h"
#include "UI.ViewService.g.cpp"

using namespace winrt;
using namespace Windows::Foundation;

namespace winrt::OneToolkit::UI::implementation
{
	IViewServiceProvider ViewService::GetForCurrentView()
	{
		return make<ViewServiceUniversal>();
	}

	IViewServiceProvider ViewService::GetForWindowId(int64_t windowHandle)
	{
		return make<ViewServiceDesktop>(windowHandle);
	}
}