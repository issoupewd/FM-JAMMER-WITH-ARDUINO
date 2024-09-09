void firstall() {
  if (firsttime == false) {
    radio.tuneFM(stations[stationNum]);
    oledall();
    firsttime = true;
  }
}

void allband() {
  // stationNum = map(frequency, 88, 108, 0, 12);
  radio.tuneFM(stations[stationNum]);
}

void onechannel() {

  radio.tuneFM(frequency);
}
/*
for (int stationNum = 0; stationNum <= 12; stationNum++) {
    radio.tuneFM(stations[stationNum]); 
    delay(100);
}
*/