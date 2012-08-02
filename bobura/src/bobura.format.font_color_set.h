/*! \file
    \brief The definition of bobura::format::font_color_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_FORMAT_FONTCOLORSET_H)
#define BOBURA_FORMAT_FONTCOLORSET_H

#include <tetengo2.unique.h>


namespace bobura { namespace format
{
    /*!
        \brief The class template for a font and color set.

        \tparam Font  A font type.
        \tparam Color A color type.
    */
    template <typename Font, typename Color>
    class font_color_set
    {
    public:
        // types

        //! The font type.
        typedef Font font_type;

        //! The color type.
        typedef Color color_type;


        // constructors and destructor

        /*!
            \brief Creates a font and color set.
        */
        font_color_set()
        {}


        // functions


    private:
        // types


        // variables


    };


}}


#endif
