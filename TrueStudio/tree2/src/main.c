#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

// do not add this lot
typedef uint32_t mw_handle_t;
#define MW_INVALID_HANDLE							0U									/**< Invalid handle, returned when a resource cannot be allocated */
mw_handle_t get_next_handle(void)
{
	static mw_handle_t next = 55;

	next++;
	return next;
}

#define MW_UTIL_TREE_ROOT_FOLDER_ID 		0U
#define MW_UTIL_TREE_MAX_SIZE				20U
#define MW_UTIL_TREE_NODE_LABEL_MAX_SIZE	16U
#define MW_UTIL_TREE_NODE_IS_SELECTED_FLAG	0x01U
#define MW_UTIL_TREE_NODE_IS_FOLDER_FLAG	0x02U
#define MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG	0x04U

/**
 * Tree node structure
 */
typedef struct
{
	mw_handle_t handle;									///< This node's handle
	char label[MW_UTIL_TREE_NODE_LABEL_MAX_SIZE + 1U];	///< This node's label
	uint8_t level;										///< The folder depth of this node; root folder is zero
	uint8_t flags;										///< Flags describing this node
} mw_tree_node_t;

/**
 * Tree structure
 */
typedef struct
{
	uint16_t node_count;								///< Number of used nodes in pool, never less than 1
	mw_tree_node_t nodes[MW_UTIL_TREE_MAX_SIZE];		///< Memory pool of nodes contained in the tree
} mw_tree_t;

/**
 * Pointer type to callback function when finding all descendants of a folder node
 *
 * @param tree Pointer to tree structure
 * @param node_handle The handle of the next found node
 * @return Return true to continue searching or false to quit searching
 */
typedef bool (*mw_util_tree_func_p)(mw_tree_t *tree, mw_handle_t node_handle);

/**
 * Initialize the tree. This sets up the root folder node with node_id 0 and marks all other nodes unused
 *
 * @param tree Pointer to tree structure
 * @param root_folder_label Label to give to the root folder node
 * @param flags Can be MW_UTIL_TREE_NODE_IS_SELECTED_FLAG or MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG or both
 * @return Handle to the root node
 */
mw_handle_t mw_util_tree_init(mw_tree_t *tree, char *root_folder_label, uint8_t flags);

/**
 * Empty a tree of all nodes except the root folder node which remains untouched
 *
 * @param tree Pointer to tree structure
 */
void mw_util_tree_empty(mw_tree_t *tree);

/**
 * Add a node to a tree in a specified folder
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_handle Handle of the folder node to create the new node in
 * @param label The label to assign to the new node
 * @param flags Flags describing the node. Can be any from MW_UTIL_TREE_NODE_IS_SELECTED_FLAG,
 *              MW_UTIL_TREE_NODE_IS_FOLDER_FLAG, MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG
 * @return The new node handle if added successfully or MW_INVALID_HANDLE if a parameter was illegal or no space remaining
 */
mw_handle_t mw_util_tree_add_node(mw_tree_t *tree, mw_handle_t parent_folder_handle, char *label, uint8_t flags);

/**
 * Change a node's label
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of node to change label of
 * @param label Text string of new label
 * @return True if parameters acceptable, else false
 */
bool mw_util_tree_change_node_label(mw_tree_t *tree, mw_handle_t node_handle, char *label);

/**
 * Change a node's selected state
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of node to change selected state of
 * @param is_selected True to assign a node selected, false unselected
 * @return True if parameters acceptable, else false
 */
bool mw_util_tree_change_node_selected_state(mw_tree_t *tree, mw_handle_t node_handle, bool is_selected);

/**
 * Change a folder node's open state
 *
 * @param tree Pointer to tree structure
 * @param folder_node_handle Handle of the folder node to change open state of
 * @param is_open True to assign a folder node open, false closed
 * @return True if parameters acceptable, else false
 */
bool mw_util_tree_change_folder_node_open_state(mw_tree_t *tree, mw_handle_t folder_node_handle, bool is_open);

/**
 * Remove a node
 *
 * @param tree Pointer to tree structure
 * @param node_handle Handle of node to remove
 * @return True if parameters acceptable, else false
 * @note Removing a folder node removes all of ut's children recursively
 */
bool mw_util_tree_remove_node(mw_tree_t *tree, mw_handle_t node_handle);

/**
 * Recursively get all the children and sub-children of a folder node via callback function
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_handle Handle of the folder node to start looking in
 * @param callback The function to be called for each child or sub-child found
 * @return True if parameters acceptable, else false
 * @note This function recursively descends the tree from the starting folder getting all children of all descendant folders
 * @note This function can be instructed to terminate early at any point by the callback function returning false
 */
bool mw_util_tree_get_all_children(mw_tree_t *tree, mw_handle_t parent_folder_handle, mw_util_tree_func_p callback);

/**
 * Recursively get all the children and sub-children of a folder node via callback function
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_handle Handle of the folder node to start looking in
 * @param n The number in the set of relevant nodes to get
 * @param node_handle_pointer Returns pointing to the handle of the latest found node or MW)INVALID_HANDLE if there are not any nodes at n in the set
 * @return True if parameters acceptable, else false
 * @note This function recursively descends the tree from the starting folder getting all children of all descendant folders
 */
bool mw_util_tree_get_all_children_iterator(mw_tree_t *tree, mw_handle_t parent_folder_handle, uint16_t n, mw_handle_t *node_handle_pointer);

/**
 * Recursively get all the count of children and sub-children of a folder node
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_handle Handle of the folder node to start looking in
 * @param count Pointer to int in which the result is returned
 * @return True if parameters acceptable, else false
 * @note This function recursively descends the tree from the starting folder getting all children of all descendant folders if
 *       for open sub-folders. Children of closed sub-folders are ignored.
 */
bool mw_tree_get_open_children_count(mw_tree_t *tree, mw_handle_t parent_folder_handle, uint16_t *count);

/**
 * Get a node's id from its handle
 *
 * @param tree Pointer to tree structure
 * @return The id of the node if found else MW_UTIL_TREE_MAX_SIZE
 */
uint16_t mw_util_tree_get_id_from_handle(mw_tree_t *tree, mw_handle_t handle);

static void tree_remove_all_children(mw_tree_t *tree, uint16_t parent_folder_id);

mw_tree_t my_tree;

bool node_callback(mw_tree_t *tree, mw_handle_t node_handle)
{
	uint8_t level;
	uint16_t node_id;

	if (tree == NULL)
	{
		return true;
	}

	node_id = mw_util_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return true;
	}

	for (level = 1U; level < tree->nodes[node_id].level; level++)
	{
		printf("| ");
	}
	printf("|-");

	printf("%s", tree->nodes[node_id].label);

	if ((tree->nodes[node_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == MW_UTIL_TREE_NODE_IS_FOLDER_FLAG)
	{
		printf("\\\n");
	}
	else
	{
		printf("\n");
	}
	fflush(stdout);

	return true;
}

void print_folder2(mw_tree_t *tree, mw_handle_t folder_handle)
{
	uint16_t folder_id;
	uint16_t c;
	uint16_t i;
	mw_handle_t node_handle;
	uint16_t level;
	uint16_t node_id;

	if (tree == NULL)
	{
		return;
	}

	folder_id = mw_util_tree_get_id_from_handle(tree, folder_handle);
	if (folder_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return;
	}

	if ((tree->nodes[folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return;
	}

	printf("%s\\\n", tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].label);
	mw_tree_get_open_children_count(&my_tree, folder_handle, &c);
	for (i = 0U; i < c; i++)
	{
		(void)mw_util_tree_get_all_children_iterator(tree, folder_handle, i, &node_handle);

		node_id = mw_util_tree_get_id_from_handle(tree, node_handle);
		if (node_id == MW_UTIL_TREE_MAX_SIZE)
		{
			return;
		}

		for (level = 1U; level < tree->nodes[node_id].level; level++)
		{
			printf("| ");
		}
		printf("|-");

		printf("%s", tree->nodes[node_id].label);

		if ((tree->nodes[node_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == MW_UTIL_TREE_NODE_IS_FOLDER_FLAG)
		{
			printf("\\\n");
		}
		else
		{
			printf("\n");
		}
		fflush(stdout);
	}
}

void print_folder(mw_tree_t *tree, mw_handle_t folder_handle)
{
	uint16_t folder_id;

	if (tree == NULL)
	{
		return;
	}

	folder_id = mw_util_tree_get_id_from_handle(tree, folder_handle);
	if (folder_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return;
	}

	if ((tree->nodes[folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return;
	}

	printf("%s\\\n", tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].label);
	(void)mw_util_tree_get_all_children(tree, folder_handle, node_callback);

	print_folder2(tree, folder_handle);
}

int main(void)
{
	mw_handle_t root_folder_handle = mw_util_tree_init(&my_tree, "root", MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG);

	mw_util_tree_add_node(&my_tree,
			root_folder_handle,
			"file1",
			0U);

	mw_handle_t fold1_handle = mw_util_tree_add_node(&my_tree,
			root_folder_handle,
			"fold1",
			MW_UTIL_TREE_NODE_IS_FOLDER_FLAG | MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG);

	mw_util_tree_add_node(&my_tree,
			fold1_handle,
			"file2",
			0U);

	mw_util_tree_add_node(&my_tree,
			fold1_handle,
			"file3",
			0U);

	mw_handle_t fold2_handle = mw_util_tree_add_node(&my_tree,
			fold1_handle,
			"fold2",
			MW_UTIL_TREE_NODE_IS_FOLDER_FLAG | MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG);

	mw_handle_t fold3_handle = mw_util_tree_add_node(&my_tree,
			fold1_handle,
			"fold3",
			MW_UTIL_TREE_NODE_IS_FOLDER_FLAG | MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG);

	mw_handle_t file6_handle = mw_util_tree_add_node(&my_tree,
			fold3_handle,
			"file6",
			0U);

	mw_util_tree_add_node(&my_tree,
			fold3_handle,
			"file7",
			0U);

	mw_util_tree_add_node(&my_tree,
			fold2_handle,
			"file4",
			0U);

	mw_util_tree_add_node(&my_tree,
			fold2_handle,
			"file5",
			0U);

	uint16_t i;
	for (i = 0; i < my_tree.node_count; i++)
	{
		printf("%d %s\n", my_tree.nodes[i].level, my_tree.nodes[i].label);
	}
	fflush(stdout);

	printf("The full tree\n");
	print_folder(&my_tree, root_folder_handle);

	uint16_t c;
	mw_tree_get_open_children_count(&my_tree, root_folder_handle, &c);
	printf("Root open children count %u\n", c);
	fflush(stdout);

	mw_tree_get_open_children_count(&my_tree, fold1_handle, &c);
	printf("fold1 open children count %u\n", c);
	fflush(stdout);

	printf("root closed\n");
	mw_util_tree_change_folder_node_open_state(&my_tree, root_folder_handle, false);
	print_folder(&my_tree, root_folder_handle);

	mw_tree_get_open_children_count(&my_tree, root_folder_handle, &c);
	printf("Root open children count %u\n", c);
	fflush(stdout);

	printf("root reopened\n");
	mw_util_tree_change_folder_node_open_state(&my_tree, root_folder_handle, true);
	print_folder(&my_tree, root_folder_handle);

	mw_tree_get_open_children_count(&my_tree, root_folder_handle, &c);
	printf("Root open children count %u\n", c);
	fflush(stdout);

	printf("fold2 closed\n");
	mw_util_tree_change_folder_node_open_state(&my_tree, fold2_handle, false);
	print_folder(&my_tree, root_folder_handle);

	mw_tree_get_open_children_count(&my_tree, root_folder_handle, &c);
	printf("Root open children count %u\n", c);
	fflush(stdout);

	printf("fold2 reopened\n");
	mw_util_tree_change_folder_node_open_state(&my_tree, fold2_handle, true);
	print_folder(&my_tree, root_folder_handle);

	mw_tree_get_open_children_count(&my_tree, root_folder_handle, &c);
	printf("Root open children count %u\n", c);
	fflush(stdout);

	printf("file6 removed\n");
	mw_util_tree_remove_node(&my_tree, file6_handle);
	print_folder(&my_tree, root_folder_handle);

	mw_tree_get_open_children_count(&my_tree, root_folder_handle, &c);
	printf("Root open children count %u\n", c);
	fflush(stdout);

	printf("fold2 removed\n");
	mw_util_tree_remove_node(&my_tree, fold2_handle);
	print_folder(&my_tree, root_folder_handle);

	mw_tree_get_open_children_count(&my_tree, root_folder_handle, &c);
	printf("Root open children count %u\n", c);
	fflush(stdout);

	printf("Empty tree\n");
	mw_util_tree_empty(&my_tree);
	print_folder(&my_tree, root_folder_handle);

	mw_tree_get_open_children_count(&my_tree, root_folder_handle, &c);
	printf("Root open children count %u\n", c);
	fflush(stdout);
	return 0;
}

mw_handle_t mw_util_tree_init(mw_tree_t *tree, char *root_folder_label, uint8_t flags)
{
	if (tree == NULL || root_folder_label == NULL)
	{
		return false;
	}

	tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].flags = MW_UTIL_TREE_NODE_IS_FOLDER_FLAG | flags;
	strcpy(tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].label, root_folder_label);
	tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].level = 0U;
	tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].handle = get_next_handle();

	mw_util_tree_empty(tree);

	return tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].handle;
}

void mw_util_tree_empty(mw_tree_t *tree)
{
	if (tree == NULL)
	{
		return;
	}

	tree->node_count = 1U;
}

mw_handle_t mw_util_tree_add_node(mw_tree_t *tree, mw_handle_t parent_folder_handle, char *label, uint8_t flags)
{
	uint16_t i;
	uint16_t parent_folder_id = mw_util_tree_get_id_from_handle(tree, parent_folder_handle);

	if (tree == NULL ||
			label == NULL ||
			tree->node_count == MW_UTIL_TREE_MAX_SIZE ||
			parent_folder_id >= tree->node_count ||
			(tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return MW_INVALID_HANDLE;
	}

	for (i = tree->node_count - 1U; i >= parent_folder_id + 1U; i--)
	{
		tree->nodes[i + 1U] = tree->nodes[i];
	}

	strcpy(tree->nodes[parent_folder_id + 1U].label, label);
	tree->nodes[parent_folder_id + 1U].flags = flags;
	tree->nodes[parent_folder_id + 1U].level = tree->nodes[parent_folder_id].level + 1U;
	tree->nodes[parent_folder_id + 1U].handle = get_next_handle();
	tree->node_count++;

	return tree->nodes[parent_folder_id + 1U].handle;
}

bool mw_util_tree_get_all_children(mw_tree_t *tree, mw_handle_t parent_folder_handle, mw_util_tree_func_p callback)
{
	uint16_t i;
	uint16_t parent_folder_id;
	uint16_t parent_folder_level;
	uint16_t skip_level;

	if (tree == NULL)
	{
		return false;
	}

	parent_folder_id = mw_util_tree_get_id_from_handle(tree, parent_folder_handle);
	if (parent_folder_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return false;
	}

	if ((tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return false;
	}

	if ((tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG) == 0U)
	{
		return true;
	}

	parent_folder_level = tree->nodes[parent_folder_id].level;
	skip_level = MW_UTIL_TREE_MAX_SIZE;

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

		if ((tree->nodes[i].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == MW_UTIL_TREE_NODE_IS_FOLDER_FLAG)
		{
			if ((tree->nodes[i].flags & MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG) == MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG)
			{
				skip_level = MW_UTIL_TREE_MAX_SIZE;
			}
			else
			{
				skip_level = tree->nodes[i].level + 1U;
			}
		}

		if (callback(tree, tree->nodes[i].handle) == false)
		{
			break;
		}
	}

	return true;
}

bool mw_util_tree_get_all_children_iterator(mw_tree_t *tree, mw_handle_t parent_folder_handle, uint16_t n, mw_handle_t *node_handle_pointer)
{
	uint16_t i;
	uint16_t parent_folder_id;
	uint16_t parent_folder_level;
	uint16_t skip_level;
	uint16_t found_node_count;

	if (node_handle_pointer == NULL)
	{
		return false;
	}

	*node_handle_pointer = MW_INVALID_HANDLE;
	found_node_count = 0U;

	if (tree == NULL)
	{
		return false;
	}

	parent_folder_id = mw_util_tree_get_id_from_handle(tree, parent_folder_handle);
	if (parent_folder_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return false;
	}

	if ((tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return false;
	}

	if ((tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG) == 0U)
	{
		return false;
	}

	parent_folder_level = tree->nodes[parent_folder_id].level;
	skip_level = MW_UTIL_TREE_MAX_SIZE;

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

		if ((tree->nodes[i].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == MW_UTIL_TREE_NODE_IS_FOLDER_FLAG)
		{
			if ((tree->nodes[i].flags & MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG) == MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG)
			{
				skip_level = MW_UTIL_TREE_MAX_SIZE;
			}
			else
			{
				skip_level = tree->nodes[i].level + 1U;
			}
		}

		if (found_node_count == n)
		{
			*node_handle_pointer = tree->nodes[i].handle;

			break;
		}

		found_node_count++;
	}

	return true;
}

bool mw_tree_get_open_children_count(mw_tree_t *tree, mw_handle_t parent_folder_handle, uint16_t *count)
{
	uint16_t i;
	uint16_t parent_folder_id;
	uint16_t parent_folder_level;
	uint16_t skip_level;

	if (tree == NULL || count == NULL)
	{
		return false;
	}

	parent_folder_id = mw_util_tree_get_id_from_handle(tree, parent_folder_handle);
	if (parent_folder_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return false;
	}

	if ((tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return false;
	}

	*count = 0U;

	if ((tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG) == 0U)
	{
		return true;
	}

	parent_folder_level = tree->nodes[parent_folder_id].level;
	skip_level = MW_UTIL_TREE_MAX_SIZE;

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

		if ((tree->nodes[i].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == MW_UTIL_TREE_NODE_IS_FOLDER_FLAG)
		{
			if ((tree->nodes[i].flags & MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG) == MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG)
			{
				skip_level = MW_UTIL_TREE_MAX_SIZE;
			}
			else
			{
				skip_level = tree->nodes[i].level + 1U;
			}
		}

		(*count)++;
	}

	return true;
}

bool mw_util_tree_change_node_label(mw_tree_t *tree, mw_handle_t node_handle, char *label)
{
	uint16_t node_id;

	if (tree == NULL || label == NULL)
	{
		return false;
	}

	node_id = mw_util_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return false;
	}

	strcpy(tree->nodes[node_id].label, label);

	return true;
}

bool mw_util_tree_change_node_selected_state(mw_tree_t *tree, mw_handle_t node_handle, bool is_selected)
{
	uint16_t node_id;

	if (tree == NULL)
	{
		return false;
	}

	node_id = mw_util_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return false;
	}

	if (is_selected)
	{
		tree->nodes[node_id].flags |= MW_UTIL_TREE_NODE_IS_SELECTED_FLAG;
	}
	else
	{
		tree->nodes[node_id].flags &= ~MW_UTIL_TREE_NODE_IS_SELECTED_FLAG;
	}

	return true;
}

bool mw_util_tree_change_folder_node_open_state(mw_tree_t *tree, mw_handle_t folder_node_handle, bool is_open)
{
	uint16_t i;
	uint16_t folder_id;
	uint16_t folder_level;

	if (tree == NULL)
	{
		return false;
	}

	folder_id = mw_util_tree_get_id_from_handle(tree, folder_node_handle);
	if (folder_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return false;
	}

	if ((tree->nodes[folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return false;
	}

	folder_level = tree->nodes[folder_id].level;

	for (i = folder_id + 1U; ; i++)
	{
		if (tree->nodes[i].level < folder_level + 1U || i == tree->node_count)
		{
			break;
		}

		if ((tree->nodes[i].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
		{
			continue;
		}

		if (is_open)
		{
			tree->nodes[i].flags |= MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG;
		}
		else
		{
			tree->nodes[i].flags &= ~MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG;
		}
	}

	if (is_open)
	{
		tree->nodes[folder_id].flags |= MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG;
	}
	else
	{
		tree->nodes[folder_id].flags &= ~MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG;
	}

	return true;
}

bool mw_util_tree_remove_node(mw_tree_t *tree, mw_handle_t node_handle)
{
	uint16_t i;
	uint16_t node_id;

	if (tree == NULL)
	{
		return false;
	}

	node_id = mw_util_tree_get_id_from_handle(tree, node_handle);
	if (node_id == MW_UTIL_TREE_MAX_SIZE)
	{
		return false;
	}

	if ((tree->nodes[node_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == MW_UTIL_TREE_NODE_IS_FOLDER_FLAG)
	{
		tree_remove_all_children(tree, node_id);
	}

	for (i = node_id; i < tree->node_count - 1U; i++)
	{
		tree->nodes[i] = tree->nodes[i + 1U];
	}

	tree->node_count--;

	return true;
}

uint16_t mw_util_tree_get_id_from_handle(mw_tree_t *tree, mw_handle_t handle)
{
	uint16_t i;

	for (i = 0U; i < tree->node_count; i++)
	{
		if (tree->nodes[i].handle == handle)
		{
			return i;
		}
	}

	return MW_UTIL_TREE_MAX_SIZE;
}

/**
 * Remove all children recursively of a folder node
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_id The id of the folder to remove contents of
 * @note This does not remove folder node indicated by parent_folder_id
 */
static void tree_remove_all_children(mw_tree_t *tree, uint16_t parent_folder_id)
{
	uint16_t i;
	uint16_t parent_folder_level;
	uint16_t remove_count;

	if ((tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
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
