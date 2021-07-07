#pragma once

class MockupWrapper {
public:
	virtual void InitIOPorts() = 0;
	virtual void OutputEnable() = 0;
	virtual void OutputDisable() = 0;
	virtual void TriggerColumnClock() = 0;
	virtual void TriggerPlaneClock() = 0;
	virtual void TriggerColumnSto() = 0;
	virtual void TriggerPlaneSto() = 0;
	virtual void TriggerSto() = 0;
	virtual void InitDataDirections() = 0;
};

void set_target(MockupWrapper* wrapper);