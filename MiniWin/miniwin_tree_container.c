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

static void remove_all_children(mw_tree_container_t *tree, uint16_t parent_folder_id);
static uint16_t get_id_from_handle(mw_tree_container_t *tree, mw_handle_t handle);
static uint16_t find_parent_folder(mw_tree_container_t *tree, uint16_t node_id);

/**********************
*** LOCAL FUNCTIONS ***
**********************/

/**
 * Find the parent folder of any node
 *
 * @param tree Pointer to tree structure
 * @param node_id The id of the node to get the parent of
 * @return The id of the parent folder
 */
static uint16_t find_parent_folder(mw_tree_container_t *tree, uint16_t node_id)
{
	uint16_t level;

	level = tree->nodes_array[node_id].level;

	do
	{
		node_id--;
		if (tree->nodes_array[node_id].level == level - 1U)
		{
			return node_id;
		}
	}
	while (node_id > 0U);

	return (0U);
}

/**
 * Get a node's id from its handle
 *
 * @param tree Pointer to tree structure
 * @return The id of the node if found else the size of the tree's node array
 */
static uint16_t get_id_from_handle(mw_tree_container_t *tree, mw_handle_t handle)
{
	uint16_t i;
	static uint16_t cached_id = 0U;

	if (tree->nodes_array[cached_id].handle == handle)
	{
		return cached_id;
	}

	for (i = 0U; i < tree->node_count; i++)
	{
		if (tree->nodes_array[i].handle == handle)
		{
			cached_id = i;

			return i;
		}
	}

	return (tree->nodes_array_size);
}

/**
 * Remove all children recursively of a folder node
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_id The id of the folder to remove contents of
 * @note This does not remove folder node indicated by parent_folder_id
 */
static void remove_all_children(mw_tree_container_t *tree, uint16_t parent_folder_id)
{
	uint16_t i;
	uint16_t parent_folder_level;
	uint16_t remove_count;

	if ((tree->nodes_array[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return;
	}

	parent_folder_level = tree->nodes_array[parent_folder_id].level;
	remove_count = 0U;

	for (i = parent_folder_id + 1U; ; i++)
	{
		if (tree->nodes_array[i].level <= parent_folder_level || i == tree->node_count)
		{
			break;
		}

		remove_count++;
	}

	for (i = parent_folder_id + 1U; i + remove_count < tree->node_count; i++)
	{
		tree->nodes_array[i] = tree->nodes_array[i + remove_count];
	}

	tree->node_count -= remove_count;
}

/***********************
*** GLOBAL FUNCTIONS ***
***********************/

mw_handle_t mw_tree_container_init(mw_tree_container_t *tree, mw_tree_container_node_t *nodes_array, uint16_t nodes_array_size, char *root_folder_label, uint8_t root_node_flags, uint8_t tree_flags)
{
	if (tree == NULL || root_folder_label == NULL || nodes_array == NULL || nodes_array_size == 0U)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return MW_INVALID_HANDLE;
	}

	tree->nodes_array_size = nodes_array_size;
	tree->nodes_array = nodes_array;
	tree->tree_flags = tree_flags;
	tree->nodes_array[MW_TREE_CONTAINER_ROOT_FOLDER_ID].node_flags = MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG | root_node_flags;
	mw_util_safe_strcpy(tree->nodes_array[MW_TREE_CONTAINER_ROOT_FOLDER_ID].label, (size_t)MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE, root_folder_label);
	tree->nodes_array[MW_TREE_CONTAINER_ROOT_FOLDER_ID].level = 0U;
	tree->nodes_array[MW_TREE_CONTAINER_ROOT_FOLDER_ID].handle = get_next_handle();

	mw_tree_container_empty(tree);

	return tree->nodes_array[MW_TREE_CONTAINER_ROOT_FOLDER_ID].handle;
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

	if (tree->node_count == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "No space in tree");

		return MW_INVALID_HANDLE;
	}

	parent_folder_id = get_id_from_handle(tree, parent_folder_handle);

	if (parent_folder_id == tree->nodes_array_size ||
			(tree->nodes_array[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		MW_ASSERT((bool)false, "Invalid parent folder");

		return MW_INVALID_HANDLE;
	}

	for (i = tree->node_count - 1U; i >= parent_folder_id + 1U; i--)
	{
		tree->nodes_array[i + 1U] = tree->nodes_array[i];
	}

	mw_util_safe_strcpy(tree->nodes_array[parent_folder_id + 1U].label, (size_t)MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE, label);
	tree->nodes_array[parent_folder_id + 1U].node_flags = node_flags;
	tree->nodes_array[parent_folder_id + 1U].level = tree->nodes_array[parent_folder_id].level + 1U;
	tree->nodes_array[parent_folder_id + 1U].handle = get_next_handle();
	tree->node_count++;

	return tree->nodes_array[parent_folder_id + 1U].handle;
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

	parent_folder_id = get_id_from_handle(tree, parent_folder_handle);
	if (parent_folder_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	if ((tree->nodes_array[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		MW_ASSERT((bool)false, "Parent node not a folder");

		return;
	}

	if ((tree->nodes_array[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == 0U)
	{
		return;
	}

	parent_folder_level = tree->nodes_array[parent_folder_id].level;
	skip_level = tree->nodes_array_size;

	for (i = parent_folder_id + 1U; ; i++)
	{
		if (tree->nodes_array[i].level <= parent_folder_level || i == tree->node_count)
		{
			break;
		}

		if (tree->nodes_array[i].level >= skip_level)
		{
			continue;
		}

		if ((tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
		{
			if ((tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
			{
				skip_level = tree->nodes_array_size;
			}
			else
			{
				skip_level = tree->nodes_array[i].level + 1U;
			}
		}

		/* ignore if folders only and don't have a folder */
		if ((tree->tree_flags & MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY) == MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY &&
				(tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
		{
			continue;
		}

		if (callback(tree, tree->nodes_array[i].handle, callback_data) == false)
		{
			break;
		}
	}
}

uint16_t mw_tree_container_get_open_children_count(mw_tree_container_t *tree, mw_handle_t parent_folder_handle)
{
	uint16_t i;
	uint16_t parent_folder_id;
	uint16_t parent_folder_level;
	uint16_t skip_level;
	uint16_t count;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return (0);
	}

	parent_folder_id = get_id_from_handle(tree, parent_folder_handle);
	if (parent_folder_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return (0);
	}

	if ((tree->nodes_array[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return (0);
	}

	count = 0U;

	if ((tree->nodes_array[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == 0U)
	{
		return (0);
	}

	parent_folder_level = tree->nodes_array[parent_folder_id].level;
	skip_level = tree->nodes_array_size;

	for (i = parent_folder_id + 1U; ; i++)
	{
		if (tree->nodes_array[i].level <= parent_folder_level || i == tree->node_count)
		{
			break;
		}

		if (tree->nodes_array[i].level >= skip_level)
		{
			continue;
		}

		if ((tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
		{
			if ((tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
			{
				skip_level = tree->nodes_array_size;
			}
			else
			{
				skip_level = tree->nodes_array[i].level + 1U;
			}
		}

		/* ignore if folders only and don't have a folder */
		if ((tree->tree_flags & MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY) == MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY &&
				(tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
		{
			continue;
		}

		count++;
	}

	return (count);
}

void mw_tree_container_change_node_label(mw_tree_container_t *tree, mw_handle_t node_handle, char *label)
{
	uint16_t node_id;

	if (tree == NULL || label == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return;
	}

	node_id = get_id_from_handle(tree, node_handle);
	if (node_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	mw_util_safe_strcpy(tree->nodes_array[node_id].label, (size_t)MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE, label);
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

	node_id = get_id_from_handle(tree, node_handle);
	if (node_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	/* check if selection type is allowed */
	if (((tree->tree_flags & MW_TREE_CONTAINER_FOLDER_SELECT_ONLY) == MW_TREE_CONTAINER_FOLDER_SELECT_ONLY &&
			(tree->nodes_array[node_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U) ||
			((tree->tree_flags & MW_TREE_CONTAINER_FILE_SELECT_ONLY) == MW_TREE_CONTAINER_FILE_SELECT_ONLY &&
					(tree->nodes_array[node_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG))
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
				tree->nodes_array[i].node_flags &= ~MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG;
			}
		}

		tree->nodes_array[node_id].node_flags |= MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG;
	}
	else
	{
		tree->nodes_array[node_id].node_flags &= ~MW_TREE_CONTAINER_NODE_IS_SELECTED_FLAG;
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

	folder_id = get_id_from_handle(tree, folder_node_handle);
	if (folder_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	if ((tree->nodes_array[folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		MW_ASSERT((bool)false, "Not a folder");

		return;
	}

	folder_level = tree->nodes_array[folder_id].level;

	for (i = folder_id + 1U; ; i++)
	{
		if (tree->nodes_array[i].level < folder_level + 1U || i == tree->node_count)
		{
			break;
		}

		if ((tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
		{
			continue;
		}

		if (is_open)
		{
			tree->nodes_array[i].node_flags |= MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG;
		}
		else
		{
			tree->nodes_array[i].node_flags &= ~MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG;
		}
	}

	if (is_open)
	{
		tree->nodes_array[folder_id].node_flags |= MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG;
	}
	else
	{
		tree->nodes_array[folder_id].node_flags &= ~MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG;
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

	node_id = get_id_from_handle(tree, node_handle);
	if (node_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return;
	}

	if ((tree->nodes_array[node_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
	{
		remove_all_children(tree, node_id);
	}

	for (i = node_id; i < tree->node_count - 1U; i++)
	{
		tree->nodes_array[i] = tree->nodes_array[i + 1U];
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

		return (MW_INVALID_HANDLE);
	}

	parent_folder_id = get_id_from_handle(tree, parent_folder_handle);
	if (parent_folder_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Invalid parent folder handle");

		return (MW_INVALID_HANDLE);
	}

	if ((tree->nodes_array[parent_folder_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
	{
		MW_ASSERT((bool)false, "Parent node is not a folder");

		return (MW_INVALID_HANDLE);
	}

	parent_folder_level = tree->nodes_array[parent_folder_id].level;
	skip_level = tree->nodes_array_size;

	visible_position_count = 0U;
	for (i = parent_folder_id; ; i++)
	{
		if (tree->nodes_array[i].level < parent_folder_level || i == tree->node_count)
		{
			break;
		}

		if (tree->nodes_array[i].level >= skip_level)
		{
			continue;
		}

		if ((tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
		{
			if ((tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG) == MW_TREE_CONTAINER_NODE_FOLDER_IS_OPEN_FLAG)
			{
				skip_level = tree->nodes_array_size;
			}
			else
			{
				skip_level = tree->nodes_array[i].level + 1U;
			}
		}

		/* ignore if folders only and don't have a folder */
		if ((tree->tree_flags & MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY) == MW_TREE_CONTAINER_SHOW_FOLDERS_ONLY &&
				(tree->nodes_array[i].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == 0U)
		{
			continue;
		}

		if (visible_position_count == visible_position)
		{
			return (tree->nodes_array[i].handle);
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

		return (0U);
	}

	node_id = get_id_from_handle(tree, node_handle);
	if (node_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return (0U);
	}

	return (tree->nodes_array[node_id].node_flags);
}

uint16_t mw_tree_container_get_node_level(mw_tree_container_t *tree, mw_handle_t node_handle)
{
	uint16_t node_id;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return (0U);
	}

	node_id = get_id_from_handle(tree, node_handle);
	if (node_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return (0U);
	}

	return (tree->nodes_array[node_id].level);
}

char *mw_tree_container_get_node_label(mw_tree_container_t *tree, mw_handle_t node_handle)
{
	uint16_t node_id;

	if (tree == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return ("");
	}

	node_id = get_id_from_handle(tree, node_handle);
	if (node_id == tree->nodes_array_size)
	{
		MW_ASSERT((bool)false, "Bad node handle");

		return ("");
	}

	if (tree->nodes_array[node_id].label == NULL)
	{
		return ("");
	}

	return (tree->nodes_array[node_id].label);
}

void mw_tree_container_get_node_path(mw_tree_container_t *tree, mw_handle_t node_handle, char *node_path, uint16_t node_path_length)
{
	uint16_t level;
	uint16_t node_id;
	uint16_t i;
	char node_label[MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE];

	/* check pointer parameters */
	if (tree == NULL || node_path == NULL)
	{
		MW_ASSERT((bool)false, "Null pointer");

		return;
	}

	/* check path buffer length is sensible */
	if (node_path_length == 0U)
	{
		MW_ASSERT((bool)false, "Bad parameter");

		return;
	}

	/* initialize node path buffer */
	node_path[0] = '\0';

	/* get node id and level of node to get path of */
	node_id = get_id_from_handle(tree, node_handle);
	level = tree->nodes_array[node_id].level;

	/* the path is built up backwards so to start add a folder separator if node is a folder */
	if ((tree->nodes_array[node_id].node_flags & MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG) == MW_TREE_CONTAINER_NODE_IS_FOLDER_FLAG)
	{
		mw_util_safe_strcat(node_path, node_path_length, MW_TREE_CONTAINER_FOLDER_SEPARATOR);
	}

	/* get the starting node's label, copy it to a local buffer, reverse it, then cat it to path */
	mw_util_safe_strcpy(node_label, MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE, tree->nodes_array[node_id].label);
	mw_util_safe_strcat(node_path, node_path_length, mw_util_strrev(node_label));

	/* if starting node is not root folder add a folder separator */
	if (level > 1U)
	{
		mw_util_safe_strcat(node_path, node_path_length, MW_TREE_CONTAINER_FOLDER_SEPARATOR);
	}

	/* now go up the levels to root folder */
	for (i = 0U; i < level; i++)
	{
		/* get id of parent folder */
		node_id = find_parent_folder(tree, node_id);

		/* get the parent folder's label, copy it to a local buffer, reverse it, then cat it to path */
		mw_util_safe_strcpy(node_label, MW_TREE_CONTAINER_NODE_LABEL_MAX_SIZE, tree->nodes_array[node_id].label);
		mw_util_safe_strcat(node_path, node_path_length, mw_util_strrev(node_label));

		/* if not last folder, which will be root, add a folder separator */
		if (i < level - 1U)
		{
			mw_util_safe_strcat(node_path, node_path_length, MW_TREE_CONTAINER_FOLDER_SEPARATOR);
		}
	}

	/* reverse everything to correct direction */
	(void)mw_util_strrev(node_path);
}
