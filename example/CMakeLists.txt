# (c) 1997-2016 SAGEMCOM, SAS.  All content herein is protected by
# copyright and other applicable intellectual property laws and
# may not be copied without the express permission of Sagemcom, SAS.,
# which reserves all rights.  Reuse of any of this content for any
# purpose without the permission of Sagemcom, SAS. is strictly
# prohibited.

cmake_minimum_required(VERSION 3.10.2)

include_directories(${PROJECT_SOURCE_DIR}/doip/include)
#~ # source file liste
set(SAMPLE_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/example.c
    )

add_executable(example ${SAMPLE_SRCS} ${LIB_HEADERS})
target_link_libraries(example doip)
