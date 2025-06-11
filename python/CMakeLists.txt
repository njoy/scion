if(scion.python)

    find_package( Python3 REQUIRED )
    pybind11_add_module( scion.python
        ${CMAKE_CURRENT_SOURCE_DIR}/src/scion.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/interpolation.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/interpolation/interpolation.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/interpolation/InterpolationType.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/integration.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/integration/integration.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/integration/GaussLegendre.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/integration/GaussLobatto.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linearisation.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linearisation/MidpointSplit.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linearisation/ToleranceConvergence.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/linearisation/Lineariser.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/clenshaw.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/compare.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/horner.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/newton.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/chebyshev.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/legendre.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/IntervalDomain.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/OpenDomain.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/LinearLinearTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/HistogramTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/LogLogTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/LogLinearTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/LinearLogTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/InterpolationTable.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/ChebyshevSeries.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/ChebyshevApproximation.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/LegendreSeries.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/PolynomialSeries.python.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/math/AnalyticalIntegrator.python.cpp
    )

    target_link_libraries(scion.python PRIVATE njoy::scion)
    target_include_directories( scion.python PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src )
    set_target_properties( scion.python PROPERTIES CXX_VISIBILITY_PRESET hidden)
    set_target_properties( scion.python PROPERTIES OUTPUT_NAME scion )
    set_target_properties( scion.python PROPERTIES LIBRARY_OUTPUT_DIRECTORY  ${CMAKE_CURRENT_BINARY_DIR})
    set_target_properties( scion.python PROPERTIES COMPILE_DEFINITIONS "PYBIND11" )
    set_target_properties( scion.python PROPERTIES POSITION_INDEPENDENT_CODE ON )
    # add all .so's that are installed with mcatk to the installed library rpath
    set_target_properties( scion.python PROPERTIES INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}")
    # add all .so's that are linked to at build time to the installed library rpath
    set_target_properties( scion.python PROPERTIES INSTALL_RPATH_USE_LINK_PATH ON)

    set(PyVersion "${Python3_VERSION_MAJOR}.${Python3_VERSION_MINOR}")
    set( py_library_install_prefix ${CMAKE_INSTALL_PREFIX}/${CMAKE_INSTALL_LIBDIR}/python${PyVersion}/site-packages )

    if (scion.installation)
        install( TARGETS scion.python LIBRARY DESTINATION ${py_library_install_prefix} )
    endif()

    message( STATUS "Building scion's python API" )

    # Append potential installation and build paths for tools python module
    set(scion_PYTHONPATH "$<TARGET_FILE_DIR:scion.python>")

    # Windows and unix have different delimiter for paths
    if (WIN32)
	    set(PATH_DELIM "\;")
    else()
	    set(PATH_DELIM ":")
    endif()

    if( scion.tests )
        include( ${PROJECT_SOURCE_DIR}/cmake/unit_testing_python.cmake )
    endif()

    # generate python stubs if possible
    find_program(pybind11stubgen_exe pybind11-stubgen)

    set(PYTHONPATH_PARTS ${scion_PYTHONPATH} $ENV{PYTHONPATH})
    string( JOIN "${PATH_DELIM}" PYTHONPATH_VALUE ${PYTHONPATH_PARTS})

    set(stubdir "${CMAKE_CURRENT_SOURCE_DIR}/stubs/scion")
    if (pybind11stubgen_exe)
        # the following command executes the pybind11-stubgen executable found via find_program
        # and puts its terminal output into pybind11-stubgen.log in the build tree.
        # The stubs get generated in the source tree so users can determine what changes if any were made to the stubs.
        # The stubs are then copied into the build tree so developers get the stubs when using the build tree's python bindings.
        # If the stubs fail to generate then this command exits gracefully and allows the build to continue.
        add_custom_command(
            TARGET scion.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${PYTHONPATH_VALUE}" ${pybind11stubgen_exe} scion -o ${CMAKE_CURRENT_SOURCE_DIR}/stubs &> ${CMAKE_CURRENT_BINARY_DIR}/pybind11-stubgen.log || true
            COMMAND ${CMAKE_COMMAND} -E rename ${stubdir}/__init__.pyi ${stubdir}/scion.pyi &> /dev/null || true
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
            COMMENT "Building scion's python stub files via pybind11-stubgen. See pybind11-stubgen.log for details."
            VERBATIM
        )

    else()
        # copy stub files to build tree even if pybind11stubgen isn't available.
        add_custom_command(
            TARGET scion.python POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory ${stubdir}/ ${CMAKE_CURRENT_BINARY_DIR}
        )
    endif()

    # install stubs so the installed binaries play nice with IDEs
    if (scion.installation)
        install( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/stubs/scion/ DESTINATION ${py_library_install_prefix} )
    endif()

endif() # end scion.python check
