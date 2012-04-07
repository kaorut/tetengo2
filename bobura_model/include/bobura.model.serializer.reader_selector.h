/*! \file
    \brief The definition of bobura::model::serializer::reader_selector.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READERSELECTOR_H)
#define BOBURA_MODEL_SERIALIZER_READERSELECTOR_H

#include <memory>
#include <utility>
#include <vector>

#include <tetengo2.cpp11.h>

#include "bobura.model.serializer.reader.h"


namespace bobura { namespace model { namespace serializer
{
    /*!
        \brief The class template for a reader selector.

        \tparam ForwardIterator A forward iterator type.
        \tparam Timetable       A timetable type.
    */
    template <typename ForwardIterator, typename Timetable>
    class reader_selector : public reader<ForwardIterator, Timetable>
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
            \brief Creates a reader selector.

            \param p_readers Unique pointers to readers.

            \throw std::invalid_argument When the count of the readers is
                                         empty.
        */
        explicit reader_selector(
            std::vector<std::unique_ptr<base_type>> p_readers
        )
        :
        m_p_readers(std::move(p_readers))
        {
            if (m_p_readers.empty())
            {
                BOOST_THROW_EXCEPTION(
                    std::invalid_argument("No reader is specified.")
                );
            }
        }

        /*!
            \brief Destroys the reader_selector.
        */
        virtual ~reader_selector()
        TETENGO2_CPP11_NOEXCEPT
        {}


    private:
        // variables

        const std::vector<std::unique_ptr<base_type>> m_p_readers;


        // virtual functions

        virtual bool selects_impl(const iterator first, const iterator last)
        {
            return true;
        }

        virtual std::unique_ptr<timetable_type> read_impl(
            const iterator first,
            const iterator last
        )
        {
            return m_p_readers[0]->read(first, last);
        }


    };


}}}


#endif
