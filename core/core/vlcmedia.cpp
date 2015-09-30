#include "vlcmedia.h"

#include "vlc/vlc.h"

#include "vlcinstance.h"
#include "vlcerror.h"
#include "vlcstats.h"
#include "vlccommon.h"

#include "sstream"
#include "algorithm"

VlcMedia::VlcMedia(const std::string &location,
                   bool localFile,
                   VlcInstance *instance)
{
    initMedia(location, localFile, instance);
}

VlcMedia::VlcMedia(const std::string &location, VlcInstance *instance)
{
    initMedia(location, false, instance);
}

VlcMedia::VlcMedia(libvlc_media_t *media)
{
    // Create a new libvlc media descriptor from existing one
    _vlcMedia = libvlc_media_duplicate(media);

    VlcError::showErrorMessage();
}

VlcMedia::~VlcMedia()
{
    removeCoreConnections();
    libvlc_media_release(_vlcMedia);
    VlcError::showErrorMessage();
}

libvlc_media_t* VlcMedia::getNativeVlcMedia()
{
    return _vlcMedia;
}

void VlcMedia::initMedia(const std::string &location, bool localFile, VlcInstance *instance)
{
    _currentLocation = location;
    std::string locationNativeSeparators = VlcCommon::toNativeSeparators(location);
    // Create a new libvlc media descriptor from location
    if (localFile) {
        _vlcMedia = libvlc_media_new_path(instance->getNativeVlcInstance(), locationNativeSeparators.data());
    } else {
        _vlcMedia = libvlc_media_new_location(instance->getNativeVlcInstance(), locationNativeSeparators.data());
    }
    _vlcEvents = libvlc_media_event_manager(_vlcMedia);

    createCoreConnections();

    std::cout << "libvlc" << "Media:" << location << "Local:" << localFile;
}

void VlcMedia::createCoreConnections()
{
    std::vector<libvlc_event_e> list;
    list.push_back(libvlc_MediaMetaChanged);
    list.push_back(libvlc_MediaSubItemAdded);
    list.push_back(libvlc_MediaDurationChanged);
    list.push_back(libvlc_MediaParsedChanged);
    list.push_back(libvlc_MediaFreed);
    list.push_back(libvlc_MediaStateChanged);

    for (const auto &event : list) {
        libvlc_event_attach(_vlcEvents, event, libvlc_callback, this);
    }
}

void VlcMedia::removeCoreConnections()
{
    std::vector<libvlc_event_e> list;
    list.push_back(libvlc_MediaMetaChanged);
    list.push_back(libvlc_MediaSubItemAdded);
    list.push_back(libvlc_MediaDurationChanged);
    list.push_back(libvlc_MediaParsedChanged);
    list.push_back(libvlc_MediaFreed);
    list.push_back(libvlc_MediaStateChanged);

    for (const libvlc_event_e &event : list) {
        libvlc_event_detach(_vlcEvents, event, libvlc_callback, this);
    }
}

std::string VlcMedia::currentLocation() const
{
    return _currentLocation;
}

VlcStats *VlcMedia::getStats()
{
    libvlc_media_stats_t *coreStats = new libvlc_media_stats_t;

    VlcStats *stats = new VlcStats;
    stats->valid = (libvlc_media_get_stats(_vlcMedia, coreStats) != 0);

    stats->read_bytes = coreStats->i_read_bytes;
    stats->input_bitrate = coreStats->f_input_bitrate;
    stats->demux_read_bytes = coreStats->i_demux_read_bytes;
    stats->demux_bitrate = coreStats->f_demux_bitrate;
    stats->demux_corrupted = coreStats->i_demux_corrupted;
    stats->demux_discontinuity = coreStats->i_demux_discontinuity;
    stats->decoded_video = coreStats->i_decoded_video;
    stats->decoded_audio = coreStats->i_decoded_audio;
    stats->displayed_pictures = coreStats->i_displayed_pictures;
    stats->lost_pictures = coreStats->i_lost_pictures;
    stats->played_abuffers = coreStats->i_played_abuffers;
    stats->lost_abuffers = coreStats->i_lost_abuffers;
    stats->sent_packets = coreStats->i_sent_packets;
    stats->sent_bytes = coreStats->i_sent_bytes;
    stats->send_bitrate = coreStats->f_send_bitrate;

    return stats;
}

std::string VlcMedia::duplicate(const std::string &name,
                            const std::string &path,
                            const VlcEnums::Mux &mux)
{
    return record(name, path, mux, true);
}

std::string VlcMedia::duplicate(const std::string &name,
                            const std::string &path,
                            const VlcEnums::Mux &mux,
                            const VlcEnums::AudioCodec &audioCodec,
                            const VlcEnums::VideoCodec &videoCodec)
{
    return record(name, path, mux, audioCodec, videoCodec, true);
}

std::string VlcMedia::duplicate(const std::string &name,
                            const std::string &path,
                            const VlcEnums::Mux &mux,
                            const VlcEnums::AudioCodec &audioCodec,
                            const VlcEnums::VideoCodec &videoCodec,
                            int bitrate,
                            int fps,
                            int scale)
{
    return record(name, path, mux, audioCodec, videoCodec, bitrate, fps, scale, true);
}

std::string VlcMedia::merge(const std::string &name,
                        const std::string &path,
                        const VlcEnums::Mux &mux)
{
    std::string option1, option2, parameters;
    std::string l = VlcCommon::toNativeSeparators(path + "/" + name);

    std::stringstream paramsFmt;
    paramsFmt << "gather:std{access=file,mux="
              << VlcEnums::getMux()[mux]
              << l
              << "."
              << VlcEnums::getMux()[mux];

    option1 = ":sout-keep";

    std::stringstream opt2Format;
    opt2Format << ":sout=#" << paramsFmt.str();
    option2 = opt2Format.str();

    setOption(option1);
    setOption(option2);

    VlcError::showErrorMessage();

    return l + "." + VlcEnums::getMux()[mux];
}

std::string VlcMedia::record(const std::string &name,
                         const std::string &path,
                         const VlcEnums::Mux &mux,
                         bool duplicate)
{
    std::string option1, option2;
    std::string l = VlcCommon::toNativeSeparators(path + "/" + name);

    std::stringstream paramsFmt;
    paramsFmt << "std{access=file,mux="
              << VlcEnums::getMux()[mux]
              << l
              << "."
              << VlcEnums::getMux()[mux];

    std::stringstream opt2Format;
    if (duplicate) {
        opt2Format << ":sout=#duplicate{dst=display,dst=\""
                   << paramsFmt.str()
                   << "\"}";
    } else {
        opt2Format << ":sout=#"
                   << paramsFmt.str();
    }

    option1 = ":sout-all";
    option2 = opt2Format.str();

    setOption(option1);
    setOption(option2);

    VlcError::showErrorMessage();

    return l + "." + VlcEnums::getMux()[mux];
}

std::string VlcMedia::record(const std::string &name,
                         const std::string &path,
                         const VlcEnums::Mux &mux,
                         const VlcEnums::AudioCodec &audioCodec,
                         const VlcEnums::VideoCodec &videoCodec,
                         bool duplicate)
{
    std::string option1, option2;
    std::string l = VlcCommon::toNativeSeparators(path + "/" + name);

    std::stringstream paramsFmt;
    paramsFmt << "transcode{vcodec="
              << VlcEnums::getVideoCodec()[videoCodec]
              << ",acodec="
              << VlcEnums::getAudioCodec()[audioCodec]
              << "}:std{access=file,mux="
              << VlcEnums::getMux()[mux]
              << ",dst='"
              << l
              << "."
              << VlcEnums::getMux()[mux]
              << "'}";

    std::stringstream opt2Format;
    if (duplicate) {
        opt2Format << ":sout=#duplicate{dst=display,dst=\""
                   << paramsFmt.str()
                   << "\"}";
    } else {
        opt2Format << ":sout=#" << paramsFmt.str();
    }

    option1 = ":sout-all";
    option2 = opt2Format.str();

    setOption(option1);
    setOption(option2);

    VlcError::showErrorMessage();

    return l + "." + VlcEnums::getMux()[mux];
}

std::string VlcMedia::record(const std::string &name,
                         const std::string &path,
                         const VlcEnums::Mux &mux,
                         const VlcEnums::AudioCodec &audioCodec,
                         const VlcEnums::VideoCodec &videoCodec,
                         int bitrate,
                         int fps,
                         int scale,
                         bool duplicate)
{
    std::string option1, option2;
    std::string l = VlcCommon::toNativeSeparators(path + "/" + name);

    std::stringstream paramsFmt;
    paramsFmt << "transcode{vcodec="
              << VlcEnums::getVideoCodec()[videoCodec]
              << ",vb="
              << bitrate
              << ",fps="
              << fps
              << ",scale"
              << scale
              << ",acodec="
              << VlcEnums::getAudioCodec()[audioCodec]
              << "}:std{access=file,mux="
              << VlcEnums::getMux()[mux]
              << ",dst='"
              << l
              << "."
              << VlcEnums::getMux()[mux]
              << "'}";

    std::stringstream opt2Format;
    if (duplicate) {
        opt2Format << ":sout=#duplicate{dst=display,dst=\""
                   << paramsFmt.str()
                   << "\"}";
    } else {
        opt2Format << ":sout=#" << paramsFmt.str();
    }

    option1 = ":sout-all";
    option2 = opt2Format.str();

    setOption(option1);
    setOption(option2);

    VlcError::showErrorMessage();

    return l + "." + VlcEnums::getMux()[mux];
}

void VlcMedia::setProgram(int program)
{
    std::string option = "program=" + program;
    setOption(option);
}

void VlcMedia::setOption(const std::string &option)
{
    libvlc_media_add_option(_vlcMedia, option.data());
    VlcError::showErrorMessage();
}

void VlcMedia::setOptions(const std::vector<std::string> &options)
{
    for (std::string option : options) {
         libvlc_media_add_option(_vlcMedia, option.data());
    }
    VlcError::showErrorMessage();
}

void VlcMedia::libvlc_callback(const libvlc_event_t *event,
                               void *data)
{
    VlcMedia *core = (VlcMedia *)data;

    switch(event->type) {
    case libvlc_MediaMetaChanged:
        core->metaChanged(VlcEnums::Meta(event->u.media_meta_changed.meta_type));
        break;
    case libvlc_MediaSubItemAdded:
        core->subitemAdded(event->u.media_subitem_added.new_child);
        break;
    case libvlc_MediaDurationChanged:
        core->durationChanged(event->u.media_duration_changed.new_duration);
        break;
    case libvlc_MediaParsedChanged:
        core->parsedChanged(event->u.media_parsed_changed.new_status);
        break;
    case libvlc_MediaFreed:
        core->freed(event->u.media_freed.md);
        break;
    case libvlc_MediaStateChanged:
        core->stateChanged(VlcEnums::State(event->u.media_state_changed.new_state));
        break;
    default:
        break;
    }
}

