#----------------------------------------------------------------
# Generated CMake target import file for configuration "RelWithDebInfo".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CGAL::CGAL_ImageIO" for configuration "RelWithDebInfo"
set_property(TARGET CGAL::CGAL_ImageIO APPEND PROPERTY IMPORTED_CONFIGURATIONS RELWITHDEBINFO)
set_target_properties(CGAL::CGAL_ImageIO PROPERTIES
  IMPORTED_IMPLIB_RELWITHDEBINFO "${_IMPORT_PREFIX}/lib/CGAL_ImageIO-vc140-mt-4.12.lib"
  IMPORTED_LOCATION_RELWITHDEBINFO "${_IMPORT_PREFIX}/bin/CGAL_ImageIO-vc140-mt-4.12.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS CGAL::CGAL_ImageIO )
list(APPEND _IMPORT_CHECK_FILES_FOR_CGAL::CGAL_ImageIO "${_IMPORT_PREFIX}/lib/CGAL_ImageIO-vc140-mt-4.12.lib" "${_IMPORT_PREFIX}/bin/CGAL_ImageIO-vc140-mt-4.12.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
