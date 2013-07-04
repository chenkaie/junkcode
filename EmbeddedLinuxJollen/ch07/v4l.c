/*
 * http://www.jollen.org
 *
 * v4l.c - the video4linux user space library
 * by 2001 Jollen <jollen@o3.net>
 */
#include <stdio.h>
#include <unistd.h>
#include <error.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <linux/videodev.h>
#include "v4l.h"

#define DEFAULT_DEVICE "/dev/video0"

int v4l_open(char *dev, v4l_device *vd)
{
   if (!dev)
      dev = DEFAULT_DEVICE;

   if ((vd->fd = open(dev, O_RDWR)) < 0) {
      perror("v4l_open:");
      return -1;
   }

   if (v4l_get_capability(vd))
      return -1;

   if (v4l_get_picture(vd))
      return -1;

   return 0;
}

int v4l_grab_picture(v4l_device *vd, unsigned int size)
{
   if (read(vd->fd, &(vd->map), size) == 0) return -1;
   return 0;
}

int v4l_get_capability(v4l_device *vd)
{
   if (ioctl(vd->fd, VIDIOCGCAP, &(vd->capability)) < 0) {
      perror("v4l_get_capability:");
      return -1;
   }
   return 0;
}

/*
   norm: VIDEO_MODE_PAL | VIDEO_MODE_NTSC | VIDEO_MODE_SECAM | VIDEO_MODE_AUTO
   (see videodev.h)
*/
int v4l_set_norm(v4l_device *vd, int norm) 
{
   int i;

   for (i = 0; i < vd->capability.channels; i++) {
      vd->channel[i].norm = norm;
      //vd->channel[i].type = VIDEO_TYPE_TV;	//default (VIDEO_TYPE_TV | VIDEO_TYPE_CAMERA)
   }

   if (v4l_get_capability(vd)) {
      perror("v4l_set_norm");
      return -1;
   }
   if (v4l_get_picture(vd)) {
      perror("v4l_set_norm");
   }
   return 0;
}

int v4l_get_channels(v4l_device *vd)
{
   int i;

   for (i = 0; i < vd->capability.channels; i++) {
      vd->channel[i].channel = i;
   
      if (ioctl(vd->fd, VIDIOCGCHAN, &(vd->channel[i])) < 0) {
         perror("v4l_get_channel:");
         return -1;
      }
   }
   return 0;
}

/*
 * v4l_switch_channel - select (switch) the video source
 *
 * c: the channel number
 */
int v4l_switch_channel(v4l_device *vd, int c)
{
   if (ioctl(vd->fd, VIDIOCSCHAN, &(vd->channel[c])) < 0) {
      perror("v4l_switch_channel:");
      return -1;
   }
   return 0;
}

int v4l_get_audios(v4l_device *vd)
{
   int i;

   for (i = 0; i < vd->capability.audios; i++) {
      vd->audio[i].audio = i;
   
      if (ioctl(vd->fd, VIDIOCGAUDIO, &(vd->audio[i])) < 0) {
         perror("v4l_get_audio:");
         return -1;
      }
   }
   return 0;
}

int v4l_get_picture(v4l_device *vd)
{
   if (ioctl(vd->fd, VIDIOCGPICT, &(vd->picture)) < 0) {
      perror("v4l_get_picture");
      return -1;
   }
   return 0;
}

/* ...may be not necessarily... */
int v4l_set_picture(v4l_device *vd, int br, int hue, int col, int cont, 
                    int white)
{
   if (br) vd->picture.brightness = br;
   if (hue) vd->picture.hue = hue;
   if (col) vd->picture.colour = col;
   if (cont) vd->picture.contrast = cont;
   if (white) vd->picture.whiteness = white;

   if(ioctl(vd->fd, VIDIOCSPICT, &(vd->picture)) < 0) {
      perror("v4l_set_picture");
      return -1;
   }

   return 0;
}

int v4l_close(v4l_device *vd)
{
   close(vd->fd);
   return 0;
}

int v4l_get_mbuf(v4l_device *vd)
{
   if (ioctl(vd->fd, VIDIOCGMBUF, &(vd->mbuf)) < 0) {
      perror("v4l_get_mbuf");
      return -1;
   }
   return 0;
}

int v4l_mmap_init(v4l_device *vd)
{
   //vd->mbuf.size = 0x151000;
   //vd->mbuf.offsets[0] = 0;

   if (v4l_get_mbuf(vd) < 0)
      return -1;

   if ((vd->map = mmap(0, vd->mbuf.size, PROT_READ|PROT_WRITE, MAP_SHARED, vd->fd, 0)) < 0) {
      perror("v4l_mmap_init:mmap");
      return -1;
   }
   return 0;
}

/*
 * v4l_grab_init - initalizate mmap buffer
 *
 * width: width of mmap's buffer
 * height: width of mmap's buffer
 */
int v4l_grab_init(v4l_device *vd, int width, int height)
{
   vd->mmap.width = width; //width;
   vd->mmap.height = height; //height;
   vd->mmap.format = vd->picture.palette; 

   vd->frame_current = 0;
   vd->frame_using[0] = FALSE;
   vd->frame_using[1] = FALSE;
   
   return v4l_grab_frame(vd, 0);
}

/*
 * v4l_grab_frame - activate capturing
 *
 * frame: frame number to store image data
 */
int v4l_grab_frame(v4l_device *vd, int frame)
{
   if (vd->frame_using[frame]) {
      fprintf(stderr, "v4l_grab_frame: frame %d is already used.\n", frame);
      return -1;
   }

   vd->mmap.frame = frame;
   if (ioctl(vd->fd, VIDIOCMCAPTURE, &(vd->mmap)) < 0) {
      perror("v4l_grab_frame");
      return -1;
   }
   vd->frame_using[frame] = TRUE;
   vd->frame_current = frame;
   return 0;
}

int v4l_grab_sync(v4l_device *vd) 
{
   if (ioctl(vd->fd, VIDIOCSYNC, &(vd->frame_current)) < 0) {
      perror("v4l_grab_sync");
   }
   vd->frame_using[vd->frame_current] = FALSE;
   return 0;
}

int v4l_get_buffer(v4l_device *vd)
{
   if (ioctl(vd->fd, VIDIOCGFBUF, &(vd->buffer)) < 0) {
      perror("v4l_get_buffer");
   }
   return 0;
}

int v4l_set_buffer(v4l_device *vd)
{
   if (ioctl(vd->fd, VIDIOCSFBUF, &(vd->buffer)) < 0) {
      perror("v4l_set_buffer");
      return -1;
   }
   return 0;
}

int v4l_set_palette(v4l_device *vd, int pal, int dep)
{
   vd->picture.palette = pal;
   vd->picture.depth = dep;

   vd->mmap.format =pal;
   if (ioctl(vd->fd, VIDIOCSPICT, &(vd->picture)) < 0) {
      perror("v4l_set_palette");
      return -1;
   }
   return 0;
}
