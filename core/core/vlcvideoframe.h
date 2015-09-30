#ifndef VLCVIDEOFRAME_H
#define VLCVIDEOFRAME_H

#include "array"

struct VlcVideoFrame
{
    /*!
        \brief VlcVideoFrame constructor.
        This construction ensures default data is set.
    */
    VlcVideoFrame();
    bool inited; /*!< initialisation status */
    unsigned int width; /*!< frame width */
    unsigned int height; /*!< frame height */
    unsigned int planeCount; /*!< plane count */

    std::array<unsigned char, 4> plane; /*!< plane data */

    int pitch[4]; /*!< pitch information */
    int visiblePitch[4]; /*!< visible pitch information */
    int lines[4]; /*!< lines count */
    int visibleLines[4]; /*!< visible lines count */
};

#endif // VLCVIDEOFRAME_H
