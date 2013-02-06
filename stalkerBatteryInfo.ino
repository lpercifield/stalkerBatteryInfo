void setup()
{
  Serial.begin(57600);
  analogReference(INTERNAL);
  analogRead(6);
}
 
void loop() 
{
  char CH_status_print[][4]=
  {
    "off","on ","ok ","err"
  };
  unsigned char CHstatus = read_charge_status();//read the charge status
  Serial.print("charge status -->");
  Serial.println(CH_status_print[CHstatus]);
  Battery_voltage_read();
  delay(500);
}
 
 
unsigned char read_charge_status(void)
{
  unsigned char CH_Status=0;
  unsigned int ADC6=analogRead(6);
  if(ADC6>900)
  {
    CH_Status = 0;//sleeping
  }
  else if(ADC6>550)
  {
    CH_Status = 1;//charging
  }
  else if(ADC6>350)
  {
    CH_Status = 2;//done
  }
  else
  {
    CH_Status = 3;//error
  }
  return CH_Status;
}
//=====================================
void Battery_voltage_read(void)
{
  unsigned int bat_read = analogRead(7);

  //  (1/1024)*6=0.0064453125,
 float bat_voltage = (float)bat_read * 0.0064453125;

  Serial.print(" -->Battery data = ");
  Serial.println(bat_voltage);

  if(bat_read<570)// less than 3.48v
  {
    Serial.println("low battery, please recharge");
  }
  else if(bat_read>680)// more than 4.22 v
  {
    Serial.println("out of range, over charge?");
  }
  else
  {
    // battery is fine
  }
}
