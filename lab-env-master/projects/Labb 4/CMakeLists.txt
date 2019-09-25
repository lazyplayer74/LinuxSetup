#--------------------------------------------------------------------------
# labb4 project
#--------------------------------------------------------------------------

PROJECT(labb4)
FILE(GLOB labb4_headers code/*.h)
FILE(GLOB labb4_sources code/*.cc)

SET(files_labb4 ${labb4_headers} ${labb4_sources})
SOURCE_GROUP("labb4" FILES ${files_labb4})

ADD_EXECUTABLE(labb4 ${files_labb4})
TARGET_LINK_LIBRARIES(labb4 core render)
ADD_DEPENDENCIES(labb4 core render)