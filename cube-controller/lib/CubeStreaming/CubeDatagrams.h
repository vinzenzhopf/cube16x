/*
 * NetworkDefaults.h
 *
 * Created: 08.06.2023 14:26
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "LedCube16x.h"
#include "NativeEthernet.h"

const char* CUBE_DATAGRAM_VERSION = "Cube v0.1";

enum CubeDatagramType : uint16_t
{
    Discovery = 0x10,
    Info = 0x20,
    InfoResponse = 0x21,
    ErrorResponse = 0x22,
    AnimationStart = 0x30,
    AnimationStartAck = 0x31,
    AnimationEnd = 0x32,
    AnimationEndAck = 0x33,
    FrameData = 0x40,
    FrameDataAck = 0x41,
};

enum CubeErrorCode : uint16_t
{
    Ok = 0x00,
    PackageOrder = 0x10,
    FrameOrder = 0x11,
    UnknownPackage = 0x20
};

struct CubeDatagramHeader
{
    CubeDatagramType PayloadType;
    uint16_t PacketCount;
};

//Request Datagrams
struct InfoPayload
{
    char Version[32];
};

struct AnimationStartPayload
{
    uint32_t FrameTimeUs;
    char AnimationName[64];
    uint32_t CurrentTicks;
};

struct AnimationEndPayload
{
    uint32_t CurrentTicks;
};

struct FramePayload
{
    uint32_t FrameNumber;
    uint32_t FrameTimeUs;
    uint32_t CurrentTicks;
    buffer_t Data;
};

typedef union {
	InfoPayload asInfoPayload;
	AnimationStartPayload asAnimationStartPayload;
    AnimationEndPayload asAnimationEndPayload;
    FramePayload asFramePayload;
} request_payload_t;

struct request_datagram_t{
    CubeDatagramHeader header;
    request_payload_t payload;
};

const int DATAGRAM_BUFFER_SIZE = sizeof(request_datagram_t); 

typedef union {
    request_datagram_t asDatagram;
    char asBuffer[DATAGRAM_BUFFER_SIZE];
} request_datagram_buffer_t;

//Response Datagrams
struct InfoResponsePayload
{
    char Version[32];
    uint32_t LastFrameTimeUs;
    uint32_t CurrentTicks;
    CubeErrorCode ErrorCode;
    NetworkStreamAnimationStatus Status;
};

struct AnimationStartResponsePayload
{
    uint32_t CurrentTicks;
};

struct AnimationEndResponsePayload
{
    uint32_t CurrentTicks;
};

struct FrameResponsePayload
{
    uint32_t FrameNumber;
    uint32_t LastFrameTimeUs;
    uint32_t CurrentTicks;
    uint32_t ReceivedTicks;
    NetworkStreamAnimationStatus Status;
};

typedef union {
    InfoResponsePayload asInfoResponse;
    AnimationStartResponsePayload asAnimationStartResponse;
    AnimationEndResponsePayload asAnimationEndResponse;
    FrameResponsePayload asFrameResponse;
} response_payload_t;

struct response_datagram_t{
    CubeDatagramHeader header;
    response_payload_t payload;
};

const int RESPONSE_DATAGRAM_BUFFER_SIZE = sizeof(response_datagram_t); 

typedef union {
    response_datagram_t asDatagram;
    char asBuffer[RESPONSE_DATAGRAM_BUFFER_SIZE];
} response_datagram_buffer_t;