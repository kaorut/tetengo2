/*! \file
    \brief The definition of bobura::model::train_kind.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_TRAINKIND_H)
#define BOBURA_MODEL_TRAINKIND_H

#include <utility>

#include <boost/noncopyable.hpp>


namespace bobura { namespace model
{
    /*!
        \brief The class template for a train kind.

        \tparam String A string type.
    */
    template <typename String>
    class train_kind : private boost::noncopyable
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
