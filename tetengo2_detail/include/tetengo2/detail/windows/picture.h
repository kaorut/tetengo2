/*! \file
    \brief The definition of picture utilities for tetengo2::detail::windows.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_PICTURE_H)
#define TETENGO2_DETAIL_WINDOWS_PICTURE_H

#include <system_error>
#include <utility>

#include <boost/filesystem.hpp>
#include <boost/throw_exception.hpp>

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <ObjBase.h>
#include <wincodec.h>

#include <tetengo2/detail/windows/com_ptr.h>
#include <tetengo2/detail/windows/error_category.h>

#if !defined(DOCUMENTATION)
    // Use the older version of WIC with the Windows SDK 8.0 for the time being.
#   if defined(_WIN32_WINNT_WIN8) && _WIN32_WINNT >= _WIN32_WINNT_WIN8
#      define Tetengo2_CLSID_WICImagingFactory ::CLSID_WICImagingFactory1
#   else
#      define Tetengo2_CLSID_WICImagingFactory ::CLSID_WICImagingFactory
#   endif
#endif


namespace tetengo2 { namespace detail { namespace windows { namespace picture
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        using wic_imaging_factory_ptr_type = unique_com_ptr< ::IWICImagingFactory>;


        // functions

        inline wic_imaging_factory_ptr_type create_wic_imaging_factory()
        {
            ::IWICImagingFactory* rp_factory = nullptr;
            const auto hr =
                ::CoCreateInstance(
                    Tetengo2_CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&rp_factory)
                );
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION((
                    std::system_error{ std::error_code{ hr, wic_category() }, "Can't create WIC imaging factory." }
                ));
            }

            return wic_imaging_factory_ptr_type{ rp_factory };
        }
    }
#endif


    // types

    //! The details type.
    using details_type = ::IWICBitmapSource;

    //! The details pointer type.
    using details_ptr_type = unique_com_ptr<details_type>;


    // functions

    /*!
        \brief Returns the WIC image factory.

        \return The WIC image factory.
    */
    inline ::IWICImagingFactory& wic_imaging_factory()
    {
        static const detail::wic_imaging_factory_ptr_type p_factory{ detail::create_wic_imaging_factory() };
        return *p_factory;
    }

    /*!
        \brief Creates a picture.

        \tparam Dimension A dimension type.

        \param dimension A dimension.

        \return A unique pointer to a picture.
    */
    template <typename Dimension>
    details_ptr_type create(const Dimension& dimension)
    {
        ::IWICBitmap* rp_bitmap = nullptr;
        const auto hr =
            wic_imaging_factory().CreateBitmap(
                gui::to_pixels< ::UINT>(gui::dimension<Dimension>::width(dimension)),
                gui::to_pixels< ::UINT>(gui::dimension<Dimension>::height(dimension)),
                ::GUID_WICPixelFormat32bppPBGRA,
                ::WICBitmapCacheOnDemand,
                &rp_bitmap
            );
        if (FAILED(hr))
            BOOST_THROW_EXCEPTION((std::system_error{ std::error_code(hr, wic_category()), "Can't create bitmap." }));

        return { rp_bitmap };
    }

    /*!
        \brief Reads a picture.

        \param path A path.

        \return A unique pointer to a picture.

        \throw std::system_error When the picture cannot be read.
    */
    inline details_ptr_type read(const boost::filesystem::path& path)
    {
        ::IWICBitmapDecoder* rp_decoder = nullptr;
        const auto create_decoder_hr =
            wic_imaging_factory().CreateDecoderFromFilename(
                path.c_str(), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &rp_decoder
            );
        if (FAILED(create_decoder_hr))
        {
            BOOST_THROW_EXCEPTION((
                std::system_error{ std::error_code{ create_decoder_hr, wic_category() }, "Can't create WIC decoder." }
            ));
        }
        const unique_com_ptr< ::IWICBitmapDecoder> p_decoder{ rp_decoder };

        ::IWICBitmapFrameDecode* rp_frame = nullptr;
        const auto get_frame_hr = p_decoder->GetFrame(0, &rp_frame);
        if (FAILED(get_frame_hr))
        {
            BOOST_THROW_EXCEPTION((
                std::system_error{ std::error_code{ get_frame_hr, wic_category() }, "Can't create bitmap frame." }
            ));
        }
        const unique_com_ptr< ::IWICBitmapFrameDecode> p_frame{ rp_frame };

        ::IWICFormatConverter* rp_format_converter = nullptr;
        const auto create_format_converter_hr = wic_imaging_factory().CreateFormatConverter(&rp_format_converter);
        if (FAILED(create_format_converter_hr))
        {
            BOOST_THROW_EXCEPTION((
                std::system_error{
                    std::error_code{ create_format_converter_hr, wic_category() }, "Can't create format converter."
                }
            ));
        }
        unique_com_ptr< ::IWICFormatConverter> p_format_converter{ rp_format_converter };

        const auto initialize_hr =
            p_format_converter->Initialize(
                p_frame.get(),
                ::GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                nullptr,
                0.0,
                WICBitmapPaletteTypeCustom
            );
        if (FAILED(initialize_hr))
        {
            BOOST_THROW_EXCEPTION((
                std::system_error{
                    std::error_code{ initialize_hr, wic_category() }, "Can't initialize format converter."
                }
            ));
        }

        return { std::move(p_format_converter) };
    }

    /*!
        \brief Returns the dimension of a picture.

        \tparam Dimension A dimension type.

        \param picture A picture.

        \return The dimension of the picture.
    */
    template <typename Dimension>
    Dimension dimension(const details_type& picture)
    {
        ::UINT width = 0;
        ::UINT height = 0;
        const auto hr = const_cast<details_type&>(picture).GetSize(&width, &height);
        if (FAILED(hr))
        {
            BOOST_THROW_EXCEPTION((
                std::system_error{ std::error_code{ hr, wic_category() }, "Can't get size of picture." }
            ));
        }

        return
            {
                gui::to_unit<typename gui::dimension<Dimension>::width_type>(width),
                gui::to_unit<typename gui::dimension<Dimension>::height_type>(height)
            };
    }


}}}}


#endif
