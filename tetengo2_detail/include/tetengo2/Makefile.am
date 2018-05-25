# Automake Settings
# Copyright (C) 2007-2018 kaoru
# $Id$

pkg_headers = \
    detail/base/alert.h \
    detail/base/config.h \
    detail/base/cursor.h \
    detail/base/encoding.h \
    detail/base/gui_fixture.h \
    detail/base/icon.h \
    detail/base/impl_set.h \
    detail/base/messages.h \
    detail/base/shell.h \
    detail/base/unit.h \
    detail/stub/alert.h \
    detail/stub/common_dialog.h \
    detail/stub/cursor.h \
    detail/stub/drawing.h \
    detail/stub/gui_fixture.h \
    detail/stub/icon.h \
    detail/stub/impl_set.h \
    detail/stub/menu.h \
    detail/stub/message_handler.h \
    detail/stub/message_loop.h \
    detail/stub/mouse_capture.h \
    detail/stub/scroll.h \
    detail/stub/shell.h \
    detail/stub/system_color.h \
    detail/stub/timer.h \
    detail/stub/unit.h \
    detail/stub/virtual_key.h \
    detail/stub/widget.h \
    detail/unixos/config.h \
    detail/unixos/encoding.h \
    detail/unixos/impl_set.h \
    detail/unixos/messages.h

extra_headers = \
    detail/base/0namespace.dox \
    detail/stub/0namespace.dox \
    detail/unixos/0namespace.dox \
    detail/windows/0namespace.dox \
    detail/windows/alert.h \
    detail/windows/com_ptr.h \
    detail/windows/common_dialog.h \
    detail/windows/config.h \
    detail/windows/cursor.h \
    detail/windows/direct2d/0namespace.dox \
    detail/windows/direct2d/drawing.h \
    detail/windows/direct2d/error_category.h \
    detail/windows/encoding.h \
    detail/windows/error_category.h \
    detail/windows/font.h \
    detail/windows/gdiplus/0namespace.dox \
    detail/windows/gdiplus/drawing.h \
    detail/windows/gdiplus/error_category.h \
    detail/windows/gdiplus/gui_fixture.h \
    detail/windows/gui_fixture.h \
    detail/windows/icon.h \
    detail/windows/impl_set.h \
    detail/windows/menu.h \
    detail/windows/message_handler.h \
    detail/windows/message_handler_detail/0namespace.dox \
    detail/windows/message_handler_detail/abstra.h \
    detail/windows/message_handler_detail/button.h \
    detail/windows/message_handler_detail/contro.h \
    detail/windows/message_handler_detail/custom.h \
    detail/windows/message_handler_detail/dialog.h \
    detail/windows/message_handler_detail/list_b.h \
    detail/windows/message_handler_detail/messag.h \
    detail/windows/message_handler_detail/pictur.h \
    detail/windows/message_handler_detail/text_b.h \
    detail/windows/message_handler_detail/widget.h \
    detail/windows/messages.h \
    detail/windows/mouse_capture.h \
    detail/windows/picture.h \
    detail/windows/scroll.h \
    detail/windows/shell.h \
    detail/windows/system_color.h \
    detail/windows/timer.h \
    detail/windows/unit.h \
    detail/windows/virtual_key.h \
    detail/windows/widget.h \
    detail/windows/windows_version.h

nobase_pkginclude_HEADERS = $(pkg_headers)
EXTRA_DIST = $(extra_headers)

IWYU_OPTS += -Xiwyu --mapping_file=$(top_srcdir)/$(IWYU_IMP_PATH)
iwyu_CPPFLAGS = \
    -I$(top_srcdir)/tetengo2/include \
    -I$(top_srcdir)/tetengo2_detail/include \
    -I$(top_srcdir)/tetengo2_gui/include

lint-iwyu: $(subst config.h,config_.h, $(addsuffix .iwyuout, $(pkg_headers)))

lint-iwyu-extra: $(subst config.h,config_.h, $(addsuffix .iwyuout, $(extra_headers)))

%.iwyuout: %
	mkdir -p $(dir $@)
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
	mv $(addsuffix .tmp, $@) $@

%_.h.iwyuout: %.h
	mkdir -p $(dir $@)
	$(IWYU) $(IWYU_OPTS) $(CPPFLAGS) $(iwyu_CPPFLAGS) $(CXXFLAGS) $< 2> $(addsuffix .tmp, $@) || true
	mv $(addsuffix .tmp, $@) $@

format:
	$(top_srcdir)/tools/call_clang-format.sh $(UNIX2DOS) $(CLANGFORMAT) $(srcdir) $(pkg_headers) $(extra_headers)

clean-local:
	-find -name "*.iwyuout.tmp" | xargs rm -f
	-find -name "*.iwyuout" | xargs rm -f
