cmake_minimum_required( VERSION 3.12 )
project( hw9prgm VERSION 1.0 )

add_executable( hw9prgm linklistMain.cpp linklist.cpp linklist.hpp ${EXTRA_SOURCES} )
target_compile_features( hw9prgm PRIVATE cxx_std_17 )

##
## Extra packages: fmtlib
##


install( TARGETS hw9prgm DESTINATION . )

