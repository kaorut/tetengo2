/*! \file
    \brief The definition of tetengo2::detail::base::encoding.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_ENCODING_H)
#define TETENGO2_DETAIL_BASE_ENCODING_H

#include <string>

#include <boost/core/noncopyable.hpp>
#include <boost/predef.h>

#include <tetengo2/stdalt.h>


namespace tetengo2::detail::base {
    /*!
        \brief The class for a detail implementation of an encoding.
    */
    class encoding : private boost::noncopyable
    {
    public:
        // types

        //! The pivot type type.
        enum class pivot_type_type
        {
            std_string, //!< std::string
            std_wstring, //!< std::wstring
        };

        //! The pivot type.
        using pivot_type = tetengo2::stdalt::variant<std::string, std::wstring>;

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
            \brief Returns the pivot type.

            \return The pivot type.
        */
        pivot_type_type pivot_type_() const;

        /*!
            \brief Converts a pivot to a UTF-8 string.

            \param pivot A pivot.

            \return A UTF-8 string.
        */
        utf8_string_type pivot_to_utf8(pivot_type pivot) const;

        /*!
            \brief Converts a UTF-8 string to a pivot.

            \param string A UTF-8 string.

            \return A pivot.
        */
        pivot_type utf8_to_pivot(utf8_string_type string) const;

        /*!
            \brief Converts a pivot to a CP932 string.

            \param pivot A pivot.

            \return A CP932 string.
        */
        cp932_string_type pivot_to_cp932(pivot_type pivot) const;

        /*!
            \brief Converts a CP932 string to a pivot.

            \param string A CP932 string.

            \return A pivot.
        */
        pivot_type cp932_to_pivot(cp932_string_type string) const;


    protected:
        // constructors

        /*!
            \brief Creates a detail implementation.
        */
        encoding();


    private:
        // virtual functions

        virtual pivot_type_type pivot_type_impl() const = 0;

        virtual utf8_string_type pivot_to_utf8_impl(pivot_type pivot) const = 0;

        virtual pivot_type utf8_to_pivot_impl(utf8_string_type string) const = 0;

        virtual cp932_string_type pivot_to_cp932_impl(pivot_type pivot) const = 0;

        virtual pivot_type cp932_to_pivot_impl(cp932_string_type string) const = 0;
    };
}


#endif
