/*! \file
    \brief The definition of bobura::model::serializer::writer_set.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WRITERSET_H)
#define BOBURA_MODEL_SERIALIZER_WRITERSET_H

//#include <memory>
//#include <utility>
//#include <vector>

//#include <boost/noncopyable.hpp>

#include <tetengo2.unique.h>

#include "bobura.model.serializer.bzip2_writer.h"
#include "bobura.model.serializer.json_writer.h"
#include "bobura.model.serializer.writer.h"
#include "bobura.model.serializer.writer_selector.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a writer set.

        \tparam OutputStream        A output stream type.
        \tparam Timetable           A timetable type.
        \tparam Path                A path type.
        \tparam StationGradeTypeSet A station grade type set type.
        \tparam Encoder             An encoder type.
    */
    template <typename OutputStream, typename Timetable, typename Path, typename Encoder>
    class writer_set : private boost::noncopyable
    {
    public:
        // types

        //! The output stream type.
        typedef OutputStream output_stream_type;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The path type.
        typedef Path path_type;

        //! The encoder type.
        typedef Encoder encoder_type;

        //! The writer type.
        typedef writer<output_stream_type, timetable_type, path_type> writer_type;

        //! The bzip2 writer type.
        typedef bzip2_writer<output_stream_type, timetable_type, path_type> bzip2_writer_type;

        //! The JSON writer type.
        typedef json_writer<output_stream_type, timetable_type, path_type, encoder_type> json_writer_type;


        // static functions

        /*!
            \brief Creates writers.

            \return Unique pointers to writers.
        */
        static std::vector<std::unique_ptr<writer_type>> create_writers()
        {
            std::vector<std::unique_ptr<writer_type>> writers;

            writers.push_back(tetengo2::make_unique<json_writer_type>());
            writers.push_back(tetengo2::make_unique<bzip2_writer_type>(tetengo2::make_unique<json_writer_type>()));

            return std::move(writers);
        }


    private:
        // forbidden operations

        writer_set();


    };


}}}


#endif
