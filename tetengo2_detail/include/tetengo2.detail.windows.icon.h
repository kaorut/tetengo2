/*! \file
    \brief The definition of tetengo2::detail::windows::icon.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_ICON_H)
#define TETENGO2_DETAIL_WINDOWS_ICON_H

#include <memory>

#include <boost/noncopyable.hpp>


namespace tetengo2 { namespace detail { namespace windows
{
    /*!
        \brief The class for a detail implementation of an icon.
    */
    class icon : private boost::noncopyable
    {
    public:
        // types

        //! The icon details type.
        struct icon_details_type
        {
#if !defined(DOCUMENTATION)
            icon_details_type()
            {}
#endif

        };

        //! The icon details pointer type.
        typedef std::unique_ptr<icon_details_type> icon_details_ptr_type;


        // static functions

        /*!
            \brief Creates an icon.

            \tparam Path A path type.

            \param path A path.

            \return A unique pointer to an icon.
        */
        template <typename Path>
        static icon_details_ptr_type create(const Path& path)
        {
            return icon_details_ptr_type();
        }


    };


}}}


#endif
