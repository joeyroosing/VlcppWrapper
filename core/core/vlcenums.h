#ifndef VLCENUMS_H
#define VLCENUMS_H

#include "sizef.h"

#include <vector>
#include <string>

class VlcEnums
{
public:

    // Enums
    /*!
           \enum ActionsType
           \brief Actions types identifiers
       */
    enum ActionsType {
        AudioTrack,
        Subtitles,
        VideoTrack,
        Other
    };

    /*!
           \enum AudioChannel
           \brief Audio channel options
       */
    enum AudioChannel {
        AudioChannelError = -1,
        Stereo = 1,
        RStereo = 2,
        Left = 3,
        Right = 4,
        Dolbys = 5
    };

    /*!
           \enum AudioCodec
           \brief Audio codecs list
       */
    enum AudioCodec {
        NoAudio,
        MPEG2Audio,
        MP3,
        MPEG4Audio,
        Vorbis,
        Flac
    };

    /*!
           \enum AudioOutput
           \brief Audio outputs list
       */
    enum AudioOutput {
        DefaultAout
    };

    /*!
           \enum Deinterlacing
           \brief Supported deinterlacing modes
       */
    enum Deinterlacing {
        Disabled,
        Discard,
        Blend,
        Mean,
        Bob,
        Linear,
        X,
        Yadif,
        Yadif2x,
        Phospor,
        IVTC
    };

    /*!
           \enum Meta
           \brief Supported meta types
       */
    enum Meta {
        Title,
        Artist,
        Genre,
        Copyright,
        Album,
        TrackNumber,
        Description,
        Rating,
        Date,
        Setting,
        URL,
        Language,
        NowPlaying,
        Publisher,
        EncodedBy,
        ArtworkURL,
        TrackID
    };

    /*!
           \enum Mux
           \brief Recording output file mux
       */
    enum Mux {
        TS,
        PS,
        MP4,
        OGG,
        AVI
    };

    /*!
           \enum PlaybackMode
           \brief Playlist playback mode
       */
    enum PlaybackMode {
        DefaultPlayback,
        Loop,
        Repeat
    };

    /*!
           \enum Ratio
           \brief Supported aspect and crop ratios
       */
    enum Ratio {
        Original,
        R_16_9,
        R_16_10,
        R_185_100,
        R_221_100,
        R_235_100,
        R_239_100,
        R_4_3,
        R_5_4,
        R_5_3,
        R_1_1
    };

    /*!
           \enum Scale
           \brief Supported scales
       */
    enum Scale {
        NoScale,
        S_1_05,
        S_1_1,
        S_1_2,
        S_1_3,
        S_1_4,
        S_1_5,
        S_1_6,
        S_1_7,
        S_1_8,
        S_1_9,
        S_2_0
    };

    /*!
           \enum State
           \brief VLC-Qt playback states
       */
    enum State {
        Idle,
        Opening,
        Buffering,
        Playing,
        Paused,
        Stopped,
        Ended,
        Error
    };

    /*!
           \enum VideoCodec
           \brief Video codecs list
       */
    enum VideoCodec {
        NoVideo,
        MPEG2Video,
        MPEG4Video,
        H264,
        Theora
    };

    /*!
           \enum VideoOutput
           \brief Video outputs list
       */
    enum VideoOutput {
#if defined(Q_OS_LINUX)
        X11,
        XVideo,
        GLX,
#elif defined(Q_OS_WIN32)
        DirectX,
        Direct3D,
        OpenGL,
#endif
        DefaultVout
    };

    // methods
    /*!
        \brief Audio codecs strings
        \return audio codecs strings (std::vector<std::string>)
    */
    static std::vector<std::string> getAudioCodec();

    /*!
        \brief Audio outputs strings
        \return audio outputs strings (std::vector<std::string>)
    */
    static std::vector<std::string> getAudioOutput();

    /*!
        \brief Audio outputs strings in readable form
        \return audio outputs strings (std::vector<std::string>)
    */
    static std::vector<std::string> getAudioOutputHuman();

    /*!
        \brief Deinterlacing modes strings
        \return deinterlacing strings (std::vector<std::string>)
    */
    static std::vector<std::string> getDeinterlacing();

    /*!
        \brief Mux strings
        \return mux strings (std::vector<std::string>)
    */
    static std::vector<std::string> getMux();

    /*!
        \brief Aspect and crop ratios strings
        \return ratios strings (std::vector<std::string>)
    */
    static std::vector<std::string> getRatio();

    /*!
        \brief Aspect and crop ratios strings in readable form
        \return ratios strings (std::vector<std::string>)
    */
    static std::vector<std::string> getRatioHuman();


    /*!
        \brief Aspect and crop ratios converter to QSizeF
        \param ratio aspect or crop ratio (Vlc::Ratio)
        \return two-dimensional object using floating point precision (QSizeF)
    */
    static SizeF getRatioSize(const VlcEnums::Ratio &ratio);

    /*!
        \brief Scale floats
        \return scale floats (std::vector<float>)
    */
    static std::vector<float> getScale();

    /*!
        \brief Video codecs strings
        \return video codecs strings (std::vector<std::string>)
    */
    static std::vector<std::string> getVideoCodec();

    /*!
        \brief Video outputs strings
        \return video outputs strings (std::vector<std::string>)
    */
    static std::vector<std::string> getVideoOutput();

    /*!
        \brief Video outputs strings in readable form
        \return video outputs strings (std::vector<std::string>)
    */
    static std::vector<std::string> getVideoOutputHuman();
};

#endif // VLCENUMS_H
