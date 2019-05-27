#include <stdio.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#define MW_UTIL_TREE_ROOT_FOLDER_ID 		0U
#define MW_UTIL_TREE_MAX_SIZE				20U
#define MW_UTIL_TREE_NODE_LABEL_MAX_SIZE	16U
#define MW_UTIL_TREE_NODE_IS_USED_FLAG		0x01U
#define MW_UTIL_TREE_NODE_IS_SELECTED_FLAG	0x04U
#define MW_UTIL_TREE_NODE_IS_FOLDER_FLAG	0x02U
#define MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG	0x08U

/**
 * Node structure
 */
typedef struct
{
	uint16_t parent_id;									///< The node id of this node's parent folder
	char label[MW_UTIL_TREE_NODE_LABEL_MAX_SIZE + 1U];	///< This node's label
	uint8_t level;										///< The folder depth of this node; root folder is zero
	uint8_t flags;										///< Flags describing this node
} mw_tree_node_t;

/**
 * Tree structure
 */
typedef struct
{
	uint16_t folder_node_stack[MW_UTIL_TREE_MAX_SIZE];	///< Stack used to avoid recursion when recusrively finding all descendants of a folder node
	uint16_t folder_node_stack_size;					///< The current number of entries in the above stack
	mw_tree_node_t nodes[MW_UTIL_TREE_MAX_SIZE];		///< Memory pool of nodes contained in the tree
} mw_util_tree_t;

/**
 * Pointer type to callback function when finding all descendants of a folder node
 *
 * @param tree Pointer to tree structure
 * @param node_id The node id of the next found node
 * @return Return true to continue searching or false to quit searching
 */
typedef bool (*mw_util_tree_func_p)(mw_util_tree_t *tree, uint16_t node_id);

/**
 * Initialize the tree. This sets up the root folder node with node_id 0 and marks all other nodes unused
 *
 * @param tree Pointer to tree structure
 * @param root_folder_label Label to give to the root folder node
 * @param flags Can be MW_UTIL_TREE_NODE_IS_SELECTED_FLAG or MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG or both
 * @return True if parameters acceptable, else false
 */
bool mw_util_tree_init(mw_util_tree_t *tree, char *root_folder_label, uint8_t flags);

/**
 * Empty a tree of all nodes except the root folder node which remains untouched
 *
 * @param tree Pointer to tree structure
 */
void mw_util_tree_empty(mw_util_tree_t *tree);

/**
 * Add a node to a tree in a specified folder
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_id The folder to create the new node in
 * @param label The label to assign to the new node
 * @param flags Flags describing the node. Can be any from MW_UTIL_TREE_NODE_IS_SELECTED_FLAG,
 *              MW_UTIL_TREE_NODE_IS_FOLDER_FLAG, MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG
 * @return The new node id if added successfully or MW_UTIL_TREE_MAX_SIZE if a parameter was illegal or no space remaining
 */
uint16_t mw_util_tree_add_node(mw_util_tree_t *tree, uint16_t parent_folder_id, char *label, uint8_t flags);

/**
 * Change a node's label
 *
 * @param tree Pointer to tree structure
 * @param node_id Node id of node to change label of
 * @param label Text string of new label
 * @return True if parameters acceptable, else false
 */
bool mw_util_tree_change_node_label(mw_util_tree_t *tree, uint16_t node_id, char *label);

/**
 * Change a folder node's selected state
 *
 * @param tree Pointer to tree structure
 * @param folder_node_id Node id of the folder node to change selected state of
 * @param is_selected True to assign a folder node selected, false unselected
 * @return True if parameters acceptable, else false
 */
bool mw_util_tree_change_node_selected_state(mw_util_tree_t *tree, uint16_t node_id, bool is_selected);

/**
 * Change a folder node's open state
 *
 * @param tree Pointer to tree structure
 * @param folder_node_id Node id of the folder node to change open state of
 * @param is_open True to assign a folder node open, false closed
 * @return True if parameters acceptable, else false
 */
bool mw_util_tree_change_folder_node_open_state(mw_util_tree_t *tree, uint16_t folder_node_id, bool is_open);

/**
 * Remove a node
 *
 * @param tree Pointer to tree structure
 * @param node_id Node id of node to remove
 * @return True if parameters acceptable, else false
 */
bool mw_util_tree_remove_node(mw_util_tree_t *tree, uint16_t node_id);

/**
 * Recursively get all the children and sub-children of a folder node via callback function
 *
 * @param tree Pointer to tree structure
 * @param parent_folder_id The folder to start looking in
 * @param open_if_closed When true, if parent_folder_id node is closed, open it before getting children.
 *                       When false, if parent_folder_id node is closed, do nothing.
 *                       If parent_folder_id node is already open this parameter is ignored.
 * @param callback The function to be called for each child or sub-child found
 * @return True if parameters acceptable, else false
 * @note This function recursively descends the tree from the starting folder getting all children of all descendant folders
 * @note This function can be instructed to terminate early at any point by the callback function returning false
 */
bool mw_util_tree_get_all_children(mw_util_tree_t *tree, uint16_t parent_folder_id, bool open_if_closed, mw_util_tree_func_p callback);

static uint16_t mw_util_tree_get_folder_member_count(mw_util_tree_t *tree, uint16_t folder_id);
static uint16_t mw_util_tree_get_node_id(mw_util_tree_t *tree, uint16_t parent_id, uint16_t n);
static void mw_util_tree_remove_all_children(mw_util_tree_t *tree, uint16_t folder_id);

mw_util_tree_t my_tree;

bool node_callback(mw_util_tree_t *tree, uint16_t node_id)
{
	uint8_t level;

	if (tree == NULL ||
			node_id >= MW_UTIL_TREE_MAX_SIZE ||
			(tree->nodes[node_id].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == 0U)
	{
		return true;
	}

	for (level = 1U; level < tree->nodes[node_id].level; level++)
	{
		printf("  ");
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

void print_folder(mw_util_tree_t *tree, uint16_t folder_id, bool open_if_closed)
{
	if (tree == NULL ||
			folder_id >= MW_UTIL_TREE_MAX_SIZE ||
			(tree->nodes[folder_id].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == 0U ||
			(tree->nodes[folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return;
	}

	printf("%s\\\n", tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].label);
	(void)mw_util_tree_get_all_children(tree, folder_id, open_if_closed, node_callback);
}

int main(void)
{
	mw_util_tree_init(&my_tree, "root", MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG);

	mw_util_tree_add_node(&my_tree,
			MW_UTIL_TREE_ROOT_FOLDER_ID,
			"file1",
			0U);
	uint16_t fold1_id = mw_util_tree_add_node(&my_tree,
			MW_UTIL_TREE_ROOT_FOLDER_ID,
			"fold1",
			MW_UTIL_TREE_NODE_IS_FOLDER_FLAG | MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG);
	mw_util_tree_add_node(&my_tree,
			fold1_id,
			"file2",
			0U);
	mw_util_tree_add_node(&my_tree,
			fold1_id,
			"file3",
			0U);
	uint16_t fold2_id = mw_util_tree_add_node(&my_tree,
			fold1_id,
			"fold2",
			MW_UTIL_TREE_NODE_IS_FOLDER_FLAG | MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG);
	mw_util_tree_add_node(&my_tree,
			fold2_id,
			"file4",
			0U);
	mw_util_tree_add_node(&my_tree,
			fold2_id,
			"file5",
			0U);

	printf("The full tree\n");
	print_folder(&my_tree, MW_UTIL_TREE_ROOT_FOLDER_ID, true);

	printf("root closed, not forced open\n");
	mw_util_tree_change_folder_node_open_state(&my_tree, MW_UTIL_TREE_ROOT_FOLDER_ID, false);
	print_folder(&my_tree, MW_UTIL_TREE_ROOT_FOLDER_ID, false);

	printf("root closed, forced open\n");
	print_folder(&my_tree, MW_UTIL_TREE_ROOT_FOLDER_ID, true);

	printf("fold2 closed\n");
	mw_util_tree_change_folder_node_open_state(&my_tree, fold2_id, false);
	print_folder(&my_tree, MW_UTIL_TREE_ROOT_FOLDER_ID, true);

	printf("fold2 removed\n");
	mw_util_tree_remove_node(&my_tree, fold2_id);
	print_folder(&my_tree, MW_UTIL_TREE_ROOT_FOLDER_ID, true);

	printf("Empty tree\n");
	mw_util_tree_empty(&my_tree);
	print_folder(&my_tree, MW_UTIL_TREE_ROOT_FOLDER_ID, true);

	return 0;
}

bool mw_util_tree_init(mw_util_tree_t *tree, char *root_folder_label, uint8_t flags)
{
	if (tree == NULL || root_folder_label == NULL)
	{
		return false;
	}

	tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].flags = MW_UTIL_TREE_NODE_IS_FOLDER_FLAG | MW_UTIL_TREE_NODE_IS_USED_FLAG | flags;
	strcpy(tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].label, root_folder_label);
	tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].level = 0U;
	tree->nodes[MW_UTIL_TREE_ROOT_FOLDER_ID].parent_id = MW_UTIL_TREE_MAX_SIZE;

	mw_util_tree_empty(tree);

	return true;
}

void mw_util_tree_empty(mw_util_tree_t *tree)
{
	uint16_t i;

	if (tree == NULL)
	{
		return;
	}

	for (i = 1U; i < MW_UTIL_TREE_MAX_SIZE; i++)
	{
		tree->nodes[i].flags &= ~MW_UTIL_TREE_NODE_IS_USED_FLAG;
	}
}

uint16_t mw_util_tree_add_node(mw_util_tree_t *tree, uint16_t parent_folder_id, char *label, uint8_t flags)
{
	uint16_t i;

	if (tree == NULL ||
			label == NULL ||
			parent_folder_id >= MW_UTIL_TREE_MAX_SIZE ||
			(tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == 0U ||
			(tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return MW_UTIL_TREE_MAX_SIZE;
	}

	for (i = 0U; i < MW_UTIL_TREE_MAX_SIZE; i++)
	{
		if ((tree->nodes[i].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == 0U)
		{
			tree->nodes[i].flags |= MW_UTIL_TREE_NODE_IS_USED_FLAG;
			strcpy(tree->nodes[i].label, label);
			tree->nodes[i].parent_id = parent_folder_id;
			tree->nodes[i].flags = flags | MW_UTIL_TREE_NODE_IS_USED_FLAG;
			tree->nodes[i].level = tree->nodes[parent_folder_id].level + 1U;

			return i;
		}
	}

	return MW_UTIL_TREE_MAX_SIZE;
}

bool mw_util_tree_get_all_children(mw_util_tree_t *tree, uint16_t parent_folder_id, bool open_if_closed, mw_util_tree_func_p callback)
{
	uint16_t node_member_count;
	uint16_t node_member;
	uint16_t node_member_id;
	uint16_t stack_top_folder_node_id;

	if (tree == NULL ||
			parent_folder_id >= MW_UTIL_TREE_MAX_SIZE ||
			(tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == 0U ||
			(tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return false;
	}

	if (open_if_closed)
	{
		tree->nodes[parent_folder_id].flags |= MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG;
	}

	if ((tree->nodes[parent_folder_id].flags & MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG) == 0U)
	{
		return true;
	}

	tree->folder_node_stack[0] = parent_folder_id;
	tree->folder_node_stack_size = 1U;

	while (tree->folder_node_stack_size > 0U)
	{
		stack_top_folder_node_id = tree->folder_node_stack[tree->folder_node_stack_size - 1];
		tree->folder_node_stack_size--;

		node_member_count = mw_util_tree_get_folder_member_count(tree, stack_top_folder_node_id);
		for (node_member = 0U; node_member < node_member_count; node_member++)
		{
			node_member_id = mw_util_tree_get_node_id(tree, stack_top_folder_node_id, node_member);
			if ((tree->nodes[node_member_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == MW_UTIL_TREE_NODE_IS_FOLDER_FLAG)
			{
				tree->folder_node_stack[tree->folder_node_stack_size] = node_member_id;
				tree->folder_node_stack_size++;
			}

			if ((tree->nodes[tree->nodes[node_member_id].parent_id].flags & MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG) == MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG)
			{
				if (callback(tree, node_member_id) == false)
				{
					return true;
				}
			}
		}
	}

	return true;
}

bool mw_util_tree_change_node_label(mw_util_tree_t *tree, uint16_t node_id, char *label)
{
	if (tree == NULL ||
			label == NULL ||
			node_id >= MW_UTIL_TREE_MAX_SIZE ||
			(tree->nodes[node_id].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == 0U)
	{
		return false;
	}

	strcpy(tree->nodes[node_id].label, label);

	return true;
}

bool mw_util_tree_change_node_selected_state(mw_util_tree_t *tree, uint16_t node_id, bool is_selected)
{
	if (tree == NULL ||
			node_id >= MW_UTIL_TREE_MAX_SIZE ||
			(tree->nodes[node_id].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == 0U)
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

bool mw_util_tree_change_folder_node_open_state(mw_util_tree_t *tree, uint16_t folder_node_id, bool is_open)
{
	if (tree == NULL ||
			folder_node_id >= MW_UTIL_TREE_MAX_SIZE ||
			(tree->nodes[folder_node_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U ||
			(tree->nodes[folder_node_id].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == 0U)
	{
		return false;
	}

	if (is_open)
	{
		tree->nodes[folder_node_id].flags |= MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG;
	}
	else
	{
		tree->nodes[folder_node_id].flags &= ~MW_UTIL_TREE_FOLDER_IS_OPEN_FLAG;
	}

	return true;
}

bool mw_util_tree_remove_node(mw_util_tree_t *tree, uint16_t node_id)
{
	if (tree == NULL ||
			node_id >= MW_UTIL_TREE_MAX_SIZE ||
			(tree->nodes[node_id].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == 0U ||
			node_id == MW_UTIL_TREE_ROOT_FOLDER_ID)
	{
		return false;
	}

	if ((tree->nodes[node_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == MW_UTIL_TREE_NODE_IS_FOLDER_FLAG)
	{
		mw_util_tree_remove_all_children(tree, node_id);
	}

	tree->nodes[node_id].flags &= ~MW_UTIL_TREE_NODE_IS_USED_FLAG;

	return true;
}

/**
 *
 */
static uint16_t mw_util_tree_get_folder_member_count(mw_util_tree_t *tree, uint16_t folder_id)
{
	uint16_t i;
	uint16_t child_count;

	if ((tree->nodes[folder_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == 0U)
	{
		return 0;
	}

	child_count = 0U;
	for (i = 0U; i < MW_UTIL_TREE_MAX_SIZE; i++)
	{
		if ((tree->nodes[i].flags & MW_UTIL_TREE_NODE_IS_USED_FLAG) == MW_UTIL_TREE_NODE_IS_USED_FLAG &&
				tree->nodes[i].parent_id == folder_id)
		{
			child_count++;
		}
	}

	return child_count;
}

/**
 *
 */
static uint16_t mw_util_tree_get_node_id(mw_util_tree_t *tree, uint16_t parent_id, uint16_t n)
{
	uint16_t i;
	uint16_t next_node;

	next_node = 0U;
	for (i = 0U; i < MW_UTIL_TREE_MAX_SIZE; i++)
	{
		if (tree->nodes[i].parent_id == parent_id)
		{
			if (next_node == n)
			{
				return i;
			}
			next_node++;
		}
	}

	return MW_UTIL_TREE_MAX_SIZE;
}

/**
 *
 */
static void mw_util_tree_remove_all_children(mw_util_tree_t *tree, uint16_t folder_id)
{
	uint16_t node_member_count;
	uint16_t node_member;
	uint16_t node_member_id;
	uint16_t stack_top_folder_node_id;

	tree->folder_node_stack[0] = folder_id;
	tree->folder_node_stack_size = 1U;

	while (tree->folder_node_stack_size > 0U)
	{
		stack_top_folder_node_id = tree->folder_node_stack[tree->folder_node_stack_size - 1];
		tree->folder_node_stack_size--;

		node_member_count = mw_util_tree_get_folder_member_count(tree, stack_top_folder_node_id);
		for (node_member = 0U; node_member < node_member_count; node_member++)
		{
			node_member_id = mw_util_tree_get_node_id(tree, stack_top_folder_node_id, node_member);
			if ((tree->nodes[node_member_id].flags & MW_UTIL_TREE_NODE_IS_FOLDER_FLAG) == MW_UTIL_TREE_NODE_IS_FOLDER_FLAG)
			{
				tree->folder_node_stack[tree->folder_node_stack_size] = node_member_id;
				tree->folder_node_stack_size++;
			}

			tree->nodes[node_member_id].flags &= ~MW_UTIL_TREE_NODE_IS_USED_FLAG;
		}
	}

	return;
}
