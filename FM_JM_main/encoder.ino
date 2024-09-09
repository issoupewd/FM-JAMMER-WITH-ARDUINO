// Button press handling function
void pressHandler(BfButton *KyBtn, BfButton::press_pattern_t pattern) {
  switch (pattern) {
    case BfButton::SINGLE_PRESS:
      // change jamming
      presbandcahn += 1;
      if (presbandcahn > 2) {
        presbandcahn = 1;
      }
      break;

    case BfButton::DOUBLE_PRESS:
      // start teh sys
      turnon += 1;
      if (turnon > 2) {
        turnon = 1;
      }
      break;
    case BfButton::LONG_PRESS:
      prs += 1;
      if (prs > 2) {
        prs = 1;
      }
  }

  oledfreq();
}

// Encoder handling function
void handleEncoder() {
  // Read the current state of KyCLK
  currentStateCLK = digitalRead(KyCLK);

  // If the previous and the current state of the KyCLK are different then a pulse has occurred
  if (currentStateCLK != previousStateCLK) {

    // counterclockwise
    if (digitalRead(kyDT) != currentStateCLK) {
      // Adjust frequency
      stationNum += 1;
      if (prs == 1) {
        frequency += 10;  // by 0.1 MHz
      } else {
        frequency += 100;  //  by 1 MHz
      }

      if (frequency > MAX_FREQ) {
        frequency = MIN_FREQ;  //to min frequency if above max frequency
      }
      if (stationNum > 12) {
        stationNum = 0;  //to min station if above max stationNum
      }


    } else {  //clockwise
      // Adjust frequency
      stationNum -= 1;
      if (prs == 1) {
        frequency -= 10;  // by 0.1 MHz
      } else {
        frequency -= 100;  //  by 1 MHz
      }
      if (frequency < MIN_FREQ) {
        frequency = MAX_FREQ;  //  to max frequency if below min frequency
      }
      if (stationNum < 0) {
        stationNum = 12;  //  to max station if below 0
      }
    }
    if (presbandcahn == 1) {
      oledfreq();
      onechannel();
      firsttime = false;
    } else if (presbandcahn == 2) {
      oledall();
      allband();
    }
  }

  // Update previousStateCLK
  previousStateCLK = currentStateCLK;
}