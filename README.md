# Speeduino-Copilot

This project is intended as a Teensy co-processor for the purposes of securing ECU logs from a Speeduino ECU. The intent is that the Teensy Serial1 is connected to the Speeduino SecondarySerial, and it will retrieve real-time data, and write the MGVLG (megalogviewer) format logfile onto the Teensy onboard SD card.
# Future

Although largely functional, this is not currently fully completed. Not all real time variables are made available. It's also possible that we could include faciltiies for a GPS/RTC module, to make the output more useful.

# Behaviour
By default, on boot, the code will create rolling logfiles of filename "test_0000.mlg", and will increment the filename every 1000KB. Existing files will be overwritten. In due course, it's likely that it should have a second counter and not overwrite the same file sequence.

# Contributors
Contributations welcome
