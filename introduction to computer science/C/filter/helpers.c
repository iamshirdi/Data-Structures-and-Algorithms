#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    //avg and assign for magnitude
    float gray;

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            gray = (float) image[j][i].rgbtBlue + image[j][i].rgbtGreen + image[j][i].rgbtRed;
            gray = round (gray /3);
            image[j][i].rgbtBlue = gray;
            image[j][i].rgbtGreen = gray;
            image[j][i].rgbtRed = gray;
        }
    }
}


// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int swap[3];
    for (int i = 0; i < height; i++)
    {

        for (int j = 0; j < width / 2; j++)
        {
            swap[0] = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - j -1].rgbtBlue;
            image[i][width - j -1].rgbtBlue = swap[0];

            swap[1] = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - j -1].rgbtGreen;
            image[i][width - j -1].rgbtGreen = swap[1];

            swap[2] = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - j -1].rgbtRed;
            image[i][width - j -1].rgbtRed = swap[2];

        }
    }
}



// Blur image


void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int Blue;
    int Green;
    int Red;
    // for implicit conversion
    float counter;
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            Blue = 0;
            Green = 0;
            Red = 0;
            counter = 0.00;


            for (int k = -1; k < 2; k++)
            {
                for (int h = -1; h < 2; h++)
                {
                    if (i + k < 0 || i + k >= height )
                    {
                        continue;
                    }
                    if (j + h < 0 || j + h >= width )
                    {
                        continue;
                    }

                    Blue += temp[i + k][j + h].rgbtBlue;
                    Green += temp[i + k][j + h].rgbtGreen;
                    Red += temp[i + k][j + h].rgbtRed;
                    counter++;
                }
            }
            // average
            image[i][j].rgbtBlue = round(Blue / counter);
            image[i][j].rgbtGreen = round(Green / counter);
            image[i][j].rgbtRed = round(Red / counter);
        }

    }
    return;
}


int overflow(int RGB)
{
    if (RGB > 255)
    {
        RGB = 255;
    }
    return RGB;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
     // Initialise Sobel arrays and temp for not changing orignal values
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }

    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            float gxblue = 0;
            float gxgreen = 0;
            float gxred = 0;
            float gyblue = 0;
            float gygreen = 0;
            float gyred = 0;



            for (int k = -1; k < 2; k++)
            {

                for (int l = -1; l < 2; l++)
                {
                    //skip edge black too so >=heiight,width
                     if (i + k < 0 || i + k >= height )
                    {
                        continue;
                    }
                        if (j + l < 0 || j + l >= width )
                    {
                        continue;
                    }
                    gxred += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    gxgreen += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    gxblue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    gyred += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    gygreen += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    gyblue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];

                }
            }
            //changes original image for further caluclations naeihbours
            image[i][j].rgbtRed =overflow(round(sqrt(gxred * gxred + gyred * gyred)));
            image[i][j].rgbtGreen = overflow(round(sqrt(gxgreen * gxgreen + gygreen * gygreen)));
            image[i][j].rgbtBlue = overflow(round(sqrt(gxblue*gxblue + gyblue * gyblue)));

        }
    }


}
