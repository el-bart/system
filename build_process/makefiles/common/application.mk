.PHONY: all
all:: $(APPLICATION_NAME)

.PHONY: test
test:: copy_testdata
test:: $(TEST_PROGRAM_NAME)

.PHONY: mtest
mtest:: copy_testdata
mtest:: $(CXXBIN_MTEST) $(CBIN_MTEST)

$(TEST_PROGRAM_NAME):: $(CXXOBJS_TEST) $(COBJS_TEST) \
					  $(CXXOBJS_NOMAIN) $(COBJS_NOMAIN)
	@echo "LD    $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LINK_LIBS)
	test -n "$(STRIP_BINARY)" && echo "STRIP $@" && $(STRIP) $@ ; true

$(APPLICATION_NAME):: $(CXXOBJS) $(COBJS)
	@echo "LD    $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LINK_LIBS)
	test -n "$(STRIP_BINARY)" && echo "STRIP $@" && $(STRIP) $@ ; true


%.mt: %.mt.o $(CXXOBJS_NOMAIN) $(COBJS_NOMAIN)
	@echo "LD    $@"
	$(CXX) $(CXXFLAGS) -o $@ $^ $(TEST_LINK_LIBS) $(LINK_LIBS)

$(CBIN_MTEST)::
	@echo "mtest taget is not implemented for C sources"
	@false

.PHONY: copy_testdata
copy_testdata:
	#@echo "copying test data"
	cp -pur "$(THIS_SRC_BASE_DIR)/features/testdata" .

