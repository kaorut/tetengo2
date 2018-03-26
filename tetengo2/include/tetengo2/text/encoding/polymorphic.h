/*! \file
    \brief The definition of tetengo2::text::encoding::polymorphic.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_POLYMORPHIC_H)
#define TETENGO2_TEXT_ENCODING_POLYMORPHIC_H

#include <memory>
#include <string>
#include <utility>

#include <tetengo2/stdalt.h>
#include <tetengo2/text/encoding/encoding.h>


namespace tetengo2::text::encoding {
    /*!
        \brief The class template for a polymorphic encoding holder.

        \tparam String A string type.
    */
    template <typename String>
    class polymorphic : public encoding<String>
    {
    public:
        // types

        //! The base type.
        using base_type = encoding<String>;

        //! The pivot type.
        using pivot_type = typename base_type::pivot_type;

        //! The string type.
        using string_type = typename base_type::string_type;


        // constructors and destructor

        /*!
            \brief Creates a polymorphic encoding holder.
        */
        polymorphic();

        /*!
            \brief Creates a polymorphic encoding holder.

            \param p_encoding A unique pointer to an encoding.

            \throw std::invalid_argument When p_encoding is nullptr.
        */
        explicit polymorphic(std::unique_ptr<base_type> p_encoding);

        /*!
            \brief Destroys the encoding based on a polymorphic.
        */
        virtual ~polymorphic();


    private:
        // type

        class impl;


        // variables

        std::shared_ptr<impl> m_p_impl;


        // virtual functions

        virtual const std::string& name_impl() const override;

        virtual string_type from_pivot_impl(pivot_type pivot) const override;

        virtual pivot_type to_pivot_impl(string_type string) const override;
    };


    /*!
        \brief Make a polymorphic encoding holder.

        \tparam Encoding An encoding type.

        \param args Arguments for the encoding constructor.

        \return The polymorphic encoding holder.
    */
    template <typename Encoding, typename... Args>
    polymorphic<typename Encoding::string_type> make_polymorphic(Args&&... args)
    {
        return polymorphic<typename Encoding::string_type>(stdalt::make_unique<Encoding>(std::forward<Args>(args)...));
    }
}


#endif
