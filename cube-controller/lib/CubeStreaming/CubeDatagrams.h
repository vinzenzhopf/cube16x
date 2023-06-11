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

struct InfoPayload
{
    char Version[32];
};

struct InfoResponsePayload
{
    char Version[32];
    uint32_t MaxFrameTimeUs;
    uint32_t RuntimeMs;
    CubeErrorCode ErrorCode;
};

struct AnimationStartPayload
{
    uint32_t FrameTimeUs;
    char AnimationName[64];
};

struct FramePayload
{
    uint32_t FrameNumber;
    uint32_t FrameTimeUs;
    buffer_t Data;
};

typedef union {
	InfoPayload asInfoPayload;
	InfoResponsePayload asInfoResponse;
	AnimationStartPayload asAnimationStartPayload;
    FramePayload asFramePayload;
} payload_t;

struct datagram_t{
    CubeDatagramHeader header;
    payload_t payload;
};

const int DATAGRAM_BUFFER_SIZE = sizeof(datagram_t); 

typedef union {
    datagram_t asDatagram;
    char asBuffer[DATAGRAM_BUFFER_SIZE];
} datagram_buffer_t;

