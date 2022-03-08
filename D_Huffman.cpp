#include "BitTree.h"
#include <iostream>

int main()
{
	std::string data = "ABBAABBCCCBAADDDDDAABBCCCBBDDDDDD";
	_bit_tree_ * _header_ = _init_header_();

	for (int ii = 0; ii < data.size(); ii++) {
		bool _res_ = _find_nodes_(_header_, data.at(ii));
		if (!_res_) {
			_find_nodes_(_header_, data.at(ii), true);
		}
		_update_bit_tree_(_header_);
		int label = 0;
		_label_nodes_(_header_, label);
	}


	std::cout << "Hello World!\n";
	return 0;
}
