# note: public_headers are NOT necessary for applications
.PHONY: all
all:: $(APPLICATION_NAME)

include $(MAKEFILES_COMMON_BASE_DIR)/lib_app_common.mk

MAIN_OBJS:=$(COBJS_MAIN) $(CXXOBJS_MAIN)
$(APPLICATION_NAME):: $(LIBRARY_NAME) $(MAIN_OBJS)
	@echo "LD    $@"
	$(LD) $(LDFLAGS) -o $@ $(MAIN_OBJS) -l$(COMPONENT_NAME) $(LINK_LIBS) $(END_LINK_LIBS)
	if test -n "$(STRIP_BINARY)" ; \
	then \
	  echo "STRIP $@" ; \
	  $(STRIP) $@ || rm -f "$@" ; \
	fi

