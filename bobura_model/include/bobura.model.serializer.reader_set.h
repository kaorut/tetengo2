/*! \file
    \brief The definition of bobura::model::serializer::reader_set.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READERSET_H)
#define BOBURA_MODEL_SERIALIZER_READERSET_H

//#include <memory>
//#include <utility>
//#include <vector>

//#include <boost/noncopyable.hpp>

#include <tetengo2.unique.h>

#include "bobura.model.serializer.json_reader.h"
#include "bobura.model.serializer.reader.h"
#include "bobura.model.serializer.reader_selector.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer set.

        \tparam OutputStream        A output stream type.
        \tparam Timetable           A timetable type.
        \tparam Path                A path type.
        \tparam StationGradeTypeSet A station grade type set.
        \tparam Encoder             An encoder type.
    */
    template <
        typename ForwardIterator,
        typename Timetable,
        typename PullParser,
        typename StationGradeTypeSet,
        typename Encoder
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

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The JSON writer type.
        typedef
            json_reader<
                pull_parser_type,
                timetable_type,
                station_grade_type_set_type,
                encoder_type
            >
            json_reader_type;


        // static functions

        /*!
            \brief Creates readers.

            \return Unique pointers to readers.
        */
        static std::vector<std::unique_ptr<reader_type>> create_readers()
        {
            std::vector<std::unique_ptr<reader_type>> readers;

            //readers.push_back(tetengo2::make_unique<json_reader_type>());
            //readers.push_back(
            //    tetengo2::make_unique<bzip2_writer_type>(
            //        tetengo2::make_unique<json_writer_type>()
            //    )
            //);

            return std::move(readers);
        }


    private:
        // forbidden operations

        reader_set();


    };


}}}


#endif
