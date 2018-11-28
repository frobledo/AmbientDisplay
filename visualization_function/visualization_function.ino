void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}

void visualization(int heartRate)
{
  int wait = 0; 
  int x = 0; 
  int subjectiveStress = analogRead(sliderPin); 

  if (heartRate <= 100 && subjectiveStress < 250){
    Serial.println("Normal heart rate + low stress");
    wait = 50; 
    for(int i = 0; i< 100; i++){
      colorWipe(strip.Color(255, 255, 255), wait);
      colorWipe(strip.Color(0, 174,255), wait);
    }
  }

  else if (heartRate <= 100 && subjectiveStress < 500){
    Serial.println("Normal heart rate + moderate stress");
    wait = 50; 
    for(int i = 0; i< 100; i++){
      colorWipe(strip.Color(0, 170, 255), wait); 
      colorWipe(strip.Color(0, 128, 2), wait); 
    }
  }

  else if (heartRate <= 100 && subjectiveStress < 750){
    wait = 50; 
    Serial.println("Normal heart rate + high stress");
    for(int i = 0; i< 100; i++){
      colorWipe(strip.Color(217, 255, 0), wait); 
      colorWipe(strip.Color(255, 145, 0), wait); 
    }
  }

  else if (heartRate <= 100 && subjectiveStress >= 750){
    wait = 50; 
    Serial.println("Normal heart rate + excessive stress");
    for(int i = 0; i< 100; i++){
      colorWipe(strip.Color(255, 102, 0), wait); 
      colorWipe(strip.Color(255, 0, 157), wait);
    }  
  }

  else if(subjectiveStress < 250){
    wait = heartRate/10; 
    
    Serial.println("High heart rate + low stress");
    
    while(wait<100) {
      colorWipe(strip.Color(0, 170, 255), wait); 
      colorWipe(strip.Color(0, 128, 2), wait); 
      wait++; 
    } 
    
  }

  else if(heartRate > 100 && subjectiveStress < 500){
    wait = heartRate/15; 
    Serial.println("High heart rate + moderate stress");
    
    while (wait < 100){
      colorWipe(strip.Color(217, 255, 0), wait); 
      colorWipe(strip.Color(255, 145, 0), wait); 
      wait++; 
    } 
  }
  
  else if(heartRate > 100 && subjectiveStress < 750){
    wait = heartRate/20; 
    Serial.println("High heart rate + high stress");
     
    while (wait <100) {
      colorWipe(strip.Color(255, 102, 0), wait); 
      colorWipe(strip.Color(255, 0, 157), wait); 
      wait++; 
    } while (wait <100);
  }

  else if(heartRate > 100 && subjectiveStress >= 750){
     wait = heartRate/25; 
     Serial.println("High heart rate + excessive stress");
     
     while (wait < 100) {
      colorWipe(strip.Color(255, 0, 38), wait); 
      colorWipe(strip.Color(162, 0, 255), wait); 
      wait++; 
    }
  }
}
