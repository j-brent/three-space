add_subdirectory(sp3)

install(TARGETS three-space
        EXPORT three-spaceTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(FILES ${THREE_SPACE_HEADER_FILES}
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(EXPORT three-spaceTargets
        FILE three-spaceTargets.cmake
        NAMESPACE three-space::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/three-space
)

include(CMakePackageConfigHelpers)

configure_package_config_file(
  "${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in"
  "${CMAKE_CURRENT_BINARY_DIR}/three-spaceConfig.cmake"
  INSTALL_DESTINATION
    ${CMAKE_INSTALL_LIBDIR}/cmake/three-space
)

set_property(TARGET three-space PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET three-space PROPERTY SOVERSION ${PROJECT_VERSION_MAJOR})

write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/three-spaceConfigVersion.cmake"
  VERSION "${PROJECT_VERSION}"
  COMPATIBILITY SameMajorVersion
)

install(FILES
          "${CMAKE_CURRENT_BINARY_DIR}/three-spaceConfig.cmake"
          "${CMAKE_CURRENT_BINARY_DIR}/three-spaceConfigVersion.cmake"
        DESTINATION
          ${CMAKE_INSTALL_LIBDIR}/cmake/three-space
)

# https://cmake.org/cmake/help/latest/guide/importing-exporting/index.html#exporting-targets-from-the-build-tree
export(EXPORT three-spaceTargets
       FILE "${CMAKE_CURRENT_BINARY_DIR}/cmake/three-spaceTargets.cmake"
       NAMESPACE three-space::
)
