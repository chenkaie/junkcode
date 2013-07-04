#include <stdio.h>
#include <microwin/nano-X.h>

GR_WINDOW_ID wid;
GR_GC_ID gc;

void event_handler (GR_EVENT *event);

int main (void)
{
   if (GrOpen() < 0) {
        fprintf (stderr, "GrOpen failed");
        exit (1);
   }

   gc = GrNewGC();
   GrSetGCForeground (gc, 0xFF0000);

   wid = GrNewWindowEx(GR_WM_PROPS_APPFRAME |
                       GR_WM_PROPS_CAPTION  |
                       GR_WM_PROPS_CLOSEBOX,
                       "jollen.org",
                       GR_ROOT_WINDOW_ID, 
                       0, 0, 200, 200, 0xFFFFFF);

   GrSelectEvents(wid, GR_EVENT_MASK_CLOSE_REQ | GR_EVENT_MASK_EXPOSURE);

   GrMapWindow(wid);
   GrMainLoop(event_handler);
}

void event_handler (GR_EVENT *event)
{
   switch (event->type)
   {
      case GR_EVENT_TYPE_EXPOSURE:
           GrText(wid, gc, 50, 50, "Hello World", -1, GR_TFASCII);
	   break;
      case GR_EVENT_TYPE_CLOSE_REQ: 
	   GrClose();
           exit (0);
      default: break;
   }
}
