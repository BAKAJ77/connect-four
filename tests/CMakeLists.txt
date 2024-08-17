if (CF_BUILD_TESTS)
    include_directories("${PROJECT_SOURCE_DIR}/external/SDL_ttf/external/SDL/include" "${PROJECT_SOURCE_DIR}/src" "${PROJECT_BINARY_DIR}/tests"
        "${PROJECT_SOURCE_DIR}/external/json/include")

    configure_file("Config.h.in" "Config.h")

    set(CF_TEST_TARGETS SDLInitTest ConfigHandlerTest)
    add_executable(SDLInitTest "SDLInitTest.cpp")
    add_executable(ConfigHandlerTest "ConfigHandlerTest.cpp" "../src/ConfigHandler.h" "../src/ConfigHandler.cpp")
    
    foreach(TEST_TARGET IN LISTS CF_TEST_TARGETS)
        set_target_properties("${TEST_TARGET}" PROPERTIES 
            RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/$<IF:$<CONFIG:Debug>,debug,release>"
            LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/$<IF:$<CONFIG:Debug>,debug,release>"
            ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/tests/$<IF:$<CONFIG:Debug>,debug,release>"
            FOLDER "CFTests")

        target_link_libraries("${TEST_TARGET}" PRIVATE SDL3-static)
    endforeach()

    add_test(NAME SDLInitTest COMMAND SDLInitTest)
    add_test(NAME ConfigHandlerTest COMMAND ConfigHandlerTest)
endif()