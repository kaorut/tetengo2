/*! \file
    \brief The definition of bobura::model::train_kind.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAINKIND_H)
#define BOBURA_MODEL_TRAINKIND_H

#include <utility>

#include <boost/operators.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a train kind.

        \tparam String A string type.
    */
    template <typename String>
    class train_kind : private boost::equality_comparable<train_kind<String>>
    {
    public:
        // types

        //! The string type.
        typedef String string_type;


        // constructors and destructor

        /*!
            \brief Creates a train kind.

            \tparam S1 A string type #1.
            \tparam S2 A string type #2.

            \param name         A name.
            \param abbreviation An abbreviated name.
        */
        template <typename S1, typename S2>
        train_kind(S1&& name, S2&& abbreviation)
        :
        m_name(std::forward<S1>(name)),
        m_abbreviation(std::forward<S2>(abbreviation))
        {}


        // functions

        /*!
            \brief Checks whether one train kind is equal to another.

            \param one     One train kind.
            \param another Another train kind.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const train_kind& one, const train_kind& another)
        {
            return
                one.m_name == another.m_name &&
                one.m_abbreviation == another.m_abbreviation;
        }

        /*!
            \brief Returns the name.

            \return The name.
        */
        const string_type& name()
        const
        {
            return m_name;
        }

        /*!
            \brief Returns the abbreviated name.

            \return The abbreviated name.
        */
        const string_type& abbreviation()
        const
        {
            return m_abbreviation;
        }


    private:
        // variables

        string_type m_name;

        string_type m_abbreviation;


    };


}}


#endif
