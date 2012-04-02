/*! \file
    \brief The definition of bobura::model::serializer::writer_type_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITERTYPESET_H)
#define BOBURA_MODEL_SERIALIZER_WRITERTYPESET_H

#include <boost/noncopyable.hpp>

#include "bobura.model.serializer.json_writer.h"
#include "bobura.model.serializer.writer.h"
#include "bobura.model.serializer.writer_selector.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer type set.

        \tparam OutputStream        A output stream type.
        \tparam Timetable           A timetable type.
        \tparam PathString          A path string type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam Encoder             An encoder type.
    */
    template <
        typename OutputStream,
        typename Timetable,
        typename PathString,
        typename StationGradeTypeSet,
        typename Encoder
    >
    class writer_type_set : private boost::noncopyable
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path string type.
        typedef PathString path_string_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The writer type.
        typedef
            writer<output_stream_type, timetable_type, path_string_type>
            writer_type;

        //! The JSON writer type.
        typedef
            json_writer<
                output_stream_type,
                timetable_type,
                path_string_type,
                station_grade_type_set_type,
                encoder_type
            >
            json_writer_type;


    private:
        // forbidden operations

        writer_type_set();


    };


}}}


#endif
