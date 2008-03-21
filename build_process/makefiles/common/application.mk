.PHONY: all
all:: $(APPLICATION_NAME)

include $(MAKEFILES_COMMON_BASE_DIR)/lib_app_common.mk

MAIN_OBJS:=$(COBJS_MAIN) $(CXXOBJS_MAIN)
$(APPLICATION_NAME):: $(LIBRARY_NAME) $(MAIN_OBJS)
	@echo "LD    $@"
	$(CXX) $(CXXFLAGS) -o $@ -l$(COMPONENT_NAME) $(MAIN_OBJS) $(LINK_LIBS)
	if test -n "$(STRIP_BINARY)" ; \
	then \
	  echo "STRIP $@" ; \
	  $(STRIP) $@ || rm -f "$@" ; \
	fi

