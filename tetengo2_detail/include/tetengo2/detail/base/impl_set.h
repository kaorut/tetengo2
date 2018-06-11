/*! \file
    \brief The definition of tetengo2::detail::base::impl_set.

    Copyright (C) 2007-2018 kaoru

    $Id$
*/

#if !defined(TETENGO2_DETAIL_BASE_IMPLSET_H)
#define TETENGO2_DETAIL_BASE_IMPLSET_H

#include <boost/core/noncopyable.hpp>


namespace tetengo2::detail {
    namespace base {
        class encoding;


        /*!
            The class for a detail implementation set.
        */
        class impl_set : private boost::noncopyable
        {
        public:
            // constructors and destructor

            /*!
                \brief Destroys the detail implementation set.
            */
            virtual ~impl_set();


            // functions

            /*!
                \brief Returns the detail implementation of encoding.

                \return The detail implementation.
            */
            const encoding& encoding_() const;


        protected:
            // constructors

            /*!
                \brief Creates a detail implementation set.
            */
            impl_set();


        private:
            // virtual functions

            virtual const encoding& encoding_impl() const = 0;
        };
    }


    /*!
        \brief Returns the detail implementation set.

        \return The detail implementation set.

        \throw std::logic_error When no implementation set is set yet.
    */
    const base::impl_set& detail_impl_set();

    /*!
        \brief Sets a detail implementation set.

        \param impl_set_ A detail implementation set.
    */
    void set_detail_impl_set(const base::impl_set& impl_set_);
}


#endif
