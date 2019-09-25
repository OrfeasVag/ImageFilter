#include "Image.h"
#include <fstream>
#include <string>
#include <iostream>
#include "ppm/ppm.h"

using namespace imaging;

/*! Returns the width of the image
*/

 const unsigned int imaging::Image::getWidth() const
{
	return width;
}

/*! Returns the height of the image
*/

 const unsigned int imaging::Image::getHeight() const
{
	return height;
}

Color * imaging::Image::getRawDataPtr()
{
	return &buffer[0];
}

Color imaging::Image::getPixel(unsigned int x, unsigned int y) const
{
	Color color;
	if (x >= width || y >= height)
	{
		color.r = 0;
		color.g = 0;
		color.b = 0; //return black
	}
	else
	{
		unsigned long loc = (y*width + x); // pinakas mia diastash 
		color = buffer[loc];
	}
	return color;
}

void imaging::Image::setPixel(unsigned int x, unsigned int y, Color & value)
{
	if (x >= width || y >= height)
	{
		return;
	}
	unsigned long loc = (y*width + x); // pinakas mia diastash 
	buffer[loc] = value;
}

void imaging::Image::setData(const Color *& data_ptr)
{
	if (buffer != nullptr && width != 0 && height != 0)
	{
		size_t size = width*height;
		for (size_t i = 0; i < size; i++) {
			buffer[i] = data_ptr[i];
		}
	}
	else
	{
		return; //exit
	}
}

imaging::Image::Image() :width(0), height(0), buffer(nullptr)
{
	/*width = 0;
	height = 0;
	buffer = nullptr;*/
}

imaging::Image::Image(unsigned int width, unsigned int height) :width(width), height(height), buffer(nullptr)
{
}

imaging::Image::Image(unsigned int width, unsigned int height, const Color * data_ptr)
{
	this->width = width;
	this->height = height;
	buffer = new Color[width*height];
	for (unsigned int i = 0; i < width*height; i++) {
		buffer[i] = data_ptr[i];
	}
}

imaging::Image::Image(const Image & src)
{
	this->width = src.width;
	this->height = src.height;
	buffer = new Color[width*height];
	for (unsigned int i = 0; i < width*height; i++) {
		buffer[i] = src.buffer[i];
	}
}

imaging::Image::~Image()
{
	width = NULL;
	height = NULL;
	buffer = nullptr;
}

Image & imaging::Image::operator=(const Image & right)
{
	this->width = right.width;
	this->height = right.height;
	buffer = new Color[width*height];//set size
	for (unsigned int i = 0; i < width*height; i++)
	{
		this->buffer[i] = right.buffer[i];
	}
	return *this;
}

bool imaging::Image::load(const std::string & filename, const std::string & format)
{
	size_t found = filename.find("." + format);
	//npos shmainei den bre8hke
	if (found != std::string::npos) //An bre8hke to .ppm tote
	{
		//std::cout << ".ppm found " << std::endl;
		/*if (this != NULL) //Image is initialized
		{
			Image();//clears width,height,buffer
		}*/
		std::string header;
		int width;
		int height;
		size_t max_size;
		std::ifstream image(filename, std::ios::in | std::ios::binary);
		if (image)
		{
			image >> header;//P6?
			image >> width;
			image >> height;
			image >> max_size;//255?
			if (header.compare("P6") != 0) {
				printf("Error given header is [%s].\n", header.c_str());
				return false;
			}
			if (max_size > 255)
			{
				printf("Error given max size is [%d].\n", max_size);
				return false;
			}
			std::cout << "Image dimentions are: ";
			std::cout << width;
			std::cout << " X ";
			std::cout << height;
			std::cout << std::endl;
			image.close();// close stream
			float* tmp = ReadPPM(filename.c_str(), &width, &height);
			Color *color = new Color[width*height];
			int y = 0;
			for (int i = 0; i < width*height; i++)
			{
				color[i].r = tmp[y + 0];
				color[i].g = tmp[y + 1];
				color[i].b = tmp[y + 2];
				y = y + 3;//float pinakas epomenh 8esh rgb einai h +3
			}
			//Image(width, height, color); //dwse tis times sto Image item ths main
			this->width = width;
			this->height = height;
			this->buffer = new Color[width*height];
			for (int i = 0; i < width*height; i++) {
				this->buffer[i] = color[i];
			}
			delete[] color,tmp;
			//=============================
			return true;
		}
		else
		{
			std::cout << "Stream Closed (load)" << std::endl;
			return false;
		}
	}
	else
	{
		std::cout << "Not Found" << std::endl;
		std::cout << "False load." << std::endl;
		return false;
	}
}

bool imaging::Image::save(const std::string & filename, const std::string & format)
{
	size_t found = filename.find("." + format);
	//npos shmainei den bre8hke
	if (found != std::string::npos) //An bre8hke to .ppm tote
	{
		//Color ---> Float
		float* tmp = new float[this->width*this->height * 3];
		int y = 0;
		for (unsigned int i = 0; i < width*height * 3; i = i + 3)
		{
			tmp[i] = this->buffer[y].r;
			tmp[i + 1] = this->buffer[y].g;
			tmp[i + 2] = this->buffer[y].b;
			y++;
		}
		//twra o tmp exei ola ta rgb
		return WritePPM(tmp, this->width, this->height, filename.c_str());
	}
	else
	{
		std::cout << "Error unsupported format (save)." << std::endl;
		return false;
	}
}
