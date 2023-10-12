cmake_minimum_required( VERSION 3.14 )
include( FetchContent )

#######################################################################
# Declare project dependencies
#######################################################################

FetchContent_Declare( eigen
    GIT_REPOSITORY  https://gitlab.com/libeigen/eigen.git
    GIT_TAG         d0bfdc1658ca0b4c659fd3702c351d2c2cdc876c # 3.4.1 branch on July 26, 2023
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( spdlog
    GIT_REPOSITORY  https://github.com/gabime/spdlog
    GIT_TAG         v1.11.0
    GIT_SHALLOW     TRUE
    )
set( SPDLOG_BUILD_PIC CACHE INTERNAL BOOL ON )

FetchContent_Declare( Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2
    GIT_TAG         v3.3.2
    GIT_SHALLOW     TRUE
    )

FetchContent_Declare( pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11
    GIT_TAG         v2.10.4
    GIT_SHALLOW     TRUE
    )

#######################################################################
# Load dependencies
#######################################################################

FetchContent_MakeAvailable(
    eigen
    spdlog
    )
