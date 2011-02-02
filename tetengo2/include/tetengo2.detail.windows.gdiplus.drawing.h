/*! \file
    \brief The definition of tetengo2::detail::windows::gdiplus::drawing.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H)
#define TETENGO2_DETAIL_WINDOWS_GDIPLUS_DRAWING_H

//#define NOMINMAX
//#define OEMRESOURCE
//#include <Windows.h>

#include "tetengo2.detail.windows.font.h"


namespace tetengo2 { namespace detail { namespace windows { namespace gdiplus
{
    /*!
        \brief The class for a detail implementation of a drawing.
    */
    class drawing
    {
    public:
        // static functions

        /*!
            \brief Makes a dialog font.

            \tparam Font A font type.

            \return A dialog font.
        */
        template <typename Font>
        static Font make_dialog_font()
        {
            const ::LOGFONTW log_font =
                tetengo2::detail::windows::get_message_font();

            assert(log_font.lfHeight < 0);
            return Font(
                log_font.lfFaceName,
                -log_font.lfHeight,
                log_font.lfWeight >= FW_BOLD,
                log_font.lfItalic != 0,
                log_font.lfUnderline != 0,
                log_font.lfStrikeOut != 0
            );
        }


    private:
        // forbidden operations

        drawing();


   };


}}}}


#endif
