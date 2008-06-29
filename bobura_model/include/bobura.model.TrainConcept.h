/*! \file
    \brief The definition of bobura::model::TrainConcept.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAINCONCEPT_H)
#define BOBURA_MODEL_TRAINCONCEPT_H

#include <boost/concept_check.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The concept check class template for a train.

        \tparam Train A train type.
    */
    template <typename Train>
    class TrainConcept :
        private boost::CopyConstructible<Train>,
        private boost::Assignable<Train>,
        private boost::EqualityComparable<Train>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Train::station_type station_type;

        typedef typename Train::meterage_type meterage_type;


        // usage checks

        BOOST_CONCEPT_USAGE(TrainConcept)
        {
            const_constraints(m_train);
        }

        void const_constraints(const Train& train)
        {
            //const typename Train::station_type& station =
            //    train.station();
            //boost::ignore_unused_variable_warning(station);
        }

        
    private:
        // variables

        Train m_train;


#endif
    };


}}

#endif
