#pragma once
#ifndef LOADED_IMAGE
#define LOADED_IMAGE

enum Image_Type {
	png = 0,
	jpg = 1,
	bmp = 2,
	tga = 3
	//Missing HDR
};

class Image {

public: 

	Image(const char* Imagename, int a = 0);
	Image(int w = 0, int h = 0, int s = 3, int a = 0);
	~Image();

	int getWidth();
	int getHeight();
	int has_Alpha();
	const char* FileName();
	void setFileName(const char* newPath);
	void getPixel(int x, int y, int* pixel, int a = 0);
	void setPixel(int x, int y, int* pixel, int a = 0);
	void getColorArr(int rgbVal, int* Arr);
	int load(const char* fileName = " ", int a = 0);
	int write(const char* fileName, Image_Type type = png);
private:
	const char* filepath;
	unsigned char* data;
	int width;
	int height;
	int stride;
	int nrChannels;
	int getrgbvalues();
	int has_alpha;

};

#endif