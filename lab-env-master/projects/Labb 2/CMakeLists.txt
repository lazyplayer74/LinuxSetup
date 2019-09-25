#--------------------------------------------------------------------------
# labb2 project
#--------------------------------------------------------------------------

PROJECT(labb2)
FILE(GLOB labb2_headers code/*.h)
FILE(GLOB labb2_sources code/*.cc)

SET(files_labb2 ${labb2_headers} ${labb2_sources})
SOURCE_GROUP("labb2" FILES ${files_labb2})

ADD_EXECUTABLE(labb2 ${files_labb2})
TARGET_LINK_LIBRARIES(labb2 core render)
ADD_DEPENDENCIES(labb2 core render)