int pins[] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 14, 15, 16, 17, 18, 19};

// Update with digitalReadStatus
int pinModeStatus = 0;

// Tank Level
const int tank_one_green = 2;
const int tank_one_blue = 3;
const int tank_one_yellow = 4;
const int tank_one_red = 5;

// sump level
int sump_green = 6;
int sump_black = 7;
int sump_red = 8;

// system status
int system_status = 9;

// voltage
int volatage_high = 14;
int voltage_low = 15;

// TODO Dry Run logic

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
    int tankLevel = digitalRead(19);

    // Find Tank 1 Water level
    tankLevel = checkTankLevel();
    Serial.print("Current Water Level : ");
    Serial.print(tankLevel);
    Serial.println("%");
}

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
            respArray[arrIndex] = getLevel(i);
        }
        arrIndex++;
    }
    currPerc = maxValOfArray(respArray);
    return currPerc;
}

int getLevel(int pinNo)
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

int maxValOfArray(int arr[])
{
    int maxVal = 0;
    for (int i = 1; i <= 4; i++)
    {
        if (arr[i] >= maxVal)
        {
            maxVal = arr[i];
        }
    }
    return maxVal;
}