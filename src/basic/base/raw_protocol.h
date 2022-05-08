#pragma once

#include <stdint.h>

// 二进制协议头部，40字节
typedef struct raw_protocol_header_s {
	uint32_t magic_number;			///< 魔术字
	uint8_t version;				///< 协议版本
	uint8_t protocol;				///< 正文协议格式：json,xml,raw,protobuf,http
	uint8_t cmd;					///< 命令：ack,req,heartbeat
	uint8_t source;					///< 消息来源：0-同进程，1-子系统，2-其他进程，3-设备，4-外部网络
	uint8_t compress;				///< 压缩算法：未压缩,zlib,gzip
	uint8_t extend_flag;			///< 头部扩展标记
	uint16_t extend_len;			///< 扩展头部长度
	uint32_t seq;					///< 包序号
	uint32_t crc32;					///< 校验码(包括扩展头部)
	uint32_t timestamp_high;		///< 时间戳高位
	uint32_t timestamp_low;			///< 时间戳低位
	uint32_t timestamp_mill;		///< 时间戳，毫秒
	uint32_t res;					///< 保留4字节
	uint32_t len;					///< 正文长度(包括扩展头部)
} raw_protocol_header_t;
