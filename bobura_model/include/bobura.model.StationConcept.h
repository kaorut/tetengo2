/*! \file
    \brief The definition of bobura::model::StationConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_STATIONCONCEPT_H)
#define BOBURA_MODEL_STATIONCONCEPT_H

#include <boost/concept_check.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The concept check class template for a station.

        \tparam Station A station type.
    */
    template <typename Station>
    class StationConcept :
        private boost::CopyConstructible<Station>,
        private boost::Assignable<Station>,
        private boost::EqualityComparable<Station>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Station::name_type name_type;

        typedef typename Station::grade_type grade_type;


        // usage checks

        BOOST_CONCEPT_USAGE(StationConcept)
        {
            const_constraints(m_station);
        }

        void const_constraints(const Station& station)
        {
            const name_type name = station.name();
            boost::ignore_unused_variable_warning(name);

            const grade_type& grade = station.grade();
            boost::ignore_unused_variable_warning(grade);
        }

        
    private:
        // variables

        Station m_station;


#endif
    };


}}

#endif
