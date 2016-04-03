#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information, as described below

int numRuns = 1;   // Execution count, so this doesn't run forever
int maxRuns = 10;   // Maximum number of times the Choreo should be executed

void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();
}

void loop() {
  if (numRuns <= maxRuns) {
    Serial.println("Running MakeCall - Run #" + String(numRuns++));
    
    TembooChoreo MakeCallChoreo;

    // Invoke the Temboo client
    MakeCallChoreo.begin();

    // Set Temboo account credentials
    MakeCallChoreo.setAccountName(TEMBOO_ACCOUNT);
    MakeCallChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
    MakeCallChoreo.setAppKey(TEMBOO_APP_KEY);
    
    // Set Choreo inputs
    MakeCallChoreo.addInput("ApplicationSID", "yourValueHere");
    MakeCallChoreo.addInput("AuthToken", "yourValueHere");
    MakeCallChoreo.addInput("From", "yourValueHere");
    MakeCallChoreo.addInput("AccountSID", "yourValueHere");
    
    // Identify the Choreo to run
    MakeCallChoreo.setChoreo("/Library/Twilio/Calls/MakeCall");
    
    // Run the Choreo; when results are available, print them to serial
    MakeCallChoreo.run();
    
    while(MakeCallChoreo.available()) {
      char c = MakeCallChoreo.read();
      Serial.print(c);
    }
    MakeCallChoreo.close();
  }

  Serial.println("Waiting...");
  delay(30000); // wait 30 seconds between MakeCall calls
}