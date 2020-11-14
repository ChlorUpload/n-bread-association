cmake로 캐시를 생성하기 전에 꼭 data 폴더 안에 dir.txt를 만들어 주세요.  

dir.txt 내부에 다음과 같이 입력해주세요.

```
set(MYSQL_CON "<your-mysql-connector-lib64/vsNN-directory>")
set(BOOST     "<your-boost_1_74_0-directory>")
set(MYSQL     "<your-mysql-connector-include-directory>")
set(OPENSSL   "<your-OpenSSL-Win64-include-directory>")
```

예시는 다음과 같습니다.

```
set(MYSQL_CON "C:/Program Files/MySQL/MySQL Connector C++ 8.0/lib64/vs14")
set(BOOST     "D:/configurations/boost_1_74_0")
set(MYSQL     "C:/Program Files/MySQL/MySQL Connector C++ 8.0/include")
set(OPENSSL   "C:/Program Files/OpenSSL-Win64/include")
```

