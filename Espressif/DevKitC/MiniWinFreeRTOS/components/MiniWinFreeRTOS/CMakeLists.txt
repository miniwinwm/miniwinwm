file(TO_CMAKE_PATH $ENV{IDF_PATH} IDF_PATH)
idf_component_register(SRCS "../../../../../MiniWinFreeRTOS_Common/miniwin_user.c"
							"../../../../../MiniWinFreeRTOS_Common/gyro_util.c"
							"../../../../../MiniWinFreeRTOS_Common/window_gyro_x.c"
							"../../../../../MiniWinFreeRTOS_Common/window_gyro_y.c"
							"../../../../../MiniWinFreeRTOS_Common/window_gyro_z.c"
					REQUIRES "MiniWin"
					         "MiniWinFreeRTOS"
                    INCLUDE_DIRS "../../../../../MiniWin"
                    			 "../../../../../MiniWinFreeRTOS_Common"
                    			 "../../main"
                    			 "../../../../../MiniWin/gl/fonts/truetype/mcufont"
                    			 "${IDF_PATH}/components/freertos/include/freertos")