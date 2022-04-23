#pragma once

double long mapToReal(int x, int width, double minR, double maxR) {

	double long range = maxR - minR;

	return  (double long)x * (range / (double long)width) + minR;
}


double long mapToImag(int y, int height, double minI, double maxI) {
	double long range = maxI - minI;

	return  (double long)y * (range / (double long)height) + minI;
}