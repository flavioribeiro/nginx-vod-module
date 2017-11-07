#if (VOD_HAVE_LIB_AV_CODEC)
#include <libavcodec/avcodec.h>

int convert_and_cut(char *file, float starttime, float endtime) {
    AVFrame *frame;
    AVPacket inPacket, outPacket;

    if(avio_open(&outFormatContext->pb, file, AVIO_FLAG_WRITE) < 0) {
        fprintf(stderr, "convert(): cannot open out file\n");
        return 0;
    }

    // seek to the start time you wish.
    // BEGIN
    AVRational default_timebase;
    default_timebase.num = 1;
    default_timebase.den = AV_TIME_BASE;

    // suppose you have access to the "inVideoStream" of course
    int64_t starttime_int64 = av_rescale_q((int64_t)( starttime * AV_TIME_BASE ), default_timebase, inVideoStream->time_base);
    int64_t endtime_int64 = av_rescale_q((int64_t)( endtime * AV_TIME_BASE ), default_timebase, inVideoStream->time_base);

    if(avformat_seek_file(inFormatContext, inVideoStreamIndex, INT64_MIN, starttime_int64, INT64_MAX, 0) < 0) {
        // error... do something...
        return 0; // usually 0 is used for success in C, but I am following your code.
    }

    avcodec_flush_buffers( inVideoStream->codec );
    // END

    avformat_write_header(outFormatContext, NULL);
    frame = avcodec_alloc_frame();
    av_init_packet(&inPacket);

    // you used avformat_seek_file() to seek CLOSE to the point you want... in order to give precision to your seek,
    // just go on reading the packets and checking the packets PTS (presentation timestamp) 
    while(av_read_frame(inFormatContext, &inPacket) >= 0) {
        if(inPacket.stream_index == inVideoStreamIndex) {
            avcodec_decode_video2(inCodecContext, frame, &frameFinished, &inPacket);
            // this line guarantees you are getting what you really want.
            if(frameFinished && frame->pkt_pts >= starttime_int64 && frame->pkt_pts <= endtime_int64) {
                av_init_packet(&outPacket);
                avcodec_encode_video2(outCodecContext, &outPacket, frame, &outputed);
                if(outputed) {
                    if (av_write_frame(outFormatContext, &outPacket) != 0) {
                        fprintf(stderr, "convert(): error while writing video frame\n");
                        return 0;
                    }
                }
                av_free_packet(&outPacket);
            }

            // exit the loop if you got the frames you want.
            if(frame->pkt_pts > endtime_int64) {
                break;
            }
        }
    }

    av_write_trailer(outFormatContext);
    av_free_packet(&inPacket);
    return 1;
}

#endif // (VOD_HAVE_LIB_AV_CODEC)
