#include "platform.h"
		
int vid_get_viewport_width()
{
	return 360 ;					// SD940 103c ?
}

long vid_get_viewport_height()		
{		
	return 240;					// SD940 103c
}		
		
char *camera_jpeg_count_str()		
{		
	return (char*) 0x700B0;		// SD940 103C search on "9999"
}	

char *hook_raw_image_addr()		
{		
    return (char*)0x4219D120;	// SD940 103c FFAD6FF8 from matching subroutine in S90 101a FFB0254C
								// ... search for aCrawBuffP      DCB "CRAW BUFF       %p",0
}		
		
long hook_raw_size()		
{		
	return 0x11CA240;			// SD940 103c Search for "aCrawBuffSizeP" 

}		
		
void *vid_get_bitmap_fb()		
{		
	return (void*)0x403F1000;  	// SD940 103c @ FF8532DC after DispCon_ShowBlackChart
}		
	
void *vid_get_viewport_live_fb()
{													// Matched IXUS100-SD780 100c code at 0xFF8B02F4 with IXUS120-SD940 at address 0xFF8D9014
													// Matched IXUS200-SD980 101c code at 0xFF8E0788 with IXUS120-SD940 at address 0xFF8D9014 
 	// return (void*) 0;							// __LiveImage.c__  ok
    void **fb=(void **)0x4B34; 			  			// SD940 102C @ 0xFF8D9280  
    unsigned char buff = *((unsigned char*)0x497C); // SD940 103C @ 0xFF8D9018
    if (buff == 0) {
        buff = 2;
    }
    else {
        buff--;
    }
    return fb[buff];
}
		
void *vid_get_viewport_fb()		
{		
	return (void*)0x4088B700;	// SD940 103c from matching subroutine in S90 101a
								// search on VRAM Address  sub @ 9FFAD4910)
}		
		
void *vid_get_viewport_fb_d()		
{		
	return (void*)(*(int*)(0x2790+0x58));  //  @FF869E3C  @FF869E74 
}		
			
	
		
