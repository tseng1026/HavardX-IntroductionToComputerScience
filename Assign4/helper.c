#include <math.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]){
	for (int i = 0; i < height; i ++){
		for (int j = 0; j < width; j ++){
			int R = image[i][j].rgbtRed;
			int G = image[i][j].rgbtGreen;
			int B = image[i][j].rgbtBlue;

			int avg = round((R + G + B) / 3.0);

			image[i][j].rgbtRed   = avg;
			image[i][j].rgbtGreen = avg;
			image[i][j].rgbtBlue  = avg;
		}
	}
	return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]){
	for (int i = 0; i < height; i ++){
		for (int j = 0; j < width / 2; j ++){
			RGBTRIPLE tmp = image[i][j];
			image[i][j] = image[i][width - 1 - j];
			image[i][width - 1 - j] = tmp;
		}
	}
	return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width]){
	RGBTRIPLE tmp_image[height][width];
	for (int i = 0; i < height; i ++){
		for (int j = 0; j < width; j ++){
			tmp_image[i][j] = image[i][j];
		}
	}

	for (int i = 0; i < height; i ++){
		for (int j = 0; j < width; j ++){
			float count = 1;
			int R = image[i][j].rgbtRed;
			int G = image[i][j].rgbtGreen;
			int B = image[i][j].rgbtBlue;
			for (int di = -1; di <= 1; di ++){
				for (int dj = -1; dj <= 1; dj ++){
					if (i + di < 0 || i + di >= height) continue;
					if (j + dj < 0 || j + dj >= width)  continue;
					if (di == 0 && dj == 0) continue;

					R += tmp_image[i + di][j + dj].rgbtRed;
					G += tmp_image[i + di][j + dj].rgbtGreen;
					B += tmp_image[i + di][j + dj].rgbtBlue;
					count += 1;
				}
			}

			image[i][j].rgbtRed   = round(R / count);
			image[i][j].rgbtGreen = round(G / count);
			image[i][j].rgbtBlue  = round(B / count);
		}
	}
	return;
}

// Detect edges
int min(int limit, int val){
	if (val < limit) return val;
	else return limit;
}

void edges(int height, int width, RGBTRIPLE image[height][width]){
	RGBTRIPLE tmp_image[height][width];
	for (int i = 0; i < height; i ++){
		for (int j = 0; j < width; j ++){
			tmp_image[i][j] = image[i][j];
		}
	}

	int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
	int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
	for (int i = 0; i < height; i ++){
		for (int j = 0; j < width; j ++){
			float GxRed = 0.0, GxGreen = 0.0, GxBlue = 0.0;
			float GyRed = 0.0, GyGreen = 0.0, GyBlue = 0.0;
			for (int di = -1; di <= 1; di ++){
				for (int dj = -1; dj <= 1; dj ++){
					if (i + di < 0 || i + di >= height) continue;
					if (j + dj < 0 || j + dj >= width)  continue;

					GxRed   += Gx[di + 1][dj + 1] * tmp_image[i + di][j + dj].rgbtRed;
					GxGreen += Gx[di + 1][dj + 1] * tmp_image[i + di][j + dj].rgbtGreen;
					GxBlue  += Gx[di + 1][dj + 1] * tmp_image[i + di][j + dj].rgbtBlue;
					GyRed   += Gy[di + 1][dj + 1] * tmp_image[i + di][j + dj].rgbtRed;
					GyGreen += Gy[di + 1][dj + 1] * tmp_image[i + di][j + dj].rgbtGreen;
					GyBlue  += Gy[di + 1][dj + 1] * tmp_image[i + di][j + dj].rgbtBlue;
				}
			}

			image[i][j].rgbtRed   = min(255, round(sqrt(GxRed   * GxRed   + GyRed   * GyRed)));
			image[i][j].rgbtGreen = min(255, round(sqrt(GxGreen * GxGreen + GyGreen * GyGreen)));
			image[i][j].rgbtBlue  = min(255, round(sqrt(GxBlue  * GxBlue  + GyBlue  * GyBlue)));
		}
	}
	return;
}
