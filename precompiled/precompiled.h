/*! \file
    \brief The precompiled header for Visual C++.

    Copyright (C) 2007-2014 kaoru

    $Id$
*/

#if !defined(PRECOMPILED_H)
#define PRECOMPILED_H

// The standard library headers
#include <algorithm>
#include <cassert>
#include <cerrno>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cwchar>
#include <exception>
#include <functional>
#include <iomanip>
#include <ios>
#include <istream>
#include <iterator>
#include <limits>
#include <locale>
#include <map>
#include <memory>
#include <mutex>
#include <ostream>
#include <queue>
#include <sstream>
#include <stack>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
#include <vector>

// The Boost library headers
#include <boost/algorithm/string.hpp>
#include <boost/core/ignore_unused.hpp>
#include <boost/core/noncopyable.hpp>
#include <boost/exception/all.hpp>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/iterator/indirect_iterator.hpp>
#include <boost/iterator/iterator_categories.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/iterator/transform_iterator.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/math/constants/constants.hpp>
#include <boost/mpl/assert.hpp>
#include <boost/mpl/at.hpp>
#include <boost/mpl/aux_/na.hpp>
#include <boost/mpl/begin.hpp>
#include <boost/mpl/clear.hpp>
#include <boost/mpl/count.hpp>
#include <boost/mpl/deref.hpp>
#include <boost/mpl/empty.hpp>
#include <boost/mpl/end.hpp>
#include <boost/mpl/erase.hpp>
#include <boost/mpl/erase_key.hpp>
#include <boost/mpl/front.hpp>
#include <boost/mpl/has_key.hpp>
#include <boost/mpl/insert.hpp>
#include <boost/mpl/insert_range.hpp>
#include <boost/mpl/int.hpp>
#include <boost/mpl/integral_c.hpp>
#include <boost/mpl/is_sequence.hpp>
#include <boost/mpl/iterator_tags.hpp>
#include <boost/mpl/key_type.hpp>
#include <boost/mpl/next.hpp>
#include <boost/mpl/order.hpp>
#include <boost/mpl/pair.hpp>
#include <boost/mpl/pop_front.hpp>
#include <boost/mpl/push_front.hpp>
#include <boost/mpl/reverse.hpp>
#include <boost/mpl/sequence_tag.hpp>
#include <boost/mpl/size.hpp>
#include <boost/mpl/value_type.hpp>
#include <boost/mpl/vector.hpp>
#include <boost/mpl/void.hpp>
#include <boost/operators.hpp>
#include <boost/optional.hpp>
#include <boost/predef.h>
#include <boost/rational.hpp>
#include <boost/scope_exit.hpp>
#include <boost/signals2.hpp>
#include <boost/spirit/include/qi.hpp>
#include <boost/spirit/include/support_multi_pass.hpp>
#include <boost/swap.hpp>
#include <boost/throw_exception.hpp>
#include <boost/utility.hpp>
#include <boost/variant.hpp>


#if BOOST_COMP_MSVC

// Windows headers

#pragma warning (push)
#pragma warning (disable: 4005)
#include <intsafe.h>
#include <stdint.h>
#pragma warning(pop)
#define NOMINMAX
#define OEMRESOURCE
#include <Windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include <d2d1.h>
#include <dwrite.h>
#include <dxgiformat.h>
#if !defined(min) && !defined(DOCUMENTATION)
#   define min(a, b) ((a) < (b) ? (a) : (b))
#endif
#if !defined(max) && !defined(DOCUMENTATION)
#   define max(a, b) ((a) > (b) ? (a) : (b))
#endif
#include <GdiPlus.h>
#undef min
#undef max
#include <ShObjIdl.h>
#include <ShTypes.h>
#include <Unknwn.h>
#include <wincodec.h>

#endif


#endif
