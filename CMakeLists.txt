# Copyright 2017, alex at staticlibs.net
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

cmake_minimum_required ( VERSION 2.8.12 )

# project
project ( external_asio CXX C )
set ( ${PROJECT_NAME}_STATICLIB_VERSION 1.10.8-3 )
set ( ${PROJECT_NAME}_DESCRIPTION "Asio C++ library wrapper for Staticlibs" )
set ( ${PROJECT_NAME}_URL https://github.com/staticlibs/external_asio )

# standalone build
if ( NOT DEFINED CMAKE_LIBRARY_OUTPUT_DIRECTORY )
    set ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR} )
endif ( )

if ( NOT DEFINED ${PROJECT_NAME}_LOOKASIDE_DIR )
    set ( asio_LOOKASIDE_DIR ${CMAKE_CURRENT_LIST_DIR}/../lookaside_asio CACHE INTERNAL "" )
endif ( )

add_custom_target ( ${PROJECT_NAME} )

# pkg-config
set ( ${PROJECT_NAME}_MODULE asio )
set ( ${PROJECT_NAME}_PC_CFLAGS "-I${asio_LOOKASIDE_DIR}/asio/include -DASIO_STANDALONE -DASIO_HAS_STD_CHRONO" )
if ( CMAKE_SYSTEM_NAME STREQUAL "Linux" )
    set ( ${PROJECT_NAME}_PC_LIBS "${${PROJECT_NAME}_PC_LIBS} -lpthread" )
endif ( )
if ( ${CMAKE_CXX_COMPILER_ID} MATCHES "Clang" )
    set ( ${PROJECT_NAME}_PC_CFLAGS "${${PROJECT_NAME}_PC_CFLAGS} -Wno-deprecated-declarations" )
endif ( )
configure_file ( ${CMAKE_CURRENT_LIST_DIR}/resources/pkg-config.in 
        ${CMAKE_LIBRARY_OUTPUT_DIRECTORY}/pkgconfig/asio.pc )
