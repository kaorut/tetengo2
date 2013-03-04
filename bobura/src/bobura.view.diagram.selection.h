/*! \file
    \brief The definition of bobura::view::diagram::selection.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_SELECTION_H)
#define BOBURA_VIEW_DIAGRAM_SELECTION_H

#include <boost/noncopyable.hpp>


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for the diagram view selection.

        \tparam Train A train type.
    */
    template <typename Train>
    class selection : private boost::noncopyable
    {
    public:
        // types

        //! The train type.
        typedef Train train_type;


        // constructors and destructor

        /*!
            \brief Creates a selection.
        */
        selection()
        {}


        // functions


    };


}}}


#endif
