/*! \file
    \brief The definition of bobura::timetable_model.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_TIMETABLEMODEL_H)
#define BOBURA_TIMETABLEMODEL_H

#include <memory>
#include <utility>

#include <boost/noncopyable.hpp>

#include <tetengo2.unique.h>


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
        :
        m_p_timetable(tetengo2::make_unique<timetable_type>())
        {}


        // functions

        /*!
            \brief Resets a timetable.

            \param p_timetable A unique pointer to a timetable.
        */
        void reset_timetable(std::unique_ptr<timetable_type> p_timetable)
        {
            m_p_timetable = std::move(p_timetable);
        }


    private:
        // variables

        std::unique_ptr<timetable_type> m_p_timetable;


    };


}

#endif
