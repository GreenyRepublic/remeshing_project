#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CGAL::CGAL_Core" for configuration "RelWithDebInfo"
set_property(TARGET CGAL::CGAL_Core APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(CGAL::CGAL_Core PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/CGAL_Core-vc140-mt-4.12.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/CGAL_Core-vc140-mt-4.12.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS CGAL::CGAL_Core )
list(APPEND _IMPORT_CHECK_FILES_FOR_CGAL::CGAL_Core "${_IMPORT_PREFIX}/lib/CGAL_Core-vc140-mt-4.12.lib" "${_IMPORT_PREFIX}/bin/CGAL_Core-vc140-mt-4.12.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
