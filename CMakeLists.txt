cmake_minimum_required(VERSION 3.10.2)
project(Codage)
enable_testing()

#-------#
# Flags #
#-------#

SET(GCC_COVERAGE_COMPILE_FLAGS "-g")

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} ${GCC_COVERAGE_COMPILE_FLAGS}")

#---------#
# Headers #
#---------#

include_directories(include)

#-------------------#
# Librairie commune #
#-------------------#

file(GLOB COMMON_SOURCES "src/*.c")
add_library(common OBJECT ${COMMON_SOURCES})

#----------------------------#
# Source des cibles et tests #
#----------------------------#

file(GLOB TARGETS_SOURCES "src/targets/*.c")
file(GLOB TEST_SOURCES "src/tests/*.c")

#--------------------#
# Executables cibles #
#--------------------#

foreach( sourcefile ${TARGETS_SOURCES} )
	get_filename_component(name ${sourcefile} NAME_WE)
    add_executable( ${name} ${sourcefile} $<TARGET_OBJECTS:common>)
	target_link_libraries(${name} m)
endforeach( sourcefile ${TARGETS_SOURCES} )


#---------------------#
# Executables de test #
#---------------------#

foreach( testsourcefile ${TEST_SOURCES} )
	get_filename_component( testname ${testsourcefile} NAME_WE )
    add_executable( ${testname} ${testsourcefile} $<TARGET_OBJECTS:common>)
    set_target_properties( ${testname} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/tests" )
    add_test( ${testname} ${CMAKE_BINARY_DIR}/tests/${testname} )
	target_link_libraries(${testname} m)
endforeach( testsourcefile ${TEST_SOURCES} )
