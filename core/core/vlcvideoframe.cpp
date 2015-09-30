#include "vlcvideoframe.h"

VlcVideoFrame::VlcVideoFrame()
    : inited(false), width(0), height(0)
{
    for (int i = 0; i < 4; ++i) {
        pitch[i] = 0;
        visiblePitch[i] = 0;
        lines[i] = 0;
        visibleLines[i] = 0;
    }
}

