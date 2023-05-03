#######################################################################
# Setup
#######################################################################

enable_testing()

#######################################################################
# Python unit testing
#######################################################################

message( STATUS "Adding scion Python unit testing" )

add_test( NAME scion.python.interpolation.histogram COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/interpolation/Test_scion_interpolation_histogram.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.interpolation.histogram PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.interpolation.linlin COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/interpolation/Test_scion_interpolation_linlin.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.interpolation.linlin PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.interpolation.linlog COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/interpolation/Test_scion_interpolation_linlog.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.interpolation.linlog PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.interpolation.loglin COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/interpolation/Test_scion_interpolation_loglin.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.interpolation.loglin PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.interpolation.loglog COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/interpolation/Test_scion_interpolation_loglog.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.interpolation.loglog PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})

add_test( NAME scion.python.linearisation.MidpointSplit COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/linearisation/Test_scion_linearisation_MidpointSplit.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.linearisation.MidpointSplit PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.linearisation.ToleranceConvergence COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/linearisation/Test_scion_linearisation_ToleranceConvergence.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.linearisation.ToleranceConvergence PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.linearisation.Lineariser COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/linearisation/Test_scion_linearisation_Lineariser.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.linearisation.Lineariser PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})

add_test( NAME scion.python.math.compare COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_compare.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.compare PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.math.newton COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_newton.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.newton PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})

add_test( NAME scion.python.math.clenshaw COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_clenshaw.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.clenshaw PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.math.horner COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_horner.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.horner PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})

add_test( NAME scion.python.math.legendre COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_legendre.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.legendre PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})

add_test( NAME scion.python.math.IntervalDomain COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_IntervalDomain.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.IntervalDomain PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.math.OpenDomain COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_OpenDomain.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.OpenDomain PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})

add_test( NAME scion.python.math.LinearLinearTable COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_LinearLinearTable.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.LinearLinearTable PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.math.LinearLogTable COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_LinearLogTable.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.LinearLogTable PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.math.LogLinearTable COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_LogLinearTable.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.LogLinearTable PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.math.LogLogTable COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_LogLogTable.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.LogLogTable PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.math.ChebyshevSeries COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_ChebyshevSeries.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.ChebyshevSeries PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.math.LegendreSeries COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_LegendreSeries.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.LegendreSeries PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
add_test( NAME scion.python.math.PolynomialSeries COMMAND ${PYTHON_EXECUTABLE} -m unittest -v test/math/Test_scion_math_PolynomialSeries.py WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}/python )
set_tests_properties( scion.python.math.PolynomialSeries PROPERTIES ENVIRONMENT PYTHONPATH=${SCION_PYTHONPATH}:$ENV{PYTHONPATH})
