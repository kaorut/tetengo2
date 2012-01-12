/*! \file
    \brief The definition of bobura::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_TIMETABLEMODEL_H)
#define BOBURA_TIMETABLEMODEL_H

#include <boost/noncopyable.hpp>


namespace bobura
{
   /*!
        \brief The class template for a model.

        \tparam Timetable A timetable type.
    */
    template <typename Timetable>
    class timetable_model : private boost::noncopyable
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;


        // constructors and destructor

        /*!
            \brief Creates a model.
        */
        timetable_model()
        {}


        // functions


    private:
        // variables


    };


}

#endif
