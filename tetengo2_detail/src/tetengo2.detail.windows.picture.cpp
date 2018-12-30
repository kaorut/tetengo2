/*! \file
    \brief The definition of picture utilities for tetengo2::detail::windows.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#include <memory>
#include <system_error>
#include <utility>

#include <boost/core/noncopyable.hpp>
#include <boost/throw_exception.hpp>

#pragma warning(push)
#pragma warning(disable : 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <ObjBase.h>
#include <Windows.h>
#include <wincodec.h>

#include <tetengo2/detail/windows/com_ptr.h>
#include <tetengo2/detail/windows/error_category.h>
#include <tetengo2/detail/windows/picture.h>
#include <tetengo2/gui/dimension.h>
#include <tetengo2/stdalt.h>

#if !defined(DOCUMENTATION)
// Use the older version of WIC with the Windows SDK 8.0 for the time being.
#if defined(_WIN32_WINNT_WIN8) && _WIN32_WINNT >= _WIN32_WINNT_WIN8
#define Tetengo2_CLSID_WICImagingFactory ::CLSID_WICImagingFactory1
#else
#define Tetengo2_CLSID_WICImagingFactory ::CLSID_WICImagingFactory
#endif
#endif


namespace tetengo2::detail::windows {
    class picture::impl : private boost::noncopyable
    {
    public:
        // types

        using dimension_type = picture::dimension_type;

        using details_type = picture::details_type;

        using details_ptr_type = picture::details_ptr_type;


        // static functions

        static const picture& instance()
        {
            static const picture singleton{};
            return singleton;
        }


        // functions

        ::IWICImagingFactory& wic_imaging_factory() const
        {
            static const wic_imaging_factory_ptr_type p_factory{ create_wic_imaging_factory() };
            return *p_factory;
        }

        details_ptr_type create(const dimension_type& dimension) const
        {
            ::IWICBitmap* rp_bitmap = nullptr;
            const auto    hr = wic_imaging_factory().CreateBitmap(
                static_cast<::UINT>(dimension.width().to_pixels()),
                static_cast<::UINT>(dimension.height().to_pixels()),
                ::GUID_WICPixelFormat32bppPBGRA,
                ::WICBitmapCacheOnDemand,
                &rp_bitmap);
            if (FAILED(hr))
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code(hr, wic_category()), "Can't create bitmap." }));

            return details_ptr_type{ rp_bitmap };
        }

        details_ptr_type read(const tetengo2::stdalt::filesystem::path& path) const
        {
            ::IWICBitmapDecoder* rp_decoder = nullptr;
            const auto           create_decoder_hr = wic_imaging_factory().CreateDecoderFromFilename(
                path.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &rp_decoder);
            if (FAILED(create_decoder_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ create_decoder_hr, wic_category() },
                                                          "Can't create WIC decoder." }));
            }
            const unique_com_ptr<::IWICBitmapDecoder> p_decoder{ rp_decoder };

            ::IWICBitmapFrameDecode* rp_frame = nullptr;
            const auto               get_frame_hr = p_decoder->GetFrame(0, &rp_frame);
            if (FAILED(get_frame_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ get_frame_hr, wic_category() },
                                                          "Can't create bitmap frame." }));
            }
            const unique_com_ptr<::IWICBitmapFrameDecode> p_frame{ rp_frame };

            ::IWICFormatConverter* rp_format_converter = nullptr;
            const auto create_format_converter_hr = wic_imaging_factory().CreateFormatConverter(&rp_format_converter);
            if (FAILED(create_format_converter_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ create_format_converter_hr, wic_category() },
                                                          "Can't create format converter." }));
            }
            unique_com_ptr<::IWICFormatConverter> p_format_converter{ rp_format_converter };

            const auto initialize_hr = p_format_converter->Initialize(
                p_frame.get(),
                ::GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.0,
                WICBitmapPaletteTypeCustom);
            if (FAILED(initialize_hr))
            {
                BOOST_THROW_EXCEPTION((std::system_error{ std::error_code{ initialize_hr, wic_category() },
                                                          "Can't initialize format converter." }));
            }

            return { std::move(p_format_converter) };
        }

        dimension_type dimension(const details_type& picture) const
        {
            ::UINT     width = 0;
            ::UINT     height = 0;
            const auto hr = const_cast<details_type&>(picture).GetSize(&width, &height);
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ hr, wic_category() }, "Can't get size of picture." }));
            }

            return { dimension_type::unit_type::from_pixels(width), dimension_type::unit_type::from_pixels(height) };
        }


    private:
        // types

        using wic_imaging_factory_ptr_type = unique_com_ptr<::IWICImagingFactory>;


        // functions

        wic_imaging_factory_ptr_type create_wic_imaging_factory() const
        {
            ::IWICImagingFactory* rp_factory = nullptr;
            const auto            hr = ::CoCreateInstance(
                Tetengo2_CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&rp_factory));
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    (std::system_error{ std::error_code{ hr, wic_category() }, "Can't create WIC imaging factory." }));
            }

            return wic_imaging_factory_ptr_type{ rp_factory };
        }
    };


    const picture& picture::instance()
    {
        return impl::instance();
    }

    ::IWICImagingFactory& picture::wic_imaging_factory() const
    {
        return m_p_impl->wic_imaging_factory();
    }

    picture::details_ptr_type picture::create(const dimension_type& dimension) const
    {
        return m_p_impl->create(dimension);
    }

    picture::details_ptr_type picture::read(const tetengo2::stdalt::filesystem::path& path) const
    {
        return m_p_impl->read(path);
    }

    picture::dimension_type picture::dimension(const details_type& picture) const
    {
        return m_p_impl->dimension(picture);
    }

    picture::picture() : m_p_impl{ std::make_unique<impl>() } {}
}
