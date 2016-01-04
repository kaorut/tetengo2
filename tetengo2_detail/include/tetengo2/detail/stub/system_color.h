/*! \file
    \brief The definition of tetengo2::detail::stub::system_color.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_SYSTEMCOLOR_H)
#define TETENGO2_DETAIL_STUB_SYSTEMCOLOR_H

#include <cassert>
#include <stdexcept>

#include <boost/core/noncopyable.hpp>

#include <boost/throw_exception.hpp>


namespace tetengo2 { namespace detail { namespace stub
{
    /*!
        \brief The class for a detail implementation of a GUI fixture.
    */
    class system_color : private boost::noncopyable
    {
    public:
        // types

        //! The system color index type.
        enum class system_color_index_type
        {
            title_bar_text,       //!< Title bar text.
            title_bar_background, //!< Title bar background.
            dialog_background,    //!< Dialog background.
            control_background,   //!< Control background.
            control_text,         //!< Control text.
            selected_background,  //!< Selected background.
            selected_text,        //!< Selected text.
            hyperlink_text,       //!< Hyperlink text.
        };


        // functions

        /*!
            \brief Returns the system color.

            \tparam Color A color type.

            \param index An index;

            \return The system color.
        */
        template <typename Color>
        static Color get_system_color(const system_color_index_type index)
        {
            switch (index)
            {
            case system_color_index_type::title_bar_text:
                return { 255, 255, 255 };
            case system_color_index_type::title_bar_background:
                return { 0, 0, 128 };
            case system_color_index_type::dialog_background:
                return { 192, 192, 192 };
            case system_color_index_type::control_background:
                return { 255, 255, 255 };
            case system_color_index_type::control_text:
                return { 0, 0, 0 };
            case system_color_index_type::selected_background:
                return { 0, 0, 128 };
            case system_color_index_type::selected_text:
                return { 255, 255, 255 };
            case system_color_index_type::hyperlink_text:
                return { 0, 0,255 };
            default:
                assert(false);
                BOOST_THROW_EXCEPTION((std::invalid_argument{ "Invalid system color index." }));
            }
        }


    private:
        // forbidden operations

        system_color()
        = delete;

    
    };


}}}


#endif
