int increment = 10;

void setup() {
	Serial.begin(115200);
  Serial.println("The increment variable is: " + String(increment));
}

void loop() {
	  increment += 10;
    delay(500); // Wait 500ms
    Serial.println("Increment variable is now: " + String(increment));
}