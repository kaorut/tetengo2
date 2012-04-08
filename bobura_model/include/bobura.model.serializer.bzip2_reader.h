/*! \file
    \brief The definition of bobura::model::serializer::bzip2_reader.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_BZIP2READER_H)
#define BOBURA_MODEL_SERIALIZER_BZIP2READER_H

#include <memory>
#include <utility>
#include <vector>

#include <tetengo2.cpp11.h>

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
        */
        explicit bzip2_reader()
        {}

        /*!
            \brief Destroys the bzip2_reader.
        */
        virtual ~bzip2_reader()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            return false;
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
