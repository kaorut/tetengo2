/*! \file
    \brief The definition of bobura::command::horizontally_zoom_in.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_COMMAND_HORIZONTALLYZOOMIN_H)
#define BOBURA_COMMAND_HORIZONTALLYZOOMIN_H

#include "bobura.command.command_base.h"


namespace bobura { namespace command
{
    /*!
        \brief The class template for a horizontal zoom-in command.

        \tparam Model          A model type.
        \tparam AbstractWindow An abstract window type.
        \tparam DiagramView    A diagram view type.
        \tparam ViewScaleList  A view scale list type.
    */
    template <typename Model, typename AbstractWindow, typename DiagramView, typename ViewScaleList>
    class horizontally_zoom_in : public command_base<Model, AbstractWindow>
    {
    public:
        // types

        //! The model type.
        typedef Model model_type;

        //! The abstract window type.
        typedef AbstractWindow abstract_window_type;

        //! The base type.
        typedef command_base<model_type, abstract_window_type> base_type;

        //! The diagram view type.
        typedef DiagramView diagram_view_type;

        //! The view scale list type.
        typedef ViewScaleList view_scale_list_type;


        // constructors and destructor

        /*!
            \brief Creates a horizontal zoom-in command.

            \param diagram_view A diagram view.
        */
        explicit horizontally_zoom_in(diagram_view_type& diagram_view)
        :
        m_diagram_view(diagram_view)
        {}


    private:
        // variables

        diagram_view_type& m_diagram_view;


        // virtual functions

        virtual bool enabled_impl(const model_type& model)
        const
        {
            return true;
        }

        virtual void execute_impl(model_type& model, abstract_window_type& parent)
        const
        {}


    };


}}


#endif
