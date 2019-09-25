/*
Anagnostaki Iro  3140008
Vagelakis Orfeas 3140018
*/
#include "ppm.h"
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
using namespace imaging;

float * imaging::ReadPPM(const char * filename, int * w, int * h)
{
	string header;
	int width;
	int height;
	size_t max_size;
	ifstream image(filename, ios::in | ios::binary);
	if (image)
	{
		image >> header;//P6?
		image >> width;
		image >> height;
		image >> max_size;//255?
		//cout << "Found header [" << header << "] width [" << width << "] height [" << height << "] max_size [" << max_size << "] ." << endl;
		unsigned char value; //max is 255
		image.get();//ka8arizw ta \n
		int size = (*w) * (*h) * 3;//buffer size 
		float * buffer = new float[size];//pinakas me rgb 
		for (int i = 0; i < size; i++)
		{
			image.read((char *)&value, sizeof(char));
			buffer[i] = value / 255.0f;// metatrepw se  float
		}
		image.close();
		//std::cout << "Reading Done!" << endl;
		return buffer;//return ton pinaka
	}
	else // couldnt open stream
	{
		std::cout << "Stream is closed, file not found (Read)!" << endl;
		return nullptr;
	}
}

bool imaging::WritePPM(const float * data, int w, int h, const char * filename)
{
	string header = "P6";
	int width = w;;
	int height = h;
	size_t max_size = 255;
	ofstream image(filename, ios::out | ios::binary);
	if (image)//open stream
	{
		image << header;
		image << "\n";
		image << width;
		image << "\n";
		image << height;
		image << "\n";
		image << max_size;
		image << "\n";
		int size = w * h * 3;//buffer size 
		char * tmp = new char[size];
		for ( int i = 0; i < size; i++)
		{
			tmp[i] = (char)(data[i] * 255.0f);
		}
		image.write((char *)tmp, size);
		image.close();
		std::cout << "A new image has been created [" << filename << "]." << endl;
		delete[] tmp,data;
		return true;
	}
	else
	{
		std::cout << "Stream is closed (Write)!" << endl;
		return false;
	}
}
