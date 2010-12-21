/*! \file
    \brief The definition of tetengo2::gui::unit::win32::em.

    Copyright (C) 2007-2010 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_UNIT_WIN32_EM_H)
#define TETENGO2_GUI_UNIT_WIN32_EM_H

//#include <utility>

#include <boost/operators.hpp>
#include <boost/swap.hpp>

#include "tetengo2.gui.win32.detail.font.h"
#include "tetengo2.operators.h"


namespace tetengo2 { namespace gui { namespace unit { namespace win32
{
    /*!
        \brief The class template for a EM height unit.
 
        \tparam Value      A value type.
        \tparam PixelValue A em value type.
   */
    template <typename Value, typename PixelValue>
    class em :
        private boost::totally_ordered<em<Value, PixelValue>>,
        private boost::totally_ordered<em<Value, PixelValue>, Value>,
        private tetengo2::additive<em<Value, PixelValue>>,
        private tetengo2::additive<em<Value, PixelValue>, Value>
    {
    public:
        // types

        //! The value type.
        typedef Value value_type;

        //! The pixel value type.
        typedef PixelValue pixel_value_type;


        // static functions

        /*!
            \brief Returns an EM height unit made from a value in pixels.

            \param value A value in pixels.

            \return An EM height unit.
        */
        static em from_pixels(const pixel_value_type value)
        {
            value_type em_value =
                value /
                -tetengo2::gui::win32::detail::get_message_font().lfHeight;
            return em(std::move(em_value));
        }


        // constructors and destructor

        /*!
            \brief Creates an EM height unit.

            \param value A value.
        */
        explicit em(const value_type& value)
        :
        m_value(value)
        {}

        /*!
            \brief Creates an EM height unit.

            \param value A value.
        */
        explicit em(value_type&& value)
        :
        m_value(std::forward<value_type>(value))
        {}


        // functions

        /*!
            \brief Adds another EM height unit.

            \param another Another EM height unit.

            \return This object.
        */
        em& operator+=(const em& another)
        {
            em temp(*this);

            temp.m_value += another.m_value;
            
            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Adds another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& operator+=(const value_type& another)
        {
            em temp(*this);

            temp.m_value += another;
            
            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts another EM height unit.

            \param another Another EM height unit.

            \return This object.
        */
        em& operator-=(const em& another)
        {
            em temp(*this);

            temp.m_value -= another.m_value;
            
            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Subtracts another value in EM height unit.

            \param another Another value in EM height unit.

            \return This object.
        */
        em& operator-=(const value_type& another)
        {
            em temp(*this);

            temp.m_value -= another;
            
            boost::swap(temp, *this);
            return *this;
        }

        /*!
            \brief Checks whether one EM height unit is equal to another.

            \param one     One EM height unit.
            \param another Another EM height unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const em& one, const em& another)
        {
            return one.m_value == another.m_value;
        }

        /*!
            \brief Checks whether one EM height unit is equal to another.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is equal to the other.
            \retval false Otherwise.
        */
        friend bool operator==(const em& one, const value_type& another)
        {
            return one.m_value == another;
        }

        /*!
            \brief Checks whether one EM height unit is less than another.

            \param one     One EM height unit.
            \param another Another EM height unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const em& one, const em& another)
        {
            return one.m_value < another.m_value;
        }

        /*!
            \brief Checks whether one EM height unit is less than another.

            \param one     One EM height unit.
            \param another Another value in EM height unit.

            \retval true  When the one is less than the other.
            \retval false Otherwise.
        */
        friend bool operator<(const em& one, const value_type& another)
        {
            return one.m_value < another;
        }

        /*!
            \brief Returns the value.

            \return The value.
        */
        const value_type& value()
        const
        {
            return m_value;
        }

        /*!
            \brief Returns the value in pixels.

            \return The value in ems.
        */
        pixel_value_type to_pixels()
        const
        {
            return
                m_value *
                -tetengo2::gui::win32::detail::get_message_font().lfHeight;
        }


    private:
        // variables

        value_type m_value;


    };


}}}}


#endif
