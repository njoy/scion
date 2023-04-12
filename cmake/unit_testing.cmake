#######################################################################
# Setup
#######################################################################

message( STATUS "Adding codex unit testing" )
enable_testing()


#######################################################################
# Unit testing directories
#######################################################################

add_subdirectory( src/scion/math/clenshaw/test )
add_subdirectory( src/scion/math/horner/test )
