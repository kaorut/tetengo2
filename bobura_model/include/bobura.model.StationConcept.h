/*! \file
    \brief The definition of bobura::model::StationConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONCONCEPT_H)
#define BOBURA_MODEL_STATIONCONCEPT_H

#include <algorithm>

#include <boost/concept_check.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The concept check class template for a station.

        \tparam Station A station type.
    */
    template <typename Station>
    class StationConcept
    {
    public:
        // constructors and destructor

        StationConcept();


        // functions

        /*!
            \brief Checks the constraints on a station.
        */
        void constraints()
        {
            typedef typename Station::name_type name_type;
            typedef typename Station::grade_type grade_type;

            m_station.swap(m_station);
            std::swap(m_station, m_station);

            Station& assigned = m_station = m_station;
            boost::ignore_unused_variable_warning(assigned);

            const_constraints(m_station);
        }

        /*!
            \brief Checks the const constraints on a station.

            \param station A constant object.
        */
        void const_constraints(const Station& station)
        {
            const bool equality = station == station;
            boost::ignore_unused_variable_warning(equality);

            const typename Station::name_type name = station.name();
            boost::ignore_unused_variable_warning(name);

            const typename Station::grade_type& grade = station.grade();
            boost::ignore_unused_variable_warning(grade);
        }


    private:
        // variables

        Station m_station;


    };


}}

#endif
