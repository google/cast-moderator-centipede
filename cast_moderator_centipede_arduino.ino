/* Copyright 2022 Google LLC
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
*      http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License. */
 
#include <Keyboard.h>
#include <EEPROM.h> //Library used to write to certain boards to remember the setup
 
 
/*
https://youtu.be/mqOyv3sQdOw
Pairing the remote is a first step. When bulk setting up a single
remote can be used and the packaged remotes paired later in the
classroom using the Chromecast button long press to pair.
 
After pairing the language select screen will appear.
The Arduino code below can be run at this point.
*/
 
#define wifi_name "" // Define SSID for your wireless connection.
#define wifi_pass "" // Define the password for your wireless connection.
#define account_name "" // Define Google Workspace username without numerical suffix.
#define domain "" //Define the domain name to be combined with the username and suffix.
#define account_pass "" // Define Google Workspace account password used to connect for casting.

/*
If the language of setup is not English select the
position of the language on a 0 index
*/
int languagepos = 0;

/**
* Sets the position of the Security selection for the network
*/
int security_type = 0; //0 for none, 1 for WEP, 2 for WPA/WPA2-Personal
 
/**
* Navigates to the Manual entry of network.
*/
int wifipos = 20;  //20 down clicks. Click and enter manually

/**
* Address 0-255 to write the count of use.
*/
int address = 0;

/**
* Value of the count used to calculate the suffix
*/
int value = 0;

/**
* The integer to start the suffix from.
*/
int startSuffix = 0;

/**
* The integer to end account setup with. 
*/
int endSuffix = -1;

/**
* Suffix of the Google account to be used with Cast Moderator
* Suffix increments by 1 for every 90 runs on the device.
*/
int suffix = 0; //Do not change.


/**
* The setup function runs once when you press the reset button on the
* Arduino or power-on the Arduino
*
* @return {void}
*/
 
void setup() {
 //clear_memory(); //uncomment and comment out the below lines to clear the memory.
 Keyboard.begin();  //begin the keyboard.
 wait(10);          //Provide a buffer to cancel by removing the arduino
 setSuffix();        //Set the suffice for the Google Account
 if(endSuffix>-1 && suffix>=endSuffix){
  return; //Cancel setup due to account suffix surpassing the end limit. 
 }
 start();           //Run the Chromecast setup
}
 
/**
* The start function runs each step of the setup process with waits for UI
* rendering between. Timing can be adjusted here. Going too fast will
* result in setup failures and a requirement to factory reset or complete
* manually.
* @return {void}
*/
void start() {
 selectLanguage();  //selects the language at the languagepos index assigned above
 wait(1);           //waiting 1 second to allow UI to render
 setupOnTv();       //Select setup to be on the TV
 wait(1);           //waiting 1 second to allow UI to render
 wifi();            //Select WiFi and enter credentials
 wait(60);          //Connecting. If your network is potentially slower increase this wait to accommodate
 wait(900);          //Wait for the Update. May need to be adjusted for slower networks.
 konami();          //Enters the unique setup code
 wait(3);           //waiting 3 second to allow UI to render
 optIn();           //selects the OptIn dialogs. Please ensure manual review before proceeding.
 wait(8);           //waiting 8 second to allow UI to render
 googleAccount();   //Enters the Google account credentials for Cast Moderator
 wait(8);           //waiting 8 second to allow UI to render
 legalAccepts();    //Accepts the legal notifications. Please ensure manual review before proceeding.
 wait(5);           //waiting 5 second to allow UI to render
 googleServices();  //accepts or deselects the the Google Services. Please ensure manual review before proceeding.
 wait(5);           //waiting 1 second to allow UI to render
 noRemoteSetup();   //Select No Remote setup for audio controls. Audio controls can be setup in room later.
}
 
/**
* No loop required for this functionality.
* Advanced users can assign a pin to a button
* for use in triggering the start function.
*/
void loop() {
}

/**
* Set the suffix number for the Google account.
* @return {void}
*/
void setSuffix(){
  value = EEPROM.read(address);
  EEPROM.write(address, value+1);
  suffix=floor(value/90)+startSuffix;
}
 
/**
* Select the Language
* @return {void}
*/
void selectLanguage() {
 if (languagepos > 0) {
   for (int i = 0; i <= languagepos; i++) {
     Keyboard.write(KEY_DOWN_ARROW);
     wait(1);
   }
 }
 Keyboard.write(KEY_RETURN);
}
 
/**
* Skip the Google Home setup as it does not allow the setup
* for Cast Moderator.
* Select Setup on TV
* @return {void}
*/
void setupOnTv() {
 wait(1);
 Keyboard.write(KEY_DOWN_ARROW);
 wait(1);
 Keyboard.write(KEY_RETURN);
 wait(5);
}
 
/**
* Set the WiFi credentials
* @return {void}
*/
void wifi() {
 if (wifipos > 0) {
   for (int i = 0; i <= wifipos; i++) {
     Keyboard.write(KEY_DOWN_ARROW);
   }
 }
 Keyboard.write(KEY_RETURN);
 wait(1);
 Keyboard.print(wifi_name);
 Keyboard.write(KEY_RETURN);
 wait(1);
 if(security_type>0){
   for (int i = 0; i <= security_type; i++) {
     Keyboard.write(KEY_DOWN_ARROW);
     wait(1);
   }
 }
 Keyboard.write(KEY_RETURN);
 wait(1);
 Keyboard.print(wifi_pass);
 Keyboard.write(KEY_RETURN);
}
 
/**
* Execute the konami code to get access to Cast Moderator
* @return {void}
*/
void konami() {
 Keyboard.write(KEY_ESC);  //Closes the keyboard
 wait(1);                  //Waiting 1 second to allow UI to render
 back();                   //Returns to the wifi for special code entry
 wait(5);                  //waiting 5 second to allow UI to render
 for (int i = 0; i < 7; i++) {
   Keyboard.write(KEY_UP_ARROW);
 }
}
 
/**
* Agree to Cast Moderator selections and reminders
* @return {void}
*/
void optIn() {
 wait(1);
 Keyboard.write(KEY_RETURN);  //Using Cast Moderator
 wait(3);
 Keyboard.write(KEY_RETURN);  //Organization Access
 wait(1);
 Keyboard.write(KEY_RETURN);  //Setup
 wait(1);
 Keyboard.write(KEY_RETURN);  //Device Isn't Private
 wait(1);
 Keyboard.write(KEY_RETURN);  //Cast Moderator is set up
}
 
/**
* Enter the Google Account credentials
* @return {void}
*/
void googleAccount() {
 Keyboard.print(account_name);
 Keyboard.print(suffix);
 Keyboard.print('@');
 Keyboard.print(domain);
 Keyboard.write(KEY_RETURN);
 wait(5);
 Keyboard.print(account_pass);
 Keyboard.write(KEY_RETURN);
}
 
/**
* Accept Terms of Service and Additional Legal
* @return {void}
*/
void legalAccepts() {
 Keyboard.write(KEY_RETURN);  //Accept TOS
 wait(3);
 Keyboard.write(KEY_RETURN);  //Accept Additional Legal Terms
}
 
/**
* Deselect or accept Google Services.
* @return {void}
*/
void googleServices() {
 wait(2);
 Keyboard.write(KEY_RETURN);
}
 
/**
* Skip the the Audio setup with the remote. This can be completed later.
* @return {void}
*/
void noRemoteSetup() {
 Keyboard.write(KEY_RIGHT_ARROW);
 wait(1);
 Keyboard.write(KEY_RIGHT_ARROW);
 wait(1);
 Keyboard.write(KEY_RETURN);
}
 
/**
* Wait in integer seconds
* @param {integer}
* @return {void}
*/
void wait(int seconds = 1);
void wait(int seconds) {
 for (int i = 0; i < seconds; i++) {
   blink();
 }
}
 
/**
* Back key signal
* @return {void}
*/
void back() {
 Keyboard.press(KEY_LEFT_GUI);
 delay(200);
 Keyboard.write(KEY_BACKSPACE);
 wait(1);
 Keyboard.releaseAll();
}
 
/**
* LED Blink
* @return {void}
*/
void blink() {
 digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on
 delay(500);                       // wait for half a second
 digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
 delay(500);                       // wait for half a second
}
/**
* Clears the board momory
* @return {void}
*/

void clear_memory(){
  for (int i = 0 ; i < EEPROM.length() ; i++) {
    EEPROM.write(i, 0);
  }
}