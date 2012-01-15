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

        \tparam Timetable A timetable type.
    */
    template <typename Timetable>
    class reset
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;


        // constructors and destructor

        /*!
            \brief Creates a timetable model observer of resetn.
        */
        reset()
        {}


        // functions

        /*!
            \brief Called when the timetable model is reset.

            \param timetable A timetable.
        */
        void operator()(const timetable_type& timetable)
        const
        {

        }


    private:
        // variables


    };


}}}


#endif
