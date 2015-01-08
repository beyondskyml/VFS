/*
* ���������
* ΪVFS�ṩ�����Ĵ�������д���ر��ļ�����������ת��������
* ������Ϊ�����ṩ���ļ������ӿڡ�
*/

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

// ���С �ֽ�
#define blockSize 256
// �ܿ��� 10MB
#define blockNum  10 * 1024 * 1024
// ������ ��ʼ���	�洢�û���Ϣ
#define bootBlockNo 0
// ������ ��ʼ���	�洢Ŀ¼��Ϣ
#define superBlockNo 1
// �ļ���Ϣ�� ��ʼ���	�洢�ļ���Ϣ
#define infoBlockNo 2
// ���ݿ� ��ʼ���		�洢�ļ�����
#define dataBlockNo 128 * 256
using namespace std;



class BasicService
{
private:
	/*data*/
	static int emptyBlockNum;					// ���п�����
	static bool blockStatus[blockNum];			// ��ʹ�������TRUE ���ã� FALSE ����
	static bool infoBlockStatus[dataBlockNo - infoBlockNo];			// ��Ϣ��ʹ�������TRUE ���ã� FALSE ����
	
	static int fileInfoBlockNo;						// ָ�����ļ���Ϣ�����
	
	static bool isWrite;						// ��д��־λ true�����Ƿ�����Ϣ����д
	static string fileName;
	static string fileUser;
	static int fileBlockNo[20];



	static fstream iofile;

public:
	/*test*/
	void static test_1_createFile_shoule_get_true();
	void static test_2_writeFile();
	void static test_3_saveFileInfo();
	void static test_4_writeInfoString();
	void static test_5_writeUser();
	void static test_6_readUser();
	// void static test_9_searchInfoNo();
	void static test();

	string static dir[16][3];
	void static test_8_readDir();
	void static readDir();
	void static test_7_writeDir();
	void static writeDir();
	
	string static user[11][2];
	void static readUser(); 
	void static writeUser();
	void static setFileName(string _fileName);
	void static setFileUser(string _fileUser);
	void static init();
	bool static saveFileInfo();
	void static writeFileInfo();
	void static writeInfoString(string writeString);
	bool static calDataBlock(string fileString);
	int  static infoNo;
	bool static searchInfoNo(string searchName);
	bool static createFile();
	bool static writeFile(string fileString);
};

