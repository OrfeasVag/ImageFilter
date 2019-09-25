#include <iostream>
#include <string>
#include "Image.h"
#include "Color.h"
using namespace std;
using namespace imaging;

int main(int argc, char *argv[]) {
	std::string supported_format = "ppm";
	std::string path;
	bool loaded = false;
	bool saved = false;
	bool path_ok = false;
	bool flag = false;
	imaging::Image * pic;


	if (argc == 2) { //2 arguments neg xx.yy
		path = argv[1];
		path_ok = true;
	}
	else if (argc == 1) {//1 argument  neg   (sketo)
		std::cout << "File name of the image to load: ";
		std::cin >> path;
		std::cout << std::endl;
		path_ok = true;
	}
	else {//more that 2 arguments
		std::cout << "Error getting arguments." << std::endl;
		path_ok = false;
	}
	if (path_ok == false)
	{
		std::cout << "Failure path not ok." << std::endl;
		system("pause");
		return -1;
	}
	//Check if path has . in it
	size_t hasdot = path.rfind(".");//reverse find 3ekinaei apo t telos
	if (hasdot == std::string::npos)// NO have dot in it
	{
		std::cout << "Failure path has not dot(.) in it." << std::endl;
		system("pause");
		return -1;
	}
	//============================
	pic = new imaging::Image();
	loaded = pic->load(path, supported_format);
	if (loaded == false)
	{
		std::cout << "Failure image not loaded." << std::endl;
		system("pause");
		return -1;
	}

	//=======================
	//edit image
	imaging::Color* buffer = pic->getRawDataPtr();
	unsigned int w = pic->getWidth();
	unsigned int h = pic->getHeight();
	for (unsigned int i = 0; i < w*h; i++) //pixel = 1,1,1 - pixel
	{
		buffer[i].r = 1.0f - buffer[i].r;
		buffer[i].g = 1.0f - buffer[i].g;
		buffer[i].b = 1.0f - buffer[i].b;
	}
	//=======================
	//edit save path make it xxx_neg.ppm
	//cout << "path " << path << endl;
	size_t found = path.rfind("."); //found . position 3ekinaei apo to telos
	//cout << "found " << found << endl;
	string npath = path.substr(0, found);
	//cout << "N PATH " << npath << endl;
	npath = npath + "_neg." + supported_format;
	//cout << "NEW PATH " << npath << endl;
	//=======================
	saved = pic->save(npath, supported_format);
	if (saved == false)
	{
		std::cout << "Failure image not saved." << std::endl;
		system("pause");
		return -1;
	}
	//std::cout << "Done. . ." << std::endl;
	delete pic;
	system("pause");
	return 1;
}
