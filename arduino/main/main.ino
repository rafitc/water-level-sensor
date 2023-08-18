int pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16, 17, 18, 19};

// Update with digitalReadStatus
int pinModeStatus = 0;

// Tank Level
const int tank_one_green = 2;
const int tank_one_blue = 3;
const int tank_one_yellow = 4;
const int tank_one_red = 5;

// sump level
const int sump_green = 6;
const int sump_black = 7;
const int sump_red = 8;

// system status
int system_status = 9;

// voltage
int volatage_high = 14;
int voltage_low = 15;

// TODO Dry Run logic
int pump = 16;
int dry_run = 17;

void setup()
{
    // put your setup code here, to run once:
    Serial.begin(9600);

    // init as output pin
    for (int i = 0; i <= 15; i++)
    {
        pinMode(pins[i], INPUT_PULLUP);
    }
}

void loop()
{
    // put your main code here, to run repeatedly:
    int tankLevel =0, sumpLevel = 0;
    int pumping = 0; //pumping = 0 is dry run and pumping = 1 is not dry run

    // Find Tank 1 Water level
    tankLevel = checkTankLevel();
    Serial.print("Current Tank Water Level : ");
    Serial.print(tankLevel);
    Serial.println("%");

    // Find SUMP water level 
    sumpLevel = checkSumpLevel();
    Serial.print("Current Sump Water Level : ");
    Serial.print(sumpLevel);
    Serial.println("%");
    delay(100);

    //dry run logic 
    pumping = checkPumpingStatus();
    if (pumping){
        Serial.print("Pumping \n");
    }
    else{
        Serial.println("DRY RUN !!!!\n");
    }


}
//------Functions for Tank 
int checkTankLevel()
{
    int respArray[] = {0, 0, 0, 0};
    int arrIndex = 0;
    int currPerc = 0;

    for (int i = 2; i <= 5; i++)
    {
        int pinStatus = digitalRead(i);
        if (pinStatus == pinModeStatus)
        {
            respArray[arrIndex] = getLevelOfTank(i);
        }
        arrIndex++;
    }
    currPerc = maxValOfArray(respArray);
    return currPerc;
} 

int getLevelOfTank(int pinNo)
{
    int perc = 0;
    switch (pinNo)
    {

    case tank_one_green: // level 1 - pin 2
        perc = 100;
        break;

    case tank_one_blue: // level 2 - pin 3
        perc = 75;
        break;

    case tank_one_yellow: // level 3 - pin 4
        perc = 50;
        break;

    case tank_one_red: // level 4 - pin 5
        perc = 25;
        break;

    default:
        perc = 0;
        break;
    }

    return perc;
}

//----------Functions for SUMP 

int checkSumpLevel()
{
    int respArray[] = {0, 0, 0, 0};
    int arrIndex = 0;
    int currPerc = 0;

    for (int i = 6; i <= 8; i++) {

        int pinStatus = digitalRead(i);
        if (pinStatus == pinModeStatus)
        {
            respArray[arrIndex] = getLevelOfSump(i);
        }
        arrIndex++;
    }
    currPerc = maxValOfArray(respArray);
    return currPerc;
} 

int getLevelOfSump(int pinNo)
{
    int perc = 0;
    switch (pinNo) {
    case sump_green: // level 1 - pin 6
        perc = 100;
        break;

    case sump_black: // level 2 - pin 7
        perc = 70;
        break;

    case sump_red: // level 3 - pin 8
        perc = 40;
        break;

    default:
        perc = 0;
        break;
    }

    return perc;
}

//------Gen Functions 
int maxValOfArray(int arr[])
{
    int maxVal = 0;
    for (int i = 0; i <= 3; i++)
    {
        if (arr[i] >= maxVal)
        {
            maxVal = arr[i];
        }
    }
    return maxVal;
}

//------------ Function for dry Run/pumping status 
int checkPumpingStatus(){
    const long interval = 3000; // 3 Sec interval
    unsigned long previousMillis = millis();
    bool breakFlag = false;
    int foundPumping = 0;
    int pumpStatus = 0; //Let dry run the motor 

    while (true){
        unsigned long currentMillis = millis();
        if (breakFlag){
            break;
        }

        if (currentMillis - previousMillis >= interval) {
            // add return statement
            // if pumpStatus is not updated in 3 sec. which means it is dry running 
            return pumpStatus;
        }

        // Check the pump 
        foundPumping = digitalRead(pump);
        if (foundPumping == pinModeStatus){
            if (foundPumping == HIGH){
                // found pumping 
                pumpStatus = 1;
                return pumpStatus;
            }
        }
    }

}
