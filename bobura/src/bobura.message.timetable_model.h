/*! \file
    \brief The definition of bobura::message::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TIMETABLEMODEL_H)
#define BOBURA_MESSAGE_TIMETABLEMODEL_H

#include <boost/optional.hpp>


namespace bobura { namespace message { namespace timetable_model
{
#if !defined(DOCUMENTATION)
    namespace detail
    {
        template <typename TimetableModel, typename MainWindow>
        void set_main_window_title(
            const TimetableModel& timetable_model,
            MainWindow&           main_window
        )
        {
            typedef typename TimetableModel::path_type path_type;
            typedef typename MainWindow::string_type string_type;

            const boost::optional<string_type> title =
                timetable_model.has_path() ?
                boost::make_optional(
                    timetable_model.path().filename().template string<
                        string_type
                    >()
                ) :
                boost::none;
            main_window.set_title(title, timetable_model.changed());
        }


    }
#endif


     /*!
        \brief The class template for a timetable model reset observer.

        \tparam TimetableModel  A timetable model type.
        \tparam MainWindow A main window type.
    */
    template <typename TimetableModel, typename MainWindow>
    class reset
    {
    public:
        // types

        //! The timetable model type.
        typedef TimetableModel timetable_model_type;

        //! The main window type.
        typedef MainWindow main_window_type;


        // constructors and destructor

        /*!
            \brief Creates a timetable model reset observer.

            \param timetable_model A timetable model.
            \param main_window     A main window.
        */
        reset(
            const timetable_model_type& timetable_model,
            main_window_type&           main_window
        )
        :
        m_timetable_model(timetable_model),
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
        }


    private:
        // variables

        const timetable_model_type& m_timetable_model;

        main_window_type& m_main_window;


    };

     /*!
        \brief The class template for a timetable model change observer.

        \tparam TimetableModel A timetable model type.
        \tparam MainWindow     A main window type.
    */
    template <typename TimetableModel, typename MainWindow>
    class changed
    {
    public:
        // types

        //! The timetable model type.
        typedef TimetableModel timetable_model_type;

        //! The main window type.
        typedef MainWindow main_window_type;


        // constructors and destructor

        /*!
            \brief Creates a timetable model change observer.

            \param timetable_model A timetable model.
            \param main_window     A main window.
        */
        changed(
            const timetable_model_type& timetable_model,
            main_window_type&           main_window
        )
        :
        m_timetable_model(timetable_model),
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
        }


    private:
        // variables

        const timetable_model_type& m_timetable_model;

        main_window_type& m_main_window;


    };


}}}


#endif
