# Copyright (C) 2009 by Wang Rui <wangray84 at gmail dot com>
# OpenSceneGraph Engine Book - Design and Implementation
# How to make use of the reference pointers

SET( EXAMPLE_NAME refptr )

SET( EXAMPLE_FILES
    refptr.cpp
)

SET( DATA_FILES
)

ADD_EXECUTABLE( ${EXAMPLE_NAME} ${EXAMPLE_FILES} )
SET_TARGET_PROPERTIES( ${EXAMPLE_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}" )

INCLUDE_FOR_PROJECT( ${EXAMPLE_NAME} OPENTHREADS OSG OSGDB OSGUTIL OSGVIEWER )
LINK_PROJECT( ${EXAMPLE_NAME} OPENTHREADS OSG OSGDB OSGUTIL OSGVIEWER )
INSTALL_PROJECT( ${EXAMPLE_NAME} )

INSTALL( FILES ${DATA_FILES} DESTINATION bin )
