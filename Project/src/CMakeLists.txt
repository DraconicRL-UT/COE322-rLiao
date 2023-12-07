cmake_minimum_required( VERSION 3.12 )
project( Neighprgm VERSION 1.0 )
project (SIRprgm VERSION 1.0)


add_executable( Neighprgm mainNeigh.cc contagion.cc contagion.h ${EXTRA_SOURCES} )
target_compile_features( Neighprgm PRIVATE cxx_std_17 )

add_executable( SIRprgm mainSIR.cc contagion.cc contagion.h ${EXTRA_SOURCES} )
target_compile_features( SIRprgm PRIVATE cxx_std_17 )

##
## Extra packages: fmtlib
##

install( TARGETS Neighprgm DESTINATION . )
install( TARGETS SIRprgm DESTINATION . )

