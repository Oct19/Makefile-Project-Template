#include <stdio.h>
#include "./src1/f1.h"
#include "./src2/f2.h"
#include "./src2/subsrc1/f3.h"
#include "./src3/subsrc2/f4.h"

#include "./plot/pbPlots.h"
#include "./plot/supportLib.h"

int pbPlot(void);

int main()
{
    printf("%d\n", f1(1, 2));
    printf("%d\n", f2(1, 2));
    printf("%d\n", f3(1, 2));
    printf("%d\n", f4(1, 2));

    pbPlot();
    return 0;
}

int pbPlot(void)
{
    double xs[] = {-2, -1, 0, 1, 2};
    double ys[] = {2, -1, -2, -1, 2};
    _Bool success;

    RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
    StringReference *errorMessage = CreateStringReference(L"", 0);
    success = DrawScatterPlot(canvasReference, 600, 400, xs, 5, ys, 5, errorMessage);

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
