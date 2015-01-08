// 注意：return前务必检查是否完成所需操作
// 注意：所有由用户输入的值均需要进行严格检查
// BUG:不能区分文件名和目录 - 是否有扩展名进行判断
// BUG:在目录下建立同名目录后无法进入 - 可以单独添加本层目录搜索函数
#include "Shell.h"
using namespace std;
#define LineWelcome  cout<<"Welcome! Init finish."<<endl;
#define LineUserName cout<<"Please input user name: ";
#define LinePassword cout<<"Please input password: ";
#define LineWrong	 cout<<"Wrong! Please try again."<<endl;
#define LineRight	 cout<<"Success! ^_^"<<endl;
#define LineExist	 cout<<"User or Dir existed"<<endl;
#define Line         cout <<user << " @ " <<curDir <<" $>";
#define LineTips	 cout<<"Tips: 'man'  - show   manual\n"\
						 <<"      'ls'   - show   dir\n"\
						 <<"      'md'   - create dir\n"\
						 <<"      'rd'   - delete dir\n"\
						 <<"      'cd'   - change dir\n"\
						 <<"      'open' - open   file\n"\
						 <<"      'exit' - quit\n"\
						 <<endl;
void Shell::init(){
	ManageSys::init();
	LineWelcome
}

// 流程控制函数
void Shell::contral(){
	LineTips
	string command;
	
	init();
	login();

	LineTips
	while(true){
		Line
		cin >> command;
		if (command == "exit")
			/*Shell::*/quit();
		else if(command == "man")
			LineTips
		else if(command == "ls")
			lsDir();
		// to - do 有参数指令，可以统一输入参数，检测，然后执行 - else{ if() elseif()... } 
		else if(command == "md")
			md();
		else if(command == "rd")
			rd();
		else if(command == "cd")
			cd();
		else if(command == "open")
			open();
		else{
			LineWrong
			LineTips
		}
	}
}

/****************************
* 字符串 - 长度 - 合法
* 参数：字符串
*****************************/
bool Shell::inputLegal(string input){
	if (input.length() == 0 || input.length() > 10)
		return false;
	return true;
}

/****************************
* 打开 - 文件
* 名称：用户输入
*****************************/
void Shell::open(){
	cout<<">>";
	string fName;
	cin >> fName;
	if (inputLegal(fName)){
		if(ManageSys::openFile(curDir, fName))
			LineRight
		return;
	}
	LineWrong
}

void Shell::rd(){
	cout<<">>";
	string aim;
	cin >> aim;
	rdDir(aim);
}
void Shell::cd(){
	cout<<">>";
	string aim;
	cin >> aim;
	cdDir(aim);	
}
void Shell::md(){
	cout<<">>";
	string name;
	cin>> name;
	if(name.length() == 0){
		LineWrong
		return;
	}
	mdDir(name);
}
void Shell::quit(){
	curDir = "root";
	lastDir = "root";
	login();
}

void Shell::test(){
	init();
	test_1_login();
	test_2_lsDir();
	test_3_cdDir();
	test_4_rdDir();
	test_5_mdDir();
}
string Shell::user;
string Shell::curDir = "root";
string Shell::lastDir = "root";

void Shell::test_5_mdDir(){
	mdDir("long");
	lsDir();
	mdDir("right");
	lsDir();
	mdDir("right");
	lsDir();
	mdDir("long");
	lsDir();
	mdDir("sky");
	lsDir();
}
// 调用searchNode(string name)创建目录
// BUG：连续添加相同目录时不会报错
// 		不连续添加时可以发现
// 		已解决上述BUG 原因：判断是否存在同名文件有误
void Shell::mdDir(string aim){
	if (ManageSys::curpos + 1 >= 16){
		LineWrong
		return;
	}
	// 找到当前目录
	ManageSys::searchNode(curDir);
	if (ManageSys::needNode == NULL){
		// 如果当前目录不存在
		cout<<"Dir... is empty."<<endl;
		return;
	}
	// 如果该目录下空
	if (ManageSys::needNode -> child == NULL){
		ManageSys::needNode -> child = new Dir();
		ManageSys::needNode -> child -> name = aim;
		ManageSys::needNode -> child -> next = NULL;
		ManageSys::needNode -> child -> child = NULL;
		ManageSys::writeDir();	// 写入后curpos会更新为最新目录数 -1
		return;
	}
	// 目录下是否有同名文件
	Dir * cur = ManageSys::needNode -> child;
	while(cur -> next != NULL){
		if(cur -> name == aim){
			LineExist
			return;
		}
		cur = cur -> next;
	}
	if (cur -> name == aim){ // 判断本层最后一个节点
		LineExist
		return;
	}
	// 没有同名文件，添加到链表末尾
	if(cur -> next == NULL){
		cur -> next = new Dir();
		cur = cur -> next;
		cur -> name = aim;
		cur -> next = NULL;
		cur -> child = NULL;
	}
	ManageSys::writeDir();
	
	// to-do 添加统计节点函数，保证总目录文件数不大于16
}

void Shell::test_4_rdDir(){
	rdDir("long");
	lsDir();
}
// 调用searchNode(string name)删除目录
void Shell::rdDir(string aim){
	// 找到当前目录节点
	ManageSys::searchNode(curDir);
	if (ManageSys::needNode == NULL || ManageSys::needNode -> child == NULL){
		// 如果目录不存在或者目录下为空
		cout<<"Dir... is empty."<<endl;
		return;
	}
	// 该目录中是否存在要删除目录或文件
	Dir * pre = ManageSys::needNode;
	Dir * cur = ManageSys::needNode -> child;
	while(cur != NULL){
		if(cur -> name == aim){
			if (pre -> child == cur)
				pre -> child = cur -> next;
			else
				pre -> next = cur -> next;
			ManageSys::writeDir();
			break;
		}
		pre = cur;
		cur = cur -> next;
	}
	if(cur == NULL) LineWrong
	cur = NULL;	//释放空间
}

void Shell::test_3_cdDir(){
	cdDir("long");
	Line
	system("pause");
	cdDir("doc");
	Line
	system("pause");
	cdDir("..");
	Line
	system("pause");
	cdDir("..");
	Line
	system("pause");
	cdDir("doc");
	Line
	system("pause");
}
// 调用searchNode(string name)进入目录
void Shell::cdDir(string aim){
	// 输入“..”返回父目录，但只能返回一次，再次输入返回根目录
	// 实现回退功能需要加入链表实现。
	// 其他aim进入目标子目录
	if (aim == ".."){
		curDir = lastDir;
		lastDir = user;
	}
	else{
		ManageSys::searchNode(curDir);
		if (ManageSys::needNode == NULL || ManageSys::needNode -> child == NULL){
			// 如果目录不存在或者目录下为空
			cout<<"Dir... is empty."<<endl;
			return;
		}
		Dir * cur = ManageSys::needNode -> child;
		while(cur != NULL){
			if(cur -> name == aim){
				lastDir = curDir;
				curDir  = aim;
				break;
			}
			cur = cur -> next;
		}
		if(cur == NULL) LineWrong
	}
}

void Shell::test_2_lsDir(){
	curDir = "root";
	lsDir();
}
// 调用searchNode(string name)显示目录
void Shell::lsDir(){
	// 找到当前目录
	ManageSys::searchNode(curDir);
	// 进入child
	if (ManageSys::needNode == NULL || ManageSys::needNode -> child == NULL){
		// 如果目录不存在或者目录下为空
		cout<<"Dir... is empty."<<endl;
		return;
	}
	Dir * cur = ManageSys::needNode -> child;
	// 显示next目录
	//cout <<user << " @ " <<curDir <<" $>"<<endl;
	// to - do 加入流程后应该去除改行
	// Line
	while(cur != NULL){
		cout<<setw(11)<<setiosflags(ios::left)<<cur -> name;
		cur = cur -> next;
	}
	cout<<endl;
}

void Shell::test_1_login(){
	login();
}
bool Shell::login(){
	// to - do exit(0)
	bool finish = false;
	do{
		LineUserName
		string name;
		cin >> name;
		if (name == "exit")
			exit(1);
		else if (name == "root"){
			// 输入root可以进入根目录
			user = "root";
			curDir = "root";
			lastDir = "root";
			return true;
		}
		else if (name.length() < 11){
			LinePassword
			string password;
			cin >> password;
			if (password.length() < 11){
				if (ManageSys::login(name,password)){
					finish = true;
					user = name;
					mdDir(user);
					cdDir(user);
					return true;
				}
				else
					LineWrong
			}
			else
				LineWrong
		}
		else
			LineWrong
	}while(!finish);
	return false;
}

int main(){
	// Shell::test();
	Shell::contral();
	return 0;
}