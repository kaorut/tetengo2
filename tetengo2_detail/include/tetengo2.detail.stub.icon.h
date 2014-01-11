/*! \file
    \brief The definition of detail::stub::icon.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_STUB_ICON_H)
#define TETENGO2_DETAIL_STUB_ICON_H

//#include <memory>

#include <boost/noncopyable.hpp>

#include "tetengo2.gui.measure.h"
#include "tetengo2.stdalt.h"
#include "tetengo2.utility.h"


namespace tetengo2 { namespace detail { namespace stub
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
        {};

        //! The icon details pointer type.
        typedef std::unique_ptr<icon_details_type> icon_details_ptr_type;


        // static functions

        /*!
            \brief Returns the default dimension.

            \tparam Dimension A dimension type.
            
            \return The default dimension.
        */
        template <typename Dimension>
        static Dimension default_dimension()
        {
            return
                Dimension(
                    typename gui::dimension<Dimension>::width_type(42),
                    typename gui::dimension<Dimension>::height_type(42)
                );
        }

        /*!
            \brief Creates an icon.

            \tparam Path      A path type.
            \tparam Dimension A dimension type.

            \param path      A path.
            \param dimension A dimension.

            \return A unique pointer to an icon.
        */
        template <typename Path, typename Dimension>
        static icon_details_ptr_type create(const Path& path, const Dimension& dimension)
        {
            suppress_unused_variable_warning(path, dimension);
            return stdalt::make_unique<icon_details_type>();
        }


    };


}}}


#endif
