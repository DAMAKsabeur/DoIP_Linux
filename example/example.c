#include "doip.h"

int main (void)
{
	doip_error_t result = 0x00;
	doip_msg_t doip_msg = {0x00};
    result = doip_init();
    //result = uds_init();
    //~ result = doip_process_msg_callback(&doip_msg, 0, NULL);
    while(1);
	result = doip_uninit();
}
