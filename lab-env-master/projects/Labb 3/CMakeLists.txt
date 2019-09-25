#--------------------------------------------------------------------------
# labb3 project
#--------------------------------------------------------------------------

PROJECT(labb3)
FILE(GLOB labb3_headers code/*.h)
FILE(GLOB labb3_sources code/*.cc)

SET(files_labb3 ${labb3_headers} ${labb3_sources})
SOURCE_GROUP("labb3" FILES ${files_labb3})

ADD_EXECUTABLE(labb3 ${files_labb3})
TARGET_LINK_LIBRARIES(labb3 core render)
ADD_DEPENDENCIES(labb3 core render)