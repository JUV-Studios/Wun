﻿#pragma once
#include "UI.Converters.StringLocalizationConverter.g.h"

namespace winrt::OneToolkit::UI::Converters
{
    namespace implementation
    {
        struct StringLocalizationConverter : StringLocalizationConverterT<StringLocalizationConverter, non_agile>, Mvvm::ObservableBase<StringLocalizationConverter>
        {
            StringLocalizationConverter() = default;
            Mvvm::ObservableProperty<Windows::ApplicationModel::Resources::ResourceLoader> Context { this, L"Context", Windows::ApplicationModel::Resources::ResourceLoader::GetForViewIndependentUse() };
            IInspectable Convert(IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, IInspectable const& parameter, hstring const& language);
            IInspectable ConvertBack(IInspectable const& value, Windows::UI::Xaml::Interop::TypeName const& targetType, IInspectable const& parameter, hstring const& language);
        };
    }

    namespace factory_implementation
    {
        struct StringLocalizationConverter : StringLocalizationConverterT<StringLocalizationConverter, implementation::StringLocalizationConverter>
        {
        };
    }
}