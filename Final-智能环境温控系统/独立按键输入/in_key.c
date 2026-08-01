#include "in_key.h"
#include "bus.h"
#include "at24c02.h"

u8 key_scan(void)
{
    static u8 key=1;

    if(key==1 && (K1==0 || K2==0 || K3==0 || K4==0))
    {
        Delay10us(50);
        key=0;
        if(K1==0)
            return K1_PRESS;
        else if(K2==0)
            return K2_PRESS;
        else if(K3==0)
            return K3_PRESS;
        else if(K4==0)
            return K4_PRESS;
    }
    else if(K1==1 && K2==1 && K3==1 && K4==1)
    {
        key=1;
    }
    return K_UNPRESS;
}

void key_press_function()
{
	u8 now_key;
	now_key=key_scan();

	if(now_key==K_UNPRESS) return ;


	switch(now_key)
	{
		case K1_PRESS:
			if(page==1)page=0;
			else page=1;
			page_change=1;
			break;

		case K2_PRESS:
		    if(max_temper<50)
			{
				max_temper++;
				bus_save_param(); 
			}

			break;

		case K3_PRESS:
			if(min_temper>0)
			{
				min_temper--;
				bus_save_param(); 
			}
			break;

		case K4_PRESS:
			max_temper = 30;
			min_temper = 20;
			bus_save_param();
		    page=0;
			page_change=1;
			break; 
	}
	
}



































