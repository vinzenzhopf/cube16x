/*
 * FireworksAnimation.h
 *
 * Created: 07.11.2021
 * Author: Vinzenz hopf (happyfreak.de)
 */ 

#pragma once

#include "CubeCore.h"
#include "Animations/FrameGenerator.h"
#include "FrameBuffer.h"
#include "Base/ExecuteState.h"
#include <glm/glm.hpp>

class FireworksAbstractProjectile{
    protected:
        glm::vec3 position;
        glm::vec3 v;
        glm::vec3 a;
        int timeToLife;
        bool alive;
    public:
        FireworksAbstractProjectile();
        virtual ~FireworksAbstractProjectile() = default;
        virtual bool initialize(ExecuteState executeState, glm::vec3 pos, glm::vec3 v, glm::vec3 a, int ttl) = 0;
        virtual bool update(ExecuteState executeState, uint32_t const currentTicks) = 0;
        virtual bool draw(ExecuteState executeState, FrameBuffer *buffer, uint32_t const currentTicks) = 0;
        bool isAlive();
};

class FireworksProjectile final : FireworksAbstractProjectile{
    protected:
        glm::vec3 position;
        glm::vec3 v;
        glm::vec3 a;
        int timeToLife;
    public:
        FireworksProjectile();
        ~FireworksProjectile() = default;
        bool initialize(ExecuteState executeState, glm::vec3 pos, glm::vec3 v, glm::vec3 a, int ttl) override;
        bool update(ExecuteState executeState, uint32_t const currentTicks) override;
        bool draw(ExecuteState executeState, FrameBuffer *buffer, uint32_t const currentTicks) override;
};

class FireworksCharge final : FireworksAbstractProjectile{
    public:
        static const int MaxProjectileCount = 16;
    protected:
        FireworksProjectile parts[MaxProjectileCount];
    public:
        FireworksCharge();
        ~FireworksCharge() = default;
        bool initialize(ExecuteState executeState, glm::vec3 pos, glm::vec3 v, glm::vec3 a, int ttl) override;
        bool update(ExecuteState executeState, uint32_t const currentTicks) override;
        bool draw(ExecuteState executeState, FrameBuffer *buffer, uint32_t const currentTicks) override;
};

class FireworksAnimation : public FrameGenerator {
    public:
        static const int MaxChargeCount = 4;
        const glm::vec3 G;
    protected:
    private:
        FrameBuffer tmpBuffer;
        uint32_t cycleCount;
        uint8_t planeIndex;
        FireworksCharge charges[MaxChargeCount];
	public:
        FireworksAnimation();
        virtual ~FireworksAnimation() = default;

        void initializeFrameSequence(uint32_t currentTicks) override;
        void startFrame(buffer_t *nextFrame, uint32_t const currentTicks) override;
        bool generateCyclicBase(uint32_t const currentTicks) override;
        void endFrame(uint32_t const currentTicks) override;

    protected:
    private:  
};