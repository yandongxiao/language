#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>
#include <list>
#include <fstream>
#include <initializer_list>

using namespace std;

/*******************************************************************
 * Copyright (C) Jerry Jiang
 *
 * File Name   : copy_backward.cpp
 * Author      : Jerry Jiang
 * Create Time : 2012-3-21 23:14:57
 * Mail        : jbiaojerry@gmail.com
 * Blog        : http://blog.csdn.net/jerryjbiao
 *
 * Description :  简单的程序诠释C++ STL算法系列之十四
 *                变易算法 : 反向复制copy_backward
 *
 ******************************************************************/

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

int main()
{
	vector<int> myvector;
	vector<int>::iterator iter;

	//为容器myvector赋初始值:10 20 30 40 50
	for ( int i = 1; i <= 5; ++i )
	{
		myvector.push_back( i*10 );
	}

	//将myvector容器的大小增加3个单元
	myvector.resize( myvector.size()+3 );

	//将容器元素20、10拷贝到第八、第七个单元中：10 20 30 40 50 0 10 20
	//注意copy_backward是反向复制，先将20拷贝到第八个单元，再将10拷贝到第七个单元
	copy_backward( myvector.begin(), myvector.begin()+2, myvector.end() );

	for ( iter = myvector.begin(); iter != myvector.end(); ++iter )
	{
		cout << " " << *iter;
	}

	cout << endl;


	//清除myvector容器
	myvector.clear();

	//还原容器myvector的初始值:10 20 30 40 50
	for (int i = 1; i <= 5; ++i )
	{
		myvector.push_back( i*10 );
	}

	//将容器元素40、50覆盖10、20, 即：40 50 30 40 50：
	copy_backward( myvector.end()-2, myvector.end(), myvector.end()-3 );

	for ( iter = myvector.begin(); iter != myvector.end(); ++iter )
	{
		cout << " " << *iter;
	}

	cout << endl;
	return 0;
}

