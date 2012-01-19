/*! \file
    \brief The definition of bobura::model::serializer::reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READER_H)
#define BOBURA_MODEL_SERIALIZER_READER_H

#include <cstddef>
#include <istream>
#include <memory>

#include <boost/noncopyable.hpp>

#include <tetengo2.cpp11.h>


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a reader.

        \tparam Timetable A timetable type.
    */
    template <typename Timetable>
    class reader : private boost::noncopyable
    {
    public:
        // types

        //! The timetable type.
        typedef Timetable timetable_type;


        // constructors and destructor

        /*!
            \brief Destroys the reader.
        */
        virtual ~reader()
        TETENGO2_CPP11_NOEXCEPT
        {}


        // functions

        /*!
            \brief Reads a timetable.

            When it cannot read a timetable, it returns NULL.

            \param input_stream An input stream.

            \return A unique pointer to a timetable.
        */
        std::unique_ptr<timetable_type> read(std::istream& input_stream)
        {
            return read_impl(input_stream);
        }


    protected:
        // constructors

        /*!
            \brief Creates a reader.
        */
        reader()
        {}


    private:
        // virtual functions

        virtual std::unique_ptr<timetable_type> read_impl(
            std::istream& input_stream
        )
        = 0;


    };


}}}


#endif
