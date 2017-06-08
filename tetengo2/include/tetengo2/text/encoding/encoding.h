/*! \file
    \brief The definition of tetengo2::text::encoding::encoding.

    Copyright (C) 2007-2017 kaoru

    $Id$
*/

#if !defined(TETENGO2_TEXT_ENCODING_ENCODING_H)
#define TETENGO2_TEXT_ENCODING_ENCODING_H

#include <memory>

#include <tetengo2/detail/base/encoding.h>


namespace tetengo2 { namespace text { namespace encoding
{
    /*!
        \brief The class for a encoding.
    */
    class encoding
    {
    public:
        // types

        //! The encoding details type.
        using encoding_details_type = tetengo2::detail::base::encoding;

        //! The pivot type.
        using pivot_type = typename encoding_details_type::pivot_type;


        // constructors and destructor

        /*!
            \brief Destroys the encoding.
        */
        virtual ~encoding();


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


    };


}}}


#endif
