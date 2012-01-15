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
        \brief The class for a timetable model observer of reset.
    */
    class reset
    {
    public:
        // types


        // constructors and destructor

        /*!
            \brief Creates a timetable model observer of resetn.
        */
        reset()
        {}


        // functions

        /*!
            \brief Called when the timetable model is reset.
        */
        void operator()()
        const
        {

        }


    private:
        // variables


    };


}}}


#endif
