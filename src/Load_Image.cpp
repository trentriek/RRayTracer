#include "Load_Image.h"
#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"
Image::~Image() {
	stbi_image_free(data);
}

Image::Image(int w, int h, int s, int a) {
	filepath = " ";
	width = w;
	height = h;
	stride = s;
	has_alpha = a;
	size_t cb = double(width) * height * sizeof(unsigned char) * stride;
	data = (unsigned char*)malloc(cb);
}

Image::Image(const char* Imagename, int a) {
	filepath = Imagename;
	has_alpha = a;
	getrgbvalues();
}

int Image::getrgbvalues() {
	stbi_image_free(data);

	if (has_alpha) { data = stbi_load(filepath, &width, &height, &nrChannels, STBI_rgb_alpha); stride = STBI_rgb_alpha; }
	else { data = stbi_load(filepath, &width, &height, &nrChannels, STBI_rgb); stride = STBI_rgb; }
	if (data) {
		return 0;
	}
	else {
		stbi_image_free(data);
		return -1;
	}

}


int Image::getHeight() {
	return height;
}
int Image::getWidth() {
	return width;
}
const char* Image::FileName() {
	return filepath;
}

void Image::setFileName(const char* newPath) {
	filepath = newPath;
}

//remember if the size is 1024 then the actual width is times three, because three color: 3072


void Image::getPixel(int x, int y, int* pixel, int a) {
	try {
		int ind = (width * x + y) * stride;
		pixel[0] = data[y * width * stride + x * stride];
		pixel[1] = data[y * width * stride + x * stride + 1];
		pixel[2] = data[y * width * stride + x * stride + 2];

		if(a) pixel[3] = data[y * width * stride + x * stride + 3];
	}
	catch (int e)
	{
		printf("Error accessing color in image, Exception: %d \n", e);
	}
}


void Image::setPixel(int x, int y, int* pixel, int a) {
	try {
		int ind = (width * x + y) * 3;
		data[y * width * stride + x * stride] = (unsigned char)pixel[0];
		data[y * width * stride + x * stride + 1] = (unsigned char)pixel[1];
		data[y * width * stride + x * stride + 2] = (unsigned char)pixel[2];

		if(a) data[y * width * stride + x * stride + 2] = (unsigned char)pixel[3];
	}
	catch (int e)
	{
		printf("Error setting color in image, Exception: %d \n", e);
	}
}

void Image::getColorArr(int rgbVal, int* Arr) {
		int i, j, k; k = 0;
		for (j = 0; j < height; j++) {
			for (i = 0; i < width ; i++) {
					int ind = (width * j + i) * 3;
					Arr[k] = data[ind + rgbVal];
					//printf("Red: %d \n", data[ind]);
				k++;
			}
		}

}

int Image::load(const char* fileName, int a) {
	has_alpha = a;
	if (fileName == " ") {
		return getrgbvalues();
	}
	else {
		filepath = fileName;
		return getrgbvalues();
	}
}

int Image::write(const char* fileName, Image_Type type) {
	//for reference:
	//int stbi_write_png(char const* filename, int w, int h, int comp, const void* data, int stride_in_bytes);
	//int stbi_write_bmp(char const* filename, int w, int h, int comp, const void* data);
	//int stbi_write_tga(char const* filename, int w, int h, int comp, const void* data);
	//int stbi_write_jpg(char const* filename, int w, int h, int comp, const void* data, int quality);
	//int stbi_write_hdr(char const* filename, int w, int h, int comp, const float* data);
	int rc = -1;
	if (type == png) {
		int stride_in_bytes = width * stride * sizeof(unsigned char);
		rc = stbi_write_png(fileName, width, height, 3, &data[0], stride_in_bytes);
	}
	else if (type == jpg) {
		rc = stbi_write_jpg(fileName, width, height, 3, &data[0], 100);
	}
	else if (type == bmp) {
		rc = stbi_write_bmp(fileName, width, height, 3, &data[0]);
	}
	else if (type == tga) {
		rc = stbi_write_tga(fileName, width, height, 3, &data[0]);
	}
	if (rc) {
		return 0;
	}
	else {
		printf("Image failed to Print.");
		return -1;
	}
	return 0;
}

int Image::has_Alpha() {
	return has_alpha;
}
