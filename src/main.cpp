#include <Arduino.h>
#include <EEPROM.h>
#include <string.h>
//#include <chrono>
//#include <thread>
#include "config\Configuration.h"
#include "config\PIN_DEFINITON.h"

String command = ""; // Variable zum Speichern des empfangenen Befehls

float rel_X_coord;
float rel_Y_coord;
float rel_Z_coord;

int arrow_dir = -99;
int arrow_stage = 0;

bool rel_coord_system;

double sq_factor = 1;

void extractValues(String cmd) {
  // Extrahieren Sie den X-Wert
  int xPos = cmd.indexOf('X');
  if (xPos != -1) {
    rel_X_coord = cmd.substring(xPos + 1).toFloat();
  }

  // Extrahieren Sie den Y-Wert
  int yPos = cmd.indexOf('Y');
  if (yPos != -1) {
    rel_Y_coord = cmd.substring(yPos + 1, cmd.indexOf(' ', yPos)).toFloat();
  }

  // Extrahieren Sie den Z-Wert
  int zPos = cmd.indexOf('Z');
  if (zPos != -1) {
    rel_Z_coord = cmd.substring(zPos + 1, cmd.indexOf(' ', zPos)).toFloat();
  }

  Serial.println(rel_X_coord);
  Serial.println(rel_Y_coord);
  Serial.println(rel_Z_coord);

  rel_X_coord = 0;
  rel_Y_coord = 0;
  rel_Z_coord = 0;
}

void write_coords_to_eeprom(bool rel, float x, float y, float z) {
  if (!rel) {
    EEPROM.write(ABS_X_COORD_EEPROM_ADDRESS, x);
    EEPROM.write(ABS_Y_COORD_EEPROM_ADDRESS, y);
    EEPROM.write(ABS_Z_COORD_EEPROM_ADDRESS, z);
  }
}




double use_pythagors_formula(float a, float b) {
  double c = 0;
  c = sqrt(a*a + b*b);
  return c;
}

float get_step_delay_in_micros(char axis) {

  int step_per_rev;
  float distance_per_rev;
  float feedrate;

  switch (axis) {
  case 'X':
    step_per_rev = STEPS_PER_REV_X_AXIS;
    distance_per_rev = DISTANCE_PER_REV_X_AXIS;
    feedrate = MAX_FEEDRATE_X_AXIS;
    break;
  case 'Y':
    step_per_rev = STEPS_PER_REV_Y_AXIS;
    distance_per_rev = DISTANCE_PER_REV_Y_AXIS;
    feedrate = MAX_FEEDRATE_X_AXIS;
    break;
  case 'Z':
    step_per_rev = STEPS_PER_REV_Z_AXIS;
    distance_per_rev = DISTANCE_PER_REV_Z_AXIS;
    feedrate = MAX_FEEDRATE_Z_AXIS;
    break;
  
  default:
    step_per_rev = 1600;
    distance_per_rev = 5;
    feedrate = 1000;

    break;
  }

  //d = (60*b)/(a/c)
  // a steps/rev
  // b way/rev
  // c feedrate



  return (60 * distance_per_rev) / (step_per_rev * feedrate) * 1000000;

}

float get_step_delay_in_micros(char axis, float feedrate) {

  int step_per_rev;
  float distance_per_rev;


  switch (axis) {
  case 'X':
    step_per_rev = STEPS_PER_REV_X_AXIS;
    distance_per_rev = DISTANCE_PER_REV_X_AXIS;
    break;
  case 'Y':
    step_per_rev = STEPS_PER_REV_Y_AXIS;
    distance_per_rev = DISTANCE_PER_REV_Y_AXIS;
    break;
  case 'Z':
    step_per_rev = STEPS_PER_REV_Z_AXIS;
    distance_per_rev = DISTANCE_PER_REV_Z_AXIS;
    break;
  
  default:
    step_per_rev = 1600;
    distance_per_rev = 5;

    break;
  }

  //d = (60*b)/(a/c)
  // a steps/rev
  // b way/rev
  // c feedrate



  return (60 * distance_per_rev) / (step_per_rev * feedrate) * 1000000;

}

int get_step_count(char axis, float dis) {
  int step_per_rev;
  float dis_per_rev;

  switch (axis) {
  case 'X':
    step_per_rev = STEPS_PER_REV_X_AXIS;
    dis_per_rev = DISTANCE_PER_REV_X_AXIS;
    break;
  case 'Y':
    step_per_rev = STEPS_PER_REV_Y_AXIS;
    dis_per_rev = DISTANCE_PER_REV_Y_AXIS;
    break;
  case 'Z':
    step_per_rev = STEPS_PER_REV_Z_AXIS;
    dis_per_rev = DISTANCE_PER_REV_Z_AXIS;
    break;
  default:
    step_per_rev = 1600;
    dis_per_rev = 5;
    break;
  }

  int step_count = (dis / dis_per_rev) * step_per_rev;
  return step_count;
}

bool arrow_movement = true;
unsigned long lastStepTime1 = 0;
unsigned long lastStepTime2 = 0;

int move_motor_by_arrow(int dir, int stage) {
    /*
    
    
    if (command.length() < 6) {
      Serial.println("Error -101");
      return 0
    */

    if (0 == 0)
    {
      /* code */
    }

  
    
    
    double speed_factor = stage * 0.2;
    int speed = 1000;
    bool arrow_movement = true;


    int step_duration_x = get_step_delay_in_micros('X', MAX_FEEDRATE_X_AXIS * speed_factor);
    int step_duration_y = get_step_delay_in_micros('Y', MAX_FEEDRATE_Y_AXIS * speed_factor);
    int step_duration_z = get_step_delay_in_micros('Z', MAX_FEEDRATE_Z_AXIS * speed_factor);

    
    unsigned long currentTimeMicros = micros();
    

    Serial.println(dir);

    switch (dir) {
    case 1:
    
      digitalWrite(PIN_DIR_Y, 1);
      Serial.println(arrow_movement);
          if (currentTimeMicros - lastStepTime1 >= step_duration_y) {
            digitalWrite(PIN_STEP_Y, 1);
            lastStepTime1 = currentTimeMicros;
          }
          
          if (currentTimeMicros - lastStepTime2 >= step_duration_y) {
            digitalWrite(PIN_STEP_Y, 0);
            lastStepTime2 = currentTimeMicros;
          }
      break;
    case 2:
      //
      break;
    case 3:
      //
      break;
    case 4:
      //
      break;
    case 5:
      //
      break;
    case 6:
      //
      break;
    case 7:
      //
      break;
    case 8:
      //
      break;
    case 9:
      //
      break;
    case 10:
      //
      break;
    case 99:
      arrow_movement = false;
      break;
    }
  return 1;
}

int process_serial_input(String command) {
  Serial.println(command);
  //    A01 S2
  if (command.substring(0, 1).equalsIgnoreCase("A")) {
    arrow_dir = command.substring(1,3).toInt();
    arrow_stage = command.substring(5, 6).toInt();
    Serial.println(arrow_stage);
  }
  
}

void setup() {
  rel_coord_system = true;
  sq_factor = sqrt(25) / 5;


  pinMode(PIN_DIR_X, OUTPUT);
  pinMode(PIN_DIR_Y, OUTPUT);
  pinMode(PIN_DIR_Z, OUTPUT);
  pinMode(PIN_STEP_X, OUTPUT);
  pinMode(PIN_STEP_Y, OUTPUT);
  pinMode(PIN_STEP_Z, OUTPUT);
  pinMode(ENABLE_STEPPER, OUTPUT);

  digitalWrite(ENABLE_STEPPER, 0);
  
  Serial.begin(115200); // Beginnen Sie die serielle Kommunikation mit einer Baudrate von 115200
  Serial.println("G-Code Interpreter gestartet."); // Startnachricht
  Serial.println(use_pythagors_formula(3, 2));
}



void loop() {


  // Überprüfen, ob Daten von der seriellen Schnittstelle empfangen wurden
  if (Serial.available() > 0) {
    // Lesen Sie die empfangenen Daten, bis kein Datenpunkt mehr verfügbar ist
    while (Serial.available() > 0) {
      // Lesen Sie das nächste verfügbare Zeichen
      char receivedChar = Serial.read();
      // Überprüfen, ob das Zeichen ein Zeilenumbruch ist, um den Befehl abzuschließen
      if (receivedChar == '\n') {
        // Wenn ein Zeilenumbruch empfangen wurde, führen Sie den Befehl aus
        process_serial_input(command);
        // Löschen Sie den Befehl für den nächsten
        command = "";
      } else {
        // Fügen Sie das empfangene Zeichen dem Befehl hinzu
        command += receivedChar;
      }
    }
  }
  if (arrow_dir != -99) {
  
    double speed_factor = arrow_stage * 0.2;
    int speed = 1000;
    bool arrow_movement = true;

    Serial.println(MAX_FEEDRATE_Y_AXIS * speed_factor);

    int step_duration_x = get_step_delay_in_micros('X', MAX_FEEDRATE_X_AXIS * speed_factor);
    int step_duration_y = get_step_delay_in_micros('Y', MAX_FEEDRATE_Y_AXIS * speed_factor);
    int step_duration_z = get_step_delay_in_micros('Z', MAX_FEEDRATE_Z_AXIS * speed_factor);

      
    unsigned long currentTimeMicros = micros();
      
    

    switch (arrow_dir) {
      case 1:
    
      digitalWrite(PIN_DIR_Y, 1);
      Serial.println(arrow_movement);
          if (currentTimeMicros - lastStepTime1 >= step_duration_y) {
            digitalWrite(PIN_STEP_Y, 1);
            lastStepTime1 = currentTimeMicros;
          }
          
          if (currentTimeMicros - lastStepTime2 >= step_duration_y) {
            digitalWrite(PIN_STEP_Y, 0);
            lastStepTime2 = currentTimeMicros;
          }
      break;
    case 2:
      //
      break;
    case 3:
      //
      break;
    case 4:
      //
      break;
    case 5:
      //
      break;
    case 6:
      //
      break;
    case 7:
      //
      break;
    case 8:
      //
      break;
    case 9:
      //
      break;
    case 10:
      //
      break;
    case 99:
      arrow_movement = false;
      break;
    }
  }

}

// Funktion zur Ausführung des empfangenen Befehls
void executeCommand(String cmd) {
  // Geben Sie den empfangenen Befehl auf dem seriellen Monitor aus
  Serial.println("Received command: " + cmd);
  
  // Extrahieren Sie den Befehlsteil aus dem G-Code-Befehl
  String gCode = cmd.substring(0, 1); // Extrahieren Sie den Buchstaben "G"
  String num = cmd.substring(1); // Extrahieren Sie die restliche Zeichenfolge (Zahlen)

  // Verarbeiten Sie den Befehl basierend auf dem G-Code und der Zahl
  if (gCode.equalsIgnoreCase("G")) {
    int gNumber = num.toInt(); // Konvertieren Sie die Zahl in eine Ganzzahl
    // Führen Sie die Aktion basierend auf der G-Code-Nummer aus
    switch (gNumber) {
      case 1:
        // Führen Sie die Aktion für den G1-Befehl aus
        Serial.println("G1 command received");
        // Hier können Sie den entsprechenden Code für den G1-Befehl einfügen
        break;
      case 2:
        // Führen Sie die Aktion für den G2-Befehl aus
        Serial.println("G2 command received");
        // Hier können Sie den entsprechenden Code für den G2-Befehl einfügen
        break;
      case 3:
        // Führen Sie die Aktion für den G3-Befehl aus
        Serial.println("G3 command received");
        // Hier können Sie den entsprechenden Code für den G3-Befehl einfügen
        break;
      default:
        // Ungültige G-Code-Nummer
        Serial.println("Invalid G-Code number");
        break;
    }
  } else {
    // Ungültiger G-Code-Befehl
    Serial.println("Invalid G-Code command");
  }
}

