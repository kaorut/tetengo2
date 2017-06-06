/*! \file
    \brief The definition of tetengo2::detail::base::encoding.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_ENCODING_H)
#define TETENGO2_DETAIL_BASE_ENCODING_H

#include <string>

#include <boost/core/noncopyable.hpp>


namespace tetengo2 { namespace detail { namespace base
{
    /*!
        \brief The class for a detail implementation of an encoding.
    */
    class encoding : private boost::noncopyable
    {
    public:
        // types

        //! The pivot type.
        class pivot_type;

        //! The UTF-8 string type.
        using utf8_string_type = std::string;

        //! The CP932 string type.
        using cp932_string_type = std::string;


        // constructors and destructor

        /*!
            \brief Destroys the detail implementaion.
        */
        virtual ~encoding();


        // functions

        /*!
            \brief Converts a pivot to a UTF-8 string.

            \param pivot A pivot.

            \return A UTF-8 string.
        */
        utf8_string_type pivot_to_utf8(const pivot_type& pivot)
        const;

        /*!
            \brief Converts a UTF-8 string to a pivot.

            \param string A UTF-8 string.

            \return A pivot.
        */
        pivot_type utf8_to_pivot(const utf8_string_type& string)
        const;

        /*!
            \brief Converts a pivot to a CP932 string.

            \param pivot A pivot.

            \return A CP932 string.
        */
        cp932_string_type pivot_to_cp932(const pivot_type& pivot)
        const;

        /*!
            \brief Converts a CP932 string to a pivot.

            \param string A CP932 string.

            \return A pivot.
        */
        pivot_type cp932_to_pivot(const cp932_string_type& string)
        const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        encoding();


    private:
        // virtual functions

        virtual utf8_string_type pivot_to_utf8_impl(const pivot_type& pivot)
        const = 0;

        virtual pivot_type utf8_to_pivot_impl(const utf8_string_type& string)
        const = 0;

        virtual cp932_string_type pivot_to_cp932_impl(const pivot_type& pivot)
        const = 0;

        virtual pivot_type cp932_to_pivot_impl(const cp932_string_type& string)
        const = 0;


   };
    

}}}


#endif
