#include "../PlatformWrapper.hpp"
#include "CoreInterlayer-CPP-Interface.h"

using namespace Anyon;

void PlatformWrapper::SetInterlayerInstanceId(/*CoreInterlayer*/void *id)
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
