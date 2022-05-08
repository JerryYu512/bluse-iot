# Protocol Documentation
<a name="top"></a>

## Table of Contents

- [module_db.proto](#module_db-proto)
    - [BiotAppDb](#biot-BiotAppDb)
    - [BiotAppDbLocal](#biot-BiotAppDbLocal)
  
- [module_device.proto](#module_device-proto)
    - [BiotAppDevice](#biot-BiotAppDevice)
  
- [module_hw.proto](#module_hw-proto)
    - [BiotAppHardware](#biot-BiotAppHardware)
  
- [module_media.proto](#module_media-proto)
    - [BiotAppMedia](#biot-BiotAppMedia)
  
- [module_network.proto](#module_network-proto)
    - [BiotAppCmdApi](#biot-BiotAppCmdApi)
    - [BiotAppLanParam](#biot-BiotAppLanParam)
    - [BiotAppNetwork](#biot-BiotAppNetwork)
    - [BiotAppOatppApi](#biot-BiotAppOatppApi)
    - [BiotAppRtsp](#biot-BiotAppRtsp)
    - [BiotAppWebServiceParam](#biot-BiotAppWebServiceParam)
  
- [module_storage.proto](#module_storage-proto)
    - [BiotAppStorage](#biot-BiotAppStorage)
  
- [module_subsys.proto](#module_subsys-proto)
    - [BiotAppSubsys](#biot-BiotAppSubsys)
  
- [param_basic.proto](#param_basic-proto)
    - [BiotAppAccessUser](#biot-BiotAppAccessUser)
    - [BiotAppBasicParam](#biot-BiotAppBasicParam)
    - [BiotAppUsers](#biot-BiotAppUsers)
  
- [param_module.proto](#param_module-proto)
    - [BiotAppModule](#biot-BiotAppModule)
  
- [param_product.proto](#param_product-proto)
    - [BiotAppProduct](#biot-BiotAppProduct)
  
- [param.proto](#param-proto)
    - [BiotAppParam](#biot-BiotAppParam)
  
- [param_system.proto](#param_system-proto)
    - [BiotAppSystem](#biot-BiotAppSystem)
  
- [enums/e_basic.proto](#enums_e_basic-proto)
    - [EBiotAppMode](#biot-EBiotAppMode)
  
- [enums/e_db.proto](#enums_e_db-proto)
    - [BiotAppDbType](#biot-BiotAppDbType)
  
- [enums/e_device.proto](#enums_e_device-proto)
- [enums/e_hw.proto](#enums_e_hw-proto)
- [enums/e_media.proto](#enums_e_media-proto)
- [enums/e_module.proto](#enums_e_module-proto)
- [enums/e_network.proto](#enums_e_network-proto)
    - [BiotAppModulePayload](#biot-BiotAppModulePayload)
    - [BiotAppModuleProtocol](#biot-BiotAppModuleProtocol)
    - [NetCfgType](#biot-NetCfgType)
    - [NetIfRate](#biot-NetIfRate)
    - [NetLanType](#biot-NetLanType)
    - [WireLessIfMode](#biot-WireLessIfMode)
    - [WireLessSecMode](#biot-WireLessSecMode)
    - [WireLessWepAuthType](#biot-WireLessWepAuthType)
    - [WireLessWepKeyLen](#biot-WireLessWepKeyLen)
    - [WireLessWepKeyType](#biot-WireLessWepKeyType)
    - [WireLessWorkMode](#biot-WireLessWorkMode)
    - [WireLessWpaEncryptType](#biot-WireLessWpaEncryptType)
  
- [enums/e_product.proto](#enums_e_product-proto)
- [enums/e_storage.proto](#enums_e_storage-proto)
- [enums/e_subsys.proto](#enums_e_subsys-proto)
- [enums/e_system.proto](#enums_e_system-proto)
- [Scalar Value Types](#scalar-value-types)



<a name="module_db-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## module_db.proto



<a name="biot-BiotAppDb"></a>

### BiotAppDb



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| localdb | [BiotAppDbLocal](#biot-BiotAppDbLocal) |  |  |






<a name="biot-BiotAppDbLocal"></a>

### BiotAppDbLocal



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| dbtype | [BiotAppDbType](#biot-BiotAppDbType) |  |  |





 

 

 

 



<a name="module_device-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## module_device.proto



<a name="biot-BiotAppDevice"></a>

### BiotAppDevice






 

 

 

 



<a name="module_hw-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## module_hw.proto



<a name="biot-BiotAppHardware"></a>

### BiotAppHardware






 

 

 

 



<a name="module_media-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## module_media.proto



<a name="biot-BiotAppMedia"></a>

### BiotAppMedia






 

 

 

 



<a name="module_network-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## module_network.proto



<a name="biot-BiotAppCmdApi"></a>

### BiotAppCmdApi
命令行服务


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| port | [uint32](#uint32) |  |  |
| ipv4 | [uint32](#uint32) |  |  |
| trans | [BiotAppModuleProtocol](#biot-BiotAppModuleProtocol) |  | 通信协议 |
| body | [BiotAppModulePayload](#biot-BiotAppModulePayload) |  | body内容:json/xml |






<a name="biot-BiotAppLanParam"></a>

### BiotAppLanParam
有线网参数


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| type | [NetLanType](#biot-NetLanType) |  |  |
| cfg_type | [NetCfgType](#biot-NetCfgType) |  |  |
| if_name | [string](#string) |  |  |
| mac | [string](#string) |  |  |
| ipv4 | [string](#string) |  |  |
| ipv6 | [string](#string) |  |  |
| submask | [string](#string) |  |  |
| gateway | [string](#string) |  |  |
| mtu | [uint32](#uint32) |  | mtu值[eg:1500][range:536&lt;==&gt;1500][type:uint32] |
| dns | [string](#string) |  |  |
| x1 | [float](#float) |  |  |
| x2 | [double](#double) |  |  |
| x3 | [bool](#bool) |  |  |






<a name="biot-BiotAppNetwork"></a>

### BiotAppNetwork



| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| lan | [BiotAppLanParam](#biot-BiotAppLanParam) | repeated |  |
| web | [BiotAppWebServiceParam](#biot-BiotAppWebServiceParam) |  |  |
| openapi | [BiotAppOatppApi](#biot-BiotAppOatppApi) |  |  |
| cmdapi | [BiotAppCmdApi](#biot-BiotAppCmdApi) |  |  |






<a name="biot-BiotAppOatppApi"></a>

### BiotAppOatppApi
oatpp开放api


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| port | [uint32](#uint32) |  |  |
| ipv4 | [uint32](#uint32) |  |  |
| body | [BiotAppModulePayload](#biot-BiotAppModulePayload) |  | body内容:json/xml |






<a name="biot-BiotAppRtsp"></a>

### BiotAppRtsp
rtsp






<a name="biot-BiotAppWebServiceParam"></a>

### BiotAppWebServiceParam
web服务参数


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| http_port | [uint32](#uint32) |  | http端口号 |
| https_port | [uint32](#uint32) |  | https端口号 |
| http | [bool](#bool) |  | 使能http |
| https | [bool](#bool) |  | 使能https |
| root | [string](#string) |  | 根路径 |
| connect_max | [uint32](#uint32) |  | 最大连接数 |





 

 

 

 



<a name="module_storage-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## module_storage.proto



<a name="biot-BiotAppStorage"></a>

### BiotAppStorage






 

 

 

 



<a name="module_subsys-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## module_subsys.proto



<a name="biot-BiotAppSubsys"></a>

### BiotAppSubsys






 

 

 

 



<a name="param_basic-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## param_basic.proto



<a name="biot-BiotAppAccessUser"></a>

### BiotAppAccessUser
设备访问用户


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| name | [string](#string) |  | 用户名 |
| passwd | [string](#string) |  | 密码 |
| expired | [uint64](#uint64) |  | 有效期 |
| permission | [string](#string) |  | 权限 |
| allowlist | [bool](#bool) |  | 白名单 |
| email | [string](#string) |  | 邮箱 |
| phone | [string](#string) |  | 电话 |
| github | [string](#string) |  | gihub账户 |






<a name="biot-BiotAppBasicParam"></a>

### BiotAppBasicParam
基础功能配置


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| appmode | [EBiotAppMode](#biot-EBiotAppMode) |  | 运行模式 |
| user | [BiotAppUsers](#biot-BiotAppUsers) |  | 用户 |






<a name="biot-BiotAppUsers"></a>

### BiotAppUsers
用户列表


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| access_users | [BiotAppAccessUser](#biot-BiotAppAccessUser) | repeated | 外部接入访问的用户 |





 

 

 

 



<a name="param_module-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## param_module.proto



<a name="biot-BiotAppModule"></a>

### BiotAppModule
模块配置


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| hardware | [BiotAppHardware](#biot-BiotAppHardware) |  | 硬件配置 |
| device | [BiotAppDevice](#biot-BiotAppDevice) |  | 设备配置 |
| network | [BiotAppNetwork](#biot-BiotAppNetwork) |  | 网络配置 |
| database | [BiotAppDb](#biot-BiotAppDb) |  | 数据库配置 |
| storage | [BiotAppStorage](#biot-BiotAppStorage) |  | 存储配置 |
| media | [BiotAppMedia](#biot-BiotAppMedia) |  | 媒体配置 |
| subsys | [BiotAppSubsys](#biot-BiotAppSubsys) |  | 子系统配置 |





 

 

 

 



<a name="param_product-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## param_product.proto



<a name="biot-BiotAppProduct"></a>

### BiotAppProduct
产品配置参数，每个产品定义自身的





 

 

 

 



<a name="param-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## param.proto
配置参数根节点.


<a name="biot-BiotAppParam"></a>

### BiotAppParam
BIOT应用程序配置参数


| Field | Type | Label | Description |
| ----- | ---- | ----- | ----------- |
| uuid | [string](#string) |  | 配置参数文件唯一标识，用于校验[eg:03948b6f-9c67-4a14-a53d-2db53466a4e0] |
| exec_uuid | [string](#string) |  | 执行程序唯一标识[eg:03948b6f-9c67-4a14-a53d-2db53466a4e0] |
| version | [uint32](#uint32) |  | 配置参数版本号 |
| device_name | [string](#string) |  | 设备名称[eg:biot 01] |
| device_id | [string](#string) |  | 设备id[eg:00000000000][reg:\d{11}] |
| basic | [BiotAppBasicParam](#biot-BiotAppBasicParam) |  | 基础配置参数 |
| system | [BiotAppSystem](#biot-BiotAppSystem) |  | 系统配置参数 |
| modules | [BiotAppModule](#biot-BiotAppModule) |  | 功能模块配置参数 |
| product | [BiotAppProduct](#biot-BiotAppProduct) |  | 产品配置参数 |





 

 

 

 



<a name="param_system-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## param_system.proto



<a name="biot-BiotAppSystem"></a>

### BiotAppSystem
系统配置参数，基本的系统运行参数





 

 

 

 



<a name="enums_e_basic-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_basic.proto


 


<a name="biot-EBiotAppMode"></a>

### EBiotAppMode
可选运行模式

| Name | Number | Description |
| ---- | ------ | ----------- |
| APP_DEVICE_MODE | 0 | 设备模式 |
| APP_GATEWAY_MODE | 1 | 网关模式 |
| APP_DEV_GW_MODE | 2 | 设备/网关模式 |


 

 

 



<a name="enums_e_db-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_db.proto


 


<a name="biot-BiotAppDbType"></a>

### BiotAppDbType
数据库类型

| Name | Number | Description |
| ---- | ------ | ----------- |
| DB_TYPE_SQLITE3 | 0 | sqlite3 |
| DB_TYPE_MONGODB | 1 | mongodb |
| DB_TYPE_MYSQL | 2 | mysql |
| DB_TYPE_LEVELDB | 3 | leveldb |
| DB_TYPE_CUSTOM | 4 | 自研 |


 

 

 



<a name="enums_e_device-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_device.proto


 

 

 

 



<a name="enums_e_hw-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_hw.proto


 

 

 

 



<a name="enums_e_media-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_media.proto


 

 

 

 



<a name="enums_e_module-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_module.proto


 

 

 

 



<a name="enums_e_network-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_network.proto


 


<a name="biot-BiotAppModulePayload"></a>

### BiotAppModulePayload
应用层协议类型

| Name | Number | Description |
| ---- | ------ | ----------- |
| MODULE_PAYLOAD_RAW | 0 | 二进制[str:raw] |
| MODULE_PAYLOAD_HTTP | 1 | http[str:http] |
| MODULE_PAYLOAD_JSON | 2 | json[str:json] |
| MODULE_PAYLOAD_XML | 3 | xml[str:xml] |
| MODULE_PAYLOAD_PROTOBUF | 4 | protobuf[str:protobuf] |



<a name="biot-BiotAppModuleProtocol"></a>

### BiotAppModuleProtocol
模块间通信协议

| Name | Number | Description |
| ---- | ------ | ----------- |
| MODULE_PROTOC_MQTT | 0 | mqtt[str:mqtt] |
| MODULE_PROTOC_NNG | 1 | nng[str:nng] |
| MODULE_PROTOC_PROTOBUF | 2 | protobuf[str:protobuf] |



<a name="biot-NetCfgType"></a>

### NetCfgType
网络配置方式

| Name | Number | Description |
| ---- | ------ | ----------- |
| NET_CFG_MANUAL | 0 | 手动配置 |
| NET_CFG_AUTO | 1 | 自动获取 |



<a name="biot-NetIfRate"></a>

### NetIfRate
网口速率

| Name | Number | Description |
| ---- | ------ | ----------- |
| NET_IF_RATE_100M | 0 | 百兆网口 |
| NET_IF_RATE_1000M | 1 | 千兆网口 |



<a name="biot-NetLanType"></a>

### NetLanType
有线网类型

| Name | Number | Description |
| ---- | ------ | ----------- |
| LAN_WORK_10M_HALF | 0 | 10M半双工[str:10M-half] |
| LAN_WORK_10M_FULL | 1 | 10全双工[str:10M-full] |
| LAN_WORK_100M_HALF | 2 | 100M半双工[str:100M-half] |
| LAN_WORK_100M_FULL | 3 | 100M全双工[str:100M-full] |
| LAN_WORK_AUTO | 4 | 自适应[str:auto] |
| LAN_WORK_1G_FULL | 5 | 1G全双工[str:1G-full] |



<a name="biot-WireLessIfMode"></a>

### WireLessIfMode
无线网网络接口模式

| Name | Number | Description |
| ---- | ------ | ----------- |
| WIRELESS_IF_AUTO | 0 | 自动切换 |
| WIRELESS_IF_LAN | 1 | 有线模式 |



<a name="biot-WireLessSecMode"></a>

### WireLessSecMode
无线安全模式

| Name | Number | Description |
| ---- | ------ | ----------- |
| WIRELESS_SEC_NONE | 0 | 不加密 |
| WIRELESS_SEC_WEP | 1 | WEP |
| WIRELESS_SEC_WPA_PSK | 2 | WPA-PSK |
| WIRELESS_SEC_WPA_ENTERPRISE | 3 | WPA-enterprise |
| WIRELESS_SEC_WPA2_PSK | 4 | WPA2-PSK |



<a name="biot-WireLessWepAuthType"></a>

### WireLessWepAuthType
WEP认证类型

| Name | Number | Description |
| ---- | ------ | ----------- |
| WIRELESS_WEPAUTH_OPEN | 0 | 开放式 |
| WIRELESS_WEPAUTH_SHARE | 1 | 共享式 |



<a name="biot-WireLessWepKeyLen"></a>

### WireLessWepKeyLen
WEP密钥长度

| Name | Number | Description |
| ---- | ------ | ----------- |
| WIRELESS_WEPKEY_LEN64 | 0 | 64位 |
| WIRELESS_WEPKEY_LEN128 | 1 | 128位 |
| WIRELESS_WEPKEY_LEN152 | 2 | 152位 |



<a name="biot-WireLessWepKeyType"></a>

### WireLessWepKeyType
WEP密钥类型

| Name | Number | Description |
| ---- | ------ | ----------- |
| WIRELESS_WEPKEY_HEX | 0 | 16进制 |
| WIRELESS_WEPKEY_ASCII | 1 | ASCII码 |



<a name="biot-WireLessWorkMode"></a>

### WireLessWorkMode
无线工作模式

| Name | Number | Description |
| ---- | ------ | ----------- |
| WIRELESS_WORK_MANAGED | 0 | managed |
| WIRELESS_WORK_AD_HOC | 1 | ad hoc |



<a name="biot-WireLessWpaEncryptType"></a>

### WireLessWpaEncryptType
WPA加密类型

| Name | Number | Description |
| ---- | ------ | ----------- |
| WIRELESS_WPA_ENCRYPT_AES | 0 | AES |
| WIRELESS_WPA_ENCRYPT_TKIP | 1 | TKIP |


 

 

 



<a name="enums_e_product-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_product.proto


 

 

 

 



<a name="enums_e_storage-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_storage.proto


 

 

 

 



<a name="enums_e_subsys-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_subsys.proto


 

 

 

 



<a name="enums_e_system-proto"></a>
<p align="right"><a href="#top">Top</a></p>

## enums/e_system.proto


 

 

 

 



## Scalar Value Types

| .proto Type | Notes | C++ | Java | Python | Go | C# | PHP | Ruby |
| ----------- | ----- | --- | ---- | ------ | -- | -- | --- | ---- |
| <a name="double" /> double |  | double | double | float | float64 | double | float | Float |
| <a name="float" /> float |  | float | float | float | float32 | float | float | Float |
| <a name="int32" /> int32 | Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint32 instead. | int32 | int | int | int32 | int | integer | Bignum or Fixnum (as required) |
| <a name="int64" /> int64 | Uses variable-length encoding. Inefficient for encoding negative numbers – if your field is likely to have negative values, use sint64 instead. | int64 | long | int/long | int64 | long | integer/string | Bignum |
| <a name="uint32" /> uint32 | Uses variable-length encoding. | uint32 | int | int/long | uint32 | uint | integer | Bignum or Fixnum (as required) |
| <a name="uint64" /> uint64 | Uses variable-length encoding. | uint64 | long | int/long | uint64 | ulong | integer/string | Bignum or Fixnum (as required) |
| <a name="sint32" /> sint32 | Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int32s. | int32 | int | int | int32 | int | integer | Bignum or Fixnum (as required) |
| <a name="sint64" /> sint64 | Uses variable-length encoding. Signed int value. These more efficiently encode negative numbers than regular int64s. | int64 | long | int/long | int64 | long | integer/string | Bignum |
| <a name="fixed32" /> fixed32 | Always four bytes. More efficient than uint32 if values are often greater than 2^28. | uint32 | int | int | uint32 | uint | integer | Bignum or Fixnum (as required) |
| <a name="fixed64" /> fixed64 | Always eight bytes. More efficient than uint64 if values are often greater than 2^56. | uint64 | long | int/long | uint64 | ulong | integer/string | Bignum |
| <a name="sfixed32" /> sfixed32 | Always four bytes. | int32 | int | int | int32 | int | integer | Bignum or Fixnum (as required) |
| <a name="sfixed64" /> sfixed64 | Always eight bytes. | int64 | long | int/long | int64 | long | integer/string | Bignum |
| <a name="bool" /> bool |  | bool | boolean | boolean | bool | bool | boolean | TrueClass/FalseClass |
| <a name="string" /> string | A string must always contain UTF-8 encoded or 7-bit ASCII text. | string | String | str/unicode | string | string | string | String (UTF-8) |
| <a name="bytes" /> bytes | May contain any arbitrary sequence of bytes. | string | ByteString | str | []byte | ByteString | string | String (ASCII-8BIT) |

