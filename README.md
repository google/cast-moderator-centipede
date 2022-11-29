Copyright 2022 Google LLC

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

      http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

# Cast Moderator Centipede
Cast Moderator Centipede is an Arduino script used to setup Cast Moderator 
in bulk. The script is compiled and uploaded to a keyboard enabled micro controller. 
The Arduino is then powered or executed and walks through the setup flow.
[Setup Example Video](https://youtu.be/mqOyv3sQdOw)

## Materials
- Google Chromecast 
- Arduino with HID Keyboard functionality
  - [Arduino Micro](https://store-usa.arduino.cc/products/arduino-micro) for example
- USB splitter with USB-C Data and Power ports
  - Tested using [Anker USB-C, Hub Power Expand 6-in-1](https://www.amazon.com/dp/B08C9HZ5YT/ref=redir_mobile_desktop?_encoding=UTF8&aaxitk=7ecf2e6cb8dd44356111dfafbdd8d3d8&content-id=amzn1.sym.cf8fc959-74aa-4850-a250-1b1a4e868e60%3Aamzn1.sym.cf8fc959-74aa-4850-a250-1b1a4e868e60&hsa_cr_id=8749440340201&pd_rd_plhdr=t&pd_rd_r=01294ba4-e1ad-486e-97f6-f5f486a7d4ad&pd_rd_w=jTWat&pd_rd_wg=QRjP9&qid=1666026880&ref_=sbx_be_s_sparkle_lsi4d_asin_2_title&sr=1-3-9e67e56a-6f64-441f-a281-df67fc737124)


## Steps
1. Clone this repo to your local device. 
2. Edit in an Arduino IDE to enter your WifFi SSID, Password, Google Workspace Username, and Password.          
   - Optionally adjust timings where needed to accommodate network speed and potential downloads.
   - When creating accounts on the domain use the same password. Secure accounts by turning off services such as gmail and drive which are not needed. 
   - Google accounts can only be used on up to 50 devices.
   - When using a non-Google SSO it's best to place the cast accounts in an org unit set to [Google as the SSO](https://cloud.google.com/blog/products/identity-security/google-now-supports-multi-idp-sso-in-google-workspace-and-google-cloud).
3. Compile and upload to the arduino.
4. Connect the tail of your USB-c splitter to the Chromecast. 
5. Connect the Chromecast to the HDMI. 
6. Connect the Power to the USB and let it boot. 
7. When prompted pair the remote. 
8. Once paired plug in or reset the Arduino. Code will begin the click after the set delay; 10 seconds.
9. Once asked to explore thr Chromecast it can be disconnected and installed in a Classroom. When booted it will load Cast Moderator immediately. 