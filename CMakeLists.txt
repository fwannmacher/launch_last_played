cmake_minimum_required(VERSION 2.8)

if(NOT DEFINED CMAKE_TOOLCHAIN_FILE)
  if(DEFINED ENV{VITASDK})
    set(CMAKE_TOOLCHAIN_FILE "$ENV{VITASDK}/share/vita.toolchain.cmake" CACHE PATH "toolchain file")
  else()
    message(FATAL_ERROR "Please define VITASDK to point to your SDK path!")
  endif()
endif()

set(APP_PROJECT app)
set(PLUGIN_PROJECT plugin)
project(${APP_PROJECT})
project(${PLUGIN_PROJECT})
include("${VITASDK}/share/vita.cmake" REQUIRED)

set(VITA_APP_NAME "Launch Last Played Game")
set(SHORT_NAME "launch_last_played")
set(VITA_TITLEID  "LLPG00000")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wl,-q -Wall -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti -fno-exceptions")

include_directories(
)

add_executable(${APP_PROJECT}
  app/main.c
)

add_executable(${PLUGIN_PROJECT}
  plugin/main.c
)

target_link_libraries(${APP_PROJECT}
  SceKernelThreadMgr_stub
  SceAppMgr_stub_weak
  SceIofilemgr_stub
)

target_link_libraries(${PLUGIN_PROJECT}
  taihenForKernel_stub
  SceIofilemgrForDriver_stub
  SceSysclibForDriver_stub
)

set_target_properties(${PLUGIN_PROJECT}
  PROPERTIES LINK_FLAGS "-nostdlib"
)

vita_create_self(${SHORT_NAME}.self ${APP_PROJECT})
vita_create_vpk(${SHORT_NAME}.vpk ${VITA_TITLEID} ${SHORT_NAME}.self
  VERSION ${VITA_VERSION}
  NAME ${VITA_APP_NAME}
  FILE sce_sys/icon0.png sce_sys/icon0.png
       sce_sys/livearea/contents/bg.png sce_sys/livearea/contents/bg.png
       sce_sys/livearea/contents/startup.png sce_sys/livearea/contents/startup.png
       sce_sys/livearea/contents/template.xml sce_sys/livearea/contents/template.xml
)
vita_create_self(${SHORT_NAME}.skprx ${PLUGIN_PROJECT}
  CONFIG ${CMAKE_SOURCE_DIR}/plugin/config.yml
)
