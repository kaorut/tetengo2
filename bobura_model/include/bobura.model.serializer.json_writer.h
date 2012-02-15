/*! \file
    \brief The definition of bobura::model::serializer::json_writer.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_JSONWRITER_H)
#define BOBURA_MODEL_SERIALIZER_JSONWRITER_H

#include <tetengo2.cpp11.h>

#include "bobura.model.serializer.writer.h"
#include "bobura.model.station_info.grade.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON writer.

        \tparam Timetable           A timetable type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam OutputStream        A output stream type.
        \tparam Encoder             An encoder type.
    */
    template <
        typename Timetable,
        typename StationGradeTypeSet,
        typename OutputStream,
        typename Encoder
    >
    class json_writer : public writer<OutputStream, Timetable>
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The base type.
        typedef writer<output_stream_type, timetable_type> base_type;

        //! The encoder type.
        typedef Encoder encoder_type;


        // constructors and destructor

        /*!
            \brief Creates a JSON writer.
        */
        json_writer()
        :
        base_type()
        {}

        /*!
            \brief Destroys the json_writer.
        */
        virtual ~json_writer()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename timetable_type::string_type string_type;


        // static functions

        static const encoder_type& encoder()
        {
            static const encoder_type singleton;
            return singleton;
        }


        // virtual functions

        virtual void write_impl(
            const timetable_type& timetable,
            output_stream_type&   output_stream
        )
        {

        }


    };


}}}


#endif
