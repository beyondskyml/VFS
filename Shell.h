/*
* shell²ã
*/
#include "ManageSys.h"
// using namespace std;

#define line cout<<"\t\t\t"<<"******************************\n";

class Shell
{
public:
	/* data */
	string static user;
	string static curDir;
	string static lastDir;
	void static contral();
	void static quit();
	void static md();
	void static cd();
	void static rd();
	void static test_5_mdDir();
	void static mdDir(string aim);
	void static test_4_rdDir();
	void static rdDir(string aim);
	void static test_3_cdDir();
	void static cdDir(string aim);
	void static test_2_lsDir();
	void static lsDir();
	void static init();
	void static test_1_login();
	bool static login();
	void static test();

};
