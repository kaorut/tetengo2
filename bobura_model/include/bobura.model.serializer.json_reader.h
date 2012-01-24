/*! \file
    \brief The definition of bobura::model::serializer::json_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_JSONREADER_H)
#define BOBURA_MODEL_SERIALIZER_JSONREADER_H

//#include <istream>
//#include <memory>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>
#include <tetengo2.unique.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a JSON reader.

        \tparam Timetable A timetable type.
    */
    template <typename Timetable>
    class json_reader : public reader<Timetable>
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;

        //! The base type.
        typedef reader<timetable_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a JSON reader.
        */
        json_reader()
        :
        base_type()
        {}

        /*!
            \brief Destroys the json_reader.
        */
        virtual ~json_reader()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef typename timetable_type::string_type string_type;


        // virtual functions

        virtual std::unique_ptr<timetable_type> read_impl(
            std::istream& input_stream
        )
        {
            std::unique_ptr<timetable_type> p_timetable =
                tetengo2::make_unique<timetable_type>(string_type());

            return std::move(p_timetable);
        }


    };


}}}


#endif
