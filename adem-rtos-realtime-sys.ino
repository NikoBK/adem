int increment = 10;
bool verbose = false;

void setup() {
	Serial.begin(115200);
  if (verbose) {
    Serial.println("The increment variable is: " + String(increment));
  }
}

void loop() {
	  increment += 10;
    delay(500); // Wait 500ms
    if (verbose) {
      Serial.println("Increment variable is now: " + String(increment));
    }
}