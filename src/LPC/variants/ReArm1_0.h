#ifndef REARM_H__
#define REARM_H__


//Config for ReArm v1.0

//Config is for the popular Bed+Extruder+Cooling Fan setup


//NOTES:
// Filament detector pin and Fan RPM pin must be on a spare pin on Port0 or Port2 only (UNTESTED)
// Azteeg X5 (and maybe others) probe endstop pin is not an ADC pin, so only Digital is supported, or select another spare ADC capable pin
// Note: ADC inputs are NOT 5V tolerant!


// Default board type
#define DEFAULT_BOARD_TYPE BoardType::Lpc
#define ELECTRONICS "ReArm v1.0"
#define LPC_ELECTRONICS_STRING "ReArm v1.0"
#define LPC_BOARD_STRING "Rearm1"

#define REARM1_0



// The physical capabilities of the machine

// The number of drives in the machine, including X, Y, and Z plus extruder drives
constexpr size_t DRIVES = 5;

constexpr size_t NumEndstops = 3;                    // The number of inputs we have for endstops, filament sensors etc.
constexpr size_t NumHeaters = 2;                    // The number of heaters in the machine; 0 is the heated bed even if there isn't one // set to 3 if using 2nd extruder
constexpr size_t NumThermistorInputs = 2;           //Set to 3 if using 2nd extruder

constexpr size_t MinAxes = 3;						// The minimum and default number of axes
constexpr size_t MaxAxes = 5;						// The maximum number of movement axes in the machine, usually just X, Y and Z, <= DRIVES

constexpr size_t MaxExtruders = DRIVES - MinAxes;	// The maximum number of extruders
constexpr size_t MaxDriversPerAxis = 2;				// The maximum number of stepper drivers assigned to one axis


// The numbers of entries in each array must correspond with the values of DRIVES, AXES, or HEATERS. Set values to NoPin to flag unavailability.
// DRIVES
//                                              X      Y      Z     E1     E2
constexpr Pin ENABLE_PINS[DRIVES] =             { P0_10, P0_19, P0_21, P0_4,  P4_29};
constexpr Pin STEP_PINS[DRIVES] =               { P2_1,  P2_2,  P2_3,  P2_0,  P2_8};
constexpr uint8_t STEP_PIN_PORT2_POS[DRIVES] =  { 1,     2,     3,     0,     8}; //SD: Used for calculating bitmap for stepping drivers (this is position of the pins on the port)
constexpr uint32_t STEP_DRIVER_MASK =           0x0000010F; //SD: mask of the step pins on Port 2 used for writing to step pins in parallel
constexpr Pin DIRECTION_PINS[DRIVES] =          { P0_11, P0_20, P0_22, P0_5,  P2_13};



// Endstops
// Note: RepRapFirmware only as a single endstop per axis
//       gcode defines if it is a max ("high end") or min ("low end")
//       endstop.  gcode also sets if it is active HIGH or LOW
//

//RE-Arm has 6 endstops. We will assume MAX endstops headers are used, leaving P1_24, 1_26 free for other purposes. 1_29 (Z-min used for probe)

constexpr Pin END_STOP_PINS[NumEndstops] = { P1_25, P1_27, P1_28 };


//RaArm has no current control for drivers.
#define HAS_DRIVER_CURRENT_CONTROL 0


// HEATERS - The bed is assumed to be the at index 0

//                                                     Bed    H1
constexpr Pin TEMP_SENSE_PINS[NumThermistorInputs] = {P0_24, P0_23 /*,P0_25*/};
constexpr Pin HEAT_ON_PINS[NumHeaters] = {P2_7, P2_5, /*P2.4*/};

// PWM -
//       The Hardware PWM channels ALL share the same Frequency,
//       we will use Hardware PWM for Hotends (on board which have the heater on a hardware PWM capable pin)
//       So for PWM at a different frequency to the Hotend PWM (250Hz) use the Timers to generate PWM
//       by setting the options below. If a HW PWM pin is defined below as a timer pin, it will use the timer instead of PWM
//       except if the requested freq by RRF does not match the fixed timer freq.

//       Set to {NoPin, NoPin, NoPin } if not used
//       Below is a list of HW PWM pins. There are only 6 channels, some pins share the same channel
//       P1_18  Channel 1
//       P1_20  Channel 2
//       P1_21  Channel 3
//       P1_23  Channel 4
//       P1_24  Channel 5
//       P1_26  Channel 6
//       P2_0   Channel 1
//       P2_1   Channel 2
//       P2_2   Channel 3
//       P2_3   Channel 4
//       P2_4   Channel 5
//       P2_5   Channel 6
//       P3_25  Channel 2
//       P3_26  Channel 3

//Smoothie: Bed (Timer1), H0 (HW PWM), Fan1 (HWPWM)

#define Timer1_PWM_Frequency 10 //For Bed heaters or other slow PWM (10Hz is what RRF defaults to be compatible with SSRs)
#define Timer2_PWM_Frequency 50 //For Servos 
#define Timer3_PWM_Frequency 250 //For Hotends not on HW PWM

#define Timer1_PWMPins {P2_7, NoPin, NoPin }
#define Timer2_PWMPins {P1_20, P1_19 , P1_21} // Servo 1, 2 and 3.
#define Timer3_PWMPins {NoPin, NoPin, NoPin}


// Default thermistor betas
constexpr float BED_R25 = 100000.0;
constexpr float BED_BETA = 3988.0;
constexpr float BED_SHC = 0.0;
constexpr float EXT_R25 = 100000.0;
constexpr float EXT_BETA = 4388.0;
constexpr float EXT_SHC = 0.0;

// Thermistor series resistor value in Ohms
constexpr float THERMISTOR_SERIES_RS = 4700.0;


constexpr size_t MaxSpiTempSensors = 1;
// Digital pins the 31855s have their select lines tied to
constexpr Pin SpiTempSensorCsPins[MaxSpiTempSensors] = { P0_27 };
constexpr SSPChannel TempSensorSSPChannel = SSP0;


// Digital pin number that controls the ATX power on/off
constexpr Pin ATX_POWER_PIN = NoPin;

// Z Probe pin
//Note: ReArm uses pin P1_29 which is NOT an ADC pin. Use a spare if need Analog in, else use digital options for probe
constexpr Pin Z_PROBE_PIN = P1_29;

// Digital pin number to turn the IR LED on (high) or off (low)
constexpr Pin Z_PROBE_MOD_PIN = NoPin;
constexpr Pin DiagPin = NoPin;


// Use a PWM capable pin
constexpr size_t NUM_FANS = 1;
constexpr Pin COOLING_FAN_PINS[NUM_FANS] = { P2_4 }; // Fan 0 is a Hardware PWM pin

// Firmware will attach a FALLING interrupt to this pin
// see FanInterrupt() in Platform.cpp
// SD:: Note: Only GPIO pins on Port0 and Port2 support this. If needed choose from spare pins
constexpr Pin COOLING_FAN_RPM_PIN = NoPin;

//Pins defined to use for external interrupt. **Must** be a pin on Port0 or Port2.
//I.e. for Fan RPM, Filament Detection etc
// We limit this to 3 to save memory
#define EXTERNAL_INTERRUPT_PINS {NoPin, NoPin, NoPin}



//SD: Internal SDCard is on SSP1
//    MOSI, MISO, SCLK, CS
//    P0_9, P0_8, P0_7, P0_6

//SD: 2nd SDCard can be connected to SSP0
//    MOSI, MISO, SCLK
//    P0_18 P0_17 P0_15

// SD cards
//sd:: Internal SD card is on SSP1
//NOTE::: Although this is 2nd in the List, SSP1 is Configured to be Slot0 in coreNG to be compatible with RRF
//default to supporting 2 card..... if need 1_23 then change CS no No pin

constexpr size_t NumSdCards = 2;//Note: use 2 even if only using 1 (internal) card
constexpr Pin SdCardDetectPins[NumSdCards] = { NoPin, P1_31 };
constexpr Pin SdWriteProtectPins[NumSdCards] = { NoPin, NoPin };
constexpr Pin SdSpiCSPins[NumSdCards] = { P0_6, P1_23};// Internal, external. If need 1_23 pin, and no ext sd card set to NoPin Note:: ("slot" 0 in CORE is configured to be LCP SSP1 to match default RRF behaviour)


// Definition of which pins we allow to be controlled using M42

constexpr Pin SpecialPinMap[] =
{
    //Note: PWM Channels 5 & 6 are used by the Hotend Heaters and cant be used.
    //servos
    //  LPC PIN         RAMPS
    //Servos
    P1_20, //60    Servo1   11      PWM1[2]
    P1_21, //61    Servo2    6      PWM1[3]
    P1_19, //62    Servo3    5
    P1_18, //63    Servo4    4      PWM1[1]    
    //Spare Endstops
    P1_26, //      Y-Min    14      PWM1[6] (do not use pwm - chan6 in use by heaters)
    P1_24, //      X-Min     3      PWM1[5] (do not use pwm - chan5 in use by heaters)

    //P0_27, //    Aux1  A3/57    // Conifigured as SPI Thermocouple CS
    P0_28, //    Aux1  A4/58

//J3
    //P0_15, // J3                  SCLK
    //P0_16, // J3
    //P1_23, // J3          53      PWM1[4]
    //P2_11, // J3          35
    //P1_31, // J3          49
    //P0_18, // J3                  MOSI
    //P2_6,  // J3/Aux2  A5/59
    //P0_17, // J3                  MISO
    //P3_25,  // J3          33      PWM1[2]
    //P3_26,  // J3          31      PWM1[3]

//J5
    //P1_22, // J5          41
    //P1_30  // J5          37
    //P1_21, //61    Servo2    6      PWM1[3] //overlaps with Servo2?? check me
    //P0_26, // J2/Aux2  A9/63


};


//TODO:: determine pins for LCD
//SPI LCD Common Settings (RRD Full Graphic Smart Display)
constexpr SSPChannel LcdSpiChannel = SSP0;     //SSP0 (MISO0, MOSI0, SCK0)
constexpr Pin LcdCSPin =       P0_16; //LCD Chip Select
constexpr Pin LcdDCPin =       P2_6;  //DataControl Pin (A0) if none used set to NoPin
constexpr Pin LcdBeepPin =     P1_30;
constexpr Pin EncoderPinA =    P3_25;
constexpr Pin EncoderPinB =    P3_26;
constexpr Pin EncoderPinSw =   P2_11; //click
constexpr Pin PanelButtonPin = P1_22; //Extra button on Viki and RRD Panels (reset/back etc configurable)

//VIKI2.0 Specific options
constexpr Pin VikiRedLedPin = NoPin;
constexpr Pin VikiBlueLedPin = NoPin;



#endif
