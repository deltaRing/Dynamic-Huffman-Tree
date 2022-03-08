#pragma once

#ifndef _BITTREE_H_
#define _BITTREE_H_

#include <iostream>
#include <cstdlib>
#include <cmath>

using namespace std;

struct _bit_tree_ {
	_bit_tree_ * left = NULL;
	_bit_tree_ * right = NULL;
	_bit_tree_ * parent = NULL;
	int number = 0;
	int weight = 0;
	bool NYT = false;
	char symbol = 'X';    // 数据符号
	char code;      // 编码
	char fixcode;   // 固定编码
};

_bit_tree_ * _init_header_() {
	_bit_tree_ * _header_ = new _bit_tree_;
	_header_->NYT = true;
	return _header_;
}

// 遍历各个节点
void _iterate_bit_tree(_bit_tree_ * bit_tree, int * weights, int * numbers, bool * NYTs) {
	if (bit_tree->right == NULL && bit_tree->left == NULL) {
		weights[bit_tree->number] = bit_tree->weight;
		numbers[bit_tree->number] = bit_tree->number;
		NYTs[bit_tree->number] = bit_tree->NYT;
		return;
	}
	if (bit_tree->left != NULL) {
		_iterate_bit_tree(bit_tree->left, weights, numbers, NYTs);
	}
	if (bit_tree->right != NULL) {
		_iterate_bit_tree(bit_tree->right, weights, numbers, NYTs);
	}
	weights[bit_tree->number] = bit_tree->weight;
	numbers[bit_tree->number] = bit_tree->number;
	NYTs[bit_tree->number] = bit_tree->NYT;
}

// 找到对应的节点
_bit_tree_ * _locate_bit_tree_(_bit_tree_ * header, int number) {
	if (header->number == number) {
		return header;
	}
	else {
		if (header->left != NULL) {
			_bit_tree_ * left_node = _locate_bit_tree_(header->left, number);
			if (left_node != NULL)
				return left_node;
		}
		if (header->right != NULL) {
			_bit_tree_ * right_node = _locate_bit_tree_(header->right, number);
			if (right_node != NULL)
				return right_node;
		}
	}
	return NULL;
}

// 给各个节点打上标签
bool _label_nodes_(_bit_tree_ * bit_tree, int & label) {
	if (bit_tree->left != NULL) {
		bool succ = _label_nodes_(bit_tree->left, label);
	}
	if (bit_tree->right != NULL) {
		bool succ = _label_nodes_(bit_tree->right, label);
	}
	bit_tree->number = label;
	label++;
	return true;
}

void _swap_bit_tree_(_bit_tree_ * temp1, _bit_tree_ * temp2) {
	if (temp1 == NULL || temp2 == NULL)
		return;
	_bit_tree_ * temp1_parent = temp1->parent;
	_bit_tree_ * temp2_parent = temp2->parent; // 找到父节点

	_bit_tree_ * temp1_left = temp1->left;
	_bit_tree_ * temp2_left = temp2->left;
	_bit_tree_ * temp1_right = temp1->right;
	_bit_tree_ * temp2_right = temp2->right; // 找到子节点

	bool temp1_isleft = temp1_parent->left == temp1;
	bool temp2_isleft = temp2_parent->left == temp2; // 找到节点的左右顺序

	// 父节点交换
	if (temp1_isleft) {
		temp1_parent->left = temp2;
	}
	else {
		temp1_parent->right = temp2;
	}

	if (temp2_isleft) {
		temp2_parent->left = temp1;
	}
	else {
		temp2_parent->right = temp1;
	}

	// 子节点交换
	if (temp1_left != NULL)
		temp1_left->parent = temp2;
	if (temp1_right != NULL)
		temp1_right->parent = temp2;
	if (temp2_left != NULL)
		temp2_left->parent = temp1;
	if (temp2_right != NULL)
		temp2_right->parent = temp1;

	// 本节点交换
	temp1->parent = temp2_parent;
	temp2->parent = temp1_parent;
	temp1->left = temp2_left;
	temp1->right = temp2_right;
	temp2->left = temp1_left;
	temp2->right = temp1_right;

}

// 更新二叉树的权重 应该向下搜索
void _update_bit_tree_weight_(_bit_tree_ * bit_tree) {
	if (bit_tree->left == NULL && bit_tree->right == NULL) {
		if (bit_tree->parent != NULL) {
			_update_bit_tree_weight_(bit_tree->parent);
		}
		return; // 叶子节点 不需要更新
	}
	else {
		bit_tree->weight = bit_tree->left->weight +
			bit_tree->right->weight;
		if (bit_tree->parent != NULL) {
			_update_bit_tree_weight_(bit_tree->parent);
		}
	}
}

// 更新所有的叶子节点的权重
void _update_all_weights_(_bit_tree_ * bit_tree, int & node_value) {
	// 先找叶子节点
	if (bit_tree == NULL)
		return;
	if (bit_tree->left != NULL && bit_tree->right != NULL) {
		int _left_node_value_ = 0, _right_node_value_ = 0;
		if (bit_tree->right != NULL)
			_update_all_weights_(bit_tree->right, _right_node_value_);
		if (bit_tree->left != NULL)
			_update_all_weights_(bit_tree->left, _left_node_value_);
		bit_tree->weight = _left_node_value_ + _right_node_value_;
		node_value = bit_tree->weight;
		return;
	}
	else {
		node_value = bit_tree->weight;
		return;
	}
	return;
}

// 更新二叉树 并 交换二叉树的权重
void _update_bit_tree_(_bit_tree_ * bit_tree) {
	int label = 0;
	_label_nodes_(bit_tree, label);
	// 先标号，再检查各自的权重
	int * weights = new int[label];
	int * numbers = new int[label];
	bool * NYTs = new bool[label];
	_iterate_bit_tree(bit_tree, weights, numbers, NYTs);

	for (int ii = 0; ii < label; ii++) {
		cout << weights[ii] << " ";
	}
	cout << endl;
	
	for (int ii = 0; ii < label; ii++) {
		for (int jj = ii; jj < label; jj++) {
			if (weights[ii] > weights[jj]) {
				// 交换节点
				std::cout << weights[ii] << " " << weights[jj] << endl;
				_bit_tree_ * temp1 = _locate_bit_tree_(bit_tree, ii);
				_bit_tree_ * temp2 = _locate_bit_tree_(bit_tree, jj);
				_swap_bit_tree_(temp1, temp2);
				int _temp_ = 0;
				_update_all_weights_(bit_tree, _temp_); // 更新权重
				_update_bit_tree_(bit_tree);
				delete[] weights;
				delete[] numbers;
				delete[] NYTs;
				return;
			}
		}
	}

	delete[] weights;
	delete[] numbers;
	delete[] NYTs;
}

// 创建二叉树
_bit_tree_ * _create_bit_tree_() {
	return new _bit_tree_;
}

// 默认是在右边插入节点 左边插入NYT节点
bool _insert_bit_tree_(_bit_tree_ * bit_tree, char data) {
	if (bit_tree == NULL) return false;

	_bit_tree_ * new_node = _create_bit_tree_();
	_bit_tree_ * NYT_node = _create_bit_tree_();

	new_node->parent = bit_tree;
	new_node->NYT = false;
	new_node->symbol = data;
	new_node->weight = 1;
	NYT_node->parent = bit_tree;
	NYT_node->NYT = true;
	NYT_node->weight = 0;

	if (bit_tree->NYT) {
		bit_tree->NYT = false;
	}
	bit_tree->left = NYT_node;
	bit_tree->right = new_node;

	_update_bit_tree_weight_(bit_tree);

	return true;
}

// 删除二叉树
void _remove_bit_tree_() {
	// TODO
}

// 找到节点并增加权重、如果没有找到权重，那就往后面增加节点
bool _find_nodes_(_bit_tree_ * bit_tree, char data, bool NYTnode = false) {
	if (!NYTnode) {
		// 先找节点，没有找到就找NYTnode
		if (bit_tree->symbol == data) {
			bit_tree->weight++;
			_update_bit_tree_weight_(bit_tree);
			return true;
		}
		else {
			if (bit_tree->left == NULL && bit_tree->right == NULL) {
				// 是否应该插入子节点？
				if (bit_tree->parent == NULL && bit_tree->weight == 0) {
					_find_nodes_(bit_tree, data, true);
					return true;
				} // 如果检查到该节点是初始节点，那么直接创建新节点
				return false; // 到叶子节点了 
			}
			bool left_node_found;
			if (bit_tree->left != NULL)
				left_node_found = _find_nodes_(bit_tree->left, data);
			bool right_node_found;
			if (bit_tree->right != NULL)
				right_node_found = _find_nodes_(bit_tree->right, data);
			// 遍历两边的
			if (left_node_found || right_node_found) {
				return true;
			}
			return false;
		}
	}

	// 以上操作均没有找到节点，找到NYTnode
	if (!bit_tree->NYT) {
		if (bit_tree->left != NULL)
			_find_nodes_(bit_tree->left, data, true);
		if (bit_tree->right != NULL)
			_find_nodes_(bit_tree->right, data, true);
	}
	else {
		_insert_bit_tree_(bit_tree, data);
	}
	return true;
}

#endif
