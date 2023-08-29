#include <stdlib.h>
#include <xcb/xcb.h>
#include <assert.h>
#include <stdio.h>
#include <inttypes.h>

int
main()
{
  /* open connection to the X server */
  int screenNumber;
  xcb_connection_t *connection = xcb_connect (NULL,&screenNumber);
  assert(xcb_connection_has_error (connection));
  /* get screen whose number is screenNumber */
  const xcb_setup_t *setup = xcb_get_setup (connection);
  xcb_screen_iterator_t iter =  xcb_setup_roots_iterator (setup);
  /* screen at the index of the iterator */
  int i;
  for(i = 0; i < screenNumber; ++i) {
    xcb_screen_next (&iter);
  }

  xcb_screen_t *screen = iter.data;

  xcb_window_t windowId = xcb_generate_id (connection);
  uint32_t propName = XCB_CW_BACK_PIXEL;
  uint32_t propValue = screen->white_pixel;

  xcb_map_window (connection, windowId);
  xcb_flush (connection);


  printf ("\n");
  printf ("Screen Information: %"PRIu32": \n", screen->root);
  printf ("Width..............:%"PRIu16" \n", screen->width_in_pixels);
  printf ("Height.............:%"PRIu16" \n", screen->height_in_pixels);


  xcb_disconnect (connection);
  return 0;
}
