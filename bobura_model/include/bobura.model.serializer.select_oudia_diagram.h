/*! \file
    \brief The definition of bobura::model::serializer::select_oudia_diagram.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_SELECTOUDIADIAGRAM_H)
#define BOBURA_MODEL_SERIALIZER_SELECTOUDIADIAGRAM_H


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for an OuDia diagram selecting.

        \tparam OuDiaDiagramDialog An OuDia diagram dialog type.
    */
    template <typename OuDiaDiagramDialog>
    class select_oudia_diagram
    {
    public:
        // types

        //! The OuDia diagram dialog type.
        typedef OuDiaDiagramDialog oudia_diagram_dialog_type;

        //! The abstract window type.
        typedef typename oudia_diagram_dialog_type::abstract_window_type abstract_window_type;

        //! The message catalog type.
        typedef typename oudia_diagram_dialog_type::message_catalog_type message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates an OuDia diagram selecting.

            \param parent          A parent window.
            \param message_catalog A message catalog.
        */
        select_oudia_diagram(abstract_window_type& parent, const message_catalog_type& message_catalog)
        :
        m_parent(parent),
        m_message_catalog(message_catalog)
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
            {
                oudia_diagram_dialog_type dialog(m_parent, m_message_catalog);
                dialog.do_modal();
            }
            return first;
        }


    private:
        // variables

        abstract_window_type& m_parent;

        const message_catalog_type& m_message_catalog;


    };


}}}


#endif
