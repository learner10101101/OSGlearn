# Copyright (C) 2009 by Wang Rui <wangray84 at gmail dot com>
# OpenSceneGraph Engine Book - Design and Implementation
# How to embed the viewer with Win32 API window

SET( EXAMPLE_NAME gui )

SET( EXAMPLE_FILES
    gui.cpp
)

SET( DATA_FILES
)

ADD_EXECUTABLE( ${EXAMPLE_NAME} WIN32 ${EXAMPLE_FILES} )
SET_TARGET_PROPERTIES( ${EXAMPLE_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}" )

INCLUDE_FOR_PROJECT( ${EXAMPLE_NAME} OPENTHREADS OSG OSGDB OSGUTIL OSGGA OSGVIEWER )
LINK_PROJECT( ${EXAMPLE_NAME} OPENTHREADS OSG OSGDB OSGUTIL OSGGA OSGVIEWER )
INSTALL_PROJECT( ${EXAMPLE_NAME} )

INSTALL( FILES ${DATA_FILES} DESTINATION bin )
