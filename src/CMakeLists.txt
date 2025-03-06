add_library(${PROJECT}
            OpusFile.c
            OpusPage.c
            OpusIdHeader.c
            OpusCommentHeader.c
)


target_link_libraries(${PROJECT}
  opus)
