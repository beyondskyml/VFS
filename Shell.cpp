// ע�⣺returnǰ��ؼ���Ƿ�����������
// ע�⣺�������û������ֵ����Ҫ�����ϸ���
// BUG:���������ļ�����Ŀ¼ - �Ƿ�����չ�������ж�
// BUG:��Ŀ¼�½���ͬ��Ŀ¼���޷����� - ���Ե�����ӱ���Ŀ¼��������
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

// ���̿��ƺ���
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
		// to - do �в���ָ�����ͳһ�����������⣬Ȼ��ִ�� - else{ if() elseif()... } 
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
* �ַ��� - ���� - �Ϸ�
* �������ַ���
*****************************/
bool Shell::inputLegal(string input){
	if (input.length() == 0 || input.length() > 10)
		return false;
	return true;
}

/****************************
* �� - �ļ�
* ���ƣ��û�����
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
// ����searchNode(string name)����Ŀ¼
// BUG�����������ͬĿ¼ʱ���ᱨ��
// 		���������ʱ���Է���
// 		�ѽ������BUG ԭ���ж��Ƿ����ͬ���ļ�����
void Shell::mdDir(string aim){
	if (ManageSys::curpos + 1 >= 16){
		LineWrong
		return;
	}
	// �ҵ���ǰĿ¼
	ManageSys::searchNode(curDir);
	if (ManageSys::needNode == NULL){
		// �����ǰĿ¼������
		cout<<"Dir... is empty."<<endl;
		return;
	}
	// �����Ŀ¼�¿�
	if (ManageSys::needNode -> child == NULL){
		ManageSys::needNode -> child = new Dir();
		ManageSys::needNode -> child -> name = aim;
		ManageSys::needNode -> child -> next = NULL;
		ManageSys::needNode -> child -> child = NULL;
		ManageSys::writeDir();	// д���curpos�����Ϊ����Ŀ¼�� -1
		return;
	}
	// Ŀ¼���Ƿ���ͬ���ļ�
	Dir * cur = ManageSys::needNode -> child;
	while(cur -> next != NULL){
		if(cur -> name == aim){
			LineExist
			return;
		}
		cur = cur -> next;
	}
	if (cur -> name == aim){ // �жϱ������һ���ڵ�
		LineExist
		return;
	}
	// û��ͬ���ļ�����ӵ�����ĩβ
	if(cur -> next == NULL){
		cur -> next = new Dir();
		cur = cur -> next;
		cur -> name = aim;
		cur -> next = NULL;
		cur -> child = NULL;
	}
	ManageSys::writeDir();
	
	// to-do ���ͳ�ƽڵ㺯������֤��Ŀ¼�ļ���������16
}

void Shell::test_4_rdDir(){
	rdDir("long");
	lsDir();
}
// ����searchNode(string name)ɾ��Ŀ¼
void Shell::rdDir(string aim){
	// �ҵ���ǰĿ¼�ڵ�
	ManageSys::searchNode(curDir);
	if (ManageSys::needNode == NULL || ManageSys::needNode -> child == NULL){
		// ���Ŀ¼�����ڻ���Ŀ¼��Ϊ��
		cout<<"Dir... is empty."<<endl;
		return;
	}
	// ��Ŀ¼���Ƿ����Ҫɾ��Ŀ¼���ļ�
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
	cur = NULL;	//�ͷſռ�
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
// ����searchNode(string name)����Ŀ¼
void Shell::cdDir(string aim){
	// ���롰..�����ظ�Ŀ¼����ֻ�ܷ���һ�Σ��ٴ����뷵�ظ�Ŀ¼
	// ʵ�ֻ��˹�����Ҫ��������ʵ�֡�
	// ����aim����Ŀ����Ŀ¼
	if (aim == ".."){
		curDir = lastDir;
		lastDir = user;
	}
	else{
		ManageSys::searchNode(curDir);
		if (ManageSys::needNode == NULL || ManageSys::needNode -> child == NULL){
			// ���Ŀ¼�����ڻ���Ŀ¼��Ϊ��
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
// ����searchNode(string name)��ʾĿ¼
void Shell::lsDir(){
	// �ҵ���ǰĿ¼
	ManageSys::searchNode(curDir);
	// ����child
	if (ManageSys::needNode == NULL || ManageSys::needNode -> child == NULL){
		// ���Ŀ¼�����ڻ���Ŀ¼��Ϊ��
		cout<<"Dir... is empty."<<endl;
		return;
	}
	Dir * cur = ManageSys::needNode -> child;
	// ��ʾnextĿ¼
	//cout <<user << " @ " <<curDir <<" $>"<<endl;
	// to - do �������̺�Ӧ��ȥ������
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
			// ����root���Խ����Ŀ¼
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