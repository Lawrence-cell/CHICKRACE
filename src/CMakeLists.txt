aux_source_directory(. APP_DIR)
aux_source_directory(common APP_DIR)
aux_source_directory(game APP_DIR)
aux_source_directory(network APP_DIR)
aux_source_directory(ui APP_DIR)
aux_source_directory(CR APP_DIR)

add_executable(uno ${APP_DIR})
#使用MinGW编译器时会出现找不到库情况所以需要添加wsock32,以及ws2_32等库
target_link_libraries(uno PUBLIC wsock32)
target_link_libraries(uno PUBLIC ws2_32)
target_link_libraries(uno PRIVATE asio)
target_link_libraries(uno PRIVATE cxxopts)
target_link_libraries(uno PRIVATE yaml-cpp)

if(ENABLE_LOG)
    target_link_libraries(uno PRIVATE spdlog::spdlog)
endif()