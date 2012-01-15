/*! \file
    \brief The definition of bobura::message::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MESSAGE_TIMETABLEMODEL_H)
#define BOBURA_MESSAGE_TIMETABLEMODEL_H


namespace bobura { namespace message { namespace timetable_model
{
     /*!
        \brief The class template for a timetable model observer of reset.

        \tparam Timetable  A timetable type.
        \tparam MainWindow A main window type.
    */
    template <typename Timetable, typename MainWindow>
    class reset
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The main window type.
        typedef MainWindow main_window_type;


        // constructors and destructor

        /*!
            \brief Creates a timetable model observer of resetn.

            \param main_window A main window.
        */
        reset(main_window_type& main_window)
        :
        m_main_window(main_window)
        {}


        // functions

        /*!
            \brief Called when the timetable model is reset.

            \param timetable A timetable.
        */
        void operator()(const timetable_type& timetable)
        const
        {
            m_main_window.set_text(timetable.title());
        }


    private:
        // variables

        main_window_type& m_main_window;


    };


}}}


#endif
