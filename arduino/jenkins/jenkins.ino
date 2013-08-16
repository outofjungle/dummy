#define LED_RED 3
#define LED_GREEN 5
#define LED_BLUE 6
#define LED_WHITE 9
#define SPEAKER_PIN 10
#define DELAY 1000.0

char state;
char current_state;
double shift;

void setup() {
  Serial.begin(9600);
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(LED_WHITE, OUTPUT);
  pinMode(SPEAKER_PIN, OUTPUT);

  shift = DELAY/(4 * DELAY);
  
  int boot = millis() + 5000;
  
  do {
    double theta = millis()/DELAY;
    switch_on( LED_RED, theta );
    switch_on( LED_GREEN, theta + 1*shift );
    switch_on( LED_BLUE, theta + 2*shift );
    switch_on( LED_WHITE, theta + 3*shift );
  } while ( millis() < boot );
  switch_off();
}

void loop() {
  double theta = millis()/DELAY;

  if ( Serial.available() ) {
    current_state = Serial.read();
  }

  if ( state != current_state ) {
    switch_off();
    state = current_state;
  }

  if ( state == 'F' ) {
    switch_on( LED_RED, theta );
    tone(SPEAKER_PIN, millis() % 1000 );
  } else if ( state == 'S' ) {
    analogWrite( LED_GREEN, 255 );
  }
}

void switch_on( int pin, double theta ) {
  analogWrite( pin, 128.0 + 128 * sin( theta * 2.0 * PI  ) );    
}

void switch_off() {
    analogWrite( LED_RED, 0 );
    analogWrite( LED_GREEN, 0 );
    analogWrite( LED_BLUE, 0 );
    analogWrite( LED_WHITE, 0 );
    noTone( SPEAKER_PIN );
}

