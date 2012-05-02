/*! \file
    \brief The definition of tetengo2::detail::windows::picture.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_PICTURE_H)
#define TETENGO2_DETAIL_WINDOWS_FONT_H

#include <system_error>

#include <boost/throw_exception.hpp>

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>
#include <wincodec.h>

#include "tetengo2.detail.windows.com_ptr.h"


namespace tetengo2 { namespace detail { namespace windows { namespace picture
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        // types

        typedef unique_com_ptr< ::IWICImagingFactory>::type wic_imaging_factory_ptr_type;


        // functions

        inline wic_imaging_factory_ptr_type create_wic_imaging_factory()
        {
            ::IWICImagingFactory* rp_factory = NULL;
            const ::HRESULT hr =
                ::CoCreateInstance(::CLSID_WICImagingFactory, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&rp_factory));
            if (FAILED(hr))
            {
                BOOST_THROW_EXCEPTION(
                    std::system_error(std::error_code(hr, win32_category()), "Can't create WIC imaging factory.")
                );
            }

            return wic_imaging_factory_ptr_type(rp_factory);
        }
    }
#endif


    // types

    //! The details type.
    typedef ::IWICBitmapSource details_type;

    //! The details pointer type.
    typedef unique_com_ptr<details_type>::type details_ptr_type;


    // functions

    /*!
        \brief Returns the WIC image factory.

        \return The WIC image factory.
    */
    inline ::IWICImagingFactory& wic_imaging_factory()
    {
        static const detail::wic_imaging_factory_ptr_type p_factory(detail::create_wic_imaging_factory());
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
        ::IWICBitmap* rp_bitmap = NULL;
        const ::HRESULT hr =
            wic_imaging_factory().CreateBitmap(
                gui::to_pixels< ::UINT>(gui::dimension<Dimension>::width(dimension)),
                gui::to_pixels< ::UINT>(gui::dimension<Dimension>::height(dimension)),
                ::GUID_WICPixelFormat32bppPBGRA,
                ::WICBitmapCacheOnDemand,
                &rp_bitmap
            );
        if (FAILED(hr))
        {
            BOOST_THROW_EXCEPTION(std::system_error(std::error_code(hr, win32_category()), "Can't create bitmap."));
        }

        return details_ptr_type(rp_bitmap);
    }

    /*!
        \brief Reads a picture.

        \tparam Path A path type.

        \param path A path.

        \return A unique pointer to a picture.

        \throw std::system_error When the picture cannot be read.
    */
    template <typename Path>
    details_ptr_type read(const Path& path)
    {
        ::IWICBitmapDecoder* rp_decoder = NULL;
        const ::HRESULT create_decoder_hr =
            wic_imaging_factory().CreateDecoderFromFilename(
                path.c_str(), NULL, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &rp_decoder
            );
        if (FAILED(create_decoder_hr))
        {
            BOOST_THROW_EXCEPTION(
                std::system_error(std::error_code(create_decoder_hr, win32_category()), "Can't create WIC decoder.")
            );
        }
        const typename unique_com_ptr< ::IWICBitmapDecoder>::type p_decoder(rp_decoder);

        ::IWICBitmapFrameDecode* rp_frame = NULL;
        const ::HRESULT get_frame_hr = p_decoder->GetFrame(0, &rp_frame);
        if (FAILED(get_frame_hr))
        {
            BOOST_THROW_EXCEPTION(
                std::system_error(std::error_code(get_frame_hr, win32_category()), "Can't create bitmap frame.")
            );
        }
        const typename unique_com_ptr< ::IWICBitmapFrameDecode>::type p_frame(rp_frame);

        ::IWICFormatConverter* rp_format_converter = NULL;
        const ::HRESULT create_format_converter_hr = wic_imaging_factory().CreateFormatConverter(&rp_format_converter);
        if (FAILED(create_format_converter_hr))
        {
            BOOST_THROW_EXCEPTION(
                std::system_error(
                    std::error_code(create_format_converter_hr, win32_category()), "Can't create format converter."
                )
            );
        }
        typename unique_com_ptr< ::IWICFormatConverter>::type p_format_converter(rp_format_converter);

        const ::HRESULT initialize_hr =
            p_format_converter->Initialize(
                p_frame.get(),
                ::GUID_WICPixelFormat32bppPBGRA,
                WICBitmapDitherTypeNone,
                NULL,
                0.0,
                WICBitmapPaletteTypeCustom
            );
        if (FAILED(initialize_hr))
        {
            BOOST_THROW_EXCEPTION(
                std::system_error(
                    std::error_code(initialize_hr, win32_category()), "Can't initialize format converter."
                )
            );
        }

        return details_ptr_type(std::move(p_format_converter));
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
        const ::HRESULT hr = const_cast<details_type&>(picture).GetSize(&width, &height);
        if (FAILED(hr))
        {
            BOOST_THROW_EXCEPTION(
                std::system_error(std::error_code(hr, win32_category()), "Can't get size of picture.")
            );
        }

        return
            Dimension(
                gui::to_unit<typename gui::dimension<Dimension>::width_type>(width),
                gui::to_unit<typename gui::dimension<Dimension>::height_type>(height)
            );
    }


}}}}


#endif
