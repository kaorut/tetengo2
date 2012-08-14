/*! \file
    \brief The definition of bobura::message::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TIMETABLEMODEL_H)
#define BOBURA_MESSAGE_TIMETABLEMODEL_H

#include <boost/optional.hpp>

#include <tetengo2.gui.measure.h>


namespace bobura { namespace message { namespace timetable_model
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        template <typename TimetableModel, typename MainWindow>
        void set_main_window_title(const TimetableModel& timetable_model, MainWindow& main_window)
        {
            typedef typename TimetableModel::path_type path_type;
            typedef typename MainWindow::string_type string_type;

            const boost::optional<string_type> title =
                timetable_model.has_path() ?
                boost::make_optional(timetable_model.path().filename().template string<string_type>()) : boost::none;
            main_window.set_title(title, timetable_model.changed());
        }


    }
#endif


     /*!
        \brief The class template for a timetable model reset observer.

        \tparam TimetableModel A timetable model type.
        \tparam DiagramView    A diagram view type.
        \tparam MainWindow     A main window type.
    */
    template <typename TimetableModel, typename DiagramView, typename MainWindow>
    class reset
    {
    public:
        // types

        //! The timetable model type.
        typedef TimetableModel timetable_model_type;

        //! The diagram view type.
        typedef DiagramView diagram_view_type;

        //! The main window type.
        typedef MainWindow main_window_type;


        // constructors and destructor

        /*!
            \brief Creates a timetable model reset observer.

            \param timetable_model A timetable model.
            \param diagram_view    A diagram view.
            \param main_window     A main window.
        */
        reset(
            const timetable_model_type& timetable_model,
            diagram_view_type&          diagram_view,
            main_window_type&           main_window
        )
        :
        m_timetable_model(timetable_model),
        m_diagram_view(diagram_view),
        m_main_window(main_window)
        {}


        // functions

        /*!
            \brief Called when the timetable model is reset.
        */
        void operator()()
        const
        {
            detail::set_main_window_title(m_timetable_model, m_main_window);
            {
                const std::unique_ptr<canvas_type> p_canvas(m_main_window.diagram_picture_box().create_fast_canvas());
                m_diagram_view.recalculate_and_update_dimension(
                    *p_canvas,
                    m_main_window.diagram_picture_box().client_dimension(),
                    to_position(
                        m_main_window.diagram_picture_box().horizontal_scroll_bar()->tracking_position(),
                        m_main_window.diagram_picture_box().vertical_scroll_bar()->tracking_position()
                    )
                );
            }
            m_main_window.diagram_picture_box().repaint();
            m_main_window.window_observer_set().resized()();
        }


    private:
        // types

        typedef typename main_window_type::diagram_picture_box_type::base_type picture_box_type;
        
        typedef typename picture_box_type::fast_canvas_type canvas_type;

        typedef typename picture_box_type::position_type position_type;

        typedef typename tetengo2::gui::position<position_type>::left_type left_type;

        typedef typename tetengo2::gui::position<position_type>::top_type top_type;

        typedef typename picture_box_type::scroll_bar_type::size_type scroll_bar_size_type;


        // static functions

        static position_type to_position(const scroll_bar_size_type left, const scroll_bar_size_type top)
        {
            return position_type(left_type(left), top_type(top));
        }


        // variables

        const timetable_model_type& m_timetable_model;

        diagram_view_type& m_diagram_view;

        main_window_type& m_main_window;


    };


     /*!
        \brief The class template for a timetable model change observer.

        \tparam TimetableModel A timetable model type.
        \tparam DiagramView    A diagram view type.
        \tparam MainWindow     A main window type.
    */
    template <typename TimetableModel, typename DiagramView, typename MainWindow>
    class changed
    {
    public:
        // types

        //! The timetable model type.
        typedef TimetableModel timetable_model_type;

        //! The diagram view type.
        typedef DiagramView diagram_view_type;

        //! The main window type.
        typedef MainWindow main_window_type;


        // constructors and destructor

        /*!
            \brief Creates a timetable model change observer.

            \param timetable_model A timetable model.
            \param diagram_view    A diagram view.
            \param main_window     A main window.
        */
        changed(
            const timetable_model_type& timetable_model,
            diagram_view_type&          diagram_view,
            main_window_type&           main_window
        )
        :
        m_timetable_model(timetable_model),
        m_diagram_view(diagram_view),
        m_main_window(main_window)
        {}


        // functions

        /*!
            \brief Called when the timetable model is changed.
        */
        void operator()()
        const
        {
            detail::set_main_window_title(m_timetable_model, m_main_window);
            m_diagram_view.update_dimension();
            m_main_window.diagram_picture_box().repaint();
            m_main_window.window_observer_set().resized()();
        }


    private:
        // variables

        const timetable_model_type& m_timetable_model;

        diagram_view_type& m_diagram_view;

        main_window_type& m_main_window;


    };


}}}


#endif
