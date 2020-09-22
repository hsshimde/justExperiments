#include <new>
#include "JustTesting1.h"	

int main()
{
	using placenew1::JustTesting;
	char* buffer = new char[BUF];

	JustTesting* pc1{};
	JustTesting* pc2{};

	pc1 = new (buffer) JustTesting;
	pc2 = new JustTesting{ "Heap1",20 };
	
	std::cout << "Memory block address :\n"
		<< "buffer : "
		<< (void*)buffer << "\theap : " << pc2 << std::endl;

	std::cout << "Memory Content :\n";
	std::cout << pc1 << " : ";
	pc1->Show();

	std::cout << pc2 << " : ";
	pc2->Show();

	JustTesting* pc3{};
	JustTesting* pc4{};

	pc3 = new (buffer) JustTesting("Bad Idea", 6);
	pc4 = new JustTesting("Heap2", 10);

	std::cout << "Memory block address :\n"
		<< "buffer : "
		<< pc3 << "\theap : " << pc4 << std::endl;

	std::cout << "Memory Content : \n";
	std::cout << pc3 << " : ";
	pc3->Show();

	std::cout << pc4 << " : ";
	pc4->Show();

	delete pc2;
	delete pc4;
	delete[] buffer;

	std::cout << "End!\n";
	
	return 0;

}