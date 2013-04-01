/*! \file
    \brief The definition of bobura::model::serializer::reader_selector.

    Copyright (C) 2007-2013 kaoru

    $Id$
*/

#if !defined(BOBURA_MODEL_SERIALIZER_READERSELECTOR_H)
#define BOBURA_MODEL_SERIALIZER_READERSELECTOR_H

#include <algorithm>
//#include <memory>
#include <stdexcept>
#include <utility>
#include <vector>

#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.utility.h>

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

        //! The base type.
        typedef reader<iterator, timetable_type> base_type;

        //! The error type.
        typedef typename base_type::error_type error_type;


        // constructors and destructor

        /*!
            \brief Creates a reader selector.

            \param p_readers Unique pointers to readers.

            \throw std::invalid_argument When the count of the readers is empty.
        */
        explicit reader_selector(std::vector<std::unique_ptr<base_type>> p_readers)
        :
        m_p_readers(std::move(p_readers))
        {
            if (m_p_readers.empty())
                BOOST_THROW_EXCEPTION(std::invalid_argument("No reader is specified."));
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

#if defined(__GNUC__)
#   pragma GCC diagnostic ignored "-Wreturn-type"
#endif
        virtual bool selects_impl(const iterator first, const iterator last)
        override
        {
            tetengo2::suppress_unused_variable_warning(first, last);

            BOOST_THROW_EXCEPTION(std::logic_error("This function cannot be called."));
        }
#if defined(__GNUC__)
#   pragma GCC diagnostic warning "-Wreturn-type"
#endif

        virtual std::unique_ptr<timetable_type> read_impl(const iterator first, const iterator last, error_type& error)
        override
        {
            const auto found =
                std::find_if(
                    m_p_readers.begin(),
                    m_p_readers.end(),
                    [first, last](const std::unique_ptr<base_type>& p_reader)
                    {
                        return p_reader->selects(first, last);
                    }
                );
            if (found == m_p_readers.end())
            {
                error = error_type::unsupported;
                return std::unique_ptr<timetable_type>();
            }

            return (*found)->read(first, last, error);
        }


    };


}}}


#endif
