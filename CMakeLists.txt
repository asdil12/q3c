cmake_minimum_required(VERSION 3.2)

project(readq3c C)

add_executable(readq3c readq3c.c q3c.c backlog.c ini.c config.c)
target_compile_definitions(readq3c PRIVATE INI_ALLOW_MULTILINE=0 INI_ALLOW_BOM=0)
target_link_libraries(readq3c paho-mqtt3c)
install(TARGETS readq3c DESTINATION bin)
