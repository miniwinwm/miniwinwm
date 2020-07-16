idf_component_register(SRCS "../../../../../MiniWinSimple_Common/miniwin_user.c"
							"../../../../../MiniWinSimple_Common/window_simple.c"
					REQUIRES "MiniWin"
					         "MiniWinSimple"
                    INCLUDE_DIRS "../../../../../MiniWin"
                    			 "../../../../../MiniWinSimple_Common"
                    			 "../../main"
                    			 "../../../../../MiniWin/gl/fonts/truetype/mcufont")