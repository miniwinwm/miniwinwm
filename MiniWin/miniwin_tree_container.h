/*

MIT License

Copyright (c) John Blaiklock 2019 miniwin Embedded Window Manager

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#ifndef MINWIN_TREE_CONTAINER_H
#define MINWIN_TREE_CONTAINER_H

#ifdef __cplusplus
 extern "C" {
#endif

/***************
*** INCLUDES ***
***************/

#include <stdint.h>
#include <stdbool.h>
#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

#define MW_TREE_CONTAINER_ROOT_FOLDER_ID 			0U
#define MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE		16U
#define MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG		0x01U
#define MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG		0x02U
#define MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG	0x04U
#define MW_TREE_CONTAINER_SINGLE_SELECT_ONLY		0x01U
#define MW_TREE_CONTAINER_FOLDER_SELECT_ONLY		0x02U
#define MW_TREE_CONTAINER_FILE_SELECT_ONLY			0x04U
#define MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY			0x08U
#define MW_TREE_CONTAINER_FOLDER_SEPARATOR			"/"

/************
*** TYPES ***
************/

typedef struct mw_tree_container_tag mw_tree_container_t;

/**
 * Pointer type to callback function called from library to user code when finding all descendants of a folder node
 *
 * @param tree Pointer to tree structure
 * @param node_handle The handle of the next found node
 * @param callback_data Generic pointer to extra data that needs passing to callback function
 * @return Return true to continue searching or false to quit searching
 */
typedef bool (mw_tree_container_next_child_callback_t)(mw_tree_container_t *tree, mw_handle_t node_handle, void *callback_data);

/**
 * Function typedef of callback function called from library to user code when adding a node fails because of lack of
 * space for new nodes
 *
 * @param tree Pointer to tree structure
 * @note If it is not possible to allocate a larger space for the array this callback function should do nothing
 */
typedef void (mw_tree_container_no_space_callback_t)(mw_tree_container_t *tree);

/**
 * Tree node structure
 */
typedef struct
{
	mw_handle_t handle;											/**< This node's handle */
	char label[MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE];			/**< This node's label */
	uint16_t level;												/**< The folder depth of this node; root folder is zero */
	uint8_t node_flags;											/**< Flags describing this node */
} mw_tree_container_node_t;

/**
 * Tree structure
 */
typedef struct mw_tree_container_tag
{
	uint16_t nodes_array_size;									/**< Maximum number of nodes in nodes_array */
	uint16_t node_count;										/**< Number of used nodes in pool, never less than 1 */
	mw_tree_container_node_t *nodes_array;						/**< Pointer to array of nodes */
	uint8_t tree_flags;											/**< Flags describing this tree */
	mw_tree_container_no_space_callback_t *no_space_callback;	/**< Callback to be called when adding a node fails because of lack of space; can be NULL */
} mw_tree_container_t;

/*************************
*** EXTERNAL VARIABLES ***
*************************/

/***************************
*** FUNCTIONS PROTOTYPES ***
***************************/

/**
 * Initialize the tree. This sets up the root folder node with node_id 0 and marks all other nodes unused
 *
 * @param tree Pointer to tree structure
 * @param nodes_array Pointer to array to contain nodes
 * @param nodes_array_size Size of nodes_array
 * @param root_folder_label Label to give to the root folder node
 * @param root_node_flags Flags to use for root node; can be MW_UTREE_NODE_IS_SELECTED_FLAG or MW_TREE_FOLDER_IS_OPEN_FLAG or both
 * @param tree_flags Flags that apply to the whole tree, can be MW_TREE_CONTAINER_SINGLE_SELECT_ONLY or MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY or both or neither
 * @param no_space_callback Pointer to callback function that is called when adding a node fails because of lack of space for a new node. This can be NULL if not required.
 * @return Handle to the root node
 */
mw_handle_t mw_tree_container_init(mw_tree_container_t *tree,
		mw_tree_container_node_t *nodes_array,
		uint16_t nodes_array_size,
		char *root_folder_label,
		uint8_t root_node_flags,
		uint8_t tree_flags,
		mw_tree_container_no_space_callback_t *no_space_callback);

/**
 * Empty a tree of all nodes except the root folder node which remains untouched
 *
 * @param tree Pointer to tree structure
 */
void mw_tree_container_empty(mw_tree_container_t *tree);

/**
 * Get the size of the tree's node storage array
 *
 * @param tree Pointer to tree structure
 * @return The node array size
 */
uint16_t mw_tree_container_get_node_array_size(mw_tree_container_t *tree);

/**
 * Get pointer to the tree's node storage array
 *
 * @param tree Pointer to tree structure
 * @return Pointer to the tree's node storage array
 */
mw_tree_container_node_t *mw_tree_container_get_node_array(mw_tree_container_t *tree);

/**
 * Replace the tree's node storage array with a new one
 *
 * @param tree Pointer to tree structure
 * @param new_node_array Pointer to new node array
 * @param new_node_array_size Size of the new node array
 * @note The node array can be expanded or shrunk
 * @note The new node array must already be initialised with whatever contents are required in it. The root node is not created.
 */
void mw_tree_container_set_new_node_array(mw_tree_container_t *tree, mw_tree_container_node_t *new_node_array, uint16_t new_node_array_size);

/**
 * Add a node to a tree in a specified folder
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_handle Handle of the folder node to create the new node in
 * @param label The label to assign to the new node
 * @param flags Flags describing the node. Can be any from MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG,
 *              MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG, MW_TREE_FOLDER_IS_OPEN_FLAG
 * @return The new node handle if added successfully or MW_INVALID_HANDLE if a parameter was illegal or no space remaining
 */
mw_handle_t mw_tree_container_add_node(mw_tree_container_t *tree, mw_handle_t parent_folder_handle, char *label, uint8_t node_flags);

/**
 * Change a node's label
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of node to change label of
 * @param label Text string of new label
 */
void mw_tree_container_change_node_label(mw_tree_container_t *tree, mw_handle_t node_handle, char *label);

/**
 * Change a node's selected state
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of node to change selected state of
 * @param is_selected True to assign a node selected, false unselected
 */
void mw_tree_container_change_node_selected_state(mw_tree_container_t *tree, mw_handle_t node_handle, bool is_selected);

/**
 * Change a folder node's open state
 *
 * @param tree Pointer to tree structure
 * @param folder_node_handle Handle of the folder node to change open state of
 * @param is_open True to assign a folder node open, false closed
 */
void mw_tree_container_change_folder_node_open_state(mw_tree_container_t *tree, mw_handle_t folder_node_handle, bool is_open);

/**
 * Remove a node
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of node to remove
 * @return True if parameters acceptable, else false
 */
void mw_tree_container_remove_node(mw_tree_container_t *tree, mw_handle_t node_handle);

/**
 * Recursively get all the children and sub-children of a folder node via callback function
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_handle Handle of the folder node to start looking in
 * @param callback The function to be called for each child or sub-child found
 * @param callback_data Pointer to generic data to be passed from caller to callback function
 * @note This function recursively descends the tree from the starting folder getting all children of all descendant folders if
 *       for open sub-folders. Children of closed sub-folders are ignored.
 * @note This function can be instructed to terminate early at any point by the callback function returning false
 */
void mw_tree_container_get_all_children(mw_tree_container_t *tree,
		mw_handle_t parent_folder_handle,
		mw_tree_container_next_child_callback_t *callback,
		void *callback_data);

/**
 * Recursively get the count of children and sub-children of a folder node
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_handle Handle of the folder node to start looking in
 * @return The number of open children
 * @note This function recursively descends the tree from the starting folder getting all children of all descendant folders if
 *       for open sub-folders. Children of closed sub-folders are ignored. The parent folder is not included in the count.
 */
uint16_t mw_tree_container_get_open_children_count(mw_tree_container_t *tree, mw_handle_t parent_folder_handle);

/**
 * Get a node's handle from it's position after a parent folder, looking into open folders only
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_handle Handle of the folder node to start looking in
 * @param position The position after the parent folder
 * @return The handle of the node or MW_INVALID_HANDLE if no node found at the position
 */
mw_handle_t mw_tree_container_get_handle_from_visible_position(mw_tree_container_t *tree, mw_handle_t parent_folder_handle, uint16_t visible_position);

/**
 * Get the flags of a node
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of the node to get flags for
 * @return The node's flags
 */
uint8_t mw_tree_container_get_node_flags(mw_tree_container_t *tree, mw_handle_t node_handle);

/**
 * Get the flags of a node
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of the node to get level for
 * @return The level of the node
 */
uint16_t mw_tree_container_get_node_level(mw_tree_container_t *tree, mw_handle_t node_handle);

/**
 * Get the label of a node
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of the node to get label for
 * @return Pointer to node's label or empty string if node cannot be found or the label is NULL
 * @note Never returns a NULL pointer
 */
char *mw_tree_container_get_node_label(mw_tree_container_t *tree, mw_handle_t node_handle);

/**
 * Get the full path and filename of a node from its handle. This includes the root path. If the node is
 * a file this is included. The folder separator defined above is used to separate the folders. If the node
 * is a folder then the folder separator is appended to the folder name.
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of the node to get label for
 * @param node_path Buffer that contains the returned path
 * @param node_path_length Size of the node path buffer
 */
void mw_tree_container_get_node_path(mw_tree_container_t *tree, mw_handle_t node_handle, char *node_path, uint16_t node_path_length);

#ifdef __cplusplus
}
#endif

#endif
