# (c) 1997-2016 SAGEMCOM, SAS.  All content herein is protected by
# copyright and other applicable intellectual property laws and
# may not be copied without the express permission of Sagemcom, SAS.,
# which reserves all rights.  Reuse of any of this content for any
# purpose without the permission of Sagemcom, SAS. is strictly
# prohibited.

cmake_minimum_required(VERSION 3.10.2)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/SoAD/include)
# source file liste
set(LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Alive_Check.c  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Diagnostic_message.c  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/doip.c  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/DoIP_entity_status.c  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Generic_DoIP_header.c  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Power_mode_information.c  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Routing_activation.c  
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Vehicle_Identification.c
    )
# headers file liste

set(LIB_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/doip_types.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/doip.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Alive_Check.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Diagnostic_message.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/include/DoIP_entity_status.h 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Generic_DoIP_header.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Power_mode_information.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Routing_activation.h  
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Vehicle_Identification.h
    ${PROJECT_SOURCE_DIR}/SoAD/include/soad_types.h
    )

add_library(doip SHARED ${LIB_SRCS} ${LIB_HEADERS})
target_link_libraries(doip SoAD)
install (TARGETS doip DESTINATION lib)
install (FILES ${HEADER_FILES} DESTINATION include)
