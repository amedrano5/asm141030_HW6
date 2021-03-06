//Antonio Medrano
//SE3377.502
//Program6

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <stdint.h>

#define MAT_W 3
#define MAT_H 5
#define BOX_WIDTH 15
#define MATRIX_NAME_STRING "Binary Matrix"

using namespace std;
class BinaryFileHeader{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};
const int maxRecordStrLen = 25;

class BinaryFileRecord{
public:
  uint8_t strLen;
  char stringBuff[maxRecordStrLen];
};

int main()
{

  WINDOW        *window;
  CDKSCREEN 	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

   // Finally... make sure your arrays have enough entries given the
  // values you choose to set for MATRIX_WIDTH and MATRIX_HEIGHT
  // above.

  const char 		*rowTitles[] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[] = {"C0", "C1", "C2", "C3", "C4", "C5"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MAT_H, MAT_W, MAT_H, MAT_W,MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths, boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix == NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  
  BinaryFileHeader *binHeader = new BinaryFileHeader();
  //  BinaryFileRecord *binRecord = new BinaryFileRecord();

  ifstream binFile("cs3377.bin", ios::in | ios::binary);

  binFile.read((char*) binHeader, sizeof(BinaryFileHeader));

  setCDKMatrixCell(myMatrix, 1, 1,"Magic: " );
  setCDKMatrixCell(myMatrix, 1, 2,"Version: " );
  setCDKMatrixCell(myMatrix, 1, 3,"NumRecords: ");


  drawCDKMatrix(myMatrix, true);    /* required  */
  binFile.close();
  /* So we can see results, pause until a key is pressed. */
  unsigned char x;
  cin >> x;

  // Cleanup screen
  endCDK();
}
