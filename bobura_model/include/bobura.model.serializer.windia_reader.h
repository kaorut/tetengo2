/*! \file
    \brief The definition of bobura::model::serializer::windia_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_WINDIA2READER_H)
#define BOBURA_MODEL_SERIALIZER_WINDIA2READER_H

#include <tetengo2.text.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a WinDIA reader.

        \tparam ForwardIterator A forward iterator type.
        \tparam Timetable       A timetable type.
    */
    template <typename ForwardIterator, typename Timetable>
    class windia_reader : public reader<ForwardIterator, Timetable>
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
            \brief Creates a WinDIA reader.
        */
        windia_reader()
        :
        base_type()
        {}

        /*!
            \brief Destroys the windia_reader.
        */
        virtual ~windia_reader()
        {}


    private:
        // types

        typedef std::basic_string<typename iterator::value_type> input_string_type;


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            return false;
        }

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last)
        {
            return std::unique_ptr<timetable_type>();
        }


    };


}}}


#endif
