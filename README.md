# Dynamic-Huffman-Tree
动态哈夫曼树VS2017 

对Char类型的数据进行编码，注解：
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

left：二叉树的左节点
right：二叉树的右节点
parent：二叉树的父节点
number：当前节点的标号
weight：当前节点的权重
symbol：编码的字符
code：哈夫曼树的编码
fixcode：哈夫曼树的固定编码

具体使用方法还请自行添加编码功能
哈夫曼树的原理请参考本工程的lecture02small.pdf

// 2022 11 27
更新了编码器 与 解码器部分
经过实际测试，可以把乱序的96字节数据压缩到51字节

How to use:
下载 新建工程 复制粘贴 编码 在 函数 _dhuff_decode_ 608行 处暂停即可得到解码结果
