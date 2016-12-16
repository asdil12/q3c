cmake_minimum_required(VERSION 3.2)

project(q3c_read C)

add_executable(read read.c q3c.c)
target_link_libraries(read paho-mqtt3c)
install(TARGETS read DESTINATION bin)
