# (c) 1997-2016 SAGEMCOM, SAS.  All content herein is protected by
# copyright and other applicable intellectual property laws and
# may not be copied without the express permission of Sagemcom, SAS.,
# which reserves all rights.  Reuse of any of this content for any
# purpose without the permission of Sagemcom, SAS. is strictly
# prohibited.

cmake_minimum_required(VERSION 3.10.2)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/SoAD/include)
include_directories(${PROJECT_SOURCE_DIR}/doip/include)
# source file liste
set(LIB_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Diagnostic_srv.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Diagnostic_Session_Control.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/ECU_Reset.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Clear_Diagnostic_Information.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Security_Access.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Communication_Control.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Authentication.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Tester_Present.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Access_Timing_Parameters.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Secured_Data_Transmission.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Control_DTC_Settings.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Response_On_Event.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Link_Control.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Read_Data_By_Identifier.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Read_Memory_By_Address.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Read_Scaling_Data_By_Identifier.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Read_Data_By_Identifier_Periodic.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Dynamically_Define_Data_Identifier.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Write_Data_By_Identifier.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Write_Memory_By_Address.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Clear_Diagnostic_Information.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Read_DTC_Information.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Input_Output_Control_By_Identifier.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Routine_Control.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Request_Download.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Request_Upload.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Transfer_Data.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Request_Transfer_Exit.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Request_File_Transfer.c
    ${CMAKE_CURRENT_SOURCE_DIR}/src/Negative_Response.c
    )
# headers file liste

set(LIB_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Diagnostic_srv.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Diagnostic_Session_Control.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/ECU_Reset.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Clear_Diagnostic_Information.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Security_Access.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Communication_Control.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Authentication.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Tester_Present.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Access_Timing_Parameters.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Secured_Data_Transmission.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Control_DTC_Settings.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Response_On_Event.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Link_Control.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Read_Data_By_Identifier.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Read_Memory_By_Address.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Read_Scaling_Data_By_Identifier.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Read_Data_By_Identifier_Periodic.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Dynamically_Define_Data_Identifier.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Write_Data_By_Identifier.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Write_Memory_By_Address.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Clear_Diagnostic_Information.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Read_DTC_Information.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Input_Output_Control_By_Identifier.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Routine_Control.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Request_Download.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Request_Upload.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Transfer_Data.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Request_Transfer_Exit.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Request_File_Transfer.h
    ${CMAKE_CURRENT_SOURCE_DIR}/include/Negative_Response.h
    )

add_library(uds SHARED ${LIB_SRCS} ${LIB_HEADERS})
target_link_libraries(uds rt)
install (TARGETS uds DESTINATION lib)
install (FILES ${HEADER_FILES} DESTINATION include)
