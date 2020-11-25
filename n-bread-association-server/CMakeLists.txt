cmake_minimum_required(VERSION 3.17.2)
project(n-bread-association-server)
enable_testing()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(JWT       "libs/jwt-cpp/include")
set(JSON      "libs/nlohmann-json/include")
set(OPENSSL   "libs/openssl/include")

add_library(server-lib
    source/api/controller-manager.cpp
    source/core/check-token-query.cpp
    source/core/login-query.cpp
    source/core/register-command.cpp
    source/infrastructure/credentials-service.cpp
    source/infrastructure/db-context.cpp
    source/infrastructure/encryption-service.cpp
)
target_include_directories(server-lib PUBLIC
    header/api
    header/core
    header/infrastructure
    header/domain
    ${JSON}
    ${BOOST}
    ${MYSQL}
    ${OPENSSL}
    ${JWT}
)
target_compile_definitions(server-lib PUBLIC
    BOOST_DATE_TIME_NO_LIB
)
target_link_directories(server-lib PUBLIC
    ${MYSQL_CON}
)
target_link_libraries(server-lib 
    libcrypto
    libssl
    mysqlcppconn
    ws2_32
)

add_executable(server source/main.cpp)
target_link_libraries(server server-lib)

add_custom_command(
    TARGET server POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/data/libcrypto-1_1-x64.dll libcrypto-1_1-x64.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/data/libssl-1_1-x64.dll libssl-1_1-x64.dll
    COMMAND ${CMAKE_COMMAND} -E copy_if_different ${PROJECT_SOURCE_DIR}/data/mysqlcppconn-7-vs14.dll mysqlcppconn-7-vs14.dll
)

macro(add_nbas_test NAME)
    add_executable(${NAME} tests/${NAME}.cpp)
    target_link_libraries(${NAME} server-lib)
    add_test(NAME ${NAME} COMMAND ${NAME})
endmacro()
add_nbas_test(add-remove-test)
add_nbas_test(check-token-test)