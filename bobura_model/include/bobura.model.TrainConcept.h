/*! \file
    \brief The definition of bobura::model::TrainConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAINCONCEPT_H)
#define BOBURA_MODEL_TRAINCONCEPT_H

#include <algorithm>

#include <boost/concept_check.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The concept check class template for a train.

        \tparam Train A train type.
    */
    template <typename Train>
    class TrainConcept
    {
    public:
        // constructors and destructor

        TrainConcept();


        // functions

        /*!
            \brief Checks the constraints on a train.
        */
        void constraints()
        {
            typedef typename Train::station_type station_type;
            typedef typename Train::meterage_type meterage_type;

            m_train.swap(m_train);
            std::swap(m_train, m_train);

            Train& train =
                m_train = m_train;
            boost::ignore_unused_variable_warning(train);

            const_constraints(m_train);
        }

        /*!
            \brief Checks the const constraints on a train.

            \param train A constant object.
        */
        void const_constraints(const Train& train)
        {
            const typename Train::station_type& station =
                train.station();
            boost::ignore_unused_variable_warning(station);

            const typename Train::meterage_type& meterage =
                train.meterage();
            boost::ignore_unused_variable_warning(meterage);

            const bool before = train.before(train);
            boost::ignore_unused_variable_warning(before);
        }


    private:
        // variables

        Train m_train;


    };


}}

#endif
