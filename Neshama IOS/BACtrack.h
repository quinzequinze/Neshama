//
//  Public-SDK
//
//  Copyright (c) 2014 KHN Solutions LLC. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <CoreBluetooth/CoreBluetooth.h>


/*******************************************************************************************/
//Global Values

typedef NS_ENUM(NSInteger, BACtrackDeviceType) {
    BACtrackDeviceType_DATech = 0,
    BACtrackDeviceType_Kotex,
    BACtrackDeviceType_Unknown
};

#define SIMPLE_GATT_SERVICE_READ_LEN                    6


// HW Revisions Services
#define GLOBAL_BACTRACK_DATECH_HW_REVISION          @"5265766973696f6e204200" // Revision B
#define GLOBAL_BACTRACK_KOTEX_HW_REVISION           @"322e300000" // 2.0


// Universal Services
#define GLOBAL_BACTRACK_SERVICE_BATTERY @"180F"
#define GLOBAL_BACTRACK_SERVICE_VERSIONS  @"180A"

// DATech Services
#define DATECH_BACTRACK_SERVICE_ONE     @"FFF0"
#define DATECH_BACTRACK_SERVICE_TWO     @"FFA0"

// Kotex Services
#define KOTEX_BACTRACK_SERVICE_ONE                  @"0xCD06FD00-4AFF-11E3-8F96-0800200C9A66"

// Kotex Characteristics
#define KOTEX_BACTRACK_CHARACTERISTIC_SERIAL_TRANSMIT   @"0xCD06FD03-4AFF-11E3-8F96-0800200C9A66"
#define KOTEX_BACTRACK_CHARACTERISTIC_SERIAL_RECEIVE    @"0xCD06FD04-4AFF-11E3-8F96-0800200C9A66"


// Serial Protocol
#define SERIAL_PROTOCOL_SOP                                  @"1002"
#define SERIAL_PROTOCOL_EOP                                  @"1017"



// Characteristics
#define GLOBAL_BACTRACK_CHARACTERISTIC_TRANSMIT    @"FFA1"
#define GLOBAL_BACTRACK_CHARACTERISTIC_RECEIVE     @"FFA2"

#define GLOBAL_BACTRACK_CHARACTERISTIC_BATTERY     @"2A19"
#define GLOBAL_BACTRACK_CHARACTERISTIC_HARDWARE_VERSION @"2A27"
#define GLOBAL_BACTRACK_CHARACTERISTIC_FIRMWARE_VERSION @"2A26"
#define GLOBAL_BACTRACK_CHARACTERISTIC_SOFTWARE_VERSION @"2A28"

#define GLOBAL_BACTRACK_CHARACTERISTIC_SHUTDOWN    @"FFF3"

#define GLOBAL_BACTRACK_CHARACTERISTIC_COUNTDOWN_NOTIFY  @"FFF5"

#define GLOBAL_CHARACTERISITIC_LED_ONE             @"FFF6"
#define GLOBAL_CHARACTERISITIC_LED_TWO             @"FFF7"
#define GLOBAL_CHARACTERISITIC_PULSE_LED           @"FFF8"

#define GLOBAL_CHARACTERISITC_PROTECTION           @"FFF9"
#define GLOBAL_CHARACTERISITC_ADVERTISING          @"FFFA"
#define GLOBAL_CHARACTERISITC_RESET_TIMEOUT        @"FFFB"
#define GLOBAL_CHARACTERISITC_CALIBRATION_RESULTS  @"FFFC"
#define GLOBAL_CHARACTERISITC_POWER_MANGEMENT      @"FFFD"
#define GLOBAL_CHARACTERISITC_TRANSMIT_POWER       @"FFFE"
#define GLOBAL_CHARACTERISITC_BLOW_COUNT           @"FFFF"

#define GLOBAL_BACTRACK_SERVICE_OAD                @"0xF000FFC0-0451-4000-B000-000000000000"
#define GLOBAL_CHARACTERISTIC_OAD_ONE              @"0xF000FFC1-0451-4000-B000-000000000000"
#define GLOBAL_CHARACTERISTIC_OAD_TWO              @"0xF000FFC2-0451-4000-B000-000000000000"


#define DATECH_SOF                                  0x02
#define DATECH_EOF                                  0xE0

#define DATECH_COMMAND_RECEIVE_ACK                  0xA0
#define DATECH_COMMAND_RECEIVE_NACK                 0xB0
#define DATECH_COMMAND_RECEIVE_STATUS               0x81
#define DATECH_COMMAND_RECEIVE_ERROR                0x82
#define DATECH_COMMAND_RECEIVE_BLOW_SETTING         0x83
#define DATECH_COMMAND_RECEIVE_USE_COUNT            0x85
#define DATECH_COMMAND_RECEIVE_CALIBRATION_STATUS   0xA1
#define DATECH_COMMAND_RECEIVE_CALIBRATION_RESULTS  0xA3
#define DATECH_COMMAND_TRANSMIT_POWERSTATE          0x72
#define DATECH_COMMAND_TRANSMIT_BLOWSETTING_READ    0x73
#define DATECH_COMMAND_TRANSMIT_BLOWSETTING_SET     0x74
#define DATECH_COMMAND_TRANSMIT_REQUEST_USE_COUNT   0x75
#define DATECH_COMMAND_TRANSMIT_CALIBRATION_START   0x90
#define DATECH_COMMAND_TRANSMIT_CALIBRATION_READ    0x91
#define DATECH_COMMAND_TRANSMIT_FACTORY_RESET       0x92

#define DATECH_COMMAND_TRANSMIT_CHARACTERISTIC_SIZE                 20
#define DATECH_COMMAND_RECEIVE_CHARACTERISTIC_SIZE                  20

#define DATECH_COMMAND_RECEIVE_STATUS_DATALENGTH                    9
#define DATECH_COMMAND_RECEIVE_ERROR_DATALENGTH                     2
#define DATECH_COMMAND_RECEIVE_BLOW_SETTING_DATALENGTH              2
#define DATECH_COMMAND_RECEIVE_USE_COUNT_DATALENGTH                 4
#define DATECH_COMMAND_RECEIVE_CALIBRATION_STATUS_DATALENGTH        3
#define DATECH_COMMAND_RECEIVE_CALIBRATION_RESULTS_DATALENGTH       3
#define DATECH_COMMAND_TRANSMIT_POWERSTATE_DATALENGTH               1
#define DATECH_COMMAND_TRANSMIT_BLOWSETTING_READ_DATALENGTH         1
#define DATECH_COMMAND_TRANSMIT_BLOWSETTING_SET_DATALENGTH          2
#define DATECH_COMMAND_TRANSMIT_REQUEST_USE_COUNT_DATALENGTH        0
#define DATECH_COMMAND_TRANSMIT_CALIBRATION_START_DATALENGTH        0
#define DATECH_COMMAND_TRANSMIT_CALIBRATION_READ_DATALENGTH         0
#define DATECH_COMMAND_TRANSMIT_FACTORY_RESET_DATALENGTH            0


#define DATECH_STATUS_COUNT                     0x01
#define DATECH_STATUS_START                     0x02
#define DATECH_STATUS_BLOW                      0x03
#define DATECH_STATUS_ANALYZING                 0x04
#define DATECH_STATUS_RESULT                    0x05

#define DATECH_ERROR_TIME_OUT                   0x01
#define DATECH_ERROR_BLOW_ERROR                 0x02
#define DATECH_ERROR_OUT_OF_TEMPERATURE         0x03
#define DATECH_ERROR_LOW_BATTERY                0x04
#define DATECH_ERROR_CALIBRATION_FAIL           0x05
#define DATECH_ERROR_NOT_CALIBRATED             0x06
#define DATECH_ERROR_COM_ERROR                  0x07
#define DATECH_ERROR_INFLOW_ERROR               0x08
#define DATECH_ERROR_SOLENOID_ERROR             0x09
#define ERROR_SENSOR                            0x0a
#define ERROR_BAC_UPPER_LIMIT                   0x0b

#define DATECH_ERROR_TEMPERATURE_HIGH           0x01
#define DATECH_ERROR_TEMPERATURE_LOW            0x02

#define DATECH_POWERSTATE_ON                    0x01
#define DATECH_POWERSTATE_OFF                   0x02
#define DATECH_POWERSTATE_RESTART               0x03

#define DATECH_BLOWSETTING_TIME                 0x01
#define DATECH_BLOWSETTING_LEVEL                0x02

#define DATECH_BLOWSETTING_TIME_3SEC            0x03
#define DATECH_BLOWSETTING_TIME_4SEC            0x04
#define DATECH_BLOWSETTING_TIME_5SEC            0x05

#define DATECH_BLOWSETTING_LEVEL_LOW            0x01
#define DATECH_BLOWSETTING_LEVEL_HIGH           0x02

#define DATECH_BATTERYLEVEL_EMPTY               0x01
#define DATECH_BATTERYLEVEL_1                   0x02
#define DATECH_BATTERYLEVEL_2                   0x03
#define DATECH_BATTERYLEVEL_FULL                0x04

#define DATECH_CALIBRATION_RESULTS_STEP_FIRST_LOW           0x01
#define DATECH_CALIBRATION_RESULTS_STEP_SECOND_LOW          0x02

#define DATECH_CALIBRATION_RESULTS_STATUS_COUNT                0x01
#define DATECH_CALIBRATION_RESULTS_STATUS_START                0x02
#define DATECH_CALIBRATION_RESULTS_STATUS_BLOW                 0x03
#define DATECH_CALIBRATION_RESULTS_STATUS_ANALYZING            0x04
#define DATECH_CALIBRATION_RESULTS_STATUS_TIMEOUT              0x05
#define DATECH_CALIBRATION_RESULTS_STATUS_BLOW_ERROR           0x06

#define DATECH_CALIBRATION_STATE_STATUS_COUNT               0x01
#define DATECH_CALIBRATION_STATE_STATUS_START               0x02
#define DATECH_CALIBRATION_STATE_STATUS_BLOW                0x03
#define DATECH_CALIBRATION_STATE_STATUS_ANALYZING           0x04
#define DATECH_CALIBRATION_STATE_STATUS_SUCCESS             0x05


/*******************************************************************************************/
//Callbacks reveived from the BACtrack Device Delegate
@class Breathalyzer;
@protocol BacTrackAPIDelegate <NSObject>
@optional

//Successfully connected to BACTrack and found services and characteristics.
-(void)BacTrackConnected __attribute__((deprecated));
-(void)BacTrackConnected:(BACtrackDeviceType)device;

//Disconnected from BACTrack.
-(void)BacTrackDisconnected;

//Attempting to connect to BACTrack timed out.
-(void)BacTrackConnectTimeout;

//Asks for connection timeout when connecting to nearest breathalyzer.
-(NSTimeInterval)BacTrackGetTimeout;

//Counting down to reading, number (a double) seconds left, error = TRUE if BAC sensor rejects request.
-(void)BacTrackCountdown:(NSNumber*)number executionFailure:(BOOL)error;

//Tell the user to start blowing.
-(void)BacTrackStart;

//Tell the user to keep blowing.
-(void)BacTrackBlow;

//BACtrack is analyzing the result.
-(void)BacTrackAnalyzing;

//Result of the blow.
-(void)BacTrackResults:(CGFloat)bac;

//Found a breathalyzer. Call comes in for every breathalyzer found during scan.
-(void)BacTrackFoundBreathalyzer:(Breathalyzer*)breathalyzer;

//BACtrack firmware version.
-(void)BacTrackFirmwareVersion:(NSString*)version;

// Reports the current battery voltage.s
-(void)BacTrackBatteryVoltage:(NSNumber*)number;

//Error with device. e.g. "Not Connected", "Bluetooth Unsupported", etc.
-(void)BacTrackError:(NSError*)error;
@end


/*******************************************************************************************/
//Command calls to the BACtrack Device
@interface BacTrackAPI : NSObject

// Callback delegate. Must be set
@property (strong, nonatomic) id<BacTrackAPIDelegate> delegate;

// Initialize class with this method
-(id)initWithDelegate:(id<BacTrackAPIDelegate>)delegate;

// Scan for BacTrack breathalyzers
-(void)startScan;

// Stop scanning for BacTrack breathalyzers
-(void)stopScan;

//Connect to Nearest Breathalyzer
-(void)connectToNearestBreathalyzer;

//Disconnect from BACtrack
-(void)disconnect;

//Get Firmware Version
-(void)getFirmwareVersion;

//Start BACtrack Countdown to Test, returns YES if test started succesfully, NO if errors.
-(BOOL)startCountdown;

//Connect to specified Breathalyzer
-(void)connectBreathalyzer:(Breathalyzer*)breathalyzer withTimeout:(NSTimeInterval)timeout;

// Request a callback with the current battery voltage.
-(void)getBreathalyzerBatteryVoltage;

@end

@interface Breathalyzer : NSObject

@property (strong, nonatomic) NSString * uuid;
@property (strong, nonatomic) NSNumber * rssi;
@property (strong, nonatomic) CBPeripheral * peripheral;
@property (nonatomic) BACtrackDeviceType type;

@end