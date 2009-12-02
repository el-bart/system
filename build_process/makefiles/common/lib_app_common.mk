# TODO: TEST_LINK_LIBS looks like it should be removed (not used)

.PHONY: test
test:: copy_testdata
test:: $(TEST_PROGRAM_NAME)

.PHONY: mtest
mtest:: copy_testdata
mtest:: $(CXXBIN_MTEST) $(CBIN_MTEST) \
		$(CXXOBJS_MTEST) $(COBJS_MTEST)

.PHONY: doc
doc:: html/index.html

html/index.html:: Doxyfile $(ALL_MODE_SOURCES)
	@echo "DOXY  makedoc"
	$(DOXYGEN)

Doxyfile:
	@echo "DOXY  $@"
	$(DOXYGEN) -g "$@.def" > /dev/null
	sed -e "s:^\(INPUT \+=\).*:\1 $(THIS_SRC_BASE_DIR):" \
		-e "s:^\(RECURSIVE \+=\).*:\1 YES:" \
		-e "s:^\(EXCLUDE_PATTERNS \+=\).*:\1 *.mt.?pp *.t.?pp:" \
		-e "s:^\(SHOW_DIRECTORIES \+=\).*:\1 YES:" \
		-e "s:^\(QUIET \+=\).*:\1 YES:" \
		-e "s:^\(WARN_NO_PARAMDOC \+=\).*:\1 YES:" \
		-e "s:^\(INCLUDE_PATH \+=\).*:\1 $(THIS_SRC_BASE_DIR) $(GEN_INCLUDES_DIR):" \
		-e "s:^\(HAVE_DOT \+=\).*:\1 YES:" \
		-e "s:^\(UML_LOOK \+=\).*:\1 YES:" \
		-e "s:^\(GENERATE_LATEX \+=\).*:\1 NO:" \
		"$@.def" > "$@" || ( rm -f "$@" ; false )

LIBS_GEN_DEPS:=$(wildcard $(DEP_LIBS_WC)) $(GEN_LIBS_DIR)/$(LIBRARY_NAME)

%.mt: %.mt.o $(LIBS_GEN_DEPS)
	@echo "LD    $@"
	$(LD) $(LDFLAGS) -o $@ $^ $(TEST_LINK_LIBS) \
		-l$(COMPONENT_NAME) $(LINK_LIBS)

$(CBIN_MTEST)::
	@echo "mtest taget is not implemented for C sources"
	@false


.PHONY: copy_testdata
copy_testdata:
	cp -purv "$(THIS_SRC_FEATURES_TESTDATA_DIR)" . 2>/dev/null | \
	  sed 's:^.* -> ...\(.*\).$$:COPY  \1:'

$(TEST_PROGRAM_NAME):: $(CXXOBJS_TEST) $(COBJS_TEST) $(LIBS_GEN_DEPS)
	@echo "LD    $@"
	$(LD) $(LDFLAGS) -o $@ $^ $(TEST_LINK_LIBS) \
		-l$(COMPONENT_NAME) $(LINK_LIBS) $(END_LINK_LIBS)

LIBRARY_OBJ_DEPS:=$(CXXOBJS_NOMAIN) $(COBJS_NOMAIN)
LIBRARY_DEPS    :=$(LIBRARY_OBJ_DEPS) $(GEN_LIBS_DIR)/$(LIBRARY_NAME) $(LIBS_GEN_DEPS)
ifeq (static,$(LIBRARY_TYPE))
$(LIBRARY_NAME):: $(LIBRARY_DEPS)
	@echo "AR    $@"
	rm -f $@
	$(AR) -r $@ $(LIBRARY_OBJ_DEPS)
endif
ifeq (dynamic,$(LIBRARY_TYPE))
CXXFLAGS+=-fPIC
LDFLAGS +=-fPIC
$(LIBRARY_NAME):: LDFLAGS+=-shared
$(LIBRARY_NAME):: $(LIBRARY_DEPS)
	@echo "LD    $@"
	$(LD) $(LDFLAGS) -o $@ $(LIBRARY_OBJ_DEPS) $(LINK_LIBS) $(END_LINK_LIBS)
endif

# ensure there is proper link in gen
$(GEN_LIBS_DIR)/$(LIBRARY_NAME):
	ln -sf "$(CURDIR)/$(LIBRARY_NAME)" "$(GEN_LIBS_DIR)"

