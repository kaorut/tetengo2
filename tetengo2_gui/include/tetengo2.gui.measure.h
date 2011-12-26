/*! \file
    \brief The definition of tetengo2::gui::measure.

    Copyright (C) 2007-2011 kaoru

    $Id$
*/

#if !defined(TETENGO2_GUI_MEASURE_H)
#define TETENGO2_GUI_MEASURE_H

#include <cstddef>
#include <type_traits>
#include <utility>


namespace tetengo2 { namespace gui
{
    /*!
        \brief Converts a value in a certain unit to pixels.

        \tparam PixelValue A pixel value type.
        \tparam Unit       A unit type.

        \param value A value in a certain unit.

        \return The converted value in pixels.
    */
    template <typename PixelValue, typename Unit>
    PixelValue to_pixels(
        const Unit& value,
        typename std::enable_if<
            !std::is_arithmetic<Unit>::value
        >::type* = NULL
    )
    {
        return static_cast<PixelValue>(value.to_pixels());
    }

    /*!
        \brief Converts a value in pixels to a certain unit.

        \tparam Unit       A unit type.
        \tparam PixelValue A pixel value type.

        \param value A value in pixels.

        \return The converted value in a certain unit.
    */
    template <typename Unit, typename PixelValue>
    Unit to_unit(
        const PixelValue value,
        typename std::enable_if<
            !std::is_arithmetic<Unit>::value
        >::type* = NULL
    )
    {
        return Unit::from_pixels(
            static_cast<typename Unit::pixel_value_type>(value)
        );
    }

#if !defined(DOCUMENTATION)
    template <typename PixelValue, typename Unit>
    PixelValue to_pixels(
        const Unit& value,
        typename std::enable_if<std::is_arithmetic<Unit>::value>::type* = NULL
    )
    {
        return static_cast<PixelValue>(value);
    }

    template <typename Unit, typename PixelValue>
    Unit to_unit(
        const PixelValue value,
        typename std::enable_if<std::is_arithmetic<Unit>::value>::type* = NULL
    )
    {
        return static_cast<Unit>(value);
    }
#endif


    /*!
        \brief The position class.

        \tparam Position A position type.
    */
    template <typename Position>
    class position
    {
    public:
        // types

        //! The position type.
        typedef Position position_type;

        //! The left type.
        typedef typename Position::left_type left_type;

        //! The top type.
        typedef typename Position::top_type top_type;


        // static functions

        /*!
            \brief Returns the left.

            \param position A position.

            \return The left.
        */
        static const left_type& left(const position_type& position);

        /*!
            \brief Returns the top.

            \param position A position.

            \return The top.
        */
        static const top_type& top(const position_type& position);

        /*!
            \brief Makes a position.

            \tparam L A left type.
            \tparam T A top type.

            \param left A left.
            \param top  A top.

            \return A position.
        */
        template <typename L, typename T>
        static position_type make(L&& left, T&& top);


    private:
        // forbidden operations

        position();


    };

#if !defined(DOCUMENTATION)
    template <typename LeftTop>
    class position<std::pair<LeftTop, LeftTop>>
    {
    public:
        // types

        typedef std::pair<LeftTop, LeftTop> position_type;

        typedef LeftTop left_type;

        typedef LeftTop top_type;


        // static functions

        static const left_type& left(const position_type& position)
        {
            return position.first;
        }

        static const top_type& top(const position_type& position)
        {
            return position.second;
        }

        template <typename L, typename T>
        static position_type make(L&& left, T&& top)
        {
            return position_type(std::forward<L>(left), std::forward<T>(top));
        }


    private:
        // forbidden operations

        position();


    };
#endif


    /*!
        \brief The dimension class.

        \tparam Dimension A dimension type.
    */
    template <typename Dimension>
    class dimension
    {
    public:
        // types

        //! The dimension type.
        typedef Dimension dimension_type;

        //! The left type.
        typedef typename Dimension::width_type width_type;

        //! The top type.
        typedef typename Dimension::height_type height_type;


        // static functions

        /*!
            \brief Returns the width.

            \param dimension A dimension.

            \return The width.
        */
        static const width_type& width(const dimension_type& dimension);

        /*!
            \brief Returns the height.

            \param dimension A dimension.

            \return The height.
        */
        static const height_type& height(const dimension_type& dimension);

        /*!
            \brief Makes a dimension.

            \tparam W A width type.
            \tparam H A height type.

            \param width  A width.
            \param height A height.

            \return A dimension.
        */
        template <typename W, typename H>
        static dimension_type make(W&& width, H&& height);


    private:
        // forbidden operations

        dimension();


    };

#if !defined(DOCUMENTATION)
    template <typename WidthHeight>
    class dimension<std::pair<WidthHeight, WidthHeight>>
    {
    public:
        // types

        typedef std::pair<WidthHeight, WidthHeight> dimension_type;

        typedef WidthHeight width_type;

        typedef WidthHeight height_type;


        // static functions

        static const width_type& width(const dimension_type& dimension)
        {
            return dimension.first;
        }

        static const height_type& height(const dimension_type& dimension)
        {
            return dimension.second;
        }

        template <typename W, typename H>
        static dimension_type make(W&& width, H&& height)
        {
            return dimension_type(
                std::forward<W>(width), std::forward<H>(height)
            );
        }


    private:
        // forbidden operations

        dimension();


    };
#endif


}}


#endif
