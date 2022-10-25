#include <Keyboard.h>
#include <SPI.h>

/*
https://youtu.be/6VjhmbJWDeI
Pairing the remote is a first step. When bulk setting up a single 
remote can be used and the packagd remotes paired later in the 
classroom using the Chromecast button longpress to pair. 

After pairing the language select screen will appear. 
The Arduino code below can be run at this point. 
*/

#define wifi_name "" // Define SSID for your wireless connection.
#define wifi_pass "" // Define the password for your wireless connection.
#define account_name "" // Define Google Workspace account used to connect for casting.
#define account_pass "" // Define Google Workspace account password used to connect for casting.

/*
If the language of setup is not English select the 
position of the language on a 0 index
*/
int languagepos = 0;

/*
WiFi SSIDs are ordered by strength. A saturted network 
environment may be more difficult to target. Identify 
the SSID position based on a 0 index.
*/
int wifipos = 0;

/*
The setup function runs once when you press the reset button on the Arduino or power-on the Arduino
*/

void setup() {
  Keyboard.begin();  //begin the keyboard.
  wait(10);          //Provide a buffer to cancel by removing the arduino
  start();           //Run the Chromecast setup
}


void start() {
  selectLanguage();  //selects the language at the languagepos index assigned above
  wait(1);           //waiting 1 second to allow UI to render
  setupOnTv();       //Select setup to be on the TV
  wait(1);           //waiting 1 second to allow UI to render
  wifi();            //Select WiFi and enter credentials
  wait(60);          //Connecting. If your network is potentially slower increase this wait to accomodate
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

/*
No loop required for this functionality. 
Advanced users can assign a pin to a button 
for use in triggering the start function.
*/
void loop() {
}

/*
Select the Language
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

/*
Skip the Google Home setup as it does not allow the setup for Cast Moderator.
Select Setup on TV
*/
void setupOnTv() {
  wait(1);
  Keyboard.write(KEY_DOWN_ARROW);
  wait(1);
  Keyboard.write(KEY_RETURN);
  wait(5);
}

/*
Set the WiFi credentials
*/
void wifi() {
  if (wifipos > 0) {
    for (int i = 0; i <= wifipos; i++) {
      Keyboard.write(KEY_DOWN_ARROW);
      wait(1);
    }
  }
  Keyboard.write(KEY_RETURN);
  wait(1);
  Keyboard.print(wifi_pass);
  Keyboard.write(KEY_RETURN);
}

/*
Execute the konami code to get access to Cast Moderator
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

/*
Agree to Cast Moderator seelctions and reminders
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

/*
Enter the Google Account credentials 
*/
void googleAccount() {
  Keyboard.print(account_name);
  Keyboard.write(KEY_RETURN);
  wait(5);
  Keyboard.print(account_pass);
  Keyboard.write(KEY_RETURN);
}

/*
Accept Terms of Service and Additional Legal 
*/
void legalAccepts() {
  Keyboard.write(KEY_RETURN);  //Accept TOS
  wait(3);
  Keyboard.write(KEY_RETURN);  //Accept Additional Legal Terms
}

/*
Deselect or accept Google Services.
*/
void googleServices() {
  wait(2);
  Keyboard.write(KEY_RETURN);
}

/*
Skip the the Audio setup with the remote. This can be completed later. 
*/
void noRemoteSetup() {
  Keyboard.write(KEY_RIGHT_ARROW);
  wait(1);
  Keyboard.write(KEY_RIGHT_ARROW);
  wait(1);
  Keyboard.write(KEY_RETURN);
}

/*
Wait in integer seconds
*/
void wait(int seconds = 1);
void wait(int seconds) {
  for (int i = 0; i < seconds; i++) {
    blink();
  }
}

/*
Back key signal
*/
void back() {
  Keyboard.press(KEY_LEFT_GUI);
  delay(200);
  Keyboard.write(KEY_BACKSPACE);
  wait(1);
  Keyboard.releaseAll();
}

/*
LED Blink
*/
void blink() {
  digitalWrite(LED_BUILTIN, HIGH);  // turn the LED on
  delay(500);                       // wait for half a second
  digitalWrite(LED_BUILTIN, LOW);   // turn the LED off
  delay(500);                       // wait for half a second
}