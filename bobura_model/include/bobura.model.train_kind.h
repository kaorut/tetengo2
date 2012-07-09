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

            \tparam S A string type.

            \param name A name.
        */
        template <typename S>
        train_kind(S&& name)
        :
        m_name(std::forward<S>(name))
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


    private:
        // variables

        string_type m_name;


    };


}}


#endif
