#include "../PlatformWrapper.hpp"
#include "EngineInterlayer-CPP-Interface.h"

using namespace AGE;

void PlatformWrapper::SetInterlayerInstanceId(/*EngineInterlayer*/void *id)
{
    this->interlayerId = id;
}

void PlatformWrapper::ToggleCursorVisiblity(bool visible)
{
    ::ToggleCursorVisiblity(interlayerId, visible);
}

void PlatformWrapper::ReconfigureWindow()
{
    ::ReconfigureWindow(interlayerId);
}

void PlatformWrapper::FatalAlert(const char *message)
{
    ::FatalAlert(interlayerId, message);
}
