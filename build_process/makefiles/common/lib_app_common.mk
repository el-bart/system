.PHONY: test
test:: copy_testdata
test:: $(TEST_PROGRAM_NAME)

.PHONY: mtest
mtest:: copy_testdata
mtest:: $(CXXBIN_MTEST) $(CBIN_MTEST) \
		$(CXXOBJS_MTEST) $(COBJS_MTEST)

%.mt: %.mt.o
	@echo "LD    $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LINK_LIBS) \
		-l$(COMPONENT_NAME) $(LINK_LIBS)

$(CBIN_MTEST)::
	@echo "mtest taget is not implemented for C sources"
	@false


.PHONY: copy_testdata
copy_testdata: testdata

testdata:
	if test -d "$(THIS_SRC_BASE_DIR)/features/testdata" ; \
	then \
	  echo "copying test data" ; \
	  cp -pur "$(THIS_SRC_BASE_DIR)/features/testdata" . ; \
	fi


$(TEST_PROGRAM_NAME):: $(CXXOBJS_TEST) $(COBJS_TEST)
	@echo "LD    $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LINK_LIBS) \
		-l$(COMPONENT_NAME) $(LINK_LIBS)

LIBRARY_OBJ_DEPS:=$(CXXOBJS_NOMAIN) $(COBJS_NOMAIN)
LIBRARY_DEPS    :=$(LIBRARY_OBJ_DEPS) $(GEN_LIBS_DIR)/$(LIBRARY_NAME)
ifeq (static,$(LIBRARY_TYPE))
$(LIBRARY_NAME):: $(LIBRARY_DEPS)
	@echo "AR    $@"
	$(AR) -r $@ $(LIBRARY_OBJ_DEPS)
endif
ifeq (dynamic,$(LIBRARY_TYPE))
CXXFLAGS+=-fPIC
LDFLAGS +=-shared -fPIC
$(LIBRARY_NAME):: $(LIBRARY_DEPS)
	@echo "LD    $@"
	$(CXX) $(CXXFLAGS) $(LDFLAGS) -o $@ $(LIBRARY_OBJ_DEPS) $(LINK_LIBS)
endif

# ensure there is proper link in gen
$(GEN_LIBS_DIR)/$(LIBRARY_NAME):
	ln -s "$(CURDIR)/$(LIBRARY_NAME)" "$(GEN_LIBS_DIR)"

