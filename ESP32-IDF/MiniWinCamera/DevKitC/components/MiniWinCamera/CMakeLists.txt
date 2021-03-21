idf_component_register(SRCS "../../../../../MiniWinCamera_Common/miniwin_user.c"
							"../../../../../MiniWinCamera_Common/window_camera.c"
					REQUIRES "MiniWin"
					         "MiniWinCamera"
                    INCLUDE_DIRS "../../../../../MiniWin"
                    			 "../../../../../MiniWinCamera_Common"
                    			 "../../main"
                    			 "../../../../../MiniWin/gl/fonts/truetype/mcufont")