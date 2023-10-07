cmake_minimum_required( VERSION 3.12 )
project( hw7prgm VERSION 1.0 )

message( "Using sources: fmtbasic.cpp ${EXTRA_SOURCES}" )
add_executable( hw7prgm hw7.cpp ${EXTRA_SOURCES} )
target_compile_features( hw7prgm PRIVATE cxx_std_17 )

##
## Extra packages: fmtlib
##
find_package( PkgConfig REQUIRED )
pkg_check_modules( FMTLIB REQUIRED fmt )
message( "Include dirs:  ${FMTLIB_INCLUDE_DIRS}" )
message( "Lib dirs and libs:  ${FMTLIB_LIBRARY_DIRS} ${FMTLIB_LIBRARIES}" )
target_include_directories(
	hw7prgm PUBLIC ${FMTLIB_INCLUDE_DIRS}
	)
target_link_directories(
	hw7prgm PUBLIC ${FMTLIB_LIBRARY_DIRS}
	)
target_link_libraries(
	hw7prgm PUBLIC ${FMTLIB_LIBRARIES}
	)
set_target_properties(
	hw7prgm PROPERTIES
	BUILD_RPATH   "${FMTLIB_LIBRARY_DIRS}"
	INSTALL_RPATH "${FMTLIB_LIBRARY_DIRS}"
    )

install( TARGETS hw7prgm DESTINATION . )

