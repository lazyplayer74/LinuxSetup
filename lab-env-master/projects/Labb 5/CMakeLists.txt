#--------------------------------------------------------------------------
# labb5 project
#--------------------------------------------------------------------------

PROJECT(labb5)
FILE(GLOB labb5_headers code/*.h)
FILE(GLOB labb5_sources code/*.cc)

SET(files_labb5 ${labb5_headers} ${labb5_sources})
SOURCE_GROUP("labb5" FILES ${files_labb5})

ADD_EXECUTABLE(labb5 ${files_labb5})
TARGET_LINK_LIBRARIES(labb5 core render)
ADD_DEPENDENCIES(labb5 core render)