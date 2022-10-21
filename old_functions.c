/*

// Show a solved rubiks cube
void showRubiksSolved(long delayTime)
{  	
			
leds[0]=sColour[		GREEN	];
leds[4]=sColour[		GREEN	];
leds[8]=sColour[		GREEN	];
leds[9]=sColour[		GREEN	];
leds[13]=sColour[		GREEN	];
leds[17]=sColour[		GREEN	];
leds[18]=sColour[		GREEN	];
leds[22]=sColour[		GREEN	];
leds[26]=sColour[		GREEN	];

leds[27]=sColour[		RED	];
leds[28]=sColour[		RED	];
leds[29]=sColour[		RED	];
leds[33]=sColour[		RED	];
leds[37]=sColour[		RED	];
leds[38]=sColour[		RED	];
leds[42]=sColour[		RED	];
leds[46]=sColour[		RED	];
			
leds[47]=sColour[		BLUE	];
leds[51]=sColour[		BLUE	];
leds[55]=sColour[		BLUE	];
leds[56]=sColour[		BLUE	];
leds[60]=sColour[		BLUE	];
leds[64]=sColour[		BLUE	];
leds[65]=sColour[		BLUE	];
leds[69]=sColour[		BLUE	];
leds[73]=sColour[		BLUE	];
			
			
leds[74]=sColour[		ORANGE	];
leds[75]=sColour[		ORANGE	];
leds[76]=sColour[		ORANGE	];
leds[80]=sColour[		ORANGE	];
leds[84]=sColour[		ORANGE	];
leds[85]=sColour[		ORANGE	];
leds[89]=sColour[		ORANGE	];
leds[93]=sColour[		ORANGE	];

    // int NumSides = 6;
    // int NumPieces = 9;
    // for (int i = 0; i < NumSides; ++i) { // loop through all 6 sides
    //     for (int j = 0; j < NumPieces; ++j) { // loop through all 9 pieces on each side
    //         leds[i*9 + j] = sColour[i]; // set the colout of all pieces to the colour of that side
    //     }
    // }
  FastLED.show();
  delay(delayTime);
}

// Show a shuffled rubiks cube.
void showRubiksShuffled(int choice, long delayTime)
{
 choice = choice % 4;
 switch(choice) {
  case 0:

 leds[0]=sColour[		YELLOW	];
 leds[4]=sColour[		GREEN	];
leds[8]=sColour[		ORANGE	];
leds[9]=sColour[		GREEN	];
leds[13]=sColour[		GREEN	];
leds[17]=sColour[		RED	];
leds[18]=sColour[		BLUE	];
leds[22]=sColour[		BLUE	];
leds[26]=sColour[		YELLOW	];

leds[27]=sColour[		GREEN	];
leds[28]=sColour[		WHITE	];
leds[29]=sColour[		YELLOW	];
leds[33]=sColour[		RED	];
leds[37]=sColour[		RED	];
leds[38]=sColour[		ORANGE	];
leds[42]=sColour[		RED	];
leds[46]=sColour[		WHITE	];

leds[47]=sColour[		ORANGE	];
leds[51]=sColour[		GREEN	];
leds[55]=sColour[		WHITE	];
leds[56]=sColour[		WHITE	];
leds[60]=sColour[		YELLOW	];
leds[64]=sColour[		BLUE	];
leds[65]=sColour[		YELLOW	];
leds[69]=sColour[		BLUE	];
leds[73]=sColour[		BLUE	];

leds[74]=sColour[		YELLOW	];
leds[75]=sColour[		WHITE	];
leds[76]=sColour[		ORANGE	];
leds[80]=sColour[		ORANGE	];
leds[84]=sColour[		BLUE	];
leds[85]=sColour[		GREEN	];
leds[89]=sColour[		YELLOW	];
leds[93]=sColour[		WHITE	];

    break;
  case 1:
    leds[0]=sColour[	ORANGE	];
 leds[1]=sColour[	RED	];
 leds[2]=sColour[	YELLOW	];
 leds[3]=sColour[	RED	];
 leds[4]=sColour[	GREEN	];
 leds[5]=sColour[	RED	];
 leds[6]=sColour[	ORANGE	];
 leds[7]=sColour[	WHITE	];
 leds[8]=sColour[	ORANGE	];
 leds[9]=sColour[	GREEN	];
leds[10]=sColour[	WHITE	];
leds[11]=sColour[	RED	];
leds[12]=sColour[	BLUE	];
leds[13]=sColour[	RED	];
leds[14]=sColour[	ORANGE	];
leds[15]=sColour[	BLUE	];
leds[16]=sColour[	YELLOW	];
leds[17]=sColour[	YELLOW	];
leds[18]=sColour[	GREEN	];
leds[19]=sColour[	YELLOW	];
leds[20]=sColour[	RED	];
leds[21]=sColour[	GREEN	];
leds[22]=sColour[	BLUE	];
leds[23]=sColour[	WHITE	];
leds[24]=sColour[	RED	];
leds[25]=sColour[	GREEN	];
leds[26]=sColour[	RED	];
leds[27]=sColour[	WHITE	];
leds[28]=sColour[	GREEN	];
leds[29]=sColour[	BLUE	];
leds[30]=sColour[	WHITE	];
leds[31]=sColour[	ORANGE	];
leds[32]=sColour[	ORANGE	];
leds[33]=sColour[	WHITE	];
leds[34]=sColour[	BLUE	];
leds[35]=sColour[	YELLOW	];
leds[36]=sColour[	GREEN	];
leds[37]=sColour[	BLUE	];
leds[38]=sColour[	YELLOW	];
leds[39]=sColour[	GREEN	];
leds[40]=sColour[	WHITE	];
leds[41]=sColour[	YELLOW	];
leds[42]=sColour[	ORANGE	];
leds[43]=sColour[	BLUE	];
leds[44]=sColour[	WHITE	];
leds[45]=sColour[	GREEN	];
leds[46]=sColour[	YELLOW	];
leds[47]=sColour[	WHITE	];
leds[48]=sColour[	ORANGE	];
leds[49]=sColour[	YELLOW	];
leds[50]=sColour[	ORANGE	];
leds[51]=sColour[	BLUE	];
leds[52]=sColour[	RED	];
leds[53]=sColour[	BLUE	];
    break;
  case 2:
 leds[0]=sColour[	WHITE	];
 leds[1]=sColour[	WHITE	];
 leds[2]=sColour[	BLUE	];
 leds[3]=sColour[	RED	];
 leds[4]=sColour[	GREEN	];
 leds[5]=sColour[	BLUE	];
 leds[6]=sColour[	YELLOW	];
 leds[7]=sColour[	ORANGE	];
 leds[8]=sColour[	YELLOW	];
 leds[9]=sColour[	WHITE	];
leds[10]=sColour[	YELLOW	];
leds[11]=sColour[	RED	];
leds[12]=sColour[	RED	];
leds[13]=sColour[	RED	];
leds[14]=sColour[	YELLOW	];
leds[15]=sColour[	BLUE	];
leds[16]=sColour[	ORANGE	];
leds[17]=sColour[	ORANGE	];
leds[18]=sColour[	YELLOW	];
leds[19]=sColour[	WHITE	];
leds[20]=sColour[	GREEN	];
leds[21]=sColour[	BLUE	];
leds[22]=sColour[	BLUE	];
leds[23]=sColour[	WHITE	];
leds[24]=sColour[	WHITE	];
leds[25]=sColour[	GREEN	];
leds[26]=sColour[	RED	];
leds[27]=sColour[	YELLOW	];
leds[28]=sColour[	BLUE	];
leds[29]=sColour[	ORANGE	];
leds[30]=sColour[	YELLOW	];
leds[31]=sColour[	ORANGE	];
leds[32]=sColour[	WHITE	];
leds[33]=sColour[	GREEN	];
leds[34]=sColour[	RED	];
leds[35]=sColour[	GREEN	];
leds[36]=sColour[	RED	];
leds[37]=sColour[	GREEN	];
leds[38]=sColour[	BLUE	];
leds[39]=sColour[	GREEN	];
leds[40]=sColour[	WHITE	];
leds[41]=sColour[	ORANGE	];
leds[42]=sColour[	BLUE	];
leds[43]=sColour[	ORANGE	];
leds[44]=sColour[	RED	];
leds[45]=sColour[	ORANGE	];
leds[46]=sColour[	GREEN	];
leds[47]=sColour[	ORANGE	];
leds[48]=sColour[	YELLOW	];
leds[49]=sColour[	YELLOW	];
leds[50]=sColour[	BLUE	];
leds[51]=sColour[	WHITE	];
leds[52]=sColour[	RED	];
leds[53]=sColour[	GREEN	];
    break;
  case 3:
   leds[0]=sColour[	YELLOW	];
 leds[1]=sColour[	RED	];
 leds[2]=sColour[	GREEN	];
leds[3]=sColour[	BLUE	];
leds[4]=sColour[	GREEN	];
leds[5]=sColour[	YELLOW	];
leds[6]=sColour[	GREEN	];
leds[7]=sColour[	BLUE	];
leds[8]=sColour[	YELLOW	];
leds[9]=sColour[	WHITE	];
leds[10]=sColour[	RED	];
leds[11]=sColour[	BLUE	];
leds[12]=sColour[	WHITE	];
leds[13]=sColour[	RED	];
leds[14]=sColour[	YELLOW	];
leds[15]=sColour[	BLUE	];
leds[16]=sColour[	WHITE	];
leds[17]=sColour[	YELLOW	];
leds[18]=sColour[	WHITE	];
leds[19]=sColour[	WHITE	];
leds[20]=sColour[	WHITE	];
leds[21]=sColour[	RED	];
leds[22]=sColour[	BLUE	];
leds[23]=sColour[	RED	];
leds[24]=sColour[	RED	];
leds[25]=sColour[	ORANGE	];
leds[26]=sColour[	BLUE	];
leds[27]=sColour[	GREEN	];
leds[28]=sColour[	GREEN	];
leds[29]=sColour[	GREEN	];
leds[30]=sColour[	GREEN	];
leds[31]=sColour[	ORANGE	];
leds[32]=sColour[	BLUE	];
leds[33]=sColour[	WHITE	];
leds[34]=sColour[	WHITE	];
leds[35]=sColour[	ORANGE	];
leds[36]=sColour[	RED	];
leds[37]=sColour[	BLUE	];
leds[38]=sColour[	RED	];
leds[39]=sColour[	YELLOW	];
leds[40]=sColour[	WHITE	];
leds[41]=sColour[	ORANGE	];
leds[42]=sColour[	RED	];
leds[43]=sColour[	GREEN	];
leds[44]=sColour[	ORANGE	];
leds[45]=sColour[	YELLOW	];
leds[46]=sColour[	ORANGE	];
leds[47]=sColour[	ORANGE	];
leds[48]=sColour[	GREEN	];
leds[49]=sColour[	YELLOW	];
leds[50]=sColour[	ORANGE	];
leds[51]=sColour[	ORANGE	];
leds[52]=sColour[	YELLOW	];
leds[53]=sColour[	BLUE	];

    break;
  case 4:
    break;
  default:
    break;
  }
  FastLED.show();
  delay(delayTime);
}

// switches on all LEDs. Each LED is shown in random color.
// numIterations: indicates how often LEDs are switched on in random colors
// delayTime: indicates for how long LEDs are switched on.
void showProgramRandom(int numIterations, long delayTime) {
  for (int iteration = 0; iteration < numIterations; ++iteration) {
    for (int i = 0; i < NUM_LEDS; ++i) {
      leds[i] = CHSV(random8(),255,255); // hue, saturation, value
    }
    FastLED.show();
    delay(delayTime);
  }
}


// initialize the square colours to black - no light.
void initSquareColours()
{
  // initialize the square colours
  for(int i=0; i<NUM_SQUARES; i++)
   {
    SquareColours[i] = CRGB::Black;
   }
}
*/