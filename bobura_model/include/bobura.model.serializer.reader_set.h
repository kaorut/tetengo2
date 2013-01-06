/*! \file
    \brief The definition of bobura::model::serializer::reader_set.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READERSET_H)
#define BOBURA_MODEL_SERIALIZER_READERSET_H

//#include <memory>
//#include <utility>
//#include <vector>

//#include <boost/noncopyable.hpp>

#include <tetengo2.unique.h>

#include "bobura.model.serializer.bzip2_reader.h"
#include "bobura.model.serializer.json_reader.h"
#include "bobura.model.serializer.oudia_reader.h"
#include "bobura.model.serializer.reader.h"
#include "bobura.model.serializer.reader_selector.h"
#include "bobura.model.serializer.windia_reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a reader set.

        \tparam ForwardIterator     A forward iterator type.
        \tparam Timetable           A timetable type.
        \tparam PullParser          A pull parser type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam Utf8Encoder         A UTF-8 encoder type.
        \tparam Cp932Encoder        A CP932 encoder type.
    */
    template <
        typename ForwardIterator,
        typename Timetable,
        typename PullParser,
        typename StationGradeTypeSet,
        typename Utf8Encoder,
        typename Cp932Encoder
    >
    class reader_set : private boost::noncopyable
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The base type.
        typedef reader<iterator, timetable_type> base_type;

        //! The pull parser type.
        typedef PullParser pull_parser_type;

        //! The station grade type set type.
        typedef StationGradeTypeSet station_grade_type_set_type;

        //! The UTF-8 encoder type.
        typedef Utf8Encoder utf8_encoder_type;

        //! The CP932 encoder type.
        typedef Cp932Encoder cp932_encoder_type;

        //! The reader type.
        typedef reader<iterator, timetable_type> reader_type;

        //! The JSON reader type.
        typedef
            json_reader<pull_parser_type, timetable_type, station_grade_type_set_type, utf8_encoder_type>
            json_reader_type;

        //! The bzip2 reader type.
        typedef bzip2_reader<iterator, timetable_type> bzip2_reader_type;

        //! The OuDia reader type.
        typedef
            oudia_reader<iterator, timetable_type, station_grade_type_set_type, cp932_encoder_type> oudia_reader_type;

        //! The WinDIA reader type.
        typedef
            windia_reader<iterator, timetable_type, station_grade_type_set_type, cp932_encoder_type>
            windia_reader_type;


        // static functions

        /*!
            \brief Creates readers.

            \return Unique pointers to readers.
        */
        static std::vector<std::unique_ptr<reader_type>> create_readers()
        {
            std::vector<std::unique_ptr<reader_type>> readers;

            readers.push_back(tetengo2::make_unique<json_reader_type>());
            readers.push_back(tetengo2::make_unique<bzip2_reader_type>(tetengo2::make_unique<json_reader_type>()));
            readers.push_back(tetengo2::make_unique<windia_reader_type>());

            return std::move(readers);
        }


    private:
        // forbidden operations

        reader_set();


    };


}}}


#endif
