# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

headers =

extra_headers =

sources = \
    tetengo2.detail.base.alert.cpp \
    tetengo2.detail.base.common_dialog.cpp \
    tetengo2.detail.base.config.cpp \
    tetengo2.detail.base.cursor.cpp \
    tetengo2.detail.base.drawing.cpp \
    tetengo2.detail.base.encoding.cpp \
    tetengo2.detail.base.gui_fixture.cpp \
    tetengo2.detail.base.gui_impl_set.cpp \
    tetengo2.detail.base.icon.cpp \
    tetengo2.detail.base.impl_set.cpp \
    tetengo2.detail.base.menu.cpp \
    tetengo2.detail.base.message_handler.cpp \
    tetengo2.detail.base.message_loop.cpp \
    tetengo2.detail.base.messages.cpp \
    tetengo2.detail.base.mouse_capture.cpp \
    tetengo2.detail.base.scroll.cpp \
    tetengo2.detail.base.shell.cpp \
    tetengo2.detail.base.system_color.cpp \
    tetengo2.detail.base.timer.cpp \
    tetengo2.detail.base.unit.cpp \
    tetengo2.detail.base.virtual_key.cpp \
    tetengo2.detail.base.widget.cpp \
    tetengo2.detail.stub.alert.cpp \
    tetengo2.detail.stub.common_dialog.cpp \
    tetengo2.detail.stub.cursor.cpp \
    tetengo2.detail.stub.drawing.cpp \
    tetengo2.detail.stub.gui_fixture.cpp \
    tetengo2.detail.stub.gui_impl_set.cpp \
    tetengo2.detail.stub.icon.cpp \
    tetengo2.detail.stub.impl_set.cpp \
    tetengo2.detail.stub.menu.cpp \
    tetengo2.detail.stub.message_handler.cpp \
    tetengo2.detail.stub.message_loop.cpp \
    tetengo2.detail.stub.mouse_capture.cpp \
    tetengo2.detail.stub.scroll.cpp \
    tetengo2.detail.stub.shell.cpp \
    tetengo2.detail.stub.system_color.cpp \
    tetengo2.detail.stub.timer.cpp \
    tetengo2.detail.stub.unit.cpp \
    tetengo2.detail.stub.virtual_key.cpp \
    tetengo2.detail.stub.widget.cpp \
    tetengo2.detail.unixos.config.cpp \
    tetengo2.detail.unixos.encoding.cpp \
    tetengo2.detail.unixos.gui_impl_set.cpp \
    tetengo2.detail.unixos.impl_set.cpp \
    tetengo2.detail.unixos.messages.cpp

extra_sources = \
    tetengo2.detail.windows.alert.cpp \
    tetengo2.detail.windows.com_ptr.cpp \
    tetengo2.detail.windows.common_dialog.cpp \
    tetengo2.detail.windows.config.cpp \
    tetengo2.detail.windows.cursor.cpp \
    tetengo2.detail.windows.direct2d.drawing.cpp \
    tetengo2.detail.windows.direct2d.error_category.cpp \
    tetengo2.detail.windows.encoding.cpp \
    tetengo2.detail.windows.error_category.cpp \
    tetengo2.detail.windows.font.cpp \
    tetengo2.detail.windows.gdiplus.drawing.cpp \
    tetengo2.detail.windows.gdiplus.error_category.cpp \
    tetengo2.detail.windows.gdiplus.gui_fixture.cpp \
    tetengo2.detail.windows.gui_fixture.cpp \
    tetengo2.detail.windows.gui_impl_set.cpp \
    tetengo2.detail.windows.icon.cpp \
    tetengo2.detail.windows.impl_set.cpp \
    tetengo2.detail.windows.menu.cpp \
    tetengo2.detail.windows.message_handler.cpp \
    tetengo2.detail.windows.message_handler_detail.widget.cpp \
    tetengo2.detail.windows.message_handler_detail.abstra.cpp \
    tetengo2.detail.windows.message_handler_detail.button.cpp \
    tetengo2.detail.windows.message_handler_detail.contro.cpp \
    tetengo2.detail.windows.message_handler_detail.custom.cpp \
    tetengo2.detail.windows.message_handler_detail.dialog.cpp \
    tetengo2.detail.windows.message_handler_detail.dropdo.cpp \
    tetengo2.detail.windows.message_handler_detail.list_b.cpp \
    tetengo2.detail.windows.message_handler_detail.messag.cpp \
    tetengo2.detail.windows.message_handler_detail.pictur.cpp \
    tetengo2.detail.windows.message_handler_detail.text_b.cpp \
    tetengo2.detail.windows.message_loop.cpp \
    tetengo2.detail.windows.messages.cpp \
    tetengo2.detail.windows.mouse_capture.cpp \
    tetengo2.detail.windows.picture.cpp \
    tetengo2.detail.windows.scroll.cpp \
    tetengo2.detail.windows.shell.cpp \
    tetengo2.detail.windows.system_color.cpp \
    tetengo2.detail.windows.timer.cpp \
    tetengo2.detail.windows.unit.cpp \
    tetengo2.detail.windows.virtual_key.cpp \
    tetengo2.detail.windows.widget.cpp \
    tetengo2.detail.windows.windows_version.cpp

BUILT_SOURCES = $(PRECOMPILE_BUILT_SOURCES)

lib_LIBRARIES = libtetengo2_detail.a
EXTRA_DIST = $(extra_headers) $(extra_sources)

libtetengo2_detail_a_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include \
    -I$(top_srcdir)/tetengo2_gui/include
libtetengo2_detail_a_SOURCES = $(headers) $(sources)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)

lint-iwyu: $(addsuffix .iwyuout, $(headers) $(sources))

lint-iwyu-extra: $(addsuffix .iwyuout, $(extra_headers) $(extra_sources))

%.iwyuout: %
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(libtetengo2_detail_a_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
	mv $(addsuffix .tmp, $@) $@

format:
	$(top_srcdir)/tools/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(headers) $(sources) $(extra_headers) $(extra_sources)

clean-local:
	-rm -f *.iwyuout.tmp
	-rm -f *.iwyuout

$(top_builddir)/precompiled/precompiled.h.$(PRECOMPILE_EXT): $(top_srcdir)/precompiled/precompiled.h
	pushd $(top_builddir)/precompiled; \
	$(MAKE) all; \
	popd
