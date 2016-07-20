/*! \file
    \brief The facade of tetengo2.

    Copyright (C) 2007-2016 kaoru

    $Id$
*/

#if !defined(TETENGO2_H)
#define TETENGO2_H


#include <tetengo2/concurrent/channel.h>
#include <tetengo2/concurrent/consumer.h>
#include <tetengo2/concurrent/producer.h>
#include <tetengo2/concurrent/progressive_future.h>
#include <tetengo2/concurrent/progressive_promise.h>
#include <tetengo2/config/cached_config.h>
#include <tetengo2/config/config_base.h>
#include <tetengo2/config/config_list.h>
#include <tetengo2/config/persistent_config.h>
#include <tetengo2/config/temporary_config.h>
#include <tetengo2/iterator/observable_forward_iterator.h>
#include <tetengo2/message/message_catalog.h>
#include <tetengo2/message/message_catalog_parser.h>
#include <tetengo2/message/messages.h>
#include <tetengo2/meta/assoc_list.h>
#include <tetengo2/stdalt.h>
#include <tetengo2/text.h>
#include <tetengo2/text/encoder.h>
#include <tetengo2/text/character_iterator.h>
#include <tetengo2/text/encoding/ascii.h>
#include <tetengo2/text/encoding/cp932.h>
#include <tetengo2/text/encoding/encoding.h>
#include <tetengo2/text/encoding/locale.h>
#include <tetengo2/text/encoding/utf8.h>
#include <tetengo2/text/grammar/json.h>
#include <tetengo2/text/pull_parser.h>
#include <tetengo2/text/push_parser.h>
#include <tetengo2/type_list.h>


#endif
