#include "MockupWrapper.h"
#include "../../MainControllerSharedResources/MockupFunctions.h"

#include <memory>

namespace {
	MockupWrapper* target(nullptr);
}

void set_target(MockupWrapper* wrapper) {
	target = wrapper;
}

void TestDevice_InitDataDirections() {
	target->InitDataDirections();
}
void TestDevice_InitIOPorts() {
	target->InitIOPorts();
}
void TestCube_OutputEnable() {
	target->OutputEnable();
}
void TestCube_OutputDisable() {
	target->OutputDisable();
}
void TestCube_TriggerColumnClock() {
	target->TriggerColumnClock();
}
void TestCube_TriggerPlaneClock() {
	target->TriggerPlaneClock();
}
void TestCube_TriggerColumnSto() {
	target->TriggerColumnSto();
}
void TestCube_TriggerPlaneSto() {
	target->TriggerPlaneSto();
}
void TestCube_TriggerSto() {
	target->TriggerSto();
}