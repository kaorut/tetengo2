/*! \file
    \brief String encoding conversion

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

//#include <string>

#include <tetengo2.detail.windows.encoding.h>
#include <tetengo2.text.encoder.h>
#include <tetengo2.text.encoding.ascii.h>
#include <tetengo2.text.encoding.locale.h>

#include "encode.h"


namespace setup
{
    namespace
    {
        typedef tetengo2::detail::windows::encoding encoding_details_type;

        typedef
            tetengo2::text::encoder<
                tetengo2::text::encoding::ascii<encoding_details_type>,
                tetengo2::text::encoding::locale<std::wstring, encoding_details_type>
            >
            encoder_type;

        const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }

    }


    std::wstring encode(const std::string& string)
    {
        return encoder().encode(string);
    }


}
