void Command() {

  FONA('r');            //tell fona to check for new message
 
  //Serial2.write(1);     //tell fona to check messaage 1

  if (ValidMessage = 0) {
    return;                         //if no message was received, leave function and continue operation
  }

  //at this point, we know we've received a message.
  ComRcv = String(IncCommand);        //copy our incomming command character array to string.
  int i;
    for(i = 0; i < sizeof(IncCommand)-1; i++){

    IncCommand[i] = 0;
    }

  Serial.println("Command Received: ");
  Serial.print(ComRcv);

  ComRcv.toUpperCase();            //change our incoming command to all caps to ease string comparison.

  Serial.println("Command converted to ALL CAPS: ");
  Serial.print(ComRcv);


  if (ComRcv.startsWith("STATUS") ) {
    Serial.println("Command Received: STATUS REQUEST");
    FONA('s');
  }

  else if (ComRcv.startsWith("CHANGE WPC")) {
    Serial.println("Command Received: CHANGE WAY POINT COUNTER");
    WPCount = ComRcv.charAt(12);
    FONA('w');
  }

  else if (ComRcv.startsWith("HALT")) {
    Serial.println("Command Received: HALT, send any other command to resume.");
    FONA('h');
    
      THRT = 90; //STOP all motor movement.  We are waiting.
      Throttle.write(THRT); //send command to set throttle
      pos = 90; //set steering to dead ahead.
      Rudder.write(pos);  //send command to steering

      HALT=1;
      Serial.println(HALT);

  }

  else if (ComRcv.startsWith("RESUME")) {
    Serial.println("Command Received: RESUME");
    FONA('R');
    FONA('d');
    HALT=0;
    Serial.println(HALT);
    return;

  }

  else if (ComRcv.startsWith("DEMO")) {
    Serial.println("Command Received: DEMONSTRATION");
    FONA('D');
    FONA('d');
  
  }

  /*Changing the Latitude and Longitude with different waypoint #*/
  else if (ComRcv.startsWith("CHANGE LL")) {
    Serial.println("Command Received: UPDATE A WAYPOINT'S LAT/LONG");
    FONA('l');
  }

  /*Changing the craft to follow a heading vs to a waypoint*/
  else if (ComRcv.startsWith("HEADING MODE ON"))
  {
    Serial.println("Command Received: HEADING MODE ON");
    FONA('H');
  }

  /*Changing the craft to follow a waypoint vs folling a heading*/
  else if (ComRcv.startsWith("HEADING MODE OFF"))
  {
    Serial.println("Command Received: HEADING MODE OFF");
    FONA('m');
  }

  /*Requesting a list of waypoints */
  else if (ComRcv.startsWith("PRINT WP"))
  {
    Serial.println("Command Received: LIST WAYPOINTS");
    FONA('p');
  }


  //delete sms
  FONA('d');
  ComRcv = "";
  Serial.println("Incoming Command Variable Cleared");
  Serial.println(ComRcv);

}

