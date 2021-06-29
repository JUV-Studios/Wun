#pragma once
#ifdef __cplusplus_winrt
namespace WUXC = Windows::UI::Xaml::Controls;
namespace MUXC = Microsoft::UI::Xaml::Controls;

namespace OneToolkit::UI::Xaml::Media::TransitionCollectionHelper
{
	inline void ApplySingleTransition(Windows::UI::Xaml::Media::Animation::TransitionCollection^& transitionCollection, Windows::UI::Xaml::Media::Animation::Transition^ transition)
	{
		if (!transitionCollection) transitionCollection = ref new Windows::UI::Xaml::Media::Animation::TransitionCollection;
		else if (transitionCollection->Size > 0) transitionCollection->Clear();
		transitionCollection->Append(transition);
	}
}

#define DeclareDependencyProperty(Type, OwnerType, Name, DefaultValue) Windows::UI::Xaml::DependencyProperty^ OwnerType::m_##Name##Property = Windows::UI::Xaml::DependencyProperty::Register(#Name, Type::typeid, OwnerType::typeid,\
ref new Windows::UI::Xaml::PropertyMetadata(DefaultValue, ref new Windows::UI::Xaml::PropertyChangedCallback(&OwnerType::DependencyPropertyChanged)));\
Windows::UI::Xaml::DependencyProperty^ OwnerType::Name##Property::get() { return m_##Name##Property; }
#else
#include <OneToolkit.h>
#include <winrt/Windows.UI.Xaml.Automation.Text.h>
#include <winrt/Windows.UI.Xaml.Automation.Peers.h>
#include <winrt/Windows.UI.Xaml.Automation.Provider.h>
#include <winrt/Windows.UI.Xaml.Controls.Maps.h>
#include <winrt/Windows.UI.Xaml.Controls.Primitives.h>
#include <winrt/Windows.UI.Xaml.Core.Direct.h>
#include <winrt/Windows.UI.Xaml.Documents.h>
#include <winrt/Windows.UI.Xaml.Hosting.h>
#include <winrt/Windows.UI.Xaml.Input.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Windows.UI.Xaml.Markup.h>
#include <winrt/Windows.UI.Xaml.Media.Animation.h>
#include <winrt/Windows.UI.Xaml.Media.Imaging.h>
#include <winrt/Windows.UI.Xaml.Media.Media3D.h>
#include <winrt/Windows.UI.Xaml.Navigation.h>
#include <winrt/Windows.UI.Xaml.Printing.h>
#include <winrt/Windows.UI.Xaml.Resources.h>
#include <winrt/Windows.UI.Xaml.Shapes.h>
#include <winrt/Microsoft.UI.Xaml.Automation.Peers.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.XamlTypeInfo.h>
#include <winrt/OneToolkit.UI.Xaml.Controls.h>
#include <winrt/OneToolkit.UI.Xaml.Media.Animation.h>

namespace winrt
{
	namespace WUXC = Windows::UI::Xaml::Controls;
	namespace MUXC = Microsoft::UI::Xaml::Controls;

	namespace OneToolkit::UI::Xaml::Media::TransitionCollectionHelper
	{
		inline void ApplySingleTransition(Windows::UI::Xaml::Media::Animation::TransitionCollection& transitionCollection, Windows::UI::Xaml::Media::Animation::Transition const& transition)
		{
			if (!transitionCollection) transitionCollection = {};
			else if (transitionCollection.Size() > 0) transitionCollection.Clear();
			transitionCollection.Append(transition);
		}
	}
}

#endif