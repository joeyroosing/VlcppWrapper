#ifndef VLCMEDIA_H
#define VLCMEDIA_H

#include "vlcenums.h"

#include <string>

class VlcInstance;
struct VlcStats;
struct libvlc_event_t;
struct libvlc_event_manager_t;
struct libvlc_media_t;

class VlcMedia
{
public:
    /*!
        \brief VlcMedia constructor.
        This constructor creates a new media instance from a media location.
        \param location location of the media (std::string)
        \param localFile true, if media is local file (bool)
        \param instance main libvlc instance (VlcInstance *)
    */
    explicit VlcMedia(const std::string &location,
                      bool localFile,
                      VlcInstance *instance);

    /*!
        \brief VlcMedia constructor.
        This constructor creates a new media instance from a remote media location.
        Provided for convenience.
        \param location remote location of the media (std::string)
        \param instance main libvlc instance (VlcInstance *)
    */
    explicit VlcMedia(const std::string &location,
                      VlcInstance *instance);

    /*!
        \brief VlcMedia constructor.
        This constructor creates a new media instance from an existing one.
        \param media libvlc media item (libvlc_media_t *)
    */
    VlcMedia(libvlc_media_t *media);

    /*!
        \brief VlcMedia destructor
    */
    ~VlcMedia();

    /*!
        \brief libvlc media item
        \return libvlc media item (libvlc_media_t *)
    */
    libvlc_media_t *getNativeVlcMedia();

    /*!
        \brief Current media location
        \return std::string media location
    */
    std::string currentLocation() const;

    /*!
        \brief Get media stats
        \return VlcStats media stats object
    */
    VlcStats *getStats();

    /*!
        \brief Duplicate (provided for convenience)
        Apply duplicate options with desired mux but without transcoding.
        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \return QString output file
        \sa record()
    */
    std::string duplicate(const std::string &name,
                      const std::string &path,
                      const VlcEnums::Mux &mux);

    /*!
        \brief Duplicate (provided for convenience)
        Apply duplicate options with desired mux and transcoding (experimental).
        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param audioCodec audio codec (Vlc::AudioCodec)
        \param videoCodec video codec (Vlc::VideoCodec)
        \return QString output file
        \sa record()
    */
    std::string duplicate(const std::string &name,
                      const std::string &path,
                      const VlcEnums::Mux &mux,
                      const VlcEnums::AudioCodec &audioCodec,
                      const VlcEnums::VideoCodec &videoCodec);

    /*!
        \brief Duplicate (provided for convenience)
        Apply duplicate options with desired mux, transcoding
        and some other options (experimental).
        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param audioCodec audio codec (Vlc::AudioCodec)
        \param videoCodec video codec (Vlc::VideoCodec)
        \param bitrate video bitrate (int)
        \param fps frames per second (int)
        \param scale video scale (int)
        \return QString output file
        \sa record()
    */
    std::string duplicate(const std::string &name,
                      const std::string &path,
                      const VlcEnums::Mux &mux,
                      const VlcEnums::AudioCodec &audioCodec,
                      const VlcEnums::VideoCodec &videoCodec,
                      int bitrate,
                      int fps,
                      int scale);


    /*!
        \brief Merge
        Apply merge options with desired mux but without transcoding.
        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \return QString output file
    */
    std::string merge(const std::string &name,
                  const std::string &path,
                  const VlcEnums::Mux &mux);

    /*!
        \brief Record
        Apply recording options with desired mux but without transcoding.
        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param duplicate also duplicate on screen (bool)
        \return QString output file
    */
    std::string record(const std::string &name,
                   const std::string &path,
                   const VlcEnums::Mux &mux,
                   bool duplicate = false);

    /*!
        \brief Record
        Apply recording options with desired mux and transcoding (experimental).
        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param audioCodec audio codec (Vlc::AudioCodec)
        \param videoCodec video codec (Vlc::VideoCodec)
        \param duplicate also duplicate on screen (bool)
        \return QString output file
    */
    std::string record(const std::string &name,
                   const std::string &path,
                   const VlcEnums::Mux &mux,
                   const VlcEnums::AudioCodec &audioCodec,
                   const VlcEnums::VideoCodec &videoCodec,
                   bool duplicate = false);

    /*!
        \brief Record
        Apply recording options with desired mux, transcoding
        and some other options (experimental).
        \param name output file name (QString)
        \param path output path (QString)
        \param mux output mux (Vlc::Mux)
        \param audioCodec audio codec (Vlc::AudioCodec)
        \param videoCodec video codec (Vlc::VideoCodec)
        \param bitrate video bitrate (int)
        \param fps frames per second (int)
        \param scale video scale (int)
        \param duplicate also duplicate on screen (bool)
        \return QString output file
    */
    std::string record(const std::string &name,
                   const std::string &path,
                   const VlcEnums::Mux &mux,
                   const VlcEnums::AudioCodec &audioCodec,
                   const VlcEnums::VideoCodec &videoCodec,
                   int bitrate,
                   int fps,
                   int scale,
                   bool duplicate = false);

    /*!
        \brief Set program
        \param program program PID (int)
    */
    void setProgram(int program);

    /*!
        \brief Set media option
        \param option media option (QString)
    */
    void setOption(const std::string &option);

    /*!
        \brief Set media options
        \param options media options (QStringList)
    */
    void setOptions(const std::vector<std::string> &options);

public:
    /*!
        \brief Signal sent on meta change
        \param meta new meta
    */
    void metaChanged(const VlcEnums::Meta &meta);

    /*!
        \brief Signal sent on subitem added
        \param subitem subitem that was added
    */
    void subitemAdded(libvlc_media_t *subitem);

    /*!
        \brief Signal sent on duration change
        \param duration new duration
    */
    void durationChanged(int duration);

    /*!
        \brief Signal sent on parsed change
        \param status new parsed status
    */
    void parsedChanged(int status);

    /*!
        \brief Signal sent on freed
        \param media freed libvlc_media_t object
    */
    void freed(libvlc_media_t *media);

    /*!
        \brief Signal sent on state change
        \param state new state
    */
    void stateChanged(const VlcEnums::State &state);

private:
    void initMedia(const std::string &location,
                   bool localFile,
                   VlcInstance *instance);

    static void libvlc_callback(const libvlc_event_t *event,
                                void *data);

    void createCoreConnections();
    void removeCoreConnections();

    libvlc_media_t *_vlcMedia;
    libvlc_event_manager_t *_vlcEvents;

    std::string _currentLocation;
};

#endif // VLCMEDIA_H
