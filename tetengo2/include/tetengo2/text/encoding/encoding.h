/*! \file
    \brief The definition of tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_ENCODING_H)
#define TETENGO2_TEXT_ENCODING_ENCODING_H

#include <memory>
#include <string>

#include <tetengo2/detail/base/encoding.h>


namespace tetengo2::text::encoding {
    /*!
        \brief The class template for a encoding.

        \param String A string type.
    */
    template <typename String>
    class encoding
    {
    public:
        // types

        //! The pivot type.
        using pivot_type = typename detail::base::encoding::pivot_type;

        //! The string type.
        using string_type = String;


        // constructors and destructor

        /*!
            \brief Destroys the encoding.
        */
        virtual ~encoding();


        // functions

        /*!
            \brief Returns the encoding name.

            \return The encoding name.
        */
        const std::string& name() const;

        /*!
            \brief Checks whether one encoding is equal to another.

            \tparam S A string type #1.
            \tparam T A string type #2

            \param one     One encoding.
            \param another Another encoding.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        template <typename S, typename T>
        friend bool operator==(const encoding<S>& one, const encoding<T>& another);

        /*!
            \brief Checks whether one encoding is not equal to another.

            \tparam S A string type #1.
            \tparam T A string type #2

            \param one     One encoding.
            \param another Another encoding.

            \retval true  When the one is not equal to the other.
            \retval false Otherwise.
        */
        template <typename S, typename T>
        friend bool operator!=(const encoding<S>& one, const encoding<T>& another);

        /*!
            \brief Translates a string from the pivot encoding.

            \param pivot A pivot string.

            \return A translated string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        string_type from_pivot(pivot_type pivot) const;

        /*!
            \brief Translates a string to the pivot encoding.

            \param string A string.

            \return A translated pivot string.

            \throw std::invalid_argument When the string cannot be translated.
        */
        pivot_type to_pivot(string_type string) const;


    protected:
        // constructors

        /*!
            \brief Creates an encoding.
        */
        encoding();


    private:
        // types

        class impl;


        // variables

        std::shared_ptr<impl> m_p_impl;


        // virtual functions

        virtual const std::string& name_impl() const = 0;

        virtual string_type from_pivot_impl(pivot_type pivot) const = 0;

        virtual pivot_type to_pivot_impl(string_type string) const = 0;
    };
}


#endif
