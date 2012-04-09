/*! \file
    \brief The definition of bobura::model::serializer::reader_selector.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READERSELECTOR_H)
#define BOBURA_MODEL_SERIALIZER_READERSELECTOR_H

#include <algorithm>
#include <cassert>
//#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/throw_exception.hpp>

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
            BOOST_THROW_EXCEPTION(
                std::logic_error("This function cannot be called.")
            );
        }

        virtual std::unique_ptr<timetable_type> read_impl(
            const iterator first,
            const iterator last
        )
        {
            typedef
                typename std::vector<
                    std::unique_ptr<base_type>
                >::const_iterator
                iterator_type;

            const iterator_type found =
                std::find_if(
                    m_p_readers.begin(),
                    m_p_readers.end(),
                    TETENGO2_CPP11_BIND(
                        &reader_selector::call_selects,
                        this,
                        tetengo2::cpp11::placeholders_1(),
                        first,
                        last
                    )
                );
            if (found == m_p_readers.end())
            {
                assert(!m_p_readers.empty());
                return m_p_readers.front()->read(first, last);
            }

            return (*found)->read(first, last);
        }


        // functions

        bool call_selects(
            const std::unique_ptr<base_type>& p_reader,
            const iterator                    first,
            const iterator                    last
        )
        const
        {
            return p_reader->selects(first, last);
        }


    };


}}}


#endif
