# Copyright (c) 2017 The Chromium Embedded Framework Authors. All rights
# reserved. Use of this source code is governed by a BSD-style license that
# can be found in the LICENSE file.

cmake_minimum_required(VERSION 3.8)

SET_PROPERTY(
  DIRECTORY
  APPEND PROPERTY COMPILE_DEFINITIONS
)

ADD_DEFINITIONS(-DUNICODE)
ADD_DEFINITIONS(-D_UNICODE)

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11")
#set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /DEBUG /OPT:REF /OPT:ICF")
#set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")

ADD_LOGICAL_TARGET("libcef_lib" "${CEF_LIB_DEBUG}" "${CEF_LIB_RELEASE}")

if(OS_LINUX)
  link_directories(${GST_LIBRARY_DIRS})
endif()


include_directories(AFTER
#   ${GST_INSTALL_BASE}/include
#   ${GST_INSTALL_BASE}/include/lib
#   ${GST_INSTALL_BASE}/include/static
#   ${GST_INSTALL_BASE}/include/gstreamer-1.0
#   ${GST_INSTALL_BASE}/include/glib-2.0
#   ${GST_INSTALL_BASE}/lib/glib-2.0/include
#   ${GST_INSTALL_BASE}/lib/gstreamer-1.0/include
#   # ${PROJECT_SOURCE_DIR}/../../win32/common
   ${CMAKE_BINARY_DIR}/cef/cef_binary_${CEF_VERSION}_${CEF_PLATFORM}
   ${GST_INCLUDE_DIRS}
)

#LINK_DIRECTORIES(
#  ${GST_INSTALL_BASE}/lib
#)

# ADD_LIBRARY(libgstcef SHARED
ADD_LIBRARY(gstcef SHARED
  gstcef.c
  gstcef.h
  cef_gst_interface.cpp
  cef_gst_interface.h
  browser_manager.cpp
  browser_manager.h
  cef_window_manager.cpp
  cef_window_manager.h
  file_scheme_handler.cpp
  file_scheme_handler.h
)

ADD_DEFINITIONS(-DSUBPROCESS_NAME="${SUBPROCESS}")


# We probably don't need most of these libraries.
TARGET_LINK_LIBRARIES(gstcef
  gstreamer-1.0
  gstaudio-1.0
  gstvideo-1.0
  gstbase-1.0
  glib-2.0
  gobject-2.0
#  rpcrt4
#  uuid
#  winmm
#  dmoguids
#  wmcodecdspuuid
#  msdmo
  libcef_lib
  libcef_dll_wrapper
)

if(USE_SANDBOX)
  # Logical target used to link the cef_sandbox library.
  ADD_LOGICAL_TARGET("cef_sandbox_lib" "${CEF_SANDBOX_LIB_DEBUG}" "${CEF_SANDBOX_LIB_RELEASE}")
  TARGET_LINK_LIBRARIES(gstcef
    cef_sandbox_lib
    ${CEF_SANDBOX_STANDARD_LIBS}
  )
endif()

ADD_EXECUTABLE(${SUBPROCESS}
  subprocess.cpp
)

#ADD_EXECUTABLE(bebo_cef WIN32
#  subprocess.cpp
#)

TARGET_LINK_LIBRARIES(${SUBPROCESS}
  libcef_lib
  libcef_dll_wrapper
)

# SET_TARGET_PROPERTIES(bebo_cef PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS")

# Copy binary and resource files to the target output directory.
set(DIST_DIR "${CMAKE_BINARY_DIR}/dist")
file(MAKE_DIRECTORY ${DIST_DIR}/locales)

set(BINARY_DIST_FILES
  chrome_elf.dll
  d3dcompiler_47.dll
  libcef.dll
  libEGL.dll
  libGLESv2.dll
  natives_blob.bin
  snapshot_blob.bin
  v8_context_snapshot.bin
  swiftshader
)

# COPY_FILES(gstcef "${BINARY_DIST_FILES}" "${CEF_BINARY_DIR}" "${DIST_DIR}")

set(RESOURCE_FILES
  cef.pak
  cef_100_percent.pak
  cef_200_percent.pak
  cef_extensions.pak
  devtools_resources.pak
  icudtl.dat
)
COPY_FILES(cef "${RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${DIST_DIR}")

set(ENGLISH_FILES
  en-US.pak
  en-US.pak.info
)
COPY_FILES(gstcef "${CEF_BINARY_FILES}" "${CEF_BINARY_DIR}" "${CEF_TARGET_OUT_DIR}")
COPY_FILES(gstcef "${CEF_RESOURCE_FILES}" "${CEF_RESOURCE_DIR}" "${CEF_TARGET_OUT_DIR}")
#COPY_FILES(libgstcef "${ENGLISH_FILES}" "${CEF_RESOURCE_DIR}/locales" "${DIST_DIR}/locales")
#COPY_FILES(libgstcef "libgstcef.dll" "${CMAKE_BINARY_DIR}/src/$<CONFIGURATION>" "${DIST_DIR}")
#COPY_FILES(bebo_cef "bebo_cef.exe" "${CMAKE_BINARY_DIR}/src/$<CONFIGURATION>" "${DIST_DIR}")
