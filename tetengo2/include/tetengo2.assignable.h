/*! \file
    \brief The definition of tetengo2::assignable.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_ASSIGNABLE_H)
#define TETENGO2_ASSIGNABLE_H


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
        // types

        //! The derived type.
        typedef Derived derived_type;


        // constructors and destructor

        /*!
            \brief Creates an assignable object.
        */
        assignable()
        {}

        /*!
            \brief Destroys the assignable object.
        */
        ~assignable()
        throw ()
        {}


        // functions

        /*!
            \brief Assigns another object.

            The parameter another is passed by value to invoke the copy
            constructor.

            \param another Another object.
        */
        derived_type& assign(derived_type another)
        {
            derived_type* const self = static_cast<derived_type*>(this);
            another.swap(*self);
            return *self;
        }
    };
}


#endif
