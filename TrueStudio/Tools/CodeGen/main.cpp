#include <string>
#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#if defined(_WIN32)
#include <direct.h>
#else
#include <sys/stat.h>
#endif
#include "json11.hpp"

using namespace json11;
using namespace std;

int main(int argc, char **argv)
{
	vector<string> all_identifier_names;

	// check command line args
	if (argc != 2)
	{
		cout << "Usage: " << argv[0] << " <config file> \n";
		exit(1);
	}
	std::ifstream json_file(argv[1]);
	if (!json_file.is_open())
	{
		cout << "Could not open input file" << argv[1] << ".\n";
		exit(1);
	}

	// read json config file
    json_file.seekg(0, std::ios::end);
    std::string str;
    str.reserve(json_file.tellg());
    json_file.seekg(0, std::ios::beg);
    str.assign((std::istreambuf_iterator<char>(json_file)),
                std::istreambuf_iterator<char>());

    // parse json config file
    string parse_error;
    const auto json = Json::parse(str, parse_error);
	if (parse_error != "")
	{
		cout << "There was a JSON parsing error: " << parse_error << "\n";
		exit(0);
	}

	// check target type
    if (json["TargetType"].string_value() == "")
    {
    	cout << "No target type specified\n";
    	exit(1);
    }
    if (json["TargetType"].string_value() != "Linux" && json["TargetType"].string_value() != "Windows")
	{
		cout << "Target type not supported\n";
		exit(1);
	}

    // check target name
    if (json["TargetName"].string_value() == "")
    {
    	cout << "No target name specified\n";
    	exit(1);
    }

	// check number of windows
	if (json["Windows"].array_items().size() == 0)
	{
		cout << "No windows found.\n";
		exit(1);
	}

	// check max window count
	uint32_t max_window_count;
	if (!json["MaxWindowCount"].is_number())
	{
		max_window_count = json["Windows"].array_items().size() + 2;
	}
	else
	{
		max_window_count = json["MaxWindowCount"].number_value();
	}
	if (max_window_count < json["Windows"].array_items().size() + 1)
	{
		cout << "Not enough space for all the specified windows.\n";
		exit(1);
	}
	
	// check max control count
	uint32_t control_count = 0;
	uint32_t max_control_count;
	for (auto& window : json["Windows"].array_items())
	{
		// count buttons handles
		for (auto& button : window["Buttons"].array_items())
		{
			control_count++;
		}
		// count labels handles
		for (auto& label : window["Labels"].array_items())
		{
			control_count++;
		}		
		// count check boxes handles
		for (auto& check_box : window["CheckBoxes"].array_items())
		{
			control_count++;
		}	
		// count arrows handles
		for (auto& arrow : window["Arrows"].array_items())
		{
			control_count++;
		}		
		// count progress bars handles
		for (auto& progress_bar : window["ProgressBars"].array_items())
		{
			control_count++;
		}				
		// count horiz scroll bars handles
		for (auto& scroll_bar_horiz : window["ScrollBarsHoriz"].array_items())
		{
			control_count++;
		}			
		// count vert scroll bars handles
		for (auto& scroll_bar_vert : window["ScrollBarsVert"].array_items())
		{
			control_count++;
		}				
		// count radio buttons handles
		for (auto& radio_button : window["RadioButtons"].array_items())
		{
			control_count++;
		}	
		// count list boxes handles
		for (auto& list_box : window["ListBoxes"].array_items())
		{
			control_count++;
		}	
		// count text boxes handles
		for (auto& text_box : window["TextBoxes"].array_items())
		{
			control_count++;
		}		
		// count scrolling list boxes handles
		for (auto& scrolling_list_box : window["ScrollingListBoxes"].array_items())
		{
			control_count += 2;
		}			
		// count scrolling text boxes handles
		for (auto& scrolling_text_box : window["ScrollingTextBoxes"].array_items())
		{
			control_count += 2;	
		}															
	}		
	if (!json["MaxControlCount"].is_number())
	{
		max_control_count = control_count + 5;
	}
	else
	{
		max_control_count = json["MaxControlCount"].number_value();
		if (max_control_count < control_count)
		{
			cout << "Not enough space for all the specified controls.\n";
			exit(1);
		}		
	}
	
	// get max timer count
	uint32_t max_timer_count;
	if (!json["MaxTimerCount"].is_number())
	{
		max_timer_count = 8;
	}
	else
	{
		max_timer_count = json["MaxTimerCount"].number_value();
	}
	
	// get max message count
	uint32_t max_message_count;
	if (!json["MaxMessageCount"].is_number())
	{
		max_message_count = 80;
	}
	else
	{
		max_message_count = json["MaxMessageCount"].number_value();
	}
	
	// get calibrate text
	std::string calibrate_text;
	if (!json["CalibrateText"].is_string())
	{
		calibrate_text = "Touch centre of cross";
	}
	else
	{
		calibrate_text = json["CalibrateText"].string_value();
	}
	
	// get busy text
	std::string busy_text;
	if (!json["BusyText"].is_string())
	{
		busy_text = "BUSY...";
	}
	else
	{
		busy_text = json["BusyText"].string_value();
	}	
	
    // make output folders
#if defined(_WIN32)
	if (_mkdir(("../../" + json["TargetName"].string_value()).c_str()) != 0 && errno != EEXIST)
	{
    	cout << "Could not make " + json["TargetName"].string_value() + " folder.\n";
    	exit(1);
	}
	if (_mkdir(("../../" + json["TargetName"].string_value() + "/" + json["TargetType"].string_value()).c_str()) != 0 && errno != EEXIST)
	{
    	cout << "Could not make " + json["TargetName"].string_value() + "/" << json["TargetType"].string_value() << " folder.\n";
    	exit(1);
	}
	if (_mkdir(("../../" + json["TargetName"].string_value() + "/" + json["TargetType"].string_value() + "/src").c_str()) != 0 && errno != EEXIST)
	{
		cout << "Could not make " + json["TargetName"].string_value() + "/" << json["TargetType"].string_value() << "/src folder.\n";
		exit(1);
	}
	if (_mkdir(("../../" + json["TargetName"].string_value() + "/" + json["TargetName"].string_value() + "_Common").c_str()) != 0 && errno != EEXIST)
	{
		cout << "Could not make " + json["TargetName"].string_value() + "_Common folder.\n";
		exit(1);
	}
#elif defined(__linux__)
	if (mkdir(("../../" + json["TargetName"].string_value()).c_str(), 0777) != 0 && errno != EEXIST)
	{
    	cout << "Could not make " + json["TargetName"].string_value() + " folder.\n";
    	exit(1);
	}
	if (mkdir(("../../" + json["TargetName"].string_value() + "/" + json["TargetType"].string_value()).c_str(), 0777) != 0 && errno != EEXIST)
	{
    	cout << "Could not make " + json["TargetName"].string_value() + "/" << json["TargetType"].string_value() << " folder.\n";
    	exit(1);
	}
	if (mkdir(("../../" + json["TargetName"].string_value() + "/" + json["TargetType"].string_value() + "/src").c_str(), 0777) != 0 && errno != EEXIST)
	{
		cout << "Could not make " + json["TargetName"].string_value() + "/" << json["TargetType"].string_value() << "/src folder.\n";
		exit(1);
	}
	if (mkdir(("../../" + json["TargetName"].string_value() + "/" + json["TargetName"].string_value() + "_Common").c_str(), 0777) != 0 && errno != EEXIST)
	{
		cout << "Could not make " + json["TargetName"].string_value() + "_Common folder.\n";
		exit(1);
	}
#endif

	// create the config header file
	std::ofstream outfileConfigHeader("../../" + json["TargetName"].string_value() + "/" + json["TargetName"].string_value() + "_Common/miniwin_config.h",   std::ios::binary);

	if (!outfileConfigHeader.is_open())
	{
		cout << "Could not create file\n";
		exit(1);
	}
		outfileConfigHeader << "#ifndef MINIWIN_CONFIG_H\n"
				"#define MINIWIN_CONFIG_H\n\n"
				"#ifdef __cplusplus\n"
				" extern \"C\" {\n"
				"#endif\n\n"
				"#define MW_MAX_WINDOW_COUNT 				" << max_window_count << "               		/**< Maximum number of allowed windows; root window always takes 1 space */\n"
				"#define MW_MAX_CONTROL_COUNT				" << max_control_count << "              		/**< Total maximum number of allowed controls in all windows */\n"
				"#define MW_MAX_TIMER_COUNT					" << max_timer_count << "              			/**< Maximum number of timers */\n"
				"#define MW_MESSAGE_QUEUE_SIZE				" << max_message_count << "              		/**< Maximum number of messages in message queue */\n"
				"#define MW_DISPLAY_ROTATION_0\n"
				"/* #define MW_DISPLAY_ROTATION_90 */\n"
				"/* #define MW_DISPLAY_ROTATION_180 */\n"
				"/* #define MW_DISPLAY_ROTATION_270 */\n"
				"#if defined(MW_DISPLAY_ROTATION_0) || defined(MW_DISPLAY_ROTATION_180)\n"
				"#define MW_ROOT_WIDTH 						mw_hal_lcd_get_display_width()  /**< Width of root window */\n"
				"#define MW_ROOT_HEIGHT 						mw_hal_lcd_get_display_height() /**< Height of root window */\n"
				"#elif defined(MW_DISPLAY_ROTATION_90) || defined(MW_DISPLAY_ROTATION_270)\n"
				"#define MW_ROOT_WIDTH 						mw_hal_lcd_get_display_height() /**< Width of root window */\n"
				"#define MW_ROOT_HEIGHT 						mw_hal_lcd_get_display_width()	/**< Height of root window */\n"
				"#endif\n"
				"#define MW_MAX_TITLE_SIZE 					14              		/**< Maximum window title bar title size in characters */\n"
				"#define MW_TITLE_BAR_COLOUR_FOCUS			MW_HAL_LCD_BLUE    		/**< Colour of title bar of window with focus */\n"
				"#define MW_TITLE_BAR_COLOUR_NO_FOCUS		MW_HAL_LCD_GREY5    	/**< Colour of title bars of windows without focus */\n"
				"#define MW_TITLE_BAR_COLOUR_MODAL			MW_HAL_LCD_RED			/**< Colour of title bar of modal window */\n"
				"#define MW_TITLE_TEXT_COLOUR_FOCUS			MW_HAL_LCD_WHITE    	/**< Title bar text colour of window with focus */\n"
				"#define MW_TITLE_TEXT_COLOUR_NO_FOCUS		MW_HAL_LCD_WHITE    	/**< Title bar text colour of window without focus */\n"
				"#define MW_TITLE_TEXT_COLOUR_MODAL			MW_HAL_LCD_WHITE   	 	/**< Title bar text colour of window that's modal */\n"
				"#define MW_CONTROL_UP_COLOUR				MW_HAL_LCD_GREY2    	/**< Animated controls up colour */\n"
				"#define MW_CONTROL_SEPARATOR_COLOUR			MW_HAL_LCD_GREY3		/**< Separator between control items colour */\n"
				"#define MW_CONTROL_DOWN_COLOUR				MW_HAL_LCD_GREY4    	/**< Animated controls down colour */\n"
				"#define MW_CONTROL_DISABLED_COLOUR			MW_HAL_LCD_GREY5		/**< Colour to draw a control that is disabled */\n"
				"#define MW_CONTROL_DOWN_TIME				4               		/**< Time for animated controls down time in system ticks */\n"
				"#define MW_KEY_DOWN_TIME					3               		/**< Time for animated keys down time in system ticks */\n"
				"#define MW_TICKS_PER_SECOND					20						/**< The number of window timer ticks per second */\n"
				"#define MW_WINDOW_MIN_MAX_EFFECT_TIME		5						/**< Number of window ticks to show window minimise/maximise effect for */\n"
				"#define MW_CURSOR_PERIOD_TICKS				10						/**< Period between cursor change in system ticks */\n"
				"#define MW_TOUCH_INTERVAL_TICKS				2               		/**< Number of window ticks a touch has to be down for to count as a touch event */\n"
				"#define MW_HOLD_DOWN_DELAY_TICKS			10						/**< Time in ticks that a ui control starts repeating if held down */\n"
				"#define MW_FONT_12_INCLUDED											/**< Comment this in to include Courier 12 point font or out to exclude it */\n"
				"#define MW_FONT_16_INCLUDED											/**< Comment this in to include Courier 16 point font or out to exclude it */\n"
				"#define MW_FONT_20_INCLUDED											/**< Comment this in to include Courier 20 point font or out to exclude it */\n"
				"#define MW_FONT_24_INCLUDED											/**< Comment this in to include Courier 24 point font or out to exclude it */\n"
				"/* #define MW_DIALOG_FILE_CHOOSER */								/**< File chooser dialog is optional and is only built if this is defined */\n"
				"#define MW_DRAG_THRESHOLD_PIXELS			2               		/**< Distance a touch pointer moves before a drag event is created */\n"
				"#define MW_BUSY_TEXT						\"" << busy_text << "\"				/**< Text to display when screen is not responsive because of long operation */\n"
				"#define MW_CALIBRATE_TEXT					\"" << calibrate_text << "\"	/**< Text to display in touch screen calibrate screen */\n\n"
				"#ifdef __cplusplus\n"
				"}\n"
				"#endif\n\n"
				"#endif\n";
	outfileConfigHeader.close();

    // check large size flag
    bool large_size = json["LargeSize"].bool_value();

	// create miniwin_user.c
	std::ofstream outfileUserSource("../../" + json["TargetName"].string_value() + "/" + json["TargetName"].string_value() + "_Common/miniwin_user.c");
	if (!outfileUserSource.is_open())
	{
		cout << "Could not create file\n";
		exit(1);
	}
	
	// header comment
	outfileUserSource << "/* miniwin_user.c generated by MiniWin code generator. */\n\n";
	
	// include header files
	outfileUserSource << "#include \"miniwin.h\"\n";
	for (auto &window : json["Windows"].array_items())
    {
		outfileUserSource << "#include \"";
    	outfileUserSource << window["Name"].string_value() << ".h\"\n";
    }
	outfileUserSource << "\n";
	
	// menu arrays
	for (auto& window : json["Windows"].array_items())
    {
		if (window["MenuItems"].array_items().size() == 0)
		{
			continue;
		}

		all_identifier_names.push_back(window["Name"].string_value() + "_menu_bar_labels");
		outfileUserSource << "static const char *" << window["Name"].string_value() << "_menu_bar_labels[] = {";
		uint32_t i = 0;
	    for (auto &menu_item_label : window["MenuItems"].array_items())
	    {
	    	outfileUserSource << "\"";
	    	outfileUserSource << menu_item_label.string_value();
	    	outfileUserSource << "\"";
	    	if (i < window["MenuItems"].array_items().size() - 1)
	    	{
	    		outfileUserSource << ", ";
	    	}
	    	i++;
	    }
	    outfileUserSource << "};\n";
    }
	
	// radio button arrays
	for (auto& window : json["Windows"].array_items())
    {
		for (auto& radio_button : window["RadioButtons"].array_items())
		{
			if (radio_button["Labels"].array_items().size() == 0)
			{
				continue;
			}

			all_identifier_names.push_back("radio_button_" + radio_button["Name"].string_value() + "_labels");
			outfileUserSource << "static const char *radio_button_" << radio_button["Name"].string_value() << "_labels[] = {";
			uint32_t i = 0;
			for (auto &label : radio_button["Labels"].array_items())
			{
				outfileUserSource << "\"";
				outfileUserSource << label.string_value();
				outfileUserSource << "\"";
				if (i < radio_button["Labels"].array_items().size() - 1)
				{
					outfileUserSource << ", ";
				}
				i++;
			}
			outfileUserSource << "};\n";
		}
    }
    
    // list boxes arrays
	for (auto& window : json["Windows"].array_items())
    {
		for (auto& list_box : window["ListBoxes"].array_items())
		{
			if (list_box["Labels"].array_items().size() == 0)
			{
				continue;
			}

			all_identifier_names.push_back("list_box_" + list_box["Name"].string_value() + "_entries");
			outfileUserSource << "static const mw_ui_list_box_entry list_box_" << list_box["Name"].string_value() << "_entries[] = {";
			uint32_t i = 0;
			for (auto &label : list_box["Labels"].array_items())
			{
				outfileUserSource << "{\"";
				outfileUserSource << label.string_value();
				outfileUserSource << "\", NULL}";
				if (i < list_box["Labels"].array_items().size() - 1)
				{
					outfileUserSource << ", ";
				}
				i++;
			}
			outfileUserSource << "};\n";
		}
    }
   	
    // scrolling list boxes arrays
	for (auto& window : json["Windows"].array_items())
    {
		for (auto& scrolling_list_box : window["ScrollingListBoxes"].array_items())
		{
			if (scrolling_list_box["Labels"].array_items().size() == 0)
			{
				continue;
			}

			all_identifier_names.push_back("scrolling_list_box_" + scrolling_list_box["Name"].string_value() + "_entries");
			outfileUserSource << "static const mw_ui_list_box_entry scrolling_list_box_" << scrolling_list_box["Name"].string_value() << "_entries[] = {";
			uint32_t i = 0;
			for (auto &label : scrolling_list_box["Labels"].array_items())
			{
				outfileUserSource << "{\"";
				outfileUserSource << label.string_value();
				outfileUserSource << "\", NULL}";
				if (i < scrolling_list_box["Labels"].array_items().size() - 1)
				{
					outfileUserSource << ", ";
				}
				i++;
			}
			outfileUserSource << "};\n";
		}
    }
   	outfileUserSource << endl;	   	
    
    // truetype fonts
    vector<string> fonts;
    for (auto& window : json["Windows"].array_items())
    {
		for (auto& text_box : window["TextBoxes"].array_items())
		{	
			string next_font = text_box["Font"].string_value();
			if (next_font == "")
			{
				cout << "No font name specified for text box: " << text_box["Name"].string_value() << " in window: " << window["Name"].string_value() << endl;
				exit(1);
			}
			
			bool exists = false;
			for (auto& existing_font : fonts)
			{
				if (existing_font == next_font)
				{
					exists = true;
					break;
				}
			}
			
			if (!exists)
			{
				fonts.push_back(next_font);
				outfileUserSource << "extern const struct mf_rlefont_s " << next_font << ";\n";
			}
		}	
	}     
    for (auto& window : json["Windows"].array_items())
    {
		for (auto& scrolling_text_box : window["ScrollingTextBoxes"].array_items())
		{	
			string next_font = scrolling_text_box["Font"].string_value();
			if (next_font == "")
			{
				cout << "No font name specified for text box: " << scrolling_text_box["Name"].string_value() << " in window: " << window["Name"].string_value() << endl;
				exit(1);
			}
			
			bool exists = false;
			for (auto& existing_font : fonts)
			{
				if (existing_font == next_font)
				{
					exists = true;
					break;
				}
			}
			
			if (!exists)
			{
				fonts.push_back(next_font);
				outfileUserSource << "extern const struct mf_rlefont_s " << next_font << ";\n";
			}
		}	
	}  	  
	if (fonts.size() > 0) 
	{
		outfileUserSource << endl;	
	}

	// create window variables
    for (auto &window : json["Windows"].array_items())
    {
    	all_identifier_names.push_back("window_" + window["Name"].string_value() + "_handle");
        outfileUserSource << "mw_handle_t window_";
    	outfileUserSource << window["Name"].string_value() << "_handle;\n";
    }
   	outfileUserSource << "\n";
   	
   	// create controls handles
    for (auto &window : json["Windows"].array_items())
    {
		// create buttons handles
		for (auto& button : window["Buttons"].array_items())
		{
			all_identifier_names.push_back("button_" + button["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t button_" << button["Name"].string_value() << "_handle;\n";
		}
		// create labels handles
		for (auto& label : window["Labels"].array_items())
		{
			all_identifier_names.push_back("label_" + label["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t label_" << label["Name"].string_value() << "_handle;\n";
		}		
		// create check boxes handles
		for (auto& check_box : window["CheckBoxes"].array_items())
		{
			all_identifier_names.push_back("check_box_" + check_box["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t check_box_" << check_box["Name"].string_value() << "_handle;\n";
		}	
		// create arrows handles
		for (auto& arrow : window["Arrows"].array_items())
		{
			all_identifier_names.push_back("arrow_" + arrow["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t arrow_" << arrow["Name"].string_value() << "_handle;\n";
		}		
		// create progress bars handles
		for (auto& progress_bar : window["ProgressBars"].array_items())
		{
			all_identifier_names.push_back("progress_bar_" + progress_bar["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t progress_bar_" << progress_bar["Name"].string_value() << "_handle;\n";
		}				
		// create horiz scroll bars handles
		for (auto& scroll_bar_horiz : window["ScrollBarsHoriz"].array_items())
		{
			all_identifier_names.push_back("scroll_bar_horiz_" + scroll_bar_horiz["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t scroll_bar_horiz_" << scroll_bar_horiz["Name"].string_value() << "_handle;\n";
		}			
		// create vert scroll bars handles
		for (auto& scroll_bar_vert : window["ScrollBarsVert"].array_items())
		{
			all_identifier_names.push_back("scroll_bar_vert_" + scroll_bar_vert["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t scroll_bar_vert_" << scroll_bar_vert["Name"].string_value() << "_handle;\n";
		}				
		// create radio buttons handles
		for (auto& radio_button : window["RadioButtons"].array_items())
		{
			all_identifier_names.push_back("radio_button_" + radio_button["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t radio_button_" << radio_button["Name"].string_value() << "_handle;\n";
		}	
		// create list boxes handles
		for (auto& list_box : window["ListBoxes"].array_items())
		{
			all_identifier_names.push_back("list_box_" + list_box["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t list_box_" << list_box["Name"].string_value() << "_handle;\n";
		}
		// create text boxes handles
		for (auto& text_box : window["TextBoxes"].array_items())
		{
			all_identifier_names.push_back("text_box_" + text_box["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t text_box_" << text_box["Name"].string_value() << "_handle;\n";
		}		
		// create scrolling list boxes handles
		for (auto& scrolling_list_box : window["ScrollingListBoxes"].array_items())
		{
			all_identifier_names.push_back("scrolling_list_box_" + scrolling_list_box["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t scrolling_list_box_" << scrolling_list_box["Name"].string_value() << "_handle;\n";
			all_identifier_names.push_back("scrolling_list_box_scroll_bar_vert_" + scrolling_list_box["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t scrolling_list_box_scroll_bar_vert_" << scrolling_list_box["Name"].string_value() << "_handle;\n";			
		}			
		// create scrolling text boxes handles
		for (auto& scrolling_text_box : window["ScrollingTextBoxes"].array_items())
		{
			all_identifier_names.push_back("scrolling_text_box_" + scrolling_text_box["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t scrolling_text_box_" << scrolling_text_box["Name"].string_value() << "_handle;\n";
			all_identifier_names.push_back("scrolling_text_box_scroll_bar_vert_" + scrolling_text_box["Name"].string_value() + "_handle");
			outfileUserSource << "mw_handle_t scrolling_text_box_scroll_bar_vert_" << scrolling_text_box["Name"].string_value() << "_handle;\n";			
		}													
	}
	outfileUserSource << "\n";
    
    // create controls data
    for (auto &window : json["Windows"].array_items())
    {
		// creat buttons data
		for (auto& button : window["Buttons"].array_items())
		{
			all_identifier_names.push_back("button_" + button["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_button_data_t button_" << button["Name"].string_value() << "_data;\n";
		}
		// creat labels data
		for (auto& label : window["Labels"].array_items())
		{
			all_identifier_names.push_back("label_" + label["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_label_data_t label_" << label["Name"].string_value() << "_data;\n";
		}		
		// create check boxes data
		for (auto& check_box : window["CheckBoxes"].array_items())
		{
			all_identifier_names.push_back("check_box_" + check_box["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_check_box_data_t check_box_" << check_box["Name"].string_value() << "_data;\n";
		}	
		// create arrows data
		for (auto& arrow : window["Arrows"].array_items())
		{
			all_identifier_names.push_back("arrow_" + arrow["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_arrow_data_t arrow_" << arrow["Name"].string_value() << "_data;\n";
		}		
		// create progress bars data
		for (auto& progress_bar : window["ProgressBars"].array_items())
		{
			all_identifier_names.push_back("progress_bar_" + progress_bar["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_progress_bar_data_t progress_bar_" << progress_bar["Name"].string_value() << "_data;\n";
		}	
		// create horiz scroll bars data
		for (auto& scroll_bar_horiz : window["ScrollBarsHoriz"].array_items())
		{
			all_identifier_names.push_back("scroll_bar_horiz_" + scroll_bar_horiz["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_scroll_bar_horiz_data_t scroll_bar_horiz_" << scroll_bar_horiz["Name"].string_value() << "_data;\n";
		}			
		// create vert scroll bars data
		for (auto& scroll_bar_vert : window["ScrollBarsVert"].array_items())
		{
			all_identifier_names.push_back("scroll_bar_vert_" + scroll_bar_vert["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_scroll_bar_vert_data_t scroll_bar_vert_" << scroll_bar_vert["Name"].string_value() << "_data;\n";
		}		
		// create radio buttons data
		for (auto& radio_button : window["RadioButtons"].array_items())
		{
			all_identifier_names.push_back("radio_button_" + radio_button["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_radio_button_data_t radio_button_" << radio_button["Name"].string_value() << "_data;\n";
		}		
		// create list boxes data
		for (auto& list_box : window["ListBoxes"].array_items())
		{
			all_identifier_names.push_back("list_box_" + list_box["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_list_box_data_t list_box_" << list_box["Name"].string_value() << "_data;\n";
		}				
		// create text boxes data
		for (auto& text_box : window["TextBoxes"].array_items())
		{
			all_identifier_names.push_back("text_box_" + text_box["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_text_box_data_t text_box_" << text_box["Name"].string_value() << "_data;\n";
		}	
		// create scrolling list boxes data
		for (auto& scrolling_list_box : window["ScrollingListBoxes"].array_items())
		{		
			all_identifier_names.push_back("scrolling_list_box_" + scrolling_list_box["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_list_box_data_t scrolling_list_box_" << scrolling_list_box["Name"].string_value() << "_data;\n";
			
			all_identifier_names.push_back("scrolling_list_box_scroll_bar_vert_" + scrolling_list_box["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_scroll_bar_vert_data_t scrolling_list_box_scroll_bar_vert_" << scrolling_list_box["Name"].string_value() << "_data;\n";
		}				
		// create scrolling text boxes data
		for (auto& scrolling_text_box : window["ScrollingTextBoxes"].array_items())
		{		
			all_identifier_names.push_back("scrolling_text_box_" + scrolling_text_box["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_text_box_data_t scrolling_text_box_" << scrolling_text_box["Name"].string_value() << "_data;\n";
			
			all_identifier_names.push_back("scrolling_text_box_scroll_bar_vert_" + scrolling_text_box["Name"].string_value() + "_data");
			outfileUserSource << "static mw_ui_scroll_bar_vert_data_t scrolling_text_box_scroll_bar_vert_" << scrolling_text_box["Name"].string_value() << "_data;\n";
		}	
	}
    
    // root functions and user_init function start
    outfileUserSource << "\nvoid mw_user_root_paint_function(const mw_gl_draw_info_t *draw_info)\n" 
						 "{\n    mw_gl_set_solid_fill_colour(MW_HAL_LCD_PURPLE);\n" 
						 "    mw_gl_clear_pattern();\n" 
						 "    mw_gl_set_border(MW_GL_BORDER_OFF);\n" 
						 "    mw_gl_set_fill(MW_GL_FILL);\n" 
						 "    mw_gl_rectangle(draw_info, 0, 0, MW_ROOT_WIDTH, MW_ROOT_HEIGHT);\n}\n\n" 
						 "void mw_user_root_message_function(const mw_message_t *message)\n" 
						 "{\n    (void)message;\n}\n\n" 
						 "void mw_user_init(void)\n{\n" 
						 "    mw_util_rect_t r;\n\n";

	// each window's set_rect and mw_add_window
    for (auto& window : json["Windows"].array_items())
    {
    	// check presence and format of required window fields
    	if (window["Name"].string_value() == "")
    	{
    		cout << "No or blank Name value for window"<< endl;
    		exit(1);			
		}
    	if (!window["X"].is_number())
    	{
    		cout << "No X value for window " << window["Name"].string_value() << endl;
    		exit(1);
    	}
    	if (!window["Y"].is_number())
    	{
    		cout << "No Y value for window " << window["Name"].string_value() << endl;
    		exit(1);
    	}
    	if (!window["Width"].is_number())
    	{
    		cout << "No Width value for window " << window["Name"].string_value() << endl;
    		exit(1);
    	}
    	if (!window["Height"].is_number())
    	{
    		cout << "No Height value for window " << window["Name"].string_value() << endl;
    		exit(1);
    	}
    	if (window["MenuBar"].bool_value())
		{
			// menu bar enabled so check that there are menu items
			if (window["MenuItems"].array_items().size() == 0)
			{
				cout << "Menu bar specified for window " << window["Name"].string_value() << " but no menu items specified\n";
				exit(1);
			}
		}	
    	    	
        outfileUserSource << "    mw_util_set_rect(&r, " <<
        		(window["X"].int_value()) << ", " <<
				(window["Y"].int_value()) << ", " <<
				(window["Width"].int_value()) << ", " <<
				(window["Height"].int_value()) << ");\n" 
        		"    window_" << window["Name"].string_value() << "_handle = mw_add_window(&r,\n" 
        		"        \"" << window["Title"].string_value() << "\", \n" \
        		"        window_" << window["Name"].string_value() << "_paint_function,\n" 
				"        window_" << window["Name"].string_value() << "_message_function,\n        ";
        if (window["MenuItems"].array_items().size() == 0)
        {
        	outfileUserSource << "NULL,\n        0,\n        0";
        }
        else
        {
        	outfileUserSource << window["Name"].string_value() << "_menu_bar_labels" 
				",\n        sizeof(" << window["Name"].string_value() << "_menu_bar_labels)/sizeof(char *),\n        0"; 
        }
				
		if (window["Border"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_HAS_BORDER";
		}
		if (window["TitleBar"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_HAS_TITLE_BAR";
		}		
		if (window["CanClose"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_CAN_BE_CLOSED";
		}		
		if (window["VerticalScrollBarEnabled"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_VERT_SCROLL_BAR_ENABLED";
		}	
		if (window["HorizontalScrollBarEnabled"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_HORIZ_SCROLL_BAR_ENABLED";
		}			
		if (window["VerticalScrollBar"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_HAS_VERT_SCROLL_BAR";
		}	
		if (window["HorizontalScrollBar"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_HAS_HORIZ_SCROLL_BAR";
		}		
		if (window["MenuBar"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_HAS_MENU_BAR";
		}			
		if (window["MenuBarEnabled"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_MENU_BAR_ENABLED";
		}		
		if (window["Visible"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_IS_VISIBLE";
		}	
		if (window["Minimised"].bool_value())
		{
			outfileUserSource << " | MW_WINDOW_FLAG_IS_MINIMISED";
		}	
		if (large_size)
		{
			outfileUserSource << " | MW_WINDOW_FLAG_LARGE_SIZE";
		}							
		outfileUserSource << ",\n        NULL);\n";
        outfileUserSource << "\n";
        
        // create buttons
		for (auto& button : window["Buttons"].array_items())
		{
			// check presence and format of required fields
			if (button["Name"].string_value() == "")
			{
				cout << "No or blank Name value for button in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!button["X"].is_number())
			{
				cout << "No X value for button " << button["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!button["Y"].is_number())
			{
				cout << "No Y value for button " << button["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}		
			
			outfileUserSource << "    mw_util_safe_strcpy(button_" << button["Name"].string_value() << "_data.button_label, MW_UI_BUTTON_LABEL_MAX_CHARS, \"" <<
				button["Label"].string_value() << "\");\n";
			outfileUserSource << "    button_" << button["Name"].string_value() << "_handle = mw_ui_button_add_new(" << button["X"].int_value() << ",\n" 
				"        " << button["Y"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (button["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (button["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &button_" << button["Name"].string_value() << "_data);\n\n"; 	
		}
		
        // create labels
		for (auto& label : window["Labels"].array_items())
		{
			// check presence and format of required fields
			if (label["Name"].string_value() == "")
			{
				cout << "No or blank Name value for label in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!label["X"].is_number())
			{
				cout << "No X value for label " << label["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!label["Y"].is_number())
			{
				cout << "No Y value for label " << label["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
			if (!label["Width"].is_number())
			{
				cout << "No Width value for label " << label["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}			
					
			outfileUserSource << "    mw_util_safe_strcpy(label_" << label["Name"].string_value() << "_data.label, MW_UI_LABEL_MAX_CHARS, \"" <<
				label["Label"].string_value() << "\");\n";
			outfileUserSource << "    label_" << label["Name"].string_value() << "_handle = mw_ui_label_add_new(" << label["X"].int_value() << ",\n" 
				"        " << label["Y"].int_value() << ",\n" 
				"        " << label["Width"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (label["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (label["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &label_" << label["Name"].string_value() << "_data);\n\n"; 	
		}		
		
        // create check boxes
		for (auto& check_box : window["CheckBoxes"].array_items())
		{
			// check presence and format of required fields
			if (check_box["Name"].string_value() == "")
			{
				cout << "No or blank Name value for check box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!check_box["X"].is_number())
			{
				cout << "No X value for check box " << check_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!check_box["Y"].is_number())
			{
				cout << "No Y value for check box " << check_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
						
			outfileUserSource << "    mw_util_safe_strcpy(check_box_" << check_box["Name"].string_value() << "_data.label, MW_UI_CHECK_BOX_LABEL_MAX_CHARS, \"" <<
				check_box["Label"].string_value() << "\");\n";
			outfileUserSource << "    check_box_" << check_box["Name"].string_value() << "_handle = mw_ui_check_box_add_new(" << check_box["X"].int_value() << ",\n" 
				"        " << check_box["Y"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (check_box["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (check_box["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &check_box_" << check_box["Name"].string_value() << "_data);\n\n"; 	
		}		
		
        // create arrows
		for (auto& arrow : window["Arrows"].array_items())
		{				
			// check presence and format of required fields
			if (arrow["Name"].string_value() == "")
			{
				cout << "No or blank Name value for arrow in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!arrow["X"].is_number())
			{
				cout << "No X value for arrow " << arrow["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!arrow["Y"].is_number())
			{
				cout << "No Y value for arrow " << arrow["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
			if (!arrow["Direction"].is_string())
			{
				cout << "No Direction value for arrow " << arrow["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}				
						
			outfileUserSource << "    arrow_" << arrow["Name"].string_value() << "_data.mw_ui_arrow_direction = MW_UI_ARROW_";
			auto& f = std::use_facet<std::ctype<char>>(std::locale());
			f.toupper(const_cast<char *>(arrow["Direction"].string_value().data()), arrow["Direction"].string_value().data() + arrow["Direction"].string_value().size());			
			if (arrow["Direction"].string_value() != "UP" && arrow["Direction"].string_value() != "RIGHT" && arrow["Direction"].string_value() != "DOWN" && arrow["Direction"].string_value() != "LEFT")
			{
				cout << "Unknown value for arrow " << arrow["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);				
			}
			outfileUserSource << arrow["Direction"].string_value() << ";\n";
			outfileUserSource << "    arrow_" << arrow["Name"].string_value() << "_handle = mw_ui_arrow_add_new(" << arrow["X"].int_value() << ",\n" 
				"        " << arrow["Y"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (arrow["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (arrow["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &arrow_" << arrow["Name"].string_value() << "_data);\n\n"; 	
		}	
		
        // create progress bars
		for (auto& progress_bar : window["ProgressBars"].array_items())
		{
			// check presence and format of required fields
			if (progress_bar["Name"].string_value() == "")
			{
				cout << "No or blank Name value for progress bar in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!progress_bar["X"].is_number())
			{
				cout << "No X value for progress bar " << progress_bar["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!progress_bar["Y"].is_number())
			{
				cout << "No Y value for progress bar " << progress_bar["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
			if (!progress_bar["Width"].is_number())
			{
				cout << "No Width value for progress bar " << progress_bar["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}				
			if (!progress_bar["Height"].is_number())
			{
				cout << "No Height value for progress bar " << progress_bar["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
									
			outfileUserSource << "    progress_bar_" << progress_bar["Name"].string_value() << "_handle = mw_ui_progress_bar_add_new(" << progress_bar["X"].int_value() << ",\n" 
				"        " << progress_bar["Y"].int_value() << ",\n" 
				"        " << progress_bar["Width"].int_value() << ",\n" 
				"        " << progress_bar["Height"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (progress_bar["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (progress_bar["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &progress_bar_" << progress_bar["Name"].string_value() << "_data);\n\n"; 	
		}		

		// create horiz scroll bars
		for (auto& scroll_bar_horiz : window["ScrollBarsHoriz"].array_items())
		{
			// check presence and format of required fields
			if (scroll_bar_horiz["Name"].string_value() == "")
			{
				cout << "No or blank Name value for horizontal scroll bar in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!scroll_bar_horiz["X"].is_number())
			{
				cout << "No X value for horizontal scroll bar " << scroll_bar_horiz["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!scroll_bar_horiz["Y"].is_number())
			{
				cout << "No Y value for horizontal scroll bar " << scroll_bar_horiz["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
			if (!scroll_bar_horiz["Width"].is_number())
			{
				cout << "No Width value for horizontal scroll bar " << scroll_bar_horiz["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}				
						
			outfileUserSource << "    scroll_bar_horiz_" << scroll_bar_horiz["Name"].string_value() << "_handle = mw_ui_scroll_bar_horiz_add_new(" << scroll_bar_horiz["X"].int_value() << ",\n" 
				"        " << scroll_bar_horiz["Y"].int_value() << ",\n" 
				"        " << scroll_bar_horiz["Width"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (scroll_bar_horiz["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (scroll_bar_horiz["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &scroll_bar_horiz_" << scroll_bar_horiz["Name"].string_value() << "_data);\n\n"; 	
		}	
		
		// create vert scroll bars
		for (auto& scroll_bar_vert : window["ScrollBarsVert"].array_items())
		{
			// check presence and format of required fields
			if (scroll_bar_vert["Name"].string_value() == "")
			{
				cout << "No or blank Name value for vertical scroll bar in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!scroll_bar_vert["X"].is_number())
			{
				cout << "No X value for vertical scroll bar " << scroll_bar_vert["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!scroll_bar_vert["Y"].is_number())
			{
				cout << "No Y value for vertical scroll bar " << scroll_bar_vert["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
			if (!scroll_bar_vert["Height"].is_number())
			{
				cout << "No Height value for vertical scroll bar " << scroll_bar_vert["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}				
						
			outfileUserSource << "    scroll_bar_vert_" << scroll_bar_vert["Name"].string_value() << "_handle = mw_ui_scroll_bar_vert_add_new(" << scroll_bar_vert["X"].int_value() << ",\n" 
				"        " << scroll_bar_vert["Y"].int_value() << ",\n" 
				"        " << scroll_bar_vert["Height"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (scroll_bar_vert["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (scroll_bar_vert["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &scroll_bar_vert_" << scroll_bar_vert["Name"].string_value() << "_data);\n\n"; 	
		}		
		
		// create radio buttons
		for (auto& radio_button : window["RadioButtons"].array_items())
		{
			// check presence and format of required fields
			if (radio_button["Name"].string_value() == "")
			{
				cout << "No or blank Name value for radio buttons in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!radio_button["X"].is_number())
			{
				cout << "No X value for radio buttons " << radio_button["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!radio_button["Y"].is_number())
			{
				cout << "No Y value for radio buttons " << radio_button["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
			if (!radio_button["Width"].is_number())
			{
				cout << "No Width value for radio buttons " << radio_button["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
			if (!radio_button["Labels"].is_array())
			{
				cout << "No Labels values for radio buttons " << radio_button["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}							
						
			outfileUserSource << "    radio_button_" << radio_button["Name"].string_value() << "_data.number_of_items = (sizeof(radio_button_" << 
				radio_button["Name"].string_value() << "_labels)/sizeof(char *));\n";
			outfileUserSource << "    radio_button_" << radio_button["Name"].string_value() << "_data.radio_button_labels = radio_button_" << 
				radio_button["Name"].string_value() << "_labels;\n";
			outfileUserSource << "    radio_button_" << radio_button["Name"].string_value() << "_handle = mw_ui_radio_button_add_new(" << radio_button["X"].int_value() << ",\n" 
				"        " << radio_button["Y"].int_value() << ",\n" 
				"        " << radio_button["Width"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (radio_button["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (radio_button["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &radio_button_" << radio_button["Name"].string_value() << "_data);\n\n"; 	
		}			
		
		// create list boxes
		for (auto& list_box : window["ListBoxes"].array_items())
		{
			// check presence and format of required fields
			if (list_box["Name"].string_value() == "")
			{
				cout << "No or blank Name value for list box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!list_box["X"].is_number())
			{
				cout << "No X value for list box " << list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!list_box["Y"].is_number())
			{
				cout << "No Y value for list box " << list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!list_box["Width"].is_number())
			{
				cout << "No Width value for list box " << list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}					
			if (!list_box["Lines"].is_number())
			{
				cout << "No Lines value for list box " << list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}		
			if (!list_box["Labels"].is_array())
			{
				cout << "No Labels values for list box " << list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	
											
			outfileUserSource << "    list_box_" << list_box["Name"].string_value() << "_data.line_enables = MW_ALL_ITEMS_ENABLED;\n";
			outfileUserSource << "    list_box_" << list_box["Name"].string_value() << "_data.number_of_lines = " << list_box["Lines"].int_value() << ";\n";
			outfileUserSource << "    list_box_" << list_box["Name"].string_value() << "_data.number_of_items = (sizeof(list_box_" << 
				list_box["Name"].string_value() << "_entries)/sizeof(mw_ui_list_box_entry));\n";
			outfileUserSource << "    list_box_" << list_box["Name"].string_value() << "_data.list_box_entries = list_box_" << 
				list_box["Name"].string_value() << "_entries;\n";
			outfileUserSource << "    list_box_" << list_box["Name"].string_value() << "_handle = mw_ui_list_box_add_new(" << list_box["X"].int_value() << ",\n" 
				"        " << list_box["Y"].int_value() << ",\n" 
				"        " << list_box["Width"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (list_box["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (list_box["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &list_box_" << list_box["Name"].string_value() << "_data);\n\n"; 	
		}			

		// create text boxes
		for (auto& text_box : window["TextBoxes"].array_items())
		{
			// check presence and format of required fields
			if (text_box["Name"].string_value() == "")
			{
				cout << "No or blank Name value for text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!text_box["X"].is_number())
			{
				cout << "No X value for text box " << text_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!text_box["Y"].is_number())
			{
				cout << "No Y value for text box " << text_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!text_box["Width"].is_number())
			{
				cout << "No Width value for text box " << text_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}					
			if (!text_box["Height"].is_number())
			{
				cout << "No Height value for text box " << text_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}			
			if (text_box["Justification"].string_value() == "")
			{
				cout << "No or blank Justification value for text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}	
			if (text_box["BackgroundColour"].string_value() == "")
			{
				cout << "No or blank BackgroundColour value for text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}	
			if (text_box["ForegroundColour"].string_value() == "")
			{
				cout << "No or blank ForegroundColour value for text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}				
			if (text_box["Font"].string_value() == "")
			{
				cout << "No or blank Font value for text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}	
			
			// set data values here
			outfileUserSource << "    text_box_" << text_box["Name"].string_value() << "_data.bg_colour = " << text_box["BackgroundColour"].string_value() << ";\n";			
			outfileUserSource << "    text_box_" << text_box["Name"].string_value() << "_data.fg_colour = " << text_box["ForegroundColour"].string_value() << ";\n";				
			outfileUserSource << "    text_box_" << text_box["Name"].string_value() << "_data.text = \"Generated by MiniWin code generator.\";\n";
			outfileUserSource << "    text_box_" << text_box["Name"].string_value() << "_data.tt_font = &" << text_box["Font"].string_value() << ";\n";				
			outfileUserSource << "    text_box_" << text_box["Name"].string_value() << "_data.justification = ";
			
			if (text_box["Justification"] == "Left")
			{
				outfileUserSource << "MW_GL_TT_LEFT_JUSTIFIED";
			}
			else if (text_box["Justification"] == "Right")
			{
				outfileUserSource << "MW_GL_TT_RIGHT_JUSTIFIED";				
			}
			else if (text_box["Justification"] == "Centre")
			{
				outfileUserSource << "MW_GL_TT_CENTRE_JUSTIFIED";				
			}
			else if (text_box["Justification"] == "Full")
			{
				outfileUserSource << "MW_GL_TT_FULL_JUSTIFIED";				
			}
			else
			{
				cout << "Unrecognised justification value for text box in window " << window["Name"].string_value() << endl;
				exit(1);					
			}
			outfileUserSource << ";\n";			
			outfileUserSource << "    mw_util_set_rect(&r, " <<
					(text_box["X"].int_value()) << ", " <<
					(text_box["Y"].int_value()) << ", " <<
					(text_box["Width"].int_value()) << ", " <<
					(text_box["Height"].int_value()) << ");\n" <<					
					"    text_box_" << text_box["Name"].string_value() << "_handle = mw_ui_text_box_add_new(&r,\n" 
					"        window_" << window["Name"].string_value() << "_handle,\n" 
					"        0";
			if (text_box["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (text_box["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &text_box_" << text_box["Name"].string_value() << "_data);\n\n"; 	
		}
		
		// create scrolling list boxes
		for (auto& scrolling_list_box : window["ScrollingListBoxes"].array_items())
		{
			// check presence and format of required fields
			if (scrolling_list_box["Name"].string_value() == "")
			{
				cout << "No or blank Name value for scrolling list box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!scrolling_list_box["X"].is_number())
			{
				cout << "No X value for scrolling list box " << scrolling_list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!scrolling_list_box["Y"].is_number())
			{
				cout << "No Y value for scrolling list box " << scrolling_list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!scrolling_list_box["Width"].is_number())
			{
				cout << "No Width value for scrolling list box " << scrolling_list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}					
			if (!scrolling_list_box["Lines"].is_number())
			{
				cout << "No Lines value for scrolling list box " << scrolling_list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}		
			if (!scrolling_list_box["Labels"].is_array())
			{
				cout << "No Labels values for scrolling list box " << scrolling_list_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}	

			outfileUserSource << "    scrolling_list_box_" << scrolling_list_box["Name"].string_value() << "_data.line_enables = MW_ALL_ITEMS_ENABLED;\n";
			outfileUserSource << "    scrolling_list_box_" << scrolling_list_box["Name"].string_value() << "_data.number_of_lines = " << scrolling_list_box["Lines"].int_value() << ";\n";
			outfileUserSource << "    scrolling_list_box_" << scrolling_list_box["Name"].string_value() << "_data.number_of_items = (sizeof(scrolling_list_box_" << 
				scrolling_list_box["Name"].string_value() << "_entries)/sizeof(mw_ui_list_box_entry));\n";
			outfileUserSource << "    scrolling_list_box_" << scrolling_list_box["Name"].string_value() << "_data.list_box_entries = scrolling_list_box_" << 
				scrolling_list_box["Name"].string_value() << "_entries;\n";
			outfileUserSource << "    scrolling_list_box_" << scrolling_list_box["Name"].string_value() << "_handle = mw_ui_list_box_add_new(" << scrolling_list_box["X"].int_value() << ",\n" 
				"        " << scrolling_list_box["Y"].int_value() << ",\n" 
				"        " << scrolling_list_box["Width"].int_value() << ",\n" 
			    "        window_" << window["Name"].string_value() << "_handle,\n" 
			    "        0";
			if (scrolling_list_box["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (scrolling_list_box["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &scrolling_list_box_" << scrolling_list_box["Name"].string_value() << "_data);\n\n"; 	
			    
			if (large_size)
			{
				outfileUserSource << "    scrolling_list_box_scroll_bar_vert_" << scrolling_list_box["Name"].string_value() << "_handle = mw_ui_scroll_bar_vert_add_new(" << (scrolling_list_box["X"].int_value() + scrolling_list_box["Width"].int_value()) << ",\n" 
					"        " << scrolling_list_box["Y"].int_value() << ",\n" 
					"        " << scrolling_list_box["Lines"].int_value() << " * MW_UI_LIST_BOX_LARGE_ROW_HEIGHT,\n" 
					"        window_" << window["Name"].string_value() << "_handle,\n" 
					"        0";				
			}   
			else
			{    			    
				outfileUserSource << "    scrolling_list_box_scroll_bar_vert_" << scrolling_list_box["Name"].string_value() << "_handle = mw_ui_scroll_bar_vert_add_new(" << (scrolling_list_box["X"].int_value() + scrolling_list_box["Width"].int_value()) << ",\n" 
					"        " << scrolling_list_box["Y"].int_value() << ",\n" 
					"        " << scrolling_list_box["Lines"].int_value() << " * MW_UI_LIST_BOX_ROW_HEIGHT,\n" 
					"        window_" << window["Name"].string_value() << "_handle,\n" 
					"        0";
			}
			if (scrolling_list_box["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (scrolling_list_box["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &scrolling_list_box_scroll_bar_vert_" << scrolling_list_box["Name"].string_value() << "_data);\n\n"; 				        
		}		

		// create scrolling text boxes
		for (auto& scrolling_text_box : window["ScrollingTextBoxes"].array_items())
		{
			// check presence and format of required fields
			if (scrolling_text_box["Name"].string_value() == "")
			{
				cout << "No or blank Name value for scrolling text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}
			if (!scrolling_text_box["X"].is_number())
			{
				cout << "No X value for scrolling text box " << scrolling_text_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!scrolling_text_box["Y"].is_number())
			{
				cout << "No Y value for scrolling text box " << scrolling_text_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}
			if (!scrolling_text_box["Width"].is_number())
			{
				cout << "No Width value for scrolling text box " << scrolling_text_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}					
			if (!scrolling_text_box["Height"].is_number())
			{
				cout << "No Height value for scrolling text box " << scrolling_text_box["Name"].string_value() << " in window " << window["Name"].string_value() << endl;
				exit(1);
			}		
			if (scrolling_text_box["Justification"].string_value() == "")
			{
				cout << "No or blank Justification value for scrolling text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}	
			if (scrolling_text_box["BackgroundColour"].string_value() == "")
			{
				cout << "No or blank BackgroundColour value for scrolling text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}	
			if (scrolling_text_box["ForegroundColour"].string_value() == "")
			{
				cout << "No or blank ForegroundColour value for scrolling text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}				
			if (scrolling_text_box["Font"].string_value() == "")
			{
				cout << "No or blank Font value for scrolling text box in window " << window["Name"].string_value() << endl;
				exit(1);			
			}	

			// set data values here
			outfileUserSource << "    scrolling_text_box_" << scrolling_text_box["Name"].string_value() << "_data.bg_colour = " << scrolling_text_box["BackgroundColour"].string_value() << ";\n";			
			outfileUserSource << "    scrolling_text_box_" << scrolling_text_box["Name"].string_value() << "_data.fg_colour = " << scrolling_text_box["ForegroundColour"].string_value() << ";\n";				
			outfileUserSource << "    scrolling_text_box_" << scrolling_text_box["Name"].string_value() << "_data.text = \"Generated by MiniWin code generator.\\n\\n\\n\\n\\n\\n\\n\\n\\n\\n\";\n";
			outfileUserSource << "    scrolling_text_box_" << scrolling_text_box["Name"].string_value() << "_data.tt_font = &" << scrolling_text_box["Font"].string_value() << ";\n";				
			outfileUserSource << "    scrolling_text_box_" << scrolling_text_box["Name"].string_value() << "_data.justification = ";
			
			if (scrolling_text_box["Justification"] == "Left")
			{
				outfileUserSource << "MW_GL_TT_LEFT_JUSTIFIED";
			}
			else if (scrolling_text_box["Justification"] == "Right")
			{
				outfileUserSource << "MW_GL_TT_RIGHT_JUSTIFIED";				
			}
			else if (scrolling_text_box["Justification"] == "Centre")
			{
				outfileUserSource << "MW_GL_TT_CENTRE_JUSTIFIED";				
			}
			else if (scrolling_text_box["Justification"] == "Full")
			{
				outfileUserSource << "MW_GL_TT_FULL_JUSTIFIED";				
			}
			else
			{
				cout << "Unrecognised justification value for text box in window " << window["Name"].string_value() << endl;
				exit(1);					
			}
			outfileUserSource << ";\n";			
			outfileUserSource << "    mw_util_set_rect(&r, " <<
					(scrolling_text_box["X"].int_value()) << ", " <<
					(scrolling_text_box["Y"].int_value()) << ", " <<
					(scrolling_text_box["Width"].int_value()) << ", " <<
					(scrolling_text_box["Height"].int_value()) << ");\n" <<					
					"    scrolling_text_box_" << scrolling_text_box["Name"].string_value() << "_handle = mw_ui_text_box_add_new(&r,\n" 
					"        window_" << window["Name"].string_value() << "_handle,\n" 
					"        0";
			if (scrolling_text_box["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (scrolling_text_box["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &scrolling_text_box_" << scrolling_text_box["Name"].string_value() << "_data);\n\n"; 			
			if (large_size)
			{
				outfileUserSource << "    scrolling_text_box_scroll_bar_vert_" << scrolling_text_box["Name"].string_value() << "_handle = mw_ui_scroll_bar_vert_add_new(" << (scrolling_text_box["X"].int_value() + scrolling_text_box["Width"].int_value()) << ",\n" 
					"        " << scrolling_text_box["Y"].int_value() << ",\n" 
					"        " << scrolling_text_box["Height"].int_value() << ",\n" 
					"        window_" << window["Name"].string_value() << "_handle,\n" 
					"        0";				
			}   
			else
			{    			    
				outfileUserSource << "    scrolling_text_box_scroll_bar_vert_" << scrolling_text_box["Name"].string_value() << "_handle = mw_ui_scroll_bar_vert_add_new(" << (scrolling_text_box["X"].int_value() + scrolling_text_box["Width"].int_value()) << ",\n" 
					"        " << scrolling_text_box["Y"].int_value() << ",\n" 
					"        " << scrolling_text_box["Height"].int_value() << ",\n" 
					"        window_" << window["Name"].string_value() << "_handle,\n" 
					"        0";
			}
			if (scrolling_text_box["Visible"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_VISIBLE";
			}	
			if (scrolling_text_box["Enabled"].bool_value())
			{
				outfileUserSource << " | MW_CONTROL_FLAG_IS_ENABLED";
			}			
			if (large_size)
			{
				outfileUserSource << " | MW_CONTROL_FLAG_LARGE_SIZE";
			}	  
			outfileUserSource << ",\n" 
			    "        &scrolling_text_box_scroll_bar_vert_" << scrolling_text_box["Name"].string_value() << "_data);\n\n"; 				                    
		}	
    }

    outfileUserSource << "    mw_paint_all();\n}\n";
    outfileUserSource.close();

	// create window .c and .h files
    for (auto &window : json["Windows"].array_items())
    {
    	string windowName = window["Name"].string_value();
    	std::ofstream outfileWindowSource("../../" + json["TargetName"].string_value() + "/" + json["TargetName"].string_value() + "_Common/" + windowName + ".c");
    	if (!outfileWindowSource.is_open())
    	{
    		cout << "Could not create file\n";
    		exit(1);
    	}
    	outfileWindowSource << "/* " << windowName + ".c generated by MiniWin code generator. */\n\n" 
					"#include \"miniwin.h\"\n\n";
    	outfileWindowSource << "typedef struct\n{    /* Add your data members here */\n} window_" << windowName << "_data_t;\n\n";
    	outfileWindowSource << "static window_" << windowName << "_data_t window_" << windowName << "_data;\n\n";
    	    	
    	// create buttons extern references
		if (window["Buttons"].array_items().size() > 0)
		{
    		for (auto& button : window["Buttons"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t button_" + button["Name"].string_value() + "_handle;\n";
			}
		}
		
    	// create labels extern references
		if (window["Labels"].array_items().size() > 0)
		{
    		for (auto& label : window["Labels"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t label_" + label["Name"].string_value() + "_handle;\n";
			}
		}		
		
    	// create check boxes extern references
		if (window["CheckBoxes"].array_items().size() > 0)
		{
    		for (auto& check_box : window["CheckBoxes"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t check_box_" + check_box["Name"].string_value() + "_handle;\n";
			}
		}			
		
		// create arrows extern references
		if (window["Arrows"].array_items().size() > 0)
		{
    		for (auto& arrow : window["Arrows"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t arrow_" + arrow["Name"].string_value() + "_handle;\n";
			}
		}		
				
    	// create progress bars extern references
		if (window["ProgressBars"].array_items().size() > 0)
		{
    		for (auto& progress_bar : window["ProgressBars"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t progress_bar_" + progress_bar["Name"].string_value() + "_handle;\n";
			}
		}		
		
    	// create horizontal scroll bars extern references
		if (window["ScrollBarsHoriz"].array_items().size() > 0)
		{
    		for (auto& scroll_bar_horiz : window["ScrollBarsHoriz"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t scroll_bar_horiz_" + scroll_bar_horiz["Name"].string_value() + "_handle;\n";
			}
		}		
		
    	// create vertical scroll bars extern references
		if (window["ScrollBarsVert"].array_items().size() > 0)
		{
    		for (auto& scroll_bar_vert : window["ScrollBarsVert"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t scroll_bar_vert_" + scroll_bar_vert["Name"].string_value() + "_handle;\n";
			}
		}		
		
    	// create radio buttons extern references
		if (window["RadioButtons"].array_items().size() > 0)
		{
    		for (auto& radio_button : window["RadioButtons"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t radio_button_" + radio_button["Name"].string_value() + "_handle;\n";
			}
		}		
		
    	// create list boxes extern references
		if (window["ListBoxes"].array_items().size() > 0)
		{
    		for (auto& list_box : window["ListBoxes"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t list_box_" + list_box["Name"].string_value() + "_handle;\n";
			}
		}						
		
    	// create text boxes extern references
		if (window["TextBoxes"].array_items().size() > 0)
		{
    		for (auto& text_box : window["TextBoxes"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t text_box_" + text_box["Name"].string_value() + "_handle;\n";
			}
		}			
		
    	// create scrolling list boxes extern references
		if (window["ScrollingListBoxes"].array_items().size() > 0)
		{
    		for (auto& scrolling_list_box : window["ScrollingListBoxes"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t scrolling_list_box_" + scrolling_list_box["Name"].string_value() + "_handle;\n";
		    	outfileWindowSource << 
					"extern mw_handle_t scrolling_list_box_scroll_bar_vert_" + scrolling_list_box["Name"].string_value() + "_handle;\n";				
			}
		}			
		
    	// create scrolling text boxes extern references
		if (window["ScrollingTextBoxes"].array_items().size() > 0)
		{
    		for (auto& scrolling_text_box : window["ScrollingTextBoxes"].array_items())
			{
		    	outfileWindowSource << 
					"extern mw_handle_t scrolling_text_box_" + scrolling_text_box["Name"].string_value() + "_handle;\n";
		    	outfileWindowSource << 
					"extern mw_handle_t scrolling_text_box_scroll_bar_vert_" + scrolling_text_box["Name"].string_value() + "_handle;\n";				
			}
		}				
    	    	
    	outfileWindowSource << 
    	            "\nvoid window_" << windowName << "_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info)\n" 
    				"{\n    MW_ASSERT(draw_info, \"Null pointer parameter\");\n\n" 
    				"    /* Fill window's client area with solid white */\n" 
					"    mw_gl_set_fill(MW_GL_FILL);\n" 
					"    mw_gl_set_solid_fill_colour(MW_HAL_LCD_WHITE);\n" 
					"    mw_gl_set_border(MW_GL_BORDER_OFF);\n" 
					"    mw_gl_clear_pattern();\n" 
					"    mw_gl_rectangle(draw_info,\n" 
					"        0, 0,\n" 
					"        mw_get_window_client_rect(window_handle).width,\n" 
					"        mw_get_window_client_rect(window_handle).height);\n\n" 
					"    /* Add you window painting code here */\n}\n\n";
    	outfileWindowSource << 
    	            "void window_" << windowName << "_message_function(const mw_message_t *message)\n" 
       				"{\n    MW_ASSERT(message, \"Null pointer parameter\");\n\n" 
       	            "    /* Next line stops compiler warnings as variable is currently unused */\n";
    	outfileWindowSource << 
    	            "    (void)window_" << windowName << "_data;\n\n" 
       				"    switch (message->message_id)\n" 
					"    {\n"
       				"    case MW_WINDOW_CREATED_MESSAGE:\n" 
       				"        /* Add any window initiaslisation code here */\n" 
       				"        break;\n\n";
       				
		if (window["MenuItems"].array_items().size() > 0)
		{
			outfileWindowSource << 			
       				"    case MW_MENU_BAR_ITEM_PRESSED_MESSAGE:\n" 
       				"        /* Add window menu handling code here */\n"
       				"        break;\n\n";
   		}      
   		
		if (window["VerticalScrollBar"].bool_value())
		{
			outfileWindowSource << 			
       				"    case MW_WINDOW_VERT_SCROLL_BAR_SCROLLED_MESSAGE:\n" 
       				"        /* Add window vertical scroll bar scrolled handling code here */\n"
       				"        break;\n\n";
   		}      		
   		
		if (window["HorizontalScrollBar"].bool_value())
		{
			outfileWindowSource << 			
       				"    case MW_WINDOW_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE:\n" 
       				"        /* Add window horizontal scroll bar scrolled handling code here */\n"
       				"        break;\n\n";
   		}      		 				

		// create buttons message handlers
		if (window["Buttons"].array_items().size() > 0)
		{
			outfileWindowSource << 
						"    case MW_BUTTON_PRESSED_MESSAGE:\n"; 
			bool first = true;
			for (auto& button : window["Buttons"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "button_" + button["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "button_" + button["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Add your handler code for this control here */\n" 
						"        }\n";
			}
			outfileWindowSource << "        break;\n\n";
		}

		// create check boxes message handlers
		if (window["CheckBoxes"].array_items().size() > 0)
		{
			outfileWindowSource << 
						"    case MW_CHECKBOX_STATE_CHANGE_MESSAGE:\n"; 
			bool first = true;
			for (auto& check_box : window["CheckBoxes"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "check_box_" + check_box["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "check_box_" + check_box["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Add your handler code for this control here */\n" 
						"        }\n";
			}
			outfileWindowSource << "        break;\n\n";
		}
		
		// create arrows message handlers
		if (window["Arrows"].array_items().size() > 0)
		{
			outfileWindowSource << 
						"    case MW_ARROW_PRESSED_MESSAGE:\n"; 
			bool first = true;
			for (auto& arrow : window["Arrows"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "arrow_" + arrow["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "arrow_" + arrow["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Add your handler code for this control here */\n" 
						"        }\n";
			}
			outfileWindowSource << "        break;\n\n";
		}		
		
		// create horiz scroll bars message handlers
		if (window["ScrollBarsHoriz"].array_items().size() > 0)
		{
			outfileWindowSource << 
						"    case MW_CONTROL_HORIZ_SCROLL_BAR_SCROLLED_MESSAGE:\n"; 
			bool first = true;
			for (auto& scroll_bar_horiz : window["ScrollBarsHoriz"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "scroll_bar_horiz_" + scroll_bar_horiz["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "scroll_bar_horiz_" + scroll_bar_horiz["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Add your handler code for this control here */\n" 
						"        }\n";
			}
			outfileWindowSource << "        break;\n\n";
		}	
		
		// create vert scroll bars message handlers
		if (window["ScrollBarsVert"].array_items().size() > 0 || window["ScrollingListBoxes"].array_items().size() > 0 || window["ScrollingTextBoxes"].array_items().size() > 0)
		{
			outfileWindowSource << 
						"    case MW_CONTROL_VERT_SCROLL_BAR_SCROLLED_MESSAGE:\n"; 
			bool first = true;
			for (auto& scroll_bar_vert : window["ScrollBarsVert"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "scroll_bar_vert_" + scroll_bar_vert["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "scroll_bar_vert_" + scroll_bar_vert["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Add your handler code for this control here */\n" 
						"        }\n";
			}
			for (auto& scrolling_list_box_scroll_bar_vert : window["ScrollingListBoxes"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "scrolling_list_box_scroll_bar_vert_" + scrolling_list_box_scroll_bar_vert["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "scrolling_list_box_scroll_bar_vert_" + scrolling_list_box_scroll_bar_vert["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Post message to list box from its associated scroll bar to get it to scroll */\n"
						"            mw_post_message(MW_LIST_BOX_SCROLL_BAR_POSITION_MESSAGE,\n"
						"                message->recipient_handle,\n"
						"                scrolling_list_box_" << scrolling_list_box_scroll_bar_vert["Name"].string_value() << "_handle,\n"
						"                message->message_data,\n"
						"                MW_UNUSED_MESSAGE_PARAMETER,\n"
						"                MW_CONTROL_MESSAGE);\n"
						"\n"
						"            /* Paint the list box to show its new scrolled position */\n"
						"            mw_paint_control(scrolling_list_box_" << scrolling_list_box_scroll_bar_vert["Name"].string_value() << "_handle);\n"
						"        }\n";
			}			
			for (auto& scrolling_text_box_scroll_bar_vert : window["ScrollingTextBoxes"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "scrolling_text_box_scroll_bar_vert_" + scrolling_text_box_scroll_bar_vert["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "scrolling_text_box_scroll_bar_vert_" + scrolling_text_box_scroll_bar_vert["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Post message to text box from its associated scroll bar to get it to scroll */\n"
						"            mw_post_message(MW_TEXT_BOX_SCROLL_BAR_POSITION_MESSAGE,\n"
						"                message->recipient_handle,\n"
						"                scrolling_text_box_" << scrolling_text_box_scroll_bar_vert["Name"].string_value() << "_handle,\n"
						"                message->message_data,\n"
						"                MW_UNUSED_MESSAGE_PARAMETER,\n"
						"                MW_CONTROL_MESSAGE);\n"
						"\n"
						"            /* Paint the text box to show its new scrolled position */\n"
						"            mw_paint_control(scrolling_text_box_" << scrolling_text_box_scroll_bar_vert["Name"].string_value() << "_handle);\n"
						"        }\n";
			}					
			outfileWindowSource << "        break;\n\n";
		}					
		
		// create radio buttons message handlers
		if (window["RadioButtons"].array_items().size() > 0)
		{
			outfileWindowSource << 
						"    case MW_RADIO_BUTTON_ITEM_SELECTED_MESSAGE:\n"; 
			bool first = true;
			for (auto& radio_button : window["RadioButtons"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "radio_button_" + radio_button["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "radio_button_" + radio_button["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Add your handler code for this control here */\n" 
						"        }\n";
			}
			outfileWindowSource << "        break;\n\n";
		}			

		// create list boxes message handlers
		if (window["ListBoxes"].array_items().size() > 0 || window["ScrollingListBoxes"].array_items().size() > 0)
		{
			outfileWindowSource << 
						"    case MW_LIST_BOX_ITEM_PRESSED_MESSAGE:\n"; 
			bool first = true;
			for (auto& list_box : window["ListBoxes"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "list_box_" + list_box["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "list_box_" + list_box["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Add your handler code for this control here */\n" 
						"        }\n";
			}
			for (auto& scrolling_list_box : window["ScrollingListBoxes"].array_items())
			{
				if (first)
				{
					outfileWindowSource <<
						"        if (message->sender_handle == " << "scrolling_list_box_" + scrolling_list_box["Name"].string_value() + "_handle" << ")\n";
					first = false;
				}
				else
				{
					outfileWindowSource <<
						"        else if (message->sender_handle == " << "scrolling_list_box_" + scrolling_list_box["Name"].string_value() + "_handle" << ")\n";
				}
				outfileWindowSource <<		
						"        {\n" 
						"            /* Add your handler code for this control here */\n" 
						"        }\n";
			}			
			outfileWindowSource << "        break;\n\n";
		}       				
       				
       	outfileWindowSource << 
					"    default:\n" 
					"        break;\n    }\n}\n";
    	outfileWindowSource.close();

    	std::ofstream outfileWindowHeader("../../" + json["TargetName"].string_value() + "/" + json["TargetName"].string_value() + "_Common/" + windowName + ".h");
    	if (!outfileWindowHeader.is_open())
    	{
    		cout << "Could not create file\n";
    		exit(1);
    	}
    	outfileWindowHeader << "/* " << windowName + ".h generated by MiniWin code generator. */\n\n";
    	outfileWindowHeader << "#ifndef WINDOW_" << windowName << "_H\n" 
    			   "#define WINDOW_" << windowName << "_H\n\n" 
                   "#ifdef __cplusplus\n"
                   " extern \"C\" {\n"
                   "#endif\n\n"
				   "#include \"miniwin.h\"\n\n" 
                   "/**\n"
                   " * Window paint routine, called by window manager.\n"
                   " *\n"
                   " * @param window_handle The window identifier in the array of windows\n"
                   " * @param draw_info Draw info structure describing offset and clip region\n"
                   " * @note Do not call this directly from user code\n"
                   " */\n"
				   "void window_" << windowName << "_paint_function(mw_handle_t window_handle, const mw_gl_draw_info_t *draw_info);\n\n" 
                   "/**\n"
                   " * Window message handler called by the window manager.\n"
                   " *\n"
                   " * @param message The message to be processed\n"
                   " * @note Do not call this directly from user code\n"
                   " */\n"
				   "void window_" << windowName << "_message_function(const mw_message_t *message);\n\n" 
                   "#ifdef __cplusplus\n"
                   "}\n"
				   "#endif\n\n"
 				   "#endif\n";
                   
    	outfileWindowHeader.close();
    }

    // create main.c source file
	std::ofstream outfileMainSource("../../" + json["TargetName"].string_value() + "/" + json["TargetName"].string_value() + "_Common/main.c", std::ios::binary);

	if (!outfileMainSource.is_open())
	{
		cout << "Could not create file\n";
		exit(1);
	}

	outfileMainSource << "#include \"miniwin.h\"\n#include \"app.h\"\n\n"
				"int main(void)\n{\n"
				"	app_init();\n	mw_init();\n\n"
				"	while (true)\n	{\n"
				"		app_main_loop_process();\n		mw_process_message();\n"
				"	}\n}\n";
	outfileMainSource.close();

    // create app.h header file
	std::ofstream outfileAppHeader("../../" + json["TargetName"].string_value() + "/" + json["TargetType"].string_value() + "/src/app.h", std::ios::binary);

	if (!outfileAppHeader.is_open())
	{
		cout << "Could not create file\n";
		exit(1);
	}
	
	outfileAppHeader << "#ifndef APP_H\n"
			"#define APP_H\n"
			"\n"
			"#ifdef __cplusplus\n"
			" extern \"C\" {\n"
			"#endif\n\n"
			"void app_init(void);\n"
			"void app_main_loop_process(void);\n\n"
			"#ifdef __cplusplus\n"
			"}\n"
			"#endif\n\n"
			"#endif\n";
	outfileAppHeader.close();

	// create app.c source file
	std::ofstream outfileAppSource("../../" + json["TargetName"].string_value() + "/" + json["TargetType"].string_value() + "/src/app.c", std::ios::binary);

	if (!outfileAppSource.is_open())
	{
		cout << "Could not create file\n";
		exit(1);
	}	
	if (json["TargetType"].string_value() == "Linux")
	{ 
			outfileAppSource << "#include <X11/Xlib.h>\n"
			"#include \"miniwin.h\"\n\n"
			"Display *display;\n"
			"Window frame_window;\n"
			"GC graphical_context;\n\n"
			"void app_init(void)\n"
			"{\n"
			"	static	Visual *visual;\n"
			"	static int depth;\n"
			"	static XSetWindowAttributes frame_attributes;\n\n"
			"	display = XOpenDisplay(NULL);\n"
			"	visual = DefaultVisual(display, 0);\n"
			"	depth  = DefaultDepth(display, 0);\n\n"
			"	frame_attributes.background_pixel = XBlackPixel(display, 0);\n\n"
			"	frame_window = XCreateWindow(display, \n"
			"		XRootWindow(display, 0),\n"
			"		0,\n"
			"		0,\n" 
			"		MW_ROOT_WIDTH,\n"
			"		MW_ROOT_HEIGHT,\n"
			"		5,\n"
			"		depth,\n"
			"		InputOutput,\n" 
			"		visual,\n" 
			"		CWBackPixel,\n"
			"		&frame_attributes);\n\n"
			"	XStoreName(display, frame_window, \"MiniWin Sim\");\n\n"
			"	XSelectInput(display, frame_window, ExposureMask | StructureNotifyMask);\n\n"
			"	graphical_context = XCreateGC( display, frame_window, 0, 0 );\n\n"
			"	XMapWindow(display, frame_window);\n"
			"	XFlush(display);\n"
			"}\n\n"
			"void app_main_loop_process(void)\n"
			"{\n"
			"}\n";
	}
	else
	{
		outfileAppSource << "#include <windows.h>\n"
			"#include <stdbool.h>\n"
			"#include \"miniwin.h\"\n\n"
			"#define WINDOW_START_LOCATION_X		100\n"
			"#define WINDOW_START_LOCATION_Y		100\n\n"
			"HWND hwnd;\n"
			"bool mouse_down = false;\n"
			"SHORT mx;\n"
			"SHORT my;\n\n"
			"static VOID MouseEventProc(LPARAM lp);\n"
			"static long __stdcall WindowProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp);\n\n"
			"static VOID MouseEventProc(LPARAM lp)\n"
			"{\n"
			"    POINTS mouse_point;\n\n"
			"    mouse_point = MAKEPOINTS(lp);\n"
			"	mx = mouse_point.x;\n"
			"	my = mouse_point.y;\n\n"
			"	if (mx < 0)\n"
			"	{\n"
			"		mx = 0;\n"
			"	}\n\n"
			"	if (my < 0)\n"
			"	{\n"
			"		my = 0;\n"
			"	}\n\n"
			"	if (mx > MW_ROOT_WIDTH - 1)\n"
			"	{\n"
			"		mx = MW_ROOT_WIDTH - 1;\n"
			"	}\n\n"
			"	if (my > MW_ROOT_HEIGHT - 1)\n"
			"	{\n"
			"		my = MW_ROOT_HEIGHT - 1;\n"
			"	}\n"
			"}\n\n"
			"static long __stdcall WindowProc(HWND window, unsigned int msg, WPARAM wp, LPARAM lp)\n"
			"{\n"
			"    switch(msg)\n"
			"    {\n"
			"	case WM_DESTROY:\n"
			"		PostQuitMessage(0);\n"
			"		exit(0);\n\n"
			"	case WM_LBUTTONDOWN:\n"
			"		mouse_down = true;\n"
			"		MouseEventProc(lp);\n"
			"		break;\n\n"
			"	case WM_MOUSEMOVE:\n"
			"		MouseEventProc(lp);\n"
			"		break;\n\n"
			"	case WM_LBUTTONUP:\n"
			"		mouse_down = false;\n"
			"		break;\n\n"		
			"	case WM_SETFOCUS:\n"
			"		mw_paint_all();\n"
			"		break;\n\n"
			"    default:\n"
			"        return DefWindowProc(window, msg, wp, lp);\n"
			"    }\n\n"
			"    return 0;\n"
			"}\n\n"
			"void app_init(void)\n"
			"{\n"
			"    const char* const miniwin_class = \"miniwin_class\";\n"
			"    WNDCLASSEX wndclass = {sizeof(WNDCLASSEX), CS_DBLCLKS, WindowProc,\n"
			"                            0, 0, GetModuleHandle(0), LoadIcon(0,IDI_APPLICATION),\n"
			"                            LoadCursor(0,IDC_ARROW), (HBRUSH)COLOR_WINDOW+1,\n"
			"                            0, miniwin_class, LoadIcon(0,IDI_APPLICATION)};\n"
			"    RegisterClassEx(&wndclass);\n\n"
			"    RECT r = {WINDOW_START_LOCATION_X,\n"
			"    		WINDOW_START_LOCATION_Y,\n"
			"			WINDOW_START_LOCATION_X + MW_ROOT_WIDTH,\n"
			"			WINDOW_START_LOCATION_Y + MW_ROOT_HEIGHT};\n"
			"   AdjustWindowRectEx(&r, WS_OVERLAPPEDWINDOW, FALSE, 0);\n\n"
			"	hwnd = CreateWindow(miniwin_class, \"MiniWin Sim\",\n"
			"			   WS_OVERLAPPEDWINDOW | WS_CAPTION, r.left, r.top,\n"
			"			   r.right - r.left, r.bottom - r.top, 0, 0, GetModuleHandle(0), 0);\n\n"

			"	ShowWindow(hwnd, SW_SHOWDEFAULT);\n"
			"}\n\n"
			"void app_main_loop_process(void)\n"
			"{\n"
			"    MSG msg;\n\n"

			"    while(PeekMessageA(&msg, hwnd, 0, 0, PM_NOREMOVE))\n"
			"    {\n"
			"		GetMessage(&msg, 0, 0, 0);\n"
			"		DispatchMessage(&msg);\n"
			"    }\n"
			"}\n";
	}
	outfileAppSource.close();		

	// create makefile
	std::ofstream outfileMake("../../" + json["TargetName"].string_value() + "/" + json["TargetType"].string_value() + "/makefile");
	if (!outfileMake.is_open())
	{
		cout << "Could not create file\n";
		exit(1);
	}
	outfileMake << "BINARY = " << json["TargetName"].string_value();

	if (json["TargetType"].string_value() == "Windows")
	{
		outfileMake << ".exe\n\n";
	}
	else if (json["TargetType"].string_value() == "Linux")
	{
		outfileMake << "\n\n";
	}

	outfileMake <<
			"SRCS := $(wildcard src/*.c) \\\n" 
			"	$(wildcard ../" << json["TargetName"].string_value() << "_Common/*.c) \\\n"
			"	$(wildcard ../../../MiniWin/*.c) \\\n"
			"	$(wildcard ../../../MiniWin/bitmaps/*.c) \\\n"
			"	$(wildcard ../../../MiniWin/hal/*.c) \\\n";
	if (json["TargetType"].string_value() == "Windows")
	{
		outfileMake << "	$(wildcard ../../../MiniWin/hal/windows/*.c) \\\n";
	}
	else if (json["TargetType"].string_value() == "Linux")
	{
		outfileMake << "	$(wildcard ../../../MiniWin/hal/linux/*.c) \\\n";
	}
	outfileMake <<
			"	$(wildcard ../../../MiniWin/ui/*.c) \\\n"
			"	$(wildcard ../../../MiniWin/dialogs/*.c) \\\n"
			"	$(wildcard ../../../MiniWin/gl/*.c) \\\n"
			"	$(wildcard ../../../MiniWin/gl/fonts/bitmapped/*.c) \\\n"
			"	$(wildcard ../../../MiniWin/gl/fonts/truetype/*.c) \\\n"
			"	$(wildcard ../../../MiniWin/gl/fonts/truetype/mcufont/*.c)\n\n"
			"CC = gcc\n" 
			"CFLAGS = -I../../../MiniWin -I../../../MiniWin/gl/fonts/truetype/mcufont "
			"-Isrc -I../" << json["TargetName"].string_value() << "_Common -g -Wall\n"
			"OBJECTS := $(SRCS:.c=.o)\n";

	if (json["TargetType"].string_value() == "Windows")
	{
		outfileMake << "LIBS = -lgdi32\n\n";
	}
	else if (json["TargetType"].string_value() == "Linux")
	{
		outfileMake << "LIBS = -lX11 -lm -lpthread\n\n";
	}

	outfileMake <<
			"all: ${OBJECTS}\n" 
			"	${CC} $(CFLAGS) ${OBJECTS} ${LIBS} -o ${BINARY}\n\n" 
			"clean:\n";

	if (json["TargetType"].string_value() == "Windows")
	{
		outfileMake <<
				"	del $(subst /,\\,$(OBJECTS))\n" 
				"	del ${BINARY}\n";		
	}
	else if (json["TargetType"].string_value() == "Linux")
	{
		outfileMake <<
				"	rm $(OBJECTS)\n" 
				"	rm ${BINARY}\n";
	}			

	// check duplicate identifier names
	for (uint32_t i = 0; i < all_identifier_names.size(); i++)
	{
		auto identifier = all_identifier_names.at(i);

		for (uint32_t j = i + 1; j < all_identifier_names.size(); j++)
		{
			if (identifier == all_identifier_names.at(j))
			{
				cout << "\nDuplicate identifier found: " << identifier << endl;
				exit(1);
			}
		}

	}

	cout << "Generation completed successfully.\n";
	outfileMake.close();
}