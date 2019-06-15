/*
The code generator JSON script example_everything.json creates a window with 3 tree
controls in it. The code generator does not populate the tree containers that these
tree controls use to store their data. To give these tree controls somethging to
show paste this file's contents in to generated file miniwin_user.c near the end of 
function mw_user_init() just before the call in that function to mw_paint_all()
after code generation before building the generated code.
*/

    {
        static char tree_folder1_label[] = {"Foldy1"};
        static char tree_folder2_label[] = {"fold2"};
        static char tree_folder3_label[] = {"fold3"};
        static char tree_file1_label[] = {"File1"};
        static char tree_file2_label[] = {"File2"};
        static char tree_file3_label[] = {"File3"};
        static char tree_file4_label[] = {"File4"};
        static char tree_file5_label[] = {"File5"};
        static char tree_file6_label[] = {"File6"};
        static char tree_file7_label[] = {"File7"};

    	mw_handle_t fold1_handle;
    	mw_handle_t fold2_handle;
    	mw_handle_t fold3_handle;

    	(void)mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			tree_TR1_data.root_handle,
    			tree_file1_label,
    			0U);
    	fold1_handle = mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			tree_TR1_data.root_handle,
    			tree_folder1_label,
    			MW_TREE_CONTAINER_NODE_IS_FOLDER);
    	(void)mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			fold1_handle,
    			tree_file2_label,
    			0U);
    	(void)mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			fold1_handle,
    			tree_file3_label,
    			0U);
    	fold2_handle = mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			fold1_handle,
    			tree_folder2_label,
    			MW_TREE_CONTAINER_NODE_IS_FOLDER);
    	fold3_handle = mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			fold1_handle,
    			tree_folder3_label,
    			MW_TREE_CONTAINER_NODE_IS_FOLDER);
    	(void)mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			fold3_handle,
    			tree_file6_label,
    			0U);
    	(void)mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			fold3_handle,
    			tree_file7_label,
    			0U);
    	(void)mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			fold2_handle,
    			tree_file4_label,
    			0U);
    	(void)mw_tree_container_add_node(&tree_TR1_data.tree_container,
    			fold2_handle,
    			tree_file5_label,
    			0U);
    }

    {
        static char tree_folder1_label[] = {"Foldy1"};
        static char tree_folder2_label[] = {"fold2"};
        static char tree_folder3_label[] = {"fold3"};
        static char tree_file1_label[] = {"File1"};
        static char tree_file2_label[] = {"File2"};
        static char tree_file3_label[] = {"File3"};
        static char tree_file4_label[] = {"File4"};
        static char tree_file5_label[] = {"File5"};
        static char tree_file6_label[] = {"File6"};
        static char tree_file7_label[] = {"File7"};

    	mw_handle_t fold1_handle;
    	mw_handle_t fold2_handle;
    	mw_handle_t fold3_handle;

    	(void)mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			scrolling_tree_STR1_data.root_handle,
    			tree_file1_label,
    			0U);
    	fold1_handle = mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			scrolling_tree_STR1_data.root_handle,
    			tree_folder1_label,
    			MW_TREE_CONTAINER_NODE_IS_FOLDER);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			fold1_handle,
    			tree_file2_label,
    			0U);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			fold1_handle,
    			tree_file3_label,
    			0U);
    	fold2_handle = mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			fold1_handle,
    			tree_folder2_label,
    			MW_TREE_CONTAINER_NODE_IS_FOLDER);
    	fold3_handle = mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			fold1_handle,
    			tree_folder3_label,
    			MW_TREE_CONTAINER_NODE_IS_FOLDER);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			fold3_handle,
    			tree_file6_label,
    			0U);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			fold3_handle,
    			tree_file7_label,
    			0U);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			fold2_handle,
    			tree_file4_label,
    			0U);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR1_data.tree_container,
    			fold2_handle,
    			tree_file5_label,
    			0U);
    }

    {
        static char tree_folder1_label[] = {"Foldy1"};
        static char tree_folder2_label[] = {"fold2"};
        static char tree_folder3_label[] = {"fold3"};
        static char tree_file1_label[] = {"File1"};
        static char tree_file2_label[] = {"File2"};
        static char tree_file3_label[] = {"File3"};
        static char tree_file4_label[] = {"File4"};
        static char tree_file5_label[] = {"File5"};
        static char tree_file6_label[] = {"File6"};
        static char tree_file7_label[] = {"File7"};

    	mw_handle_t fold1_handle;
    	mw_handle_t fold2_handle;
    	mw_handle_t fold3_handle;

    	(void)mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			scrolling_tree_STR2_data.root_handle,
    			tree_file1_label,
    			0U);
    	fold1_handle = mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			scrolling_tree_STR2_data.root_handle,
    			tree_folder1_label,
    			MW_TREE_CONTAINER_NODE_IS_FOLDER);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			fold1_handle,
    			tree_file2_label,
    			0U);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			fold1_handle,
    			tree_file3_label,
    			0U);
    	fold2_handle = mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			fold1_handle,
    			tree_folder2_label,
    			MW_TREE_CONTAINER_NODE_IS_FOLDER);
    	fold3_handle = mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			fold1_handle,
    			tree_folder3_label,
    			MW_TREE_CONTAINER_NODE_IS_FOLDER);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			fold3_handle,
    			tree_file6_label,
    			0U);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			fold3_handle,
    			tree_file7_label,
    			0U);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			fold2_handle,
    			tree_file4_label,
    			0U);
    	(void)mw_tree_container_add_node(&scrolling_tree_STR2_data.tree_container,
    			fold2_handle,
    			tree_file5_label,
    			0U);
    }
