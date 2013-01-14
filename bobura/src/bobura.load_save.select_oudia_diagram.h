/*! \file
    \brief The definition of bobura::load_save::select_oudia_diagram.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_LOADSAVE_SELECTOUDIADIAGRAM_H)
#define BOBURA_LOADSAVE_SELECTOUDIADIAGRAM_H


namespace bobura { namespace load_save
{
    /*!
        \brief The class template for an OuDia diagram selecting.

        \tparam String A string type.
    */
    template <typename String>
    class select_oudia_diagram
    {
    public:
        // types

        //! The string type.
        typedef String string_type;


        // constructors and destructor

        /*!
            \brief Creates an OuDia diagram selecting.
        */
        select_oudia_diagram()
        {}


        // functions

        /*!
            \brief Selects an OuDia diagram.

            \tparam FowardIterator A forward iterator type.

            \param first The first position of the diagrams.
            \param last  The last position of the diagrams.

            \return The selected position.
        */
        template <typename ForwardIterator>
        ForwardIterator operator()(const ForwardIterator first, const ForwardIterator last)
        const
        {
            return last;
        }


    };


}}


#endif
