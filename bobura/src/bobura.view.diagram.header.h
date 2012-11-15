/*! \file
    \brief The definition of bobura::view::diagram::header.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_DIAGRAM_HEADER_H)
#define BOBURA_VIEW_DIAGRAM_HEADER_H


namespace bobura { namespace view { namespace diagram
{
     /*!
        \brief The class template for a header in the diagram view.

        \tparam Model A model type.
    */
    template <typename Model>
    class header
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;


        // constructors and destructor

        /*!
            \brief Creates a header.
        */
        header()
        {}


        // functions


    private:
        // variables


    };


}}}


#endif
