# TCppPrown Arduino Library
Available as Arduino library "TCppPrown"

### [Version 3.5.2](https://github.com/Arduino-IRremote/Arduino-IRremote/archive/master.zip) - work in progress

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![Commits since latest](https://img.shields.io/github/commits-since/Arduino-IRremote/Arduino-IRremote/latest)](https://github.com/Arduino-IRremote/Arduino-IRremote/commits/master)
[![Installation instructions](https://www.ardu-badge.com/badge/IRremote.svg?)](https://www.ardu-badge.com/IRremote)
[![LibraryBuild](https://github.com/Arduino-IRremote/Arduino-IRremote/workflows/LibraryBuild/badge.svg)](https://github.com/Arduino-IRremote/Arduino-IRremote/actions)

This library enables you to send and receive using infra-red signals on an Arduino.

# Table of content
- [API](#api)
- [Installation](#installation)
- [Supported IR Protocols](#supported-ir-protocols)
- [Old Wiki](#old-wiki)
- [Features of the 3.x version](#features-of-the-3x-version)
  * [Converting your 2.x program to the 3.x version](#converting-your-2x-program-to-the-3x-version)
    + [Example](#example)
  * [Do not want to convert your 2.x program and use the 3.x library version?](#do-not-want-to-convert-your-2x-program-and-use-the-3x-library-version)
  * [How to convert old MSB first 32 bit IR data codes to new LSB first 32 bit IR data codes](#how-to-convert-old-msb-first-32-bit-ir-data-codes-to-new-lsb-first-32-bit-ir-data-codes)
- [Receiving IR codes](#receiving-ir-codes)
  * [Minimal NEC receiver](#minimal-nec-receiver)
- [Sending IR codes](#sending-ir-codes)
    + [List of public IR code databases](#list-of-public-ir-code-databases)
- [FAQ and hints](#faq-and-hints)
- [Handling unknown Protocols](#handling-unknown-protocols)
  * [Disclaimer](#disclaimer)
  * [Protocol=PULSE_DISTANCE](#protocolpulse_distance)
  * [Protocol=UNKNOWN](#protocolunknown)
  * [How to deal with protocols not supported by IRremote](#how-to-deal-with-protocols-not-supported-by-irremote)
- [Examples for this library](#examples-for-this-library)
- [Compile options / macros for this library](#compile-options--macros-for-this-library)
    + [Changing include (*.h) files with Arduino IDE](#changing-include-h-files-with-arduino-ide)
    + [Modifying compile options with Sloeber IDE](#modifying-compile-options-with-sloeber-ide)
- [Supported Boards](#supported-boards)
- [Timer and pin usage](#timer-and-pin-usage)
    + [Incompatibilities to other libraries and Arduino commands like tone() and analogWrite()](#incompatibilities-to-other-libraries-and-arduino-commands-like-tone-and-analogwrite)
    + [Hardware-PWM signal generation for sending](#hardware-pwm-signal-generation-for-sending)
    + [Why do we use 33% duty cycle](#why-do-we-use-33-duty-cycle)
    
- [NEC encoding diagrams](#nec-encoding-diagrams)
- [Quick comparison of 4 Arduino IR receiving libraries](#quick-comparison-of-4-arduino-ir-receiving-libraries)
- [Revision History](#revision-history)
- [Contributing](#contributing)
  * [Adding new protocols](#adding-new-protocols)
    + [Integration](#integration)
    + [Creating API documentation](#creating-api-documentation)
  * [Contributors](#contributors)
- [License](#license)
  * [Copyright](#copyright)

# API
A Doxygen documentation of the sources is available on the [project homepage](https://arduino-irremote.github.io/Arduino-IRremote/classIRrecv.html).

# Installation
Click on the LibraryManager badge above to see the [instructions](https://www.ardu-badge.com/IRremote/zip).

# Supported IR Protocols
Denon / Sharp, JVC, LG,  NEC / Onkyo / Apple, Panasonic / Kaseikyo, RC5, RC6, Samsung, Sony, (Pronto), BoseWave, Lego, Whynter and optional MagiQuest.<br/>
Protocols can be switched off and on by defining macros before the line `#include <IRremote.hpp>` like [here](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino#L14):

```c++
#define DECODE_NEC
//#define DECODE_DENON
#include <IRremote.hpp>
```

# [Old Wiki](https://github.com/Arduino-IRremote/Arduino-IRremote/wiki)
This is a quite old but maybe useful [wiki](https://github.com/Arduino-IRremote/Arduino-IRremote/wiki) for this library.

# Features of the 3.x version
- You can use any pin for sending now, like you are used with receiving.
- Simultaneous sending and receiving. See the [SendAndReceive](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SendAndReceive/SendAndReceive.ino#L167-L170) example.
- No more need to use 32 bit hex values in your code. Instead a (8 bit) command value is provided for decoding (as well as an 16 bit address and a protocol number).
- Protocol values comply to protocol standards, i.e. NEC, Panasonic, Sony, Samsung and JVC decode and send LSB first.
- Supports more protocols, since adding a protocol is quite easy now.
- Better documentation and more examples :-).
- Compatible with tone() library, see [ReceiveDemo](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/21b5747a58e9d47c9e3f1beb056d58c875a92b47/examples/ReceiveDemo/ReceiveDemo.ino#L159-L169).
- Supports more platforms, since the new structure allows to easily add a new platform.
- Feedback LED also for sending.
- Ability to generate a non PWM signal to just simulate an active low receiver signal for direct connect to existent receiving devices without using IR.
- Easy configuration of protocols required, directly in your [source code](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/SimpleReceiver/SimpleReceiver.ino#L33-L57). This reduces the memory footprint and increases decoding time.


## Converting your 2.x program to the 3.x version
Starting with the 3.1 version, **the generation of PWM for sending is done by software**, thus saving the hardware timer and **enabling arbitrary output pins for sending**.<br/>
If you use an (old) Arduino core that does not use the `-flto` flag for compile, you can activate the line `#define SUPPRESS_ERROR_MESSAGE_FOR_BEGIN` in IRRemote.h, if you get false error messages regarding begin() during compilation.

- Now there is  an **IRreceiver** and **IRsender** object like the well known Arduino **Serial** object.
- Just remove the line `IRrecv IrReceiver(IR_RECEIVE_PIN);` and/or `IRsend IrSender;` in your program, and replace all occurrences of `IRrecv.` or `irrecv.` with `IrReceiver` and replace all `IRsend` or `irsend` with `IrSender`.
- Since the decoded values are now in `IrReceiver.decodedIRData` and not in `results` any more, remove the line `decode_results results` or similar.
- Like for the Serial object, call [`IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);`](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/examples/ReceiveDemo/ReceiveDemo.ino#L106)
 or `IrReceiver.begin(IR_RECEIVE_PIN, DISABLE_LED_FEEDBACK);` instead of the `IrReceiver.enableIRIn();` or `irrecv.enableIRIn();` in setup(). For sending, call `IrSender.begin(IR_SEND_PIN, ENABLE_LED_FEEDBACK);` or `IrSender.begin(IR_SEND_PIN, DISABLE_LED_FEEDBACK);` in setup().
- Old `decode(decode_results *aResults)` function is replaced by simple `decode()`. So if you have a statement `if(irrecv.decode(&results))` replace it with `if (IrReceiver.decode())`.
- The decoded result is now in in `IrReceiver.decodedIRData` and not in `results` any more, therefore replace any occurrences of `results.value` and `results.decode_type` (and similar) to
 `IrReceiver.decodedIRData.decodedRawData` and `IrReceiver.decodedIRData.protocol`.
- Overflow, Repeat and other flags are now in [`IrReceiver.receivedIRData.flags`](https://github.com/Arduino-IRremote/Arduino-IRremote/blob/master/src/IRremoteInt.h#L164-L187).
- Seldom used: `results.rawbuf` and `results.rawlen` must be replaced by `IrReceiver.decodedIRData.rawDataPtr->rawbuf` and `IrReceiver.decodedIRData.rawDataPtr->rawlen`.

### Example
#### 2.x program:

```c++
#include <IRremote.h>

IRrecv irrecv(RECV_PIN);
decode_results results;

void setup()
{
...
  irrecv.enableIRIn(); // Start the receiver
}

void loop() {
  if (irrecv.decode(&results)) {
      Serial.println(results.value, HEX);
      ...
      irrecv.resume(); // Receive the next value
  }
  ...
}
```

#### 3.x program:

```c++
#include <IRremote.hpp>

void setup()
{
...
  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop() {
  if (IrReceiver.decode()) {
      Serial.println(IrReceiver.decodedIRData.decodedRawData, HEX);
      IrReceiver.printIRResultShort(&Serial); // optional use new print version
      ...
      IrReceiver.resume(); // Enable receiving of the next value
  }
  ...
}
```

## Do not want to convert your 2.x program and use the 3.x library version?
First consider to just use the [original 2.4 release form 2017](https://github.com/Arduino-IRremote/Arduino-IRremote/releases/tag/v2.4.0)
or the last backwards compatible [2.8 version](https://github.com/Arduino-IRremote/Arduino-IRremote/releases/tag/2.8.0) for you project.
It may be sufficient and deals flawlessly with 32 bit IR codes.<br/>
If not, the 3.x versions try to be backwards compatible, so you can easily run your old examples. But some functions like e.g. `sendNEC()` -see below- could not made backwards compatible.
The (old and deprecated) call of `irrecv.decode(&results)` uses the old MSB first decoders like in 2.x and sets the 32 bit codes in `results.value`!<br/>
But only the following decoders are available then: Denon, JVC, LG,  NEC, Panasonic, RC5, RC6, Samsung, Sony.

The old functions `sendNEC()` and `sendJVC()` are deprecated and renamed to `sendNECMSB()` and `sendJVCMSB()`,
to make it clearer that they send data with MSB first, which is not the standard for NEC and JVC.
Use them to send your **old MSB-first 32 bit IR data codes**.
In the new version you will send NEC (and other) commands not by 32 bit codes but by a (constant) 8 bit address and an 8 bit command.

## How to convert old MSB first 32 bit IR data codes to new LSB first 32 bit IR data codes
For the new decoders for **NEC, Panasonic, Sony, Samsung and JVC**, the result `IrReceiver.decodedIRData.decodedRawData` is now **LSB-first**, as the definition of these protocols suggests!<br/>
To convert one into the other, you must reverse the byte/nibble positions and then reverse all bit positions of each byte/nibble or write it as one binary string and reverse/mirror it.<br/><br/>
Example:
- 0xCB340102 byte reverse -> 02 01 34 CB. Bit reverse of byte -> 40 80 2C D3.
- 0xCB340102 nibble reverse -> 201043BC. Bit reverse of nibble -> 40802CD3.<br/>
  Nibble reverse map: | 1->8 | 2->4 | 3->C | 4->2 | 5->A | 6->6 | 7->E | 8->1 | 9->9 | A->5 | B->D | C->3 | D->B | E->7 | F->F |
- 0xCB340102 is binary 11001011001101000000000100000010.<br/>
  0x40802CD3 is binary 01000000100000000010110011010011.<br/>
  If you read the first binary sequence backwards (right to left), you get the second sequence.
