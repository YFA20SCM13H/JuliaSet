#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <cmath>
#include <complex>
#include <chrono>
#include <FreeImagePlus.h>
//#include "FreeImage.h"
#include "Source.h"

#include "functions.h"

#include <time.h>
#include <tbb/tbb.h>

using namespace std;
using namespace std::chrono;
using namespace tbb;

using namespace std;

const int ITERATIONS = 1000;
int Selection;

int main() {
	clock_t tStart = clock(); //Start Timer
	cout << "Start!\n\n";

	
	//make larger number for testing speed
	//I didnt not consider different width and height so do not make them into different numbers, always same number
	int width = 5000;
	int height = 5000;

	fipImage outputImage;
	outputImage = fipImage(FIT_FLOAT, width, height, 32);
	BYTE *outputBuffer = outputImage.accessPixels();
	vector<int> colors{ 100, 140, 180, 220, 225 };

	complex<float>C(0.4, 0.6);
	const float limit = 1.7f;

	for (int y = 0; y < height; y++) {

			for (int x = 0; x < width; x++) {

				complex<float> Z(-limit + 2.0f * limit / width * x, -limit + 2.0f * limit / width * y);
				UINT i;
				for (i = 0; i < ITERATIONS; i++) {
					Z = Z * Z + C;
					if (abs(Z) > 2.0f) break; // abs returns the absolute value of an integer number
				}
				if (i < ITERATIONS) {
					outputBuffer[(y * width + x) * 4] = colors[i % 5]; //plotting color
					//testing with GetPixelColor but didn't work
					//RGBQUAD color; FreeImage_GetPixelColor(outputBuffer, input, &color);
				}
			}
	}

	//saving image
	std::cout << "Saving image...\n"; 
	outputImage.convertToType(FREE_IMAGE_TYPE::FIT_BITMAP);
	outputImage.convertTo24Bits();
	outputImage.save("Julia_Set.png");
	std::cout << "...done\n\n";


	//Timer ends and caculates time taken
	printf("Time taken: %.2fs\n", (double)(clock() - tStart) / CLOCKS_PER_SEC);
	return 0;
}
