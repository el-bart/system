# features dirs (will be expanded later on)
THIS_SRC_FEATURES_DIR=$(THIS_SRC_BASE_DIR)/features
THIS_SRC_FEATURES_DEPS_DIR=$(THIS_SRC_FEATURES_DIR)/deps
THIS_SRC_FEATURES_MODES_DIR=$(THIS_SRC_FEATURES_DIR)/modes
THIS_SRC_FEATURES_SPLIT_DIR=$(THIS_SRC_FEATURES_MODES_DIR)/features
THIS_SRC_FEATURES_TESTDATA_DIR=$(THIS_SRC_FEATURES_DIR)/testdata
SRC_FEATURES_DEPS_FULL_SURFIX:=features/deps
export THIS_SRC_BASE_DIR \
       THIS_SRC_FEATURES_DEPS_DIR \
       THIS_SRC_FEATURES_MODES_DIR \
       THIS_SRC_FEATURES_SPLIT_DIR \
	   THIS_SRC_FEATURES_TESTDATA_DIR \
       SRC_FEATURES_DEPS_FULL_SURFIX
