CMAKE_MINIMUM_REQUIRED(VERSION 3.13.1)

PROJECT(n-bread-association-server)

enable_language(CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_BUILD_TYPE Release)

include(data/dir.txt)

include_directories(
    header/api
    header/core
    header/infrastructure

    ${JSON}
    ${BOOST}
    ${MYSQL}
    ${OPENSSL}
    ${JWT}
)

add_compile_definitions(BOOST_DATE_TIME_NO_LIB)

add_executable( server
                source/api/controller-manager.cpp
                source/core/check-token-query.cpp
                source/core/count-command.cpp
                source/core/login-query.cpp
                source/core/register-command.cpp
                source/infrastructure/credentials-service.cpp
                source/infrastructure/db-context.cpp
                source/infrastructure/encryption-service.cpp
                source/main.cpp
)

target_link_libraries(
    server    
    ${MYSQL_CON}/libcrypto.lib
    ${MYSQL_CON}/libssl.lib
    ${MYSQL_CON}/mysqlcppconn.lib
    ws2_32.lib
)