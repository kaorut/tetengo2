/*! \file
    \brief The definition of bobura::view::scale_list.

    Copyright (C) 2007-2012 kaoru

    $Id$
*/

#if !defined(BOBURA_VIEW_SCALELIST_H)
#define BOBURA_VIEW_SCALELIST_H

#include <algorithm>
#include <functional>
#include <stdexcept>
#include <vector>

#include <boost/noncopyable.hpp>
#include <boost/optional.hpp>
#include <boost/throw_exception.hpp>

#include <tetengo2.cpp11.h>
#include <tetengo2.text.h>


namespace bobura { namespace view
{
    /*!
        \brief The class template for a view scale list.

        \tparam Scale  A scale type.
        \tparam Size   A size type.
        \tparam String A string type.
    */
    template <typename Scale, typename Size, typename String>
    class scale_list : boost::noncopyable
    {
    public:
        // types

        //! The scale type.
        typedef Scale scale_type;

        //! The size type.
        typedef Size size_type;

        //! The string type.
        typedef String string_type;


        // functions

        /*!
            \brief Returns the scale count.

            \return The scale count.
        */
        size_type size()
        const
        {
            assert(scales().size() == labels().size());
            return scales().size();
        }

        /*!
            \brief Returns the scale at the specified index.

            \param index.

            \return The scale.

            \throw std::out_of_range When index is out of range.
        */
        const scale_type& at(const size_type index)
        const
        {
            if (index >= scales().size())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return scales()[index];
        }

        /*!
            \brief Returns the scale label at the specified index.

            \param index.

            \return The scale label.

            \throw std::out_of_range When index is out of range.
        */
        const string_type& label_at(const size_type index)
        const
        {
            if (index >= labels().size())
                BOOST_THROW_EXCEPTION(std::out_of_range("index is out of range."));

            return labels()[index];
        }

        /*!
            \brief Returns the same scale index.

            \param scale A scale.

            \return The same scale index.
        */
        boost::optional<size_type> index_of(const scale_type& scale)
        const
        {
            for (size_type i = 0; i < scales().size(); ++i)
            {
                if (scales()[i] == scale)
                    return boost::make_optional(i);
            }
            return boost::none;
        }

        /*!
            \brief Returns the nearest larger scale.
        
            \param scale A scale.

            \return The nearest larger scale.
        */
        const scale_type& larger(const scale_type& scale)
        const
        {
            const typename std::vector<scale_type>::const_iterator found =
                std::find_if(
                    scales().begin(),
                    scales().end(),
                    TETENGO2_CPP11_BIND(
                        std::greater<scale_type>(), tetengo2::cpp11::placeholders_1(), tetengo2::cpp11::cref(scale)
                    )
                );
            return found != scales().end() ? *found : scales().back();
        }

        /*!
            \brief Returns the nearest smaller scale.
        
            \param scale A scale.

            \return The nearest smaller scale.
        */
        const scale_type& smaller(const scale_type& scale)
        const
        {
            const typename std::vector<scale_type>::const_reverse_iterator found =
                std::find_if(
                    scales().rbegin(),
                    scales().rend(),
                    TETENGO2_CPP11_BIND(
                        std::less<scale_type>(), tetengo2::cpp11::placeholders_1(), tetengo2::cpp11::cref(scale)
                    )
                );
            return found != scales().rend() ? *found : scales().front();
        }


    private:
        // static functions

        static const std::vector<scale_type>& scales()
        {
            static const std::vector<scale_type> singleton(make_scales());
            return singleton;
        }

        static const std::vector<string_type>& labels()
        {
            static const std::vector<string_type> singleton(make_labels());
            return singleton;
        }

        static std::vector<scale_type> make_scales()
        {
            std::vector<scale_type> scales;

            scales.push_back(scale_type(1, 2));
            scales.push_back(scale_type(3, 4));
            scales.push_back(scale_type(1));
            scales.push_back(scale_type(3, 2));
            scales.push_back(scale_type(2));
            scales.push_back(scale_type(4));

            assert(std::is_sorted(scales.begin(), scales.end(), std::less<scale_type>()));
            return scales;
        }

        static std::vector<string_type> make_labels()
        {
            std::vector<string_type> labels;

            labels.push_back(string_type(TETENGO2_TEXT("50%")));
            labels.push_back(string_type(TETENGO2_TEXT("75%")));
            labels.push_back(string_type(TETENGO2_TEXT("100%")));
            labels.push_back(string_type(TETENGO2_TEXT("150%")));
            labels.push_back(string_type(TETENGO2_TEXT("200%")));
            labels.push_back(string_type(TETENGO2_TEXT("400%")));

            assert(labels.size() == scales().size());
            return labels;
        }


    };


}}


#endif
