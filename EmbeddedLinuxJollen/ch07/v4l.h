/*
 * http://www.jollen.org
 *
 * v4l.c - the video4linux user space library
 * by 2001 Jollen <jollen@o3.net>
 */
#ifndef _V4L_H_
#define _V4L_H_

#include <sys/types.h>
#include <linux/videodev.h>

#define PAL_WIDTH	768
#define PAL_HEIGHT	576
#define CIF_WIDTH	352
#define CIF_HEIGHT	288 
#define NTSC_WIDTH	320
#define NTSC_HEIGHT	240

#define FALSE	0
#define TRUE	-1

struct _v4l_struct 
{
   int fd;
   struct video_capability capability;
   struct video_buffer buffer;
   struct video_window window;
   struct video_channel channel[8];
   struct video_picture picture;
   struct video_tuner tuner;
   struct video_audio audio[8];
   struct video_mmap mmap;
   struct video_mbuf mbuf;
   unsigned char *map;
   int frame_current;
   int frame_using[VIDEO_MAX_FRAME];
};

struct _v4l_attr {
   long nr;
   const char *name;
};

typedef struct _v4l_struct v4l_device;
typedef struct _v4l_attr V4LATTR;

extern int v4l_open(char *, v4l_device *);
extern int v4l_close(v4l_device *);
extern int v4l_get_capability(v4l_device *);
extern int v4l_set_norm(v4l_device *, int);
extern int v4l_get_channels(v4l_device *);
extern int v4l_get_audios(v4l_device *);
extern int v4l_get_picture(v4l_device *);
extern int v4l_grab_init(v4l_device *, int, int);
extern int v4l_grab_frame(v4l_device *, int);
extern int v4l_grab_sync(v4l_device *);
extern int v4l_mmap_init(v4l_device *);
extern int v4l_get_mbuf(v4l_device *);
extern int v4l_get_picture(v4l_device *);
extern int v4l_set_picture(v4l_device *, int, int, int, int, int);
extern int v4l_grab_picture(v4l_device *, unsigned int);
extern int v4l_set_buffer(v4l_device *);
extern int v4l_get_buffer(v4l_device *);
extern int v4l_switch_channel(v4l_device *, int);
extern int v4l_set_palette(v4l_device *, int, int);

#endif
