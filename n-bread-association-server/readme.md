빌드하기 전에 상단의 x64-Debug 드롭다운 목록을 펼쳐 `구성 요소`를 선택하세요.  
`json 편집`을 눌러 `configurations` 리스트의 첫 번째 요소 안에 "variables" 프로퍼티를 생성합니다.  
variables 프로퍼티의 value를 다음과 같이 구성합니다.  

```
"variables": [
        {
          "name": "MYSQL_CON",
          "value": "<your-mysql-connector-lib64/vsNN-directory>",
          "type": "FILEPATH"
        },
        {
          "name": "BOOST",
          "value": "<your-boost_1_74_0-directory>"
        },
        {
          "name": "MYSQL",
          "value": "<your-mysql-connector-include-directory>"
        },
        {
          "name": "OPENSSL",
          "value": "<your-OpenSSL-Win64-include-directory>"
        }
      ]
```

CMakeSettings.json 예시

```
{
  "configurations": [
    {
      "name": "x64-Debug",
      "generator": "Ninja",
      "configurationType": "Release",
      "inheritEnvironments": [ "msvc_x64_x64" ],
      "buildRoot": "${projectDir}\\out\\build\\${name}",
      "installRoot": "${projectDir}\\out\\install\\${name}",
      "cmakeCommandArgs": "",
      "buildCommandArgs": "",
      "ctestCommandArgs": "",
      "variables": [
        {
          "name": "MYSQL_CON",
          "value": "C:/Program Files/MySQL/MySQL Connector C++ 8.0/lib64/vs14",
          "type": "FILEPATH"
        },
        {
          "name": "BOOST",
          "value": "D:/configurations/boost_1_74_0"
        },
        {
          "name": "MYSQL",
          "value": "C:/Program Files/MySQL/MySQL Connector C++ 8.0/include"
        },
        {
          "name": "OPENSSL",
          "value": "C:/Program Files/OpenSSL-Win64/include"
        }
      ]
    }
  ]
}
```

