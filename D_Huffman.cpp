// 算术编码器 1 动态哈夫曼编码
#include "BitTree.h"
#include <iostream>

int main()
{
	std::string data = "lsiahifbdifishdsijfhdsilfhaoifgbodaifhgadfidsiufhdidsjiosjdsdjasdasdsadasdsadasfdsfdadafdasfasf";
	_bit_tree_ * _header_ = _init_header_();
	_bit_tree_ * de_header_ = _init_header_();

	for (int ii = 0; ii < data.size(); ii++) {
		init_transmit_byte();
		bool _res_ = _find_nodes_(_header_, data.at(ii));
		if (!_res_) {
			_find_nodes_(_header_, data.at(ii), true);
		}
		_dhuff_encode_(_header_, data[ii], _res_);
		_update_bit_tree_(_header_);
	}
	_dhuff_decode_(de_header_, transmit_buff);

	_remove_bit_tree_(_header_);
	_remove_bit_tree_(de_header_);
	return 0;
}
