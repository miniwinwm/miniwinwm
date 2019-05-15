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

/***************
*** INCLUDES ***
***************/

#include "miniwin.h"

/****************
*** CONSTANTS ***
****************/

/************
*** TYPES ***
************/

/***********************
*** GLOBAL VARIABLES ***
***********************/

/**********************
*** LOCAL VARIABLES ***
**********************/

/********************************
*** LOCAL FUNCTION PROTOTYPES ***
********************************/

static void tree_remove_all_children(mw_tree_container_t *tree, uint16_t parent_folder_id);
static uint16_t mw_tree_get_id_from_handle(mw_tree_container_t *tree, mw_handle_t handle);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Get a node's id from its handle
 *
 * @param tree Pointer to tree structure
 * @return The id of the node if found else MW_UTIL_TREE_MAX_SIZE
 */
static uint16_t mw_tree_get_id_from_handle(mw_tree_container_t *tree, mw_handle_t handle)
{
	uint16_t i;
	static uint16_t cached_id = 0U;

	MW_ASSERT(tree != (void*)0, "Null pointer argument");
	MW_ASSERT(handle != MW_INVALID_HANDLE, "Bad node handle");

	if (tree->nodes[cached_id].handle == handle)
	{
		return cached_id;
	}

	for (i = 0U; i < tree->node_count; i++)
	{
		if (tree->nodes[i].handle == handle)
		{
			cached_id = i;

			return i;
		}
	}

	return MW_TREE_CONTAINER_MAX_SIZE;
}

/**
 * Remove all children recursively of a folder node
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_id The id of the folder to remove contents of
 * @note This does not remove folder node indicated by parent_folder_id
 */
static void tree_remove_all_children(mw_tree_container_t *tree, uint16_t parent_folder_id)
{
	uint16_t i;
	uint16_t parent_folder_level;
	uint16_t remove_count;

	MW_ASSERT(tree != (void*)0, "Null pointer argument");
	MW_ASSERT(parent_folder_id < tree->node_count, "Bad folder id");

	if ((tree->nodes[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return;
	}

	parent_folder_level = tree->nodes[parent_folder_id].level;
	remove_count = 0U;

	for (i = parent_folder_id + 1U; ; i++)
	{
		if (tree->nodes[i].level <= parent_folder_level || i == tree->node_count)
		{
			break;
		}

		remove_count++;
	}

	for (i = parent_folder_id + 1U; i + remove_count < tree->node_count; i++)
	{
		tree->nodes[i] = tree->nodes[i + remove_count];
	}

	tree->node_count -= remove_count;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_tree_container_init(mw_tree_container_t *tree, char *root_folder_label, uint8_t root_node_flags, uint8_t tree_flags)
{
	if (tree == NULL || root_folder_label == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return MW_INVALID_HANDLE;
	}

	tree->tree_flags = tree_flags;
	tree->nodes[MW_TREE_CONTAINER_ROOT_FOLDER_ID].node_flags = MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG | root_node_flags;
	mw_util_safe_strcpy(tree->nodes[MW_TREE_CONTAINER_ROOT_FOLDER_ID].label, (size_t)MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE, root_folder_label);
	tree->nodes[MW_TREE_CONTAINER_ROOT_FOLDER_ID].level = 0U;
	tree->nodes[MW_TREE_CONTAINER_ROOT_FOLDER_ID].handle = get_next_handle();

	mw_tree_container_empty(tree);

	return tree->nodes[MW_TREE_CONTAINER_ROOT_FOLDER_ID].handle;
}

void mw_tree_container_empty(mw_tree_container_t *tree)
{
	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return;
	}

	tree->node_count = 1U;
}

mw_handle_t mw_tree_container_add_node(mw_tree_container_t *tree, mw_handle_t parent_folder_handle, char *label, uint8_t node_flags)
{
	uint16_t i;
	uint16_t parent_folder_id;

	if (tree == NULL || label == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return MW_INVALID_HANDLE;
	}

	if (tree->node_count == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "No space in tree");

		return MW_INVALID_HANDLE;
	}

	parent_folder_id = mw_tree_get_id_from_handle(tree, parent_folder_handle);

	if (parent_folder_id == MW_TREE_CONTAINER_MAX_SIZE ||
			(tree->nodes[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		MW_ASSERT((bool)false, "Invalid parent folder");

		return MW_INVALID_HANDLE;
	}

	for (i = tree->node_count - 1U; i >= parent_folder_id + 1U; i--)
	{
		tree->nodes[i + 1U] = tree->nodes[i];
	}

	mw_util_safe_strcpy(tree->nodes[parent_folder_id + 1U].label, (size_t)MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE, label);
	tree->nodes[parent_folder_id + 1U].node_flags = node_flags;
	tree->nodes[parent_folder_id + 1U].level = tree->nodes[parent_folder_id].level + 1U;
	tree->nodes[parent_folder_id + 1U].handle = get_next_handle();
	tree->node_count++;

	return tree->nodes[parent_folder_id + 1U].handle;
}

void mw_tree_container_get_all_children(mw_tree_container_t *tree, mw_handle_t parent_folder_handle, mw_tree_container_callback_t callback, void *callback_data)
{
	uint16_t i;
	uint16_t parent_folder_id;
	uint16_t parent_folder_level;
	uint16_t skip_level;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return;
	}

	parent_folder_id = mw_tree_get_id_from_handle(tree, parent_folder_handle);
	if (parent_folder_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	if ((tree->nodes[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		MW_ASSERT((bool)false, "Parent node not a folder");

		return;
	}

	if ((tree->nodes[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == 0U)
	{
		return;
	}

	parent_folder_level = tree->nodes[parent_folder_id].level;
	skip_level = MW_TREE_CONTAINER_MAX_SIZE;

	for (i = parent_folder_id + 1U; ; i++)
	{
		if (tree->nodes[i].level <= parent_folder_level || i == tree->node_count)
		{
			break;
		}

		if (tree->nodes[i].level >= skip_level)
		{
			continue;
		}

		if ((tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
		{
			if ((tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
			{
				skip_level = MW_TREE_CONTAINER_MAX_SIZE;
			}
			else
			{
				skip_level = tree->nodes[i].level + 1U;
			}
		}

		/* ignore if folders only and don't have a folder */
		if ((tree->tree_flags & MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY) == MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY &&
				(tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
		{
			continue;
		}

		if (callback(tree, tree->nodes[i].handle, callback_data) == false)
		{
			break;
		}
	}
}

bool mw_tree_container_get_open_children_count(mw_tree_container_t *tree, mw_handle_t parent_folder_handle, uint16_t *count)
{
	uint16_t i;
	uint16_t parent_folder_id;
	uint16_t parent_folder_level;
	uint16_t skip_level;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return false;
	}

	parent_folder_id = mw_tree_get_id_from_handle(tree, parent_folder_handle);
	if (parent_folder_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return false;
	}

	if ((tree->nodes[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return false;
	}

	*count = 0U;

	if ((tree->nodes[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == 0U)
	{
		return true;
	}

	parent_folder_level = tree->nodes[parent_folder_id].level;
	skip_level = MW_TREE_CONTAINER_MAX_SIZE;

	for (i = parent_folder_id + 1U; ; i++)
	{
		if (tree->nodes[i].level <= parent_folder_level || i == tree->node_count)
		{
			break;
		}

		if (tree->nodes[i].level >= skip_level)
		{
			continue;
		}

		if ((tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
		{
			if ((tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
			{
				skip_level = MW_TREE_CONTAINER_MAX_SIZE;
			}
			else
			{
				skip_level = tree->nodes[i].level + 1U;
			}
		}

		/* ignore if folders only and don't have a folder */
		if ((tree->tree_flags & MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY) == MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY &&
				(tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
		{
			continue;
		}

		(*count)++;
	}

	return true;
}

void mw_tree_container_change_node_label(mw_tree_container_t *tree, mw_handle_t node_handle, char *label)
{
	uint16_t node_id;

	if (tree == NULL || label == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return;
	}

	node_id = mw_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	mw_util_safe_strcpy(tree->nodes[node_id].label, (size_t)MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE, label);
}

void mw_tree_container_change_node_selected_state(mw_tree_container_t *tree, mw_handle_t node_handle, bool is_selected)
{
	uint16_t node_id;
	uint16_t i;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return;
	}

	node_id = mw_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	/* check if selection type is allowed */
	if (((tree->tree_flags & MW_TREE_CONTAINER_FOLDER_SELECT_ONLY) == MW_TREE_CONTAINER_FOLDER_SELECT_ONLY &&
			(tree->nodes[node_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U) ||
			((tree->tree_flags & MW_TREE_CONTAINER_FILE_SELECT_ONLY) == MW_TREE_CONTAINER_FILE_SELECT_ONLY &&
					(tree->nodes[node_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG))
	{
		return;
	}

	if (is_selected)
	{
		/* check if single select only */
		if ((tree->tree_flags & MW_TREE_CONTAINER_SINGLE_SELECT_ONLY) == MW_TREE_CONTAINER_SINGLE_SELECT_ONLY)
		{
			/* single select only so deselect everything */
			for (i = 0U; i < tree->node_count; i++)
			{
				tree->nodes[i].node_flags &= ~MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG;
			}
		}

		tree->nodes[node_id].node_flags |= MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG;
	}
	else
	{
		tree->nodes[node_id].node_flags &= ~MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG;
	}
}

void mw_tree_container_change_folder_node_open_state(mw_tree_container_t *tree, mw_handle_t folder_node_handle, bool is_open)
{
	uint16_t i;
	uint16_t folder_id;
	uint16_t folder_level;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return;
	}

	folder_id = mw_tree_get_id_from_handle(tree, folder_node_handle);
	if (folder_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	if ((tree->nodes[folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		MW_ASSERT((bool)false, "Not a folder");

		return;
	}

	folder_level = tree->nodes[folder_id].level;

	for (i = folder_id + 1U; ; i++)
	{
		if (tree->nodes[i].level < folder_level + 1U || i == tree->node_count)
		{
			break;
		}

		if ((tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
		{
			continue;
		}

		if (is_open)
		{
			tree->nodes[i].node_flags |= MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG;
		}
		else
		{
			tree->nodes[i].node_flags &= ~MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG;
		}
	}

	if (is_open)
	{
		tree->nodes[folder_id].node_flags |= MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG;
	}
	else
	{
		tree->nodes[folder_id].node_flags &= ~MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG;
	}
}

void mw_tree_container_remove_node(mw_tree_container_t *tree, mw_handle_t node_handle)
{
	uint16_t i;
	uint16_t node_id;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return;
	}

	node_id = mw_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	if ((tree->nodes[node_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
	{
		tree_remove_all_children(tree, node_id);
	}

	for (i = node_id; i < tree->node_count - 1U; i++)
	{
		tree->nodes[i] = tree->nodes[i + 1U];
	}

	tree->node_count--;
}

mw_handle_t mw_tree_container_get_handle_from_visible_position(mw_tree_container_t *tree, mw_handle_t parent_folder_handle, uint16_t visible_position)
{
	uint16_t i;
	uint16_t parent_folder_id;
	uint16_t parent_folder_level;
	uint16_t skip_level;
	uint16_t visible_position_count;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return MW_INVALID_HANDLE;
	}

	parent_folder_id = mw_tree_get_id_from_handle(tree, parent_folder_handle);
	if (parent_folder_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Invalid parent folder handle");

		return MW_INVALID_HANDLE;
	}

	if ((tree->nodes[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		MW_ASSERT((bool)false, "Parent node is not a folder");

		return MW_INVALID_HANDLE;
	}

	parent_folder_level = tree->nodes[parent_folder_id].level;
	skip_level = MW_TREE_CONTAINER_MAX_SIZE;

	visible_position_count = 0U;
	for (i = parent_folder_id; ; i++)
	{
		if (tree->nodes[i].level < parent_folder_level || i == tree->node_count)
		{
			break;
		}

		if (tree->nodes[i].level >= skip_level)
		{
			continue;
		}

		if ((tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
		{
			if ((tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
			{
				skip_level = MW_TREE_CONTAINER_MAX_SIZE;
			}
			else
			{
				skip_level = tree->nodes[i].level + 1U;
			}
		}

		/* ignore if folders only and don't have a folder */
		if ((tree->tree_flags & MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY) == MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY &&
				(tree->nodes[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
		{
			continue;
		}

		if (visible_position_count == visible_position)
		{
			return (tree->nodes[i].handle);
		}

		visible_position_count++;
	}

	return (MW_INVALID_HANDLE);
}

uint8_t mw_tree_container_get_node_flags(mw_tree_container_t *tree, mw_handle_t node_handle)
{
	uint16_t node_id;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return false;
	}

	node_id = mw_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return false;
	}

	return (tree->nodes[node_id].node_flags);
}

uint16_t mw_tree_container_get_node_level(mw_tree_container_t *tree, mw_handle_t node_handle)
{
	uint16_t node_id;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return false;
	}

	node_id = mw_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return (false);
	}

	return (tree->nodes[node_id].level);
}

char *mw_tree_container_get_node_label(mw_tree_container_t *tree, mw_handle_t node_handle)
{
	uint16_t node_id;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return ("");
	}

	node_id = mw_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_TREE_CONTAINER_MAX_SIZE)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return ("");
	}

	if (tree->nodes[node_id].label == NULL)
	{
		return ("");
	}

	return (tree->nodes[node_id].label);
}
