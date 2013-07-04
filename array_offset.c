#include <stdio.h>
const char *g_tMediaPrarmName[] =
{
    "#imprinttimestamp"  , "#usespecifictitle"      , "#text"           , "#codectype"      ,
    "#resolution"        , "#preset"                , "#rotate"         ,
    "#h264_intraperiod"  , "#h264_ratecontrolmode"  , "#h264_quant"     , "#h264_qvalue"    ,
    "#h264_qpercent"     , "#h264_bitrate"          , "#h264_maxframe"  , "#h264_profile"   ,
    "#mpeg4_intraperiod" , "#mpeg4_ratecontrolmode" , "#mpeg4_quant"    , "#mpeg4_qvalue"   ,
    "#mpeg4_qpercent"    , "#mpeg4_bitrate"         , "#mpeg4_maxframe" , "#mpeg4_profile"  ,
    "#mjpeg_quant"       , "#mjpeg_qvalue"          , "#mjpeg_qpercent" , "#mjpeg_maxframe" ,
    NULL
};

int main(int argc, const char *argv[])
{
    printf("%s\n", g_tMediaPrarmName[1]+1);
    return 0;
}
