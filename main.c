#include <stdio.h>
#include "./src1/f1.h"
#include "./src2/f2.h"
#include "./src2/subsrc1/f3.h"
#include "./src3/subsrc2/f4.h"

#include "./plot/pbPlots.h"
#include "./plot/supportLib.h"

int pbPlot(double xs[], double ys[], int size);
float motorPower_PowerSLine(float len, float FStart, float FStop, float flexible, int index);

float result = 0.0f;
float len = 100.0f;
float FStart = 0.0f;
float FStop = 10.0f;
float flexible = 10;
int index_size = 100;

void main(void)
{
    double speed[index_size];
    double time[index_size];
    float timestep = 0.1f;
    for (int i = 0; i < index_size; i++)
    {
        speed[i] = (double)motorPower_PowerSLine(len, FStart, FStop, flexible, i);
        time[i] = i * timestep;
        //printf("%f %f\n", time[i], speed[i]);
    }
    pbPlot(time, speed, index_size);
    printf("Run finished\n");
}

float motorPower_PowerSLine(float len, float FStart, float FStop, float flexible, int index)
{
    float deno;
    float melo;
    float num;
    float Fcurrent;

    if (index > len)
        index = len;
    num = len / 2;
    melo = flexible * (index - num) / num;
    deno = 1.0 / (1 + exp(-melo));
    Fcurrent = FStart - (FStart - FStop) * deno;

    return Fcurrent;
}

int pbPlot(double xs[], double ys[], int size)
{
    _Bool success;

    //int x_size = (sizeof(xs)/sizeof(xs[0]));

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    StringReference *errorMessage = CreateStringReference(L"", 0);
    success = DrawScatterPlot(canvasReference, 1200, 800, xs, size, ys, size, errorMessage);

    if (success)
    {
        size_t length;
        double *pngdata = ConvertToPNG(&length, canvasReference->image);
        WriteToFile(pngdata, length, "example1.png");
        DeleteImage(canvasReference->image);
    }
    else
    {
        fprintf(stderr, "Error: ");
        for (int i = 0; i < errorMessage->stringLength; i++)
        {
            fprintf(stderr, "%c", errorMessage->string[i]);
        }
        fprintf(stderr, "\n");
    }

    FreeAllocations();

    return success ? 0 : 1;
}
