pyocd erase -c -t hk32f030mf4p6 --config ./pyocd.yaml
pyocd load ./Project/MDK5/Objects/LCM_Light_Control_IO_WS2812_New.hex -t hk32f030mf4p6 --config ./pyocd.yaml