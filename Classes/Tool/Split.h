#include <list>
#include <string>
using namespace std;
class Split
{
public:
	static Split * getInstance();
	list<string> strsplit(string, string);

private:
	Split();
	~Split();
};