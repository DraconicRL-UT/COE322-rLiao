cmake_minimum_required( VERSION 3.12 )
project( myprgm VERSION 1.0 )

add_executable( myprgm container.cpp ${EXTRA_SOURCES} )
target_compile_features( myprgm PRIVATE cxx_std_17 )


install( TARGETS myprgm DESTINATION . )

