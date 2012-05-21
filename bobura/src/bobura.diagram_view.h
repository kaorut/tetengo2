/*! \file
    \brief The definition of bobura::diagram_view.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_DIAGRAMVIEW_H)
#define BOBURA_DIAGRAMVIEW_H

#include <boost/noncopyable.hpp>

namespace bobura
{
   /*!
        \brief The class template for a diagram view.

        \tparam Model A model type.
    */
    template <typename Model>
    class diagram_view : private boost::noncopyable
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;


        // constructors and destructor

        /*!
            \brief Creates a diagram view.

            \param model A model.
        */
        explicit diagram_view(const model_type& model)
        :
        m_model(model)
        {}


        // functions


    private:
        // variables

        const model_type& m_model;


    };


}

#endif
