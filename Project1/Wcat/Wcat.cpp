#include <iostream>
#include <fstream>
using namespace std;

int main(int argc, char **argv)
{
	if(argc==1){

    	return 0;
    }

    for (int i = 1; i < argc; i++)
    {
         ifstream f(argv[i]);
          
	 if (f.is_open())
		cout << f.rdbuf();
	 else{
	 	cout<<"wcat: cannot open file"<<endl;
	 	return 1;
	 }
    }
    return 0;
    
}
