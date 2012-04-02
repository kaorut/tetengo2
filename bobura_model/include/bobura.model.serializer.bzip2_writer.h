/*! \file
    \brief The definition of bobura::model::serializer::bzip2_writer.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_BZIP2WRITER_H)
#define BOBURA_MODEL_SERIALIZER_BZIP2WRITER_H

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>

#include "bobura.model.serializer.writer.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON writer.

        \tparam OutputStream        A output stream type.
        \tparam Timetable           A timetable type.
        \tparam PathString          A path string type.
    */
    template <typename OutputStream, typename Timetable, typename PathString>
    class bzip2_writer : public writer<OutputStream, Timetable, PathString>
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path string type.
        typedef PathString path_string_type;

        //! The base type.
        typedef
            writer<output_stream_type, timetable_type, path_string_type>
            base_type;


        // constructors and destructor

        /*!
            \brief Creates a JSON writer.
        */
        bzip2_writer()
        :
        base_type()
        {}

        /*!
            \brief Destroys the bzip2_writer.
        */
        virtual ~bzip2_writer()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // virtual functions

        virtual path_string_type extention_impl()
        const
        {
            return path_string_type(TETENGO2_TEXT("bttc"));
        }

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {

        }


    };


}}}


#endif
