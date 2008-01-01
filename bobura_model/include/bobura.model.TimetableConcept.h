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

        \param Timetable A timetable type.
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
            typedef typename Timetable::stations_type stations_type;

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
            typename Timetable::stations_type* const p_stations =
                timetable.p_stations();
            boost::ignore_unused_variable_warning(p_stations);
        }


    private:
        // variables

        Timetable m_timetable;


    };


}}

#endif
