/*! \file
    \brief The definition of tetengo2::assignable.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ASSIGNABLE_H)
#define TETENGO2_ASSIGNABLE_H //!< !! Include Guard !!


namespace tetengo2
{
    /*!
        \brief The class template for an assignable.

        \tparam Derived A derived type.
    */
    template <typename Derived>
    class assignable
    {
    protected:
        // constructors and destructor

        /*!
            \brief Creates an assignable.
        */
        assignable()
        {}

        /*!
            \brief Destroys the assignable.
        */
        ~assignable()
        throw ()
        {}


        // functions

        /*!
            \brief Assigns another.

            The parameter another is passed by value to invoke the copy
            constructor.

            \param another Another.
        */
        Derived& assign(Derived another)
        {
            Derived* const p_self = static_cast<Derived*>(this);
            another.swap(*p_self);
            return *p_self;
        }


    };


}


#endif
