#ifndef VLCSTATS
#define VLCSTATS

/*!
    \struct VlcStats Stats.h
    \ingroup core
    \brief Statistics container
    A direct copy of libvlc stats object to remove dependency to libvlc.
*/
struct VlcStats
{
    bool valid; /*!< VLC stats success status */
    int read_bytes; /*!< libVLC stats */
    float input_bitrate; /*!< libVLC stats */
    int demux_read_bytes; /*!< libVLC stats */
    float demux_bitrate; /*!< libVLC stats */
    int demux_corrupted; /*!< libVLC stats */
    int demux_discontinuity; /*!< libVLC stats */
    int decoded_video; /*!< libVLC stats */
    int decoded_audio; /*!< libVLC stats */
    int displayed_pictures; /*!< libVLC stats */
    int lost_pictures; /*!< libVLC stats */
    int played_abuffers; /*!< libVLC stats */
    int lost_abuffers; /*!< libVLC stats */
    int sent_packets; /*!< libVLC stats */
    int sent_bytes; /*!< libVLC stats */
    float send_bitrate; /*!< libVLC stats */
};

#endif // VLCSTATS

