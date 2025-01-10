# Copyright 2023 Comcast Cable Communications Management, LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
# http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.3)

project(FireboltCoreSDKTests)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX "${SYSROOT_PATH}/usr" CACHE INTERNAL "" FORCE)
    set(CMAKE_PREFIX_PATH ${SYSROOT_PATH}/usr/lib/cmake CACHE INTERNAL "" FORCE)
endif()

list(APPEND CMAKE_MODULE_PATH
	"${SYSROOT_PATH}/usr/lib/cmake"
	"${SYSROOT_PATH}/tools/cmake")
message("FIREBOLT_PATH inside cmake " ${FIREBOLT_PATH})
if (FIREBOLT_PATH)
    set(CMAKE_FIREBOLT_PATH
        "${FIREBOLT_PATH}/usr/lib/cmake/Firebolt"
	"${FIREBOLT_PATH}/usr/lib/cmake/FireboltSDK")
    list(APPEND CMAKE_PREFIX_PATH ${CMAKE_FIREBOLT_PATH})
    list(APPEND CMAKE_MODULE_PATH ${CMAKE_FIREBOLT_PATH})
else ()
   set(FIREBOLT_PATH "${SYSROOT_PATH}" CACHE INTERNAL "" FORCE)
endif ()

find_package(WPEFramework CONFIG REQUIRED)
find_package(${NAMESPACE}Core CONFIG REQUIRED)

set(TESTAPP TestFireboltCore)

message("Setup ${TESTAPP}")

if (NOT ENABLE_INTERACTIVE_APP)
  add_executable(${TESTAPP} CoreSDKTest.cpp Main.cpp)
else ()
  add_executable(${TESTAPP} CoreSDKTest.cpp InteractiveApp.cpp)
  add_compile_definitions(INTERACTIVE_APP)
endif ()

target_link_libraries(${TESTAPP}
    PRIVATE
        ${NAMESPACE}Core::${NAMESPACE}Core
        ${FIREBOLT_NAMESPACE}SDK::${FIREBOLT_NAMESPACE}SDK
        nlohmann_json_schema_validator
        gtest_main
)

target_include_directories(${TESTAPP}
    PRIVATE
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
)

if (POLYMORPHICS_REDUCER_METHODS)
    target_compile_definitions(${TESTAPP}
        PUBLIC
            POLYMORPHICS_REDUCER_METHODS=1)
endif()

set_target_properties(${TESTAPP} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
)

add_custom_command(
    TARGET ${TESTAPP}
    POST_BUILD
    COMMENT "=================== Installing TestApp ======================"
    COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
        COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_BINARY_DIR}/${TESTAPP} ${CMAKE_BINARY_DIR}/${FIREBOLT_NAMESPACE}/usr/bin
)

if(ENABLE_UNIT_TESTS)
    set(UNIT_TESTS_APP FireboltCoreUnitTests)

    message("Setup ${UNIT_TESTS_APP}")

    file(GLOB UNIT_TESTS "unit/*")

    add_executable(${UNIT_TESTS_APP} 
        CoreSDKTest.cpp
        Unit.cpp
        ${UNIT_TESTS}
    )
    
    link_directories(${CMAKE_SOURCE_DIR}/../../Thunder/install/usr/lib/)
    target_link_libraries(${UNIT_TESTS_APP}
        PRIVATE
            ${NAMESPACE}Core::${NAMESPACE}Core
            ${FIREBOLT_NAMESPACE}SDK::${FIREBOLT_NAMESPACE}SDK
            nlohmann_json_schema_validator
            gtest_main
    )

    target_include_directories(${UNIT_TESTS_APP}
        PRIVATE
            $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include/>
    )

    set_target_properties(${UNIT_TESTS_APP} PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
    )

    include(GoogleTest)
    gtest_discover_tests(${UNIT_TESTS_APP})
endif()

if(ENABLE_COVERAGE)
    include(${CMAKE_SOURCE_DIR}/cmake/CodeCoverage.cmake)
    
    set(COVERAGE_MAIN "coverage")
    set(COVERAGE_EXCLUDES
        "${CMAKE_SOURCE_DIR}/build/*"
        "${CMAKE_SOURCE_DIR}/cmake/*"
        "${CMAKE_SOURCE_DIR}/include/*"
        "${CMAKE_SOURCE_DIR}/test/*"
        "/usr/include/*")

    set(COVERAGE_EXTRA_FLAGS)
    set(COVERAGE_DEPENDENCIES ${UNIT_TESTS_APP})
    
    setup_target_for_coverage_gcovr_html(
        NAME ${COVERAGE_MAIN}
        BASE_DIRECTORY ${CMAKE_SOURCE_DIR}
        EXECUTABLE ctest
        EXECUTABLE_ARGS "--test-dir ../build/ --output-on-failure"
        DEPENDENCIES ${COVERAGE_DEPENDENCIES}
    )

endif()
