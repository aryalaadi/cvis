/*
	file:		src/cvis.c
	license:	GPL3
*/

#include <MiniFB.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <math.h>

#include <eval.h>

static uint32_t g_width = 600;
static uint32_t g_height = 600;
static uint32_t *g_buffer = 0x0;

char *expr = NULL;

int main(int argc, char **argv ){

	if (argc == 1) {
		printf("CVIS: plotting default function y=x+5\n");	
		expr = malloc(sizeof(char)*32);
		strcpy(expr, "x+5");
	}
	else {
		expr = malloc(sizeof(char)*32);
		strncpy(expr, argv[1], strlen(argv[1]));
		printf("CVIS: could not parse the expr");
	}
	// FIXME
	printf("NOTE: the graph is inverted due to skill issue reasons");
	fflush(stdout);
  	struct mfb_window *window = mfb_open_ex("CVIS", g_width, g_height, 0);
  	if (!window)
    		return 0;
  
  	g_buffer = (uint32_t *) malloc(g_width * g_height * 4);
  
 
  	mfb_set_target_fps(1);
 	mfb_update_state state;
  	do {
    		int i = 0;
    		for (int x = 0; x< g_width; x++) {
      			for (int y =  0; y< g_height; y++) {
				g_buffer[i] = MFB_RGB(0xFF, 0xFF, 0xFF);
				if (x%10==0 || y%10==0) {
					g_buffer[i] = MFB_RGB(0x80, 0x80, 0x80);
				}
				if (x == 300 || y == 300) {
					g_buffer[i] = MFB_RGB(0x00, 0x00, 0x00);
				}
				++i;	
      			}
    		}
		i = 0;
		
		int tx = 0;
		int ty = 0;
     		for (int x = 0; x< g_width; x++) {
		for (int y = 0; y< g_height; y++) {
			if(x<300) {
				tx = -300+x; 	
			}
			else if(x>300) {	
				tx = x-300;
			}
			if (y<300) {
				ty = 300-y;
			}
			else if(y>300) {
				ty = (y-300)*(-1);
			}

			double ftx = tx/75.0;
			double fty = ty/75.0;
			double d = fabs(ftx - eval(expr, fty));		
			if (d < 0.01) {
				g_buffer[i] = MFB_RGB(0x00, 0x00, 0xFF);			
			}
			++i;    		   		
		}
		}

    		state = mfb_update_ex(window, g_buffer, g_width, g_height);
    		if (state != STATE_OK) {
        		window = 0x0;
       	 		break;
    		}
  	} while(mfb_wait_sync(window));
  	return 0;
}
