/*! \file
    \brief The definition of bobura::model::serializer::bzip2_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_BZIP2READER_H)
#define BOBURA_MODEL_SERIALIZER_BZIP2READER_H

#include <memory>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <boost/utility.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a bzip2 reader.

        \tparam ForwardIterator A forward iterator type.
        \tparam Timetable       A timetable type.
    */
    template <typename ForwardIterator, typename Timetable>
    class bzip2_reader : public reader<ForwardIterator, Timetable>
    {
    public:
        // types

        //! The iterator type.
        typedef ForwardIterator iterator;

        //! The timetable type.
        typedef Timetable timetable_type;

        //! THe base type.
        typedef reader<iterator, timetable_type> base_type;


        // constructors and destructor

        /*!
            \brief Creates a bzip2 reader.

            \param p_reader A unique pointer to a reader.

        */
        explicit bzip2_reader(std::unique_ptr<base_type> p_reader)
        :
        m_p_reader(std::move(p_reader))
        {}

        /*!
            \brief Destroys the bzip2_reader.
        */
        virtual ~bzip2_reader()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // types

        typedef
            std::basic_string<typename iterator::value_type> input_string_type;

        typedef
            std::basic_istringstream<typename iterator::value_type>
            input_stream_type;


        // variables

        const std::unique_ptr<base_type> m_p_reader;


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            const input_string_type input(first, last);
            if (input.length() < 2)
                return false;
            if (input.substr(0, 2) != input_string_type(TETENGO2_TEXT("BZ")))
                return false;

            return m_p_reader->selects(first, last);
        }

        virtual std::unique_ptr<timetable_type> read_impl(
            const iterator first,
            const iterator last
        )
        {
            return std::unique_ptr<timetable_type>();
        }


    };


}}}


#endif
