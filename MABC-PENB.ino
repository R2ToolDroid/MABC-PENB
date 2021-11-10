// =======================================================================================
//         Penumbra: Minimal drive system for the ESP32
// =======================================================================================
//  Written by: skelmir
// =======================================================================================
//
//         This program is distributed in the hope that it will be useful 
//         as a courtesy to fellow astromech club members wanting to develop
//         their own droid control system.
//
//         IT IS OFFERED WITHOUT ANY WARRANTY; without even the implied warranty of
//         MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
//
//         You are using this software at your own risk and, as a fellow club member, it is
//         expected you will have the proper experience / background to handle and manage that 
//         risk appropriately.  It is completely up to you to insure the safe operation of
//         your droid and to validate and test all aspects of your droid control system.
//
// =======================================================================================
//   Note: You will need an ESP32 (either WROOM or WRover).
//
//   You will need to install the Reeltwo library. 
//      https://github.com/reeltwo/Reeltwo
//
//   To use Roboteq SBL2360 as your motor controller. Define:
//     #define DRIVE_SYSTEM         DRIVE_SYSTEM_ROBOTEQ_PWM
//
//   To use Roboteq SBL2360 as your motor controller and enable turtle command control. Define:
//     #define DRIVE_SYSTEM         DRIVE_SYSTEM_ROBOTEQ_PWM_SERIAL
//
//   To use Sabertooth 2x32 as your motor controller. Define:
//     #define DRIVE_SYSTEM         DRIVE_SYSTEM_SABER
//
//   To use a PWM based motor controller. Define:
//     #define DRIVE_SYSTEM         DRIVE_SYSTEM_PWM
//
//   Define MY_BT_ADDR to the address stored in your PS3 Navication controller. Or update
//   your PS3 Nav controller to match the BT address of your ESP32.
//     #define MY_BT_ADDR          "24:6f:28:44:a5:ae"
//
// =======================================================================================
//
//  PS3 Controll button mapping:
//
//    L2: Throttle
//    L1: Hard brake
//    Joystick: Drive
//
//  All other buttons are unmapped and will print a debug message for you to repurpose
//
// =======================================================================================
//

////////////////////////////////
// CONFIGURATION OPTIONS
////////////////////////////////

// Enable WiFi
#define USE_WIFI
#ifdef USE_WIFI
// Enable OTA update
#define USE_OTA
// Enable Web interface
#define USE_WIFI_WEB
#endif

// Optional SYK base radio controller
//#define USE_RADIO

// Drive System options
#define DRIVE_SYSTEM_PWM                1
#define DRIVE_SYSTEM_SABER              2
#define DRIVE_SYSTEM_ROBOTEQ_PWM        3
#define DRIVE_SYSTEM_ROBOTEQ_SERIAL     4
#define DRIVE_SYSTEM_ROBOTEQ_PWM_SERIAL 5

// Drive System selection
#define DRIVE_SYSTEM         DRIVE_SYSTEM_ROBOTEQ_PWM_SERIAL
//#define DRIVE_SYSTEM         DRIVE_SYSTEM_PWM

#ifdef USE_WIFI
#if 1
// Set these to your desired credentials.
#define WIFI_AP_NAME         "R2D2"
#define WIFI_AP_PASSPHRASE   "Astromech"
#define WIFI_ACCESS_POINT    true  /* true if access point: false if joining existing wifi */
#else
// Alternatively join an existing AP
#define WIFI_AP_NAME         "R2_Router"
#define WIFI_AP_PASSPHRASE   "tronic307"
#define WIFI_ACCESS_POINT    false  /* true if access point: false if joining existing wifi */
#endif
#endif

////////////////////////////////
// Default drive system configuration. Can be changed through web interface and stored in flash

// Top speed limiter
#define MAXIMUM_SPEED        0.5f   // percentage 0.0 - 1.0. default 50%
// Top speed for a guest joystick (if used)
#define MAXIMUM_GUEST_SPEED  0.3f   // percentage 0.0 - 1.0. default 30%

// Scale value of 1 means instant. Scale value of 100 means that the throttle will increase 1/100 every 25ms
#define ACCELERATION_SCALE   100 
// Scale value of 1 means instant. Scale value of 20 means that the throttle will decrease 1/20 every 25ms
#define DECELRATION_SCALE    20

#define SCALING              true   // set to true if acceleration/decelleration should be applied

#define THROTTLE_INVERTED    false  // set to true if throttle should be inverted
#define TURN_INVERTED        false  // set to true if turn should be inverted

#if DRIVE_SYSTEM == DRIVE_SYSTEM_SABER
#define CHANNEL_MIXING       true   // set to true premix channels before sending commands
#define DRIVE_BAUD_RATE      9600
#elif DRIVE_SYSTEM == DRIVE_SYSTEM_PWM
#define CHANNEL_MIXING       false  // set to false if motor controller will mix the channels
#elif DRIVE_SYSTEM == DRIVE_SYSTEM_ROBOTEQ_PWM
#define CHANNEL_MIXING       false  // set to false if motor controller will mix the channels
#elif DRIVE_SYSTEM == DRIVE_SYSTEM_ROBOTEQ_SERIAL
#define DRIVE_BAUD_RATE      115200
#define CHANNEL_MIXING       false  // set to false if motor controller will mix the channels
#elif DRIVE_SYSTEM == DRIVE_SYSTEM_ROBOTEQ_PWM_SERIAL
#define DRIVE_BAUD_RATE      115200
#define CHANNEL_MIXING       false  // set to false if motor controller will mix the channels
#else
#error Unsupported DRIVE_SYSTEM
#endif

#ifndef MARCDUINO_BAUD_RATE
#define MARCDUINO_BAUD_RATE  9600
#endif

#ifndef MAX_GESTURE_LENGTH
#define MAX_GESTURE_LENGTH   20
#endif

#ifndef GESTURE_TIMEOUT_MS
#define GESTURE_TIMEOUT_MS   2000
#endif

////////////////////////////////
// Bluetooth address of this ESP32 device. If you already have a Shadow system configured
// the easiest thing is reuse the address of your USB Bluetooth dongle here. Alternatively,
// you can use sixaxispair to pair your controllers with the ESP32.
//#define MY_BT_ADDR             "24:6f:28:44:a5:ae"
#define MY_BT_ADDR             "01:1a:7d:da:71:12"
//#define MY_BT_ADDR           "03:03:03:03:03:03"
//#define MY_BT_ADDR           "b6:0c:76:94:05:b0" (PS4)


////////////////////////////////
// Assign a BT address here if you want to assign a specific controller as the drive stick
// otherwise it will be first come first serve
#define DRIVE_STICK_BT_ADDR     nullptr
//#define DRIVE_STICK_BT_ADDR  "00:07:04:09:b4:05"

////////////////////////////////
// Serial1 pins used to communicate with the motor controller
#define SERIAL1_RX_PIN 4
#define SERIAL1_TX_PIN 2

#ifdef USE_RADIO
////////////////////////////////
// Serial2 pins used to communicate with SYK Radio if used.
#define SERIAL2_RX_PIN 18
#define SERIAL2_TX_PIN 19
#endif

#if 0
////////////////////////////////
// Software serial TX pin used to send Marcduino commands.
#define SERIAL_MARCDUINO_TX_PIN 5
#endif

////////////////////////////////
// 
//#define LEFT_MOTOR_PWM      23
//#define RIGHT_MOTOR_PWM     22
#define LEFT_MOTOR_PWM      12 //23
#define RIGHT_MOTOR_PWM     13   //22
////////////////////////////////
// Optional Roboteq pin needs a Microbasic script running on the Roboteq controller to change the throttle.
// If the Microbasic script is not runnig this PWM signal will have no effect.
//#define THROTTLE_MOTOR_PWM  21

////////////////////////////////

#define USE_DEBUG
//#define USE_MOTOR_DEBUG
#define USE_SERVO_DEBUG
//#define USE_VERBOSE_SERVO_DEBUG

////////////////////////////////

#include "ReelTwo.h"
#include "drive/TankDrivePWM.h"
#include "drive/TankDriveRoboteq.h"
#if DRIVE_SYSTEM == DRIVE_SYSTEM_SABER
#include "drive/TankDriveSabertooth.h"
#endif
#include "ServoDispatchDirect.h"
#include "ServoEasing.h"
#include "SoftwareSerial.h"
#include "Images.h"
#include <Preferences.h>
#ifdef USE_WIFI
#include <ESPmDNS.h>
#ifdef USE_WIFI_WEB
#include "wifi/WifiWebServer.h"
#endif
#endif
#include "bt/PSController/PSController.h"

#ifdef USE_OTA
#include <ArduinoOTA.h>
#endif
//
#include "DFRobotDFPlayerMini.h"

DFRobotDFPlayerMini myDFPlayer;

SoftwareSerial mp3; // RX, TX

////////////////////////////////

// Group ID is used by the ServoSequencer and some ServoDispatch functions to
// identify a group of servos.
//
//   Pin  Group ID,      Min,  Max
const ServoSettings servoSettings[] PROGMEM = {
    { LEFT_MOTOR_PWM,     1000, 2000, 0 },
    { RIGHT_MOTOR_PWM,    1000, 2000, 0 }
#ifdef THROTTLE_MOTOR_PWM
    ,{ THROTTLE_MOTOR_PWM, 1000, 2000, 0 }
#endif
};

ServoDispatchDirect<SizeOfArray(servoSettings)> servoDispatch(servoSettings);

////////////////////////////////

TaskHandle_t eventTask;
Preferences preferences;
#ifdef SERIAL_MARCDUINO_TX_PIN
SoftwareSerial marcSerial;
#endif

////////////////////////////////

////////////////////////////////////
// Forward declare utility routines
////////////////////////////////////
void enableController();
void disableController();
void emergencyStop();

////////////////////////////////////

class DriveController : public PSController
{
public:
    DriveController(const char* mac = nullptr) : PSController(mac) {}
    virtual void notify() override
    {
        uint32_t currentTime = millis();
        uint32_t lagTime = (currentTime > fLastTime) ? currentTime - fLastTime : 0;
        if (lagTime > 5000)
        {
            DEBUG_PRINTLN("More than 5 seconds. Disconnect");
            emergencyStop();
            disconnect();
        }
        else if (lagTime > 500)
        {
            DEBUG_PRINTLN("It has been 500ms. Shutdown motors");
            emergencyStop();
        }
        else
        {
            // Event handling map these actions for your droid.
            // You can choose to either respond to key down or key up
            if (event.button_down.l3)
            {
                DEBUG_PRINTLN("DRIVE L3 DOWN");
            }
            else if (event.button_up.l3)
            {
                DEBUG_PRINTLN("DRIVE L3 UP");
            }

            if (event.button_down.cross)
            {
                DEBUG_PRINTLN("DRIVE X DOWN");
            }
            else if (event.button_up.cross)
            {
                DEBUG_PRINTLN("DRIVE X UP");
            }

            if (event.button_down.circle)
            {
                DEBUG_PRINTLN("DRIVE O DOWN");

               //DEBUG_PRINTLN(data.status.battery);
               myDFPlayer.play(5);

              //DEBUG_PRINTLN(driveStick.status.battery);
            }
            else if (event.button_up.circle)
            {
                DEBUG_PRINTLN("DRIVE O UP");
            }

            if (event.button_down.up)
            {
                DEBUG_PRINTLN("DRIVE Started pressing the up button");
            }
            else if (event.button_up.up)
            {
                DEBUG_PRINTLN("DRIVE Released the up button");
            }

            if (event.button_down.right)
            {
                DEBUG_PRINTLN("DRIVE Started pressing the right button");
            }
            else if (event.button_up.right)
            {
                DEBUG_PRINTLN("DRIVE Released the right button");
            }

            if (event.button_down.down)
            {
                DEBUG_PRINTLN("DRIVE Started pressing the down button");
            }
            else if (event.button_up.down)
            {
                DEBUG_PRINTLN("DRIVE Released the down button");
            }

            if (event.button_down.left)
            {
                DEBUG_PRINTLN("DRIVE Started pressing the left button");
            }
            else if (event.button_up.left)
            {
                DEBUG_PRINTLN("DRIVE Released the left button");
            }

            if (event.button_down.ps)
            {
                DEBUG_PRINTLN("DRIVE PS DOWN");
            }
            else if (event.button_up.ps)
            {
                DEBUG_PRINTLN("DRIVE PS UP");
            }
        }
        fLastTime = currentTime;
    }
    
    virtual void onConnect() override
    {
        DEBUG_PRINTLN("Drive Stick Connected");
        setPlayer(1);
        enableController();
        fLastTime = millis();
        
        
        //HIER
    }
    
    virtual void onDisconnect() override
    {
        DEBUG_PRINTLN("Drive Stick Disconnected");
        disableController();
    }

    uint32_t fLastTime = 0;
};

DriveController driveStick(DRIVE_STICK_BT_ADDR);
#ifdef USE_RADIO
RadioController radioStick(Serial2);
#endif

#if DRIVE_SYSTEM == DRIVE_SYSTEM_SABER
// Tank Drive assign:
//    Serial1 for Sabertooth packet serial commands
TankDriveSabertooth tankDrive(128, Serial1, driveStick);
#elif DRIVE_SYSTEM == DRIVE_SYSTEM_PWM
// Tank Drive assign:
//    servo index 0 (LEFT_MOTOR_PWM)
//    servo index 1 (RIGHT_MOTOR_PWM)
//    servo index 2 (THROTTLE_MOTOR_PWM)
#ifdef THROTTLE_MOTOR_PWM
TankDrivePWM tankDrive(servoDispatch, 0, 1, 2, driveStick);
#else
TankDrivePWM tankDrive(servoDispatch, 0, 1, driveStick);
#endif
#elif DRIVE_SYSTEM == DRIVE_SYSTEM_ROBOTEQ_PWM
// Tank Drive assign:
//    servo index 0 (LEFT_MOTOR_PWM)
//    servo index 1 (RIGHT_MOTOR_PWM)
//    servo index 2 (THROTTLE_MOTOR_PWM)
#ifdef THROTTLE_MOTOR_PWM
TankDriveRoboteq tankDrive(servoDispatch, 0, 1, 2, driveStick);
#else
TankDriveRoboteq tankDrive(servoDispatch, 0, 1, driveStick);
#endif
#elif DRIVE_SYSTEM == DRIVE_SYSTEM_ROBOTEQ_SERIAL
// Tank Drive assign:
//    servo index 0 (LEFT_MOTOR_PWM)
//    servo index 1 (RIGHT_MOTOR_PWM)
//    servo index 2 (THROTTLE_MOTOR_PWM)
TankDriveRoboteq tankDrive(Serial1, driveStick);
#elif DRIVE_SYSTEM == DRIVE_SYSTEM_ROBOTEQ_PWM_SERIAL
// Tank Drive assign:
//    servo index 0 (LEFT_MOTOR_PWM)
//    servo index 1 (RIGHT_MOTOR_PWM)
//    servo index 2 (THROTTLE_MOTOR_PWM)
//    Serial1 for Roboteq serial commands
#ifdef THROTTLE_MOTOR_PWM
TankDriveRoboteq tankDrive(Serial1, servoDispatch, 0, 1, 2, driveStick);
#else
TankDriveRoboteq tankDrive(Serial1, servoDispatch, 0, 1, driveStick);
#endif
#else
#error Unsupported DRIVE_SYSTEM
#endif

void enableController()
{
    tankDrive.setEnable(true);
}

void disableController()
{
    emergencyStop();
    tankDrive.setEnable(false);
}

void emergencyStop()
{
    tankDrive.stop();
}

#ifdef USE_WIFI_WEB
////////////////////////////////
// Web configurable parameters. Strongly advice not to change web settings while motors are running
// unless the wheels are off the ground.
WElement mainContents[] = {
    W1("Drive Configuration"),
    WSlider("Max Speed", "maxspeed", 0, 100,
        []()->int { return tankDrive.getMaxSpeed()*100; },
        [](int val) { tankDrive.stop(); tankDrive.setMaxSpeed(val/100.0f); } ),
    WSlider("Guest Max Speed", "guestspeed", 0, 100,
        []()->int { return tankDrive.getGuestSpeedModifier()*100; },
        [](int val) { tankDrive.stop(); tankDrive.setGuestSpeedModifier(val/100.0f); } ),
    WSlider("Throttle Acceleration", "throttleAccel", 1, 400,
        []()->int { return tankDrive.getThrottleAccelerationScale(); },
        [](int val) { tankDrive.stop(); tankDrive.setThrottleAccelerationScale(val); } ),
    WSlider("Throttle Deceleration", "throttleDecel", 1, 400,
        []()->int { return tankDrive.getThrottleDecelerationScale(); },
        [](int val) { tankDrive.stop(); tankDrive.setThrottleDecelerationScale(val); } ),
    WSlider("Turn Acceleration", "turnAccel", 1, 400,
        []()->int { return tankDrive.getTurnAccelerationScale(); },
        [](int val) { tankDrive.stop(); tankDrive.setTurnAccelerationScale(val); } ),
    WSlider("Turn Deceleration", "turnDecl", 1, 400,
        []()->int { return tankDrive.getTurnDecelerationScale(); },
        [](int val) { tankDrive.stop(); tankDrive.setTurnDecelerationScale(val); } ),
    WCheckbox("Scale Throttle", "scaling",
        []() { return tankDrive.getScaling(); },
        [](bool val) { tankDrive.stop(); tankDrive.setScaling(val); } ),
    WCheckbox("Channel Mixing", "mixing",
        []() { return tankDrive.getChannelMixing(); },
        [](bool val) { tankDrive.stop(); tankDrive.setChannelMixing(val); } ),
    WCheckbox("Throttle Inverted", "throttleInvert",
        []() { return tankDrive.getThrottleInverted(); },
        [](bool val) { tankDrive.stop(); tankDrive.setThrottleInverted(val); } ),
    WCheckbox("Turn Inverted", "turnInvert",
        []() { return tankDrive.getTurnInverted(); },
        [](bool val) { tankDrive.stop(); tankDrive.setTurnInverted(val); } ),
    WButton("Save", "save", []() {
        preferences.putFloat("maxspeed", tankDrive.getMaxSpeed());
        preferences.putFloat("throttleaccscale", tankDrive.getThrottleAccelerationScale());
        preferences.putFloat("throttledecscale", tankDrive.getThrottleDecelerationScale());
        preferences.putFloat("turnaccscale", tankDrive.getTurnAccelerationScale());
        preferences.putFloat("turndecscale", tankDrive.getTurnDecelerationScale());
        preferences.putFloat("guestmaxspeed", tankDrive.getGuestSpeedModifier());
        preferences.putBool("scaling", tankDrive.getScaling());
        preferences.putBool("mixing", tankDrive.getChannelMixing());
        preferences.putBool("throttleinvert", tankDrive.getThrottleInverted());
        preferences.putBool("turninvert", tankDrive.getTurnInverted());
    }),
    WButton("Restore", "restore", []() {
        tankDrive.setMaxSpeed(preferences.getFloat("maxspeed", MAXIMUM_SPEED));
        tankDrive.setThrottleAccelerationScale(preferences.getFloat("throttleaccscale", ACCELERATION_SCALE));
        tankDrive.setThrottleDecelerationScale(preferences.getFloat("throttledecscale", DECELRATION_SCALE));
        tankDrive.setTurnAccelerationScale(preferences.getFloat("turnaccscale", ACCELERATION_SCALE*2));
        tankDrive.setTurnDecelerationScale(preferences.getFloat("turndecscale", DECELRATION_SCALE));
        tankDrive.setScaling(preferences.getBool("scaling", SCALING));
        tankDrive.setGuestSpeedModifier(preferences.getFloat("guestmaxspeed", MAXIMUM_GUEST_SPEED));
        tankDrive.setChannelMixing(preferences.getBool("mixing", CHANNEL_MIXING));
        tankDrive.setThrottleInverted(preferences.getBool("throttleinvert", THROTTLE_INVERTED));
        tankDrive.setTurnInverted(preferences.getBool("turninvert", TURN_INVERTED));
    }),
    WImage("astromech", ASTROMECH_IMAGE)
};
WPage pages[] = {
    WPage("/", mainContents, SizeOfArray(mainContents))
};
WifiWebServer<1,SizeOfArray(pages)> motorWeb(pages, WIFI_AP_NAME, WIFI_AP_PASSPHRASE, WIFI_ACCESS_POINT);
#endif

void setup()
{
    REELTWO_READY();

    preferences.begin("rseries", false);

#ifdef DRIVE_BAUD_RATE
    // Serial1 is used for drive system
    Serial1.begin(DRIVE_BAUD_RATE, SERIAL_8N1, SERIAL1_RX_PIN, SERIAL1_TX_PIN);
#endif
#ifdef USE_RADIO
    Serial2.begin(57600, SERIAL_8N1, SERIAL2_RX_PIN, SERIAL2_TX_PIN);
#endif
#ifdef SERIAL_MARCDUINO_TX_PIN
    // Transmit only software serial on SERIAL_MARCDUINO_TX_PIN
    marcSerial.begin(MARCDUINO_BAUD_RATE, SWSERIAL_8N1, -1, SERIAL_MARCDUINO_TX_PIN, false, 0);
#endif

    SetupEvent::ready();
    PSController::startListening(MY_BT_ADDR);

    /*use mdns for host name resolution*/
    String mac = PSController::getDeviceAddress();
    String hostName = mac.substring(mac.length()-5, mac.length());
    hostName.remove(2, 1);
    hostName = "RSeries-"+hostName;
    DEBUG_PRINTLN(mac);
    DEBUG_PRINTLN(hostName);
#ifdef USE_WIFI
    if (!MDNS.begin(hostName.c_str()))
    {
        DEBUG_PRINTLN("Error setting up MDNS responder!");
    }
#endif

#ifdef USE_OTA
    ArduinoOTA.onStart([]()
    {
        String type;
        if (ArduinoOTA.getCommand() == U_FLASH)
        {
            type = "sketch";
        }
        else // U_SPIFFS
        {
            type = "filesystem";
        }
        DEBUG_PRINTLN("OTA START");
        // Kill the motors
        tankDrive.setEnable(false);
    })
    .onEnd([]()
    {
        DEBUG_PRINTLN("OTA END");
    })
    .onProgress([](unsigned int progress, unsigned int total)
    {
        float range = (float)progress / (float)total;
    })
    .onError([](ota_error_t error)
    {
        String desc;
        if (error == OTA_AUTH_ERROR) desc = "Auth Failed";
        else if (error == OTA_BEGIN_ERROR) desc = "Begin Failed";
        else if (error == OTA_CONNECT_ERROR) desc = "Connect Failed";
        else if (error == OTA_RECEIVE_ERROR) desc = "Receive Failed";
        else if (error == OTA_END_ERROR) desc = "End Failed";
        else desc = "Error: "+String(error);
        DEBUG_PRINTLN(desc);
    });
#endif

    tankDrive.setMaxSpeed(preferences.getFloat("maxspeed", MAXIMUM_SPEED));
    tankDrive.setThrottleAccelerationScale(preferences.getFloat("throttleaccscale", ACCELERATION_SCALE));
    tankDrive.setThrottleDecelerationScale(preferences.getFloat("throttledecscale", DECELRATION_SCALE));
    tankDrive.setTurnAccelerationScale(preferences.getFloat("turnaccscale", ACCELERATION_SCALE*2));
    tankDrive.setTurnDecelerationScale(preferences.getFloat("turndecscale", DECELRATION_SCALE));
#ifdef USE_RADIO
    tankDrive.setGuestStick(radioStick);
#endif
    tankDrive.setGuestSpeedModifier(preferences.getFloat("guestmaxspeed", MAXIMUM_GUEST_SPEED));
    tankDrive.setScaling(preferences.getBool("scaling", SCALING));
    tankDrive.setChannelMixing(preferences.getBool("mixing", CHANNEL_MIXING));
    tankDrive.setThrottleInverted(preferences.getBool("throttleinvert", THROTTLE_INVERTED));
    tankDrive.setTurnInverted(preferences.getBool("turninvert", TURN_INVERTED));

#ifdef USE_WIFI_WEB
    // For safety we will stop the motors if the web client is connected
    motorWeb.setConnect([]() {
        tankDrive.stop();
    });
#endif
    // tankDrive.enterCommandMode();

    xTaskCreatePinnedToCore(
          eventLoopTask,
          "Events",
          5000,    // shrink stack size?
          NULL,
          1,
          &eventTask,
          0);

    DEBUG_PRINT("Total heap:  "); DEBUG_PRINTLN(ESP.getHeapSize());
    DEBUG_PRINT("Free heap:   "); DEBUG_PRINTLN(ESP.getFreeHeap());
    DEBUG_PRINT("Total PSRAM: "); DEBUG_PRINTLN(ESP.getPsramSize());
    DEBUG_PRINT("Free PSRAM:  "); DEBUG_PRINTLN(ESP.getFreePsram());
    DEBUG_PRINTLN();

#ifdef USE_RADIO
    radioStick.start();
#endif

////
  mp3.begin(9600, SWSERIAL_8N1, 25, 26, false, 256);  // speed, type, RX, TX

  if (!myDFPlayer.begin(mp3, true, false)) {  //Use softwareSerial to communicate with mp3.
    
    Serial.println(myDFPlayer.readType(),HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    //while(true);
    delay(3000);
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500); //Set serial communictaion time out 500ms 
  //----Set volume----
  myDFPlayer.volume(10);  //Set volume value (0~30).
  myDFPlayer.volumeUp(); //Volume Up
  myDFPlayer.volumeDown(); //Volume Down
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  int delayms=100;  ///delay OEM 100
  //----Mp3 play----
  //----Read imformation----
  /*
  DEBUG_PRINTLN = "readState--------------------";
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += myDFPlayer.readState(); //read mp3 state
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += "readVolume--------------------";
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += myDFPlayer.readVolume(); //read current volume
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += "readEQ--------------------";
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += myDFPlayer.readEQ(); //read EQ setting
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += "readFileCounts--------------------";
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += myDFPlayer.readFileCounts(); //read all file counts in SD card
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += "readCurrentFileNumber--------------------";
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += myDFPlayer.readCurrentFileNumber(); //read current play file number
  DEBUG_PRINTLN += "\n";
  
  DEBUG_PRINTLN += "readFileCountsInFolder--------------------";
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += myDFPlayer.readFileCountsInFolder(3); //read fill counts in folder SD:/03";
  DEBUG_PRINTLN += "\n";
  DEBUG_PRINTLN += "---Wait---";
  DEBUG_PRINTLN += "\n";
  */
  //maxFilesinFolder = myDFPlayer.readFileCountsInFolder(1);

//

    myDFPlayer.play(1);


    
    DEBUG_PRINTLN("READY");
}

void eventLoopTask(void* arg)
{
    for (;;)
    {
        AnimatedEvent::process();
        vTaskDelay(1);
    }
}

void loop()
{

 //DEBUG_PRINTLN(driveStick.state.battery);

  
#ifdef USE_OTA
    ArduinoOTA.handle();
#endif
#ifdef USE_WIFI_WEB
    motorWeb.handle();
#endif
}
