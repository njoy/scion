#######################################################################
# Setup
#######################################################################

enable_testing()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding scion Python unit testing" )

add_test( NAME scion.python.math.horner COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_horner.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.horner PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})

add_test( NAME scion.python.math.legendre COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_legendre.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.legendre PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})

add_test( NAME scion.python.math.IntervalDomain COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_IntervalDomain.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.IntervalDomain PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
