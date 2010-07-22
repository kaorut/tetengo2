/*! \file
    \brief The definition of tetengo2::gui::win32::font.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_WIN32_FONT_H)
#define TETENGO2_GUI_WIN32_FONT_H

#include <algorithm>
#include <cassert>
#include <stdexcept>
#include <vector>

#include <boost/operators.hpp>
#include <boost/scoped_array.hpp>
#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>

#define NOMINMAX
#define OEMRESOURCE
#include <windows.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <gdiplus.h>
#undef min
#undef max

#include "tetengo2.assignable.h"
#include "tetengo2.swappable.h"


namespace tetengo2 { namespace gui { namespace win32
{
    /*!
        \brief The class template for a font for Win32 platforms.
 
        \tparam String A string type.
        \tparam Size   A size type.
   */
    template <typename String, typename Size>
    class font :
        public assignable<font<String, Size> >,
        private swappable<font<String, Size> >,
        private boost::equality_comparable<font<String, Size> >
    {
    public:
        // types

        //! \return The string type.
        typedef String string_type;

        //! \return The size type.
        typedef Size size_type;

        //! \return The families type.
        typedef std::vector<string_type> families_type;


        // static functions

        /*!
            \brief Returns the dialog font.

            \return The dialog font.
        */
        static const font& dialog_font()
        {
            static const font singleton(make_dialog_font());
            return singleton;
        }

        /*!
            \brief Returns the installed font families.

            \return The installed font families.
        */
        static const families_type& installed_families()
        {
            static const families_type singleton(make_installed_families());
            return singleton;
        }


        // constructors and destructor

        /*!
            \brief Creates a font.

            When family is not installed, the family of the dialog font is set
            instead.

            \param family    A family.
            \param size      A size.
            \param bold      Whether this font is bold.
            \param italic    Whether this font is italic.
            \param underline Whether this font is underlined.
            \param strikeout Whether this font is striked out.
        */
        font(
            const string_type& family,
            const size_type    size,
            const bool         bold,
            const bool         italic,
            const bool         underline,
            const bool         strikeout
        )
        :
        m_family(select_family(family)),
        m_size(size),
        m_bold(bold),
        m_italic(italic),
        m_underline(underline),
        m_strikeout(strikeout)
        {}

        /*!
            \brief Copies a font.

            \param another Another font.
        */
        font(const font& another)
        :
        m_family(another.m_family),
        m_size(another.m_size),
        m_bold(another.m_bold),
        m_italic(another.m_italic),
        m_underline(another.m_underline),
        m_strikeout(another.m_strikeout)
        {}

        /*!
            \brief Destroys the font.
        */
        virtual ~font()
        throw ()
        {}


        // functions

        /*!
            \brief Swaps the members with another font.

            \param another Another font.
        */
        void swap(font& another)
        throw ()
        {
            boost::swap(m_family, another.m_family);
            boost::swap(m_size, another.m_size);
            boost::swap(m_bold, another.m_bold);
            boost::swap(m_italic, another.m_italic);
            boost::swap(m_underline, another.m_underline);
            boost::swap(m_strikeout, another.m_strikeout);
        }

        /*!
            \brief Assigns another font.

            \param another Another font.

            \return This object.
        */
        font& operator=(const font& another)
        {
            return assign(another);
        }

        /*!
            \brief Checks whether one font is equal to another.

            \param one     One font.
            \param another Another font.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const font& one, const font& another)
        {
            return one.m_family == another.m_family &&
                one.m_size == another.m_size &&
                one.m_bold == another.m_bold &&
                one.m_italic == another.m_italic &&
                one.m_underline == another.m_underline &&
                one.m_strikeout == another.m_strikeout;
        }

        /*!
            \brief Returns the family.

            \return The family.
        */
        const string_type& family()
        const
        {
            return m_family;
        }

        /*!
            \brief Returns the size.

            \return The size.
        */
        size_type size()
        const
        {
            return m_size;
        }

        /*!
            \brief Returns whether this font is bold.

            \retval true  When this font is bold.
            \retval false Otherwise.
        */
        bool bold()
        const
        {
            return m_bold;
        }

        /*!
            \brief Returns whether this font is italic.

            \retval true  When this font is italic.
            \retval false Otherwise.
        */
        bool italic()
        const
        {
            return m_italic;
        }

        /*!
            \brief Returns whether this font is underlined.

            \retval true  When this font is underlined.
            \retval false Otherwise.
        */
        bool underline()
        const
        {
            return m_underline;
        }

        /*!
            \brief Returns whether this font is striked out.

            \retval true  When this font is striked out.
            \retval false Otherwise.
        */
        bool strikeout()
        const
        {
            return m_strikeout;
        }


    private:
        // static functions

        static font make_dialog_font()
        {
            const ::LOGFONTW log_font = get_message_font();

            assert(log_font.lfHeight < 0);
            assert(
                std::find(
                    installed_families().begin(),
                    installed_families().end(),
                    log_font.lfFaceName
                ) != installed_families().end()
            );
            return font(
                log_font.lfFaceName,
                -log_font.lfHeight,
                log_font.lfWeight >= FW_BOLD,
                log_font.lfItalic != 0,
                log_font.lfUnderline != 0,
                log_font.lfStrikeOut != 0
            );
        }

        static ::LOGFONTW get_message_font()
        {
            ::NONCLIENTMETRICSW metrics;
            get_nonclient_metrics(metrics);

            return metrics.lfMessageFont;
        }

        static void get_nonclient_metrics(::NONCLIENTMETRICSW& metrics)
        {
            ::OSVERSIONINFOW os_version_info;
            os_version_info.dwOSVersionInfoSize = sizeof(::OSVERSIONINFOW);
            if (::GetVersionEx(&os_version_info) == 0)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get Windows version.")
                );
            }

            const ::UINT metrics_size = os_version_info.dwMajorVersion >= 6 ?
                sizeof(::NONCLIENTMETRICSW) :
                sizeof(::NONCLIENTMETRICSW) - sizeof(int);
            metrics.cbSize = metrics_size;
            if (
                ::SystemParametersInfoW(
                    SPI_GETNONCLIENTMETRICS,
                    metrics_size,
                    &metrics,
                    0
                ) == 0
            )
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get non-client metrics.")
                );
            }
        }

        static families_type make_installed_families()
        {
            const Gdiplus::InstalledFontCollection font_collection;
            const ::INT count = font_collection.GetFamilyCount();
            const boost::scoped_array<Gdiplus::FontFamily> p_families(
                new Gdiplus::FontFamily[count]
            );
            ::INT actual_count = 0;

            const Gdiplus::Status status =
                font_collection.GetFamilies(
                    count, p_families.get(), &actual_count
                );
            if (status != Gdiplus::Ok)
            {
                BOOST_THROW_EXCEPTION(
                    std::runtime_error("Can't get installed font families.")
                );
            }

            families_type families;
            families.reserve(actual_count);
            for (::INT i = 0; i < actual_count; ++i)
            {
                wchar_t family_name[LF_FACESIZE];
                const Gdiplus::Status family_name_status =
                    p_families[i].GetFamilyName(family_name);
                if (family_name_status != Gdiplus::Ok)
                {
                    BOOST_THROW_EXCEPTION(
                        std::runtime_error("Can't get font family name.")
                    );
                }
                families.push_back(family_name);
            }
            return families;
        }

        string_type select_family(const string_type& family)
        {
            if (
                std::find(
                    installed_families().begin(),
                    installed_families().end(),
                    family
                ) == installed_families().end()
            )
            {
                return dialog_font().family();
            }
        
            return family;
        }

        // variables

        string_type m_family;

        size_type m_size;

        bool m_bold;

        bool m_italic;

        bool m_underline;

        bool m_strikeout;


    };


}}}


#endif
