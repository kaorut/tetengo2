/*! \file
    \brief The definition of tetengo2::detail::stub::system_color.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_SYSTEMCOLOR_H)
#define TETENGO2_DETAIL_STUB_SYSTEMCOLOR_H

#include <cassert>
#include <stdexcept>

#include <boost/noncopyable.hpp>

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
        struct system_color_index_type { enum enum_t
        {
            dialog_background, //!< Dialog background.
        };};


        // functions

        /*!
            \brief Returns the system color.

            \tparam Color A color type.

            \param index An index;

            \return The system color.
        */
        template <typename Color>
        static Color get_system_color(const system_color_index_type::enum_t index)
        {
            switch (index)
            {
            case system_color_index_type::dialog_background:
                return Color(192, 192, 192);
            default:
                assert(false);
                BOOST_THROW_EXCEPTION(std::invalid_argument("Invalid system color index."));
            }
        }


    private:
        // forbidden operations

        system_color();

    
    };


}}}


#endif
