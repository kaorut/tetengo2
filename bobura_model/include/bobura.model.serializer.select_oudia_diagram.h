/*! \file
    \brief The definition of bobura::model::serializer::select_oudia_diagram.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_SELECTOUDIADIAGRAM_H)
#define BOBURA_MODEL_SERIALIZER_SELECTOUDIADIAGRAM_H

#include <cassert>
#include <iterator>
#include <utility>
#include <vector>

#include <boost/optional.hpp>
#include <boost/utility.hpp>


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

        //! The string type.
        typedef typename oudia_diagram_dialog_type::string_type string_type;

        //! The string type.
        typedef typename oudia_diagram_dialog_type::string_type string_type;

        //! The message catalog type.
        typedef typename oudia_diagram_dialog_type::message_catalog_type message_catalog_type;


        // constructors and destructor

        /*!
            \brief Creates an OuDia diagram selecting.

            \param parent          A parent window.
            \param file_name       A file name.
            \param message_catalog A message catalog.
        */
        select_oudia_diagram(
            abstract_window_type&       parent,
            string_type                 file_name,
            const message_catalog_type& message_catalog
        )
        :
        m_parent(parent),
        m_file_name(std::move(file_name)),
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
            if (std::distance(first, last) < 1)
                return last;

            oudia_diagram_dialog_type dialog(m_parent, m_message_catalog);

            dialog.set_file_name(m_file_name);
            dialog.set_names(std::vector<string_type>(first, last));
            dialog.set_selected_index(0);

            dialog.do_modal();
            if (dialog.result() != oudia_diagram_dialog_type::result_type::accepted)
                return last;

            const boost::optional<selected_index_type> selected_index = dialog.selected_index();
            if (selected_index)
            {
                assert(*selected_index < static_cast<selected_index_type>(std::distance(first, last)));
                return boost::next(first, *selected_index);
            }
            else
            {
                return last;
            }
        }


    private:
        // types

        typedef typename oudia_diagram_dialog_type::int_size_type selected_index_type;


        // variables

        abstract_window_type& m_parent;

        const string_type m_file_name;

        const message_catalog_type& m_message_catalog;


    };


}}}


#endif
