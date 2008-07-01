/*! \file
    \brief The definition of concept_bobura::model::Train.

    Copyright (C) 2007-2008 kaoru

    $Id$
*/

#if !defined(CONCEPTBOBURA_MODEL_TRAIN_H)
#define CONCEPTBOBURA_MODEL_TRAIN_H

#include <boost/concept_check.hpp>


namespace concept_bobura { namespace model
{
    /*!
        \brief The concept check class template for a train.

        \tparam Type A type.
    */
    template <typename Type>
    class Train :
        private boost::CopyConstructible<Type>,
        private boost::Assignable<Type>,
        private boost::EqualityComparable<Type>
    {
#if !defined(DOCUMENTATION)
    public:
        // typedef checks

        typedef typename Type::station_type station_type;

        typedef typename Type::meterage_type meterage_type;


        // usage checks

        BOOST_CONCEPT_USAGE(Train)
        {
            const_constraints(m_object);
        }

        void const_constraints(const Type& object)
        {
            //const typename Type::station_type& station =
            //    object.station();
            //boost::ignore_unused_variable_warning(station);
        }

        
    private:
        // variables

        Type m_object;


#endif
    };


}}

#endif
