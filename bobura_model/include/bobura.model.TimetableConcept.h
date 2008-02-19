/*! \file
    \brief The definition of bobura::model::TimetableConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TIMETABLECONCEPT_H)
#define BOBURA_MODEL_TIMETABLECONCEPT_H

#include <algorithm>

#include <boost/concept_check.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The concept check class template for timetables.

        \tparam Timetable A timetable type.
    */
    template <typename Timetable>
    class TimetableConcept
    {
    public:
        // functions

        /*!
            \brief Checks the constraints on a canvas.
        */
        void constraints()
        {
            typedef typename Timetable::station_type station_type;
            typedef typename Timetable::kilometer_type kilometer_type;

            m_timetable.swap(m_timetable);
            std::swap(m_timetable, m_timetable);

            m_timetable = m_timetable;

            const_constraints(m_timetable);
        }

        /*!
            \brief Checks the const constraints on a canvas.
        */
        void const_constraints(const Timetable& timetable)
        {
        }


    private:
        // variables

        Timetable m_timetable;


    };


}}

#endif
