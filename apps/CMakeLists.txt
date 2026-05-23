project(cftal-apps)

# boost_lorenz
find_package(Boost CONFIG)
if(${Boost_FOUND})
    #message ("${Boost_FOUND}")
    #message ("${Boost_INCLUDE_DIRS}")
    include_directories(${Boost_INCLUDE_DIRS})

    set (BOOST_LORENZ_SRC boost_lorenz.cc)
    add_executable(boost_lorenz ${BOOST_LORENZ_SRC})
    target_link_libraries(boost_lorenz cftal-so)

    install (TARGETS boost_lorenz
      DESTINATION bin
      COMPONENT tools)
endif()



