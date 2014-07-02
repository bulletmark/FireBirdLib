#include                "../libFireBird.h"

//Greyscale for background
int sbBackground[15][3] =
{
  {16, 16, 16},
  {16, 16, 16},
  {21, 21, 21},
  {26, 26, 26},
  {31, 31, 31},
  {37, 37, 37},
  {43, 43, 43},
  {50, 50, 50},
  {56, 56, 56},
  {63, 63, 63},
  {70, 70, 70},
  {77, 77, 77},
  {84, 84, 84},
  {92, 92, 92},
  {118, 118, 118}
};

//Greyscale for the slider
int sbSlider[13][3] =
{
  {165, 165, 165},
  {149, 148, 149},
  {129, 129, 129},
  {108, 107, 108},
  {86, 85, 86},
  {65, 65, 65},
  {48, 47, 48},
  {35, 35, 36},
  {30, 30, 30},
  {31, 31, 31},
  {36, 36, 37},
  {45, 45, 45},
  {56, 56, 57}
};

//Greyscale for top border
int sbTopBorder[15][3] =
{
  {51, 51, 51},
  {122, 122, 122},
  {125, 125, 125},
  {127, 127, 127},
  {130, 130, 130},
  {134, 134, 134},
  {137, 137, 137},
  {141, 141, 141},
  {144, 144, 144},
  {148, 148, 148},
  {152, 152, 152},
  {156, 156, 156},
  {160, 160, 160},
  {164, 164, 164},
  {163, 163, 163}
};

//Greyscale for bottom border
int sbBotBorder[15][3] =
{
  {4, 4, 4},
  {4, 4, 4},
  {6, 6, 6},
  {7, 7, 7},
  {16, 16, 16},
  {10, 10, 10},
  {12, 12, 12},
  {14, 14, 14},
  {15, 15, 15},
  {17, 17, 17},
  {19, 19, 19},
  {21, 21, 21},
  {23, 23, 23},
  {25, 25, 25},
  {65, 65, 65}
};

dword   sbArrow = RGB(176, 177, 177);

//sbX & sbY     Top left coordinates
//sbHeight      Overall height of the scroll bar
//sbCurrent     Current "location" value
//sbWindow      The size of the entire range that the height of the slider represents.
//sbMax         Maximum "location" value.  Valid locations are zero to sbMax.

void DrawScrollbar(word sbRegion, int sbX, int sbY, int sbHeight, int sbCurrent, int sbWindow, int sbMax)
{
  TRACEENTER();

  if(sbWindow > sbMax) sbWindow = sbMax;

  int     i = 0;

  //Draw the background
  for(i = 0; i < 15; i++)
  {
    TAP_Osd_FillBox(sbRegion, sbX + i, sbY, 1, sbHeight, RGB(sbBackground[i][0], sbBackground[i][1], sbBackground[i][2]));
  }

  //Draw the top and bottom borders
  for(i = 0; i < 15; i++)
  {
    TAP_Osd_FillBox(sbRegion, sbX + i, sbY, 1, 1, RGB(sbTopBorder[i][0], sbTopBorder[i][1], sbTopBorder[i][2]));
    TAP_Osd_FillBox(sbRegion, sbX + i, sbY + sbHeight, 1, 1, RGB(sbBotBorder[i][0], sbBotBorder[i][1], sbBotBorder[i][2]));
  }

  //Draw the top arrow
  TAP_Osd_FillBox(sbRegion, sbX + 7, sbY + 2, 1, 1, sbArrow);
  TAP_Osd_FillBox(sbRegion, sbX + 6, sbY + 3, 3, 1, sbArrow);
  TAP_Osd_FillBox(sbRegion, sbX + 5, sbY + 4, 5, 1, sbArrow);
  TAP_Osd_FillBox(sbRegion, sbX + 4, sbY + 5, 7, 1, sbArrow);
  TAP_Osd_FillBox(sbRegion, sbX + 3, sbY + 6, 9, 1, sbArrow);

  //Draw the bottom arrow
  TAP_Osd_FillBox(sbRegion, sbX + 7, sbY + sbHeight - 2, 1, 1, sbArrow);
  TAP_Osd_FillBox(sbRegion, sbX + 6, sbY + sbHeight - 3, 3, 1, sbArrow);
  TAP_Osd_FillBox(sbRegion, sbX + 5, sbY + sbHeight - 4, 5, 1, sbArrow);
  TAP_Osd_FillBox(sbRegion, sbX + 4, sbY + sbHeight - 5, 7, 1, sbArrow);
  TAP_Osd_FillBox(sbRegion, sbX + 3, sbY + sbHeight - 6, 9, 1, sbArrow);

  //Draw the slider

  //The height of the slider is sbHeight * sbWindow / sbMax
  //The location of the slider is sbY + (sbHeight * sbCurrent / sbMax)

  for(i = 0; i < 13; i++)
  {
    TAP_Osd_FillBox(sbRegion, (sbX + 1 + i), sbY + ((sbHeight-26) * sbCurrent / sbMax) + 13, 1, ((sbHeight-26) * sbWindow / sbMax), RGB(sbSlider[i][0], sbSlider[i][1], sbSlider[i][2]));
  }

  TRACEEXIT();
}
