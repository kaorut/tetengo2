/*! \file
    \brief The definition of tetengo2::gui::unit::factory.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_FACTORY_H)
#define TETENGO2_GUI_UNIT_FACTORY_H

#include <memory>

#include <boost/core/noncopyable.hpp>

#include <tetengo2/detail/base/unit.h>


namespace tetengo2 { namespace gui { namespace unit
{
    /*!
        \brief The class template for a unit factory.

        \tparam Unit A unit type.
    */
    template <typename Unit>
    class factory : private boost::noncopyable
    {
    public:
        // types

        //! The unit type.
        using unit_type = Unit;

        //! The value type.
        using value_type = typename unit_type::value_type;

        //! The unit details type.
        using unit_details_type = detail::base::unit;


        // constructors and destructor;

        /*!
            \brief Creates a unit factory.

            \param unit_details Unit details.
        */
        explicit factory(const unit_details_type& unit_details);

        /*!
            \brief Destroys the unit factory.
        */
        ~factory();


        // functions

        /*!
            \brief Makes a unit.

            \param value A value.

            \return A unit.
        */
        unit_type make(value_type value)
        const;


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


    };


}}}


#endif
