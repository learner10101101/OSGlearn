# Copyright (C) 2009 by Wang Rui <wangray84 at gmail dot com>
# OpenSceneGraph Engine Book - Design and Implementation
# How to create different transform nodes

SET( EXAMPLE_NAME transform )

SET( EXAMPLE_FILES
    transform.cpp
)

SET( DATA_FILES
)

ADD_EXECUTABLE( ${EXAMPLE_NAME} ${EXAMPLE_FILES} )
SET_TARGET_PROPERTIES( ${EXAMPLE_NAME} PROPERTIES DEBUG_POSTFIX "${CMAKE_DEBUG_POSTFIX}" )

INCLUDE_FOR_PROJECT( ${EXAMPLE_NAME} OPENTHREADS OSG OSGDB OSGUTIL OSGVIEWER )
LINK_PROJECT( ${EXAMPLE_NAME} OPENTHREADS OSG OSGDB OSGUTIL OSGVIEWER )
INSTALL_PROJECT( ${EXAMPLE_NAME} )

INSTALL( FILES ${DATA_FILES} DESTINATION bin )
