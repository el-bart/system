# is any profile set?
ifneq ($(PROFILE),test)
ifneq ($(PROFILE),mtest)
ifneq ($(PROFILE),debug)
ifneq ($(PROFILE),release)
ifneq ($(PROFILE),profile)
ifneq ($(PROFILE),doc)
$(error PROFILE not set (aviable are: debug, release, test, mtest, profile, doc))
endif # PROFILE=doc
endif # PROFILE=profile
endif # PROFILE=release
endif # PROFILE=debug
endif # PROFILE=mtest
endif # PROFILE=test
