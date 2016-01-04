# Automake Settings
# Copyright (C) 2007-2016 kaoru
# $Id$

pkg_headers = \
    concurrent/channel.h \
    concurrent/consumer.h \
    concurrent/producer.h \
    concurrent/progressive_future.h \
    concurrent/progressive_promise.h \
    config/cached_config.h \
    config/config_base.h \
    config/config_list.h \
    config/persistent_config.h \
    config/temporary_config.h \
    message/messages.h \
    message/message_catalog.h \
    message/message_catalog_parser.h \
    meta/assoc_list.h \
    observable_forward_iterator.h \
    stdalt.h \
    text.h \
    text/encoder.h \
    text/encoding/encoding.h \
    text/encoding/ascii.h \
    text/encoding/cp932.h \
    text/encoding/locale.h \
    text/encoding/utf8.h \
    text/grammar/json.h \
    text/pull_parser.h \
    text/push_parser.h

extra_headers = \
    0namespace.dox \
    concurrent/0namespace.dox \
    config/0namespace.dox \
    message/0namespace.dox \
    meta/0namespace.dox \
    text/0namespace.dox \
    text/encoding/0namespace.dox \
    text/grammar/0namespace.dox

nobase_pkginclude_HEADERS = $(pkg_headers)
EXTRA_DIST = $(extra_headers)
