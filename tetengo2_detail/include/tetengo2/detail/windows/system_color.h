/*! \file
    \brief The definition of tetengo2::detail::windows::system_color.

    Copyright (C) 2007-2019 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_WINDOWS_SYSTEMCOLOR_H)
#define TETENGO2_DETAIL_WINDOWS_SYSTEMCOLOR_H

#include <tetengo2/detail/base/system_color.h>


namespace tetengo2::detail::windows {
    /*!
        \brief The class for a detail implementation of a system color.
    */
    class system_color : public base::system_color
    {
    public:
        // types

        //! The color type.
        using color_type = base::system_color::color_type;

        //! The index type.
        using index_type = base::system_color::index_type;


        // static functions

        /*!
            \brief Returns the instance.

            \return The instance.
        */
        static const system_color& instance();


        // constructors and destructor

        /*!
            \brief Destroys the detail implemntation.
        */
        virtual ~system_color();


    private:
        // types

        class impl;


        // variables

        const std::unique_ptr<impl> m_p_impl;


        // constructors

        system_color();


        // virtual functions

        virtual color_type get_system_color_impl(index_type index) const override;
    };
}


#endif
