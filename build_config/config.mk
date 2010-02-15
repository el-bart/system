#
# project specific configuration file
# to be placed in main project directory
#

# set default mode
export MODE=default
# set default profile
export PROFILE=test
# default tool chain
export TC=local

ifeq ($(TC),intel)
TMP:=-wd279,383,444,854,981
else
TMP:=
endif
export USER_DBG_FLAGS:=$(TMP)
export USER_REL_FLAGS:=$(TMP)
export USER_PRF_FLAGS:=$(TMP)
TMP:=
