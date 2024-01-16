#include "helpers.h"
#include <stdio.h>
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            RGBTRIPLE pixel = image[i][j];
            int pixel_value = (pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3;
            image[i][j].rgbtBlue = pixel_value; 
            image[i][j].rgbtGreen = pixel_value;
            image[i][j].rgbtRed = pixel_value;
        }
    }
}
// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width]) {
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width/2; ++j) {
            RGBTRIPLE *pixel = &image[i][j];
            RGBTRIPLE *converse_pixel = &image[i][(width-1)-j];
            int red = pixel->rgbtRed;
            int green = pixel->rgbtGreen;
            int blue = pixel->rgbtBlue;

            pixel->rgbtRed = converse_pixel->rgbtRed;
            pixel->rgbtGreen = converse_pixel->rgbtGreen;
            pixel->rgbtBlue = converse_pixel->rgbtBlue;

            converse_pixel->rgbtRed = red;
            converse_pixel->rgbtGreen = green;
            converse_pixel->rgbtBlue = blue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            
            int counter = 0;
            int red_sum = 0;
            int green_sum = 0;
            int blue_sum = 0;
            for (int k = i - 1; (k < i + 2) && (k < height); ++k) {
                for (int l = j - 1; (l < j + 2) && (l < width); ++l) {
                    if ((k >= 0) && (l >= 0)) {
                        red_sum += image[k][l].rgbtRed;
                        green_sum += image[k][l].rgbtGreen;
                        blue_sum += image[k][l].rgbtBlue;
                        counter++;
                    } 
                }
            }
            image[i][j].rgbtRed = red_sum / counter;
            image[i][j].rgbtGreen = green_sum / counter;
            image[i][j].rgbtBlue = blue_sum / counter;
        }
    } 

    return;
}


void blur2(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blurred[height][width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {

            int counter = 0;
            int red_sum = 0;
            int green_sum = 0;
            int blue_sum = 0;
            for (int k = i - 1; (k < i + 2) && (k < height); ++k) {
                for (int l = j - 1; (l < j + 2) && (l < width); ++l) {
                    if ((k >= 0) && (l >= 0)) {
                        red_sum += image[k][l].rgbtRed;
                        green_sum += image[k][l].rgbtGreen;
                        blue_sum += image[k][l].rgbtBlue;
                        counter++;
                    } 
                }
            }
            blurred[i][j].rgbtRed = red_sum / counter;
            blurred[i][j].rgbtGreen = green_sum / counter;
            blurred[i][j].rgbtBlue = blue_sum / counter;
        }
    } 

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image[i][j].rgbtRed = blurred[i][j].rgbtRed;
            image[i][j].rgbtBlue = blurred[i][j].rgbtBlue;
            image[i][j].rgbtGreen = blurred[i][j].rgbtGreen;
        }
    }
    return;
}


int Gx[] = {0, 0, 0};
int Gy[] = {0, 0, 0};
// Detect edges

void calculate(RGBTRIPLE pixel, int arr[], int coefficient) 
{
    arr[0] += pixel.rgbtRed * coefficient;
    arr[1] += pixel.rgbtGreen * coefficient;
    arr[2] += pixel.rgbtBlue * coefficient;
}
//if you cahnge pixel immediateley every pixel becomes white dumbass
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE edged[height][width];
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            if (i > 0) {
                if (j > 0) {//square 1
                    calculate(image[i-1][j-1], Gx, -1);
                    calculate(image[i-1][j-1], Gy, -1);
                }
                calculate(image[i-1][j], Gy, -2);//2
                if (j + 1 < width) {//3
                    calculate(image[i-1][j+1], Gx, 1);
                    calculate(image[i-1][j+1], Gy, -1);
                }
            }    

            if (j > 0) {//4
                calculate(image[i][j-1], Gx, -2);
            }      
            if (j + 1 < width) {//6
                calculate(image[i][j+1], Gx, 2);
            }
            if (i + 1 < height) {
                if (j > 0) {//7
                    calculate(image[i][j-1], Gx, -1);
                    calculate(image[i][j-1], Gy, 1);
                }  
                calculate(image[i+1][j], Gy, 2);//8

                if (j + 1 < width) {
                    calculate(image[i+1][j+1], Gx, 1);//9
                    calculate(image[i+1][j+1], Gy, 1);
                }
            }
            
            edged[i][j].rgbtRed = round(sqrt(Gx[0] * Gx[0] + Gy[0] * Gy[0]));
            edged[i][j].rgbtGreen = round(sqrt(Gx[1] * Gx[1] + Gy[1] * Gy[1]));
            edged[i][j].rgbtBlue = round(sqrt(Gx[2] * Gx[2] + Gy[2] * Gy[2])); 

            Gx[0] = 0, Gx[1] = 0, Gx[2] = 0;
            Gy[0] = 0, Gy[1] = 0, Gy[2] = 0;
        }
    }
    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            image[i][j] = edged[i][j];
        }
    } 
}




