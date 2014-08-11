# Automake Settings
# Copyright (C) 2007-2014 kaoru
# $Id$

pkg_headers = \
    concurrent/channel.h \
    concurrent/consumer.h \
    concurrent/producer.h \
    config/cached_config.h \
    config/config_base.h \
    config/config_list.h \
    config/persistent_config.h \
    config/temporary_config.h \
    message/messages.h \
    message/message_catalog.h \
    message/message_catalog_parser.h \
    meta/assoc_list.h \
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
    0namespace.h \
    concurrent/0namespace.h \
    config/0namespace.h \
    message/0namespace.h \
    meta/0namespace.h \
    text/0namespace.h \
    text/encoding/0namespace.h \
    text/grammar/0namespace.h

nobase_pkginclude_HEADERS = $(pkg_headers)
EXTRA_DIST = $(extra_headers)
