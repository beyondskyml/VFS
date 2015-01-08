/*
* 管理系统层
* 实现对文件的管理
* 面向应用提供服务
*/

// 注意：遇到问题，单步调试可以更快发现
// 注意：else分支一定要仔细考虑

#include "ManageSys.h"
// #include <iostream>
// #include <string>
// #include <iomanip>
using namespace std;

void ManageSys::test(){
	init();
	// test_1_login();
	test_2_readDir();
	// test_3_writeDir();
	// test_4_searchNode();
	system("pause");
}

void ManageSys::init(){
	BasicService::init();
	readDir();
}

Dir * ManageSys::needNode = NULL;
void ManageSys::test_4_searchNode(){
	searchNode("f.txt");
	if(needNode != NULL) 
		cout<<"name: "<<setw(11)<<setiosflags(ios::left)
			<<needNode->name
			<<"success ^_^"<<endl;
	else cout<<"error XD"<<endl;
}
// 根据名称查找指定节点
void ManageSys::searchNode(string name){
	Dir * cur = dirHead -> child;
	if (cur == NULL)
		needNode = NULL;
	else if(name == "root")
		needNode = dirHead;
	else
		searchNodeCore(cur, name);
}
void ManageSys::searchNodeCore(Dir * cur, string name){
	if (name == cur -> name){
	 	needNode = cur;
	 	return;
	}
	if (cur -> child != NULL)
		searchNodeCore(cur -> child, name);
	if (cur -> next != NULL)
		searchNodeCore(cur -> next, name);
}

// 将目录写入basicservice的dir数组，
// basicservice可以将其保存至文件
void ManageSys::test_3_writeDir(){
	readDir();
	outDir();
	dirHead -> child -> next -> child -> name = "docs";
	dirHead -> child -> next -> next -> next = new Dir();
	dirHead -> child -> next -> next -> next -> name = "test";
	dirHead -> child -> next -> next -> next -> next = NULL;
	dirHead -> child -> next -> next -> next -> child = NULL;
	outDir();
	writeDir();
	outDir();
	cout<<endl;
	for (int i = 0; i < 16; ++i)
	{
		cout<<"name: "<<setw(11)<<setiosflags(ios::left)<<BasicService::dir[i][0]
			<<"next: "<<setw(2)<<setiosflags(ios::left)<<BasicService::dir[i][1]
			<<"child: "<<setw(2)<<setiosflags(ios::left)<<BasicService::dir[i][2]
			<<endl;
	}
}
void ManageSys::writeDir(){
	Dir * cur = dirHead -> child;
	// to-do如果目录为空
	if (cur == NULL){
		BasicService::dir[0][0] = " ";
		BasicService::dir[0][1] = " ";
		BasicService::dir[0][2] = " ";
	}
	else{
		curpos = 0;
		writeDirCore(cur);
	}
	BasicService::writeDir();
}
void ManageSys::writeDirCore(Dir * cur){
	BasicService::dir[curpos][0] = cur -> name;
	int i = curpos;
	if (cur -> child != NULL){
		BasicService::dir[i][2] = "1";
		curpos ++;
		writeDirCore(cur -> child);
	}
	else
		BasicService::dir[i][2] = "0";
	if (cur -> next != NULL){
		BasicService::dir[i][1] = "1";
		curpos ++;
		writeDirCore(cur -> next);
	}
	else
		BasicService::dir[i][1] = "0";		
}


void ManageSys::test_2_readDir(){
	readDir();			
	cout<<"success-2.1 ^_^"<<endl;
	outDir();
	cout<<"success-2.2 ^_^"<<endl;
}
void ManageSys::outDir(){
	Dir * cur = dirHead -> child;
	if (cur == NULL){
		cout<<"no dir"<<endl;
		return;
	}
	outDirCore(cur);
	cout<<endl;
}
void ManageSys::outDirCore(Dir * cur){
	cout<<"name: "<<setw(11)<<setiosflags(ios::left)<<cur -> name;
	if (cur -> next != NULL)
		outDirCore(cur -> next);
	if (cur -> child != NULL){
		cout<<"\nfather dir: " <<setw(11)<<setiosflags(ios::left)<<cur -> name;
		outDirCore(cur -> child);
	}
}

Dir * ManageSys::dirHead;
int ManageSys::curpos;
void ManageSys::readDir(){
	dirHead = new Dir();
	dirHead -> next = NULL;
	dirHead -> child = new Dir();

	Dir * cur = dirHead -> child;
	cur -> next = NULL;
	cur -> child = NULL;
	if (BasicService::dir[0][0].length() == 0){
		dirHead ->child = cur = NULL;
		return;
	}
	curpos = 0;
	readDirCore(cur);
}
void ManageSys::readDirCore(Dir * cur){
	cur -> name = BasicService::dir[curpos][0];
	// cout<< cur -> name<<endl;
	int i = curpos;
	if (BasicService::dir[i][2] == "1"){
		cur -> child = new Dir();
		cur -> child -> next = NULL;
		cur -> child-> child = NULL;
		curpos ++;
		readDirCore(cur -> child);
	}
	if (BasicService::dir[i][1] == "1"){
		cur -> next = new Dir();
		cur -> next -> next = NULL;
		cur -> next -> child = NULL;
		curpos ++;
		readDirCore(cur -> next);
	}
}

void ManageSys::test_1_login(){
	if (login("001", "100"))
		cout<<"success-1.1 ^_^" <<endl;
	else
		cout<<"fail-1.1 XD" <<endl;
	if (!login("002", "123"))
		cout<<"success-1.2 ^_^" <<endl;
	else
		cout<<"fail-1.2 XD" <<endl;
}
bool ManageSys::login(string name, string key){
	for (int i = 0; i < 11; ++i){
		if (BasicService::user[i][0] == name 
			&& BasicService::user[i][1] == key){
			return true;
		}
	}
	return false;
}

// // 测试主函数
// int main(){
// 	ManageSys::test();

// 	return 0;
// }