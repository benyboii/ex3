/******************
Name: Ben Bar
ID: 212234363
Assignment: ex3
*******************/

#include <stdio.h>

#define NUM_OF_BRANDS 5
#define BRANDS_NAMES 15
#define NUM_OF_TYPES 4
#define TYPES_NAMES 10
#define DAYS_IN_YEAR 365
#define ADD_ONE  1
#define ADD_ALL  2  
#define STATS  3
#define DELTAS  6
#define DONE  7
#define TOYOGA_INDEX 0
#define HYUNNIGHT_INDEX 1
#define MAZDUH_INDEX 2
#define FOLKSVEGAN_INDEX 3
#define KEYYUH_INDEX 4
#define SUV_INDEX 0
#define SEDAN_INDEX 1
#define COUPE_INDEX 2
#define GT_INDEX 3
#define NO_INPUT 0
#define INPUTTED 1
#define PRINT_DATA_SET 4
#define INSIGHTS 5
char brands[NUM_OF_BRANDS][BRANDS_NAMES] = {"Toyoga", "HyunNight", "Mazduh", "FolksVegan", "Key-Yuh"};
char types[NUM_OF_TYPES][TYPES_NAMES] = {"SUV", "Sedan", "Coupe", "GT"};
//prints strings char by char until '\0'
void printString(char output[BRANDS_NAMES]) {
    int i = 0;
    while (output[i] != '\0') {
        printf("%c", output[i]);
        i++;
    }
}
int sumArray(int array[DAYS_IN_YEAR],int arraySize) {
    int sum = 0;
    for(int i = 0;i<arraySize;i++) {
        sum+=array[i];
    }
    return sum;
}
void initdbtArray(int dbtArray[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES]){
    for(int i= 0;i<DAYS_IN_YEAR;i++){
        for(int j= 0;j<NUM_OF_BRANDS;j++){
            for(int k= 0;k<NUM_OF_TYPES;k++){
                dbtArray[i][j][k] = -1;
      }
    }
  }
}
//finds max value in given array and puts it at the first index and his original index at the second index
void getBestValue(int arraySize,int values[DAYS_IN_YEAR]) {
    int maxValue = 0;
    int maxIndex = 0;
    for(int i = 0;i<arraySize;i++) {
        if(maxValue < values[i]) {
            maxValue = values[i];
            maxIndex = i;
        }
    }
    values[0] = maxValue;
    values[1] = maxIndex;
}
void insertDBTValue(int brandIndex,int dailySales[NUM_OF_TYPES],int dbtArray[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int brandDayCounter) {
    dbtArray[brandDayCounter][brandIndex][SUV_INDEX] = dailySales[SUV_INDEX];
    dbtArray[brandDayCounter][brandIndex][SEDAN_INDEX] = dailySales[SEDAN_INDEX];
    dbtArray[brandDayCounter][brandIndex][COUPE_INDEX] = dailySales[COUPE_INDEX];
    dbtArray[brandDayCounter][brandIndex][GT_INDEX] = dailySales[GT_INDEX];
}
void printMenu(){
    printf("Welcome to the Cars Data Cube! What would you like to do?\n"
           "1.Enter Daily Data For A Brand\n"
           "2.Populate A Day Of Sales For All Brands\n"
           "3.Provide Daily Stats\n"
           "4.Print All Data\n"
           "5.Provide Overall (simple) Insights\n"
           "6.Provide Average Delta Metrics\n"
           "7.exit\n");
}
void addOneFunc(int dbtArray[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int brandDayCounter){
    int brandIndex = 0;
    int dailySum[NUM_OF_TYPES] = {0};
    int numOfInputs = 0;
    printf("Please enter the brand index and the 4 daily sale sums for each type:\n");
    numOfInputs = scanf(" %d %d %d %d %d",&brandIndex , &dailySum[SUV_INDEX] , &dailySum[SEDAN_INDEX] , &dailySum[COUPE_INDEX], &dailySum[GT_INDEX]);
    while(numOfInputs != NUM_OF_TYPES + 1 || brandIndex < 0 ||brandIndex >= NUM_OF_BRANDS){
        printf("This brand is not valid.\n");
        printf("Please enter the brand index and the 4 daily sale sums for each type:\n");
        numOfInputs = scanf(" %d %d %d %d %d",&brandIndex , &dailySum[SUV_INDEX] , &dailySum[SEDAN_INDEX] , &dailySum[COUPE_INDEX] , &dailySum[GT_INDEX]);
    }
    insertDBTValue(brandIndex, dailySum,dbtArray,brandDayCounter);
}
void missingBrandsPrint(int brandsInputted[NUM_OF_BRANDS]) {
    printf("No data for brands");
    for(int brand = 0;brand<NUM_OF_BRANDS;brand++) {
        if(brandsInputted[brand] == NO_INPUT) {
            printf(" ");
            printString(brands[brand]);
        }
    }
    printf("\nPlease complete the data\n");
}
int addAllFunc(int dbtArray[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int brandDayCounter) {
    int brandIndex = 0;
    int brandsInputted[NUM_OF_BRANDS] = {0};
    int dailySum[NUM_OF_TYPES] = {0};
    int numOfInputs = 0;
    do {
        missingBrandsPrint(brandsInputted);
        numOfInputs = scanf(" %d %d %d %d %d",&brandIndex , &dailySum[SUV_INDEX] , &dailySum[SEDAN_INDEX] , &dailySum[COUPE_INDEX] , &dailySum[GT_INDEX]);
        while(numOfInputs != NUM_OF_TYPES + 1 ||
            brandIndex >= NUM_OF_BRANDS ||
            brandIndex < 0 ||
            brandsInputted[brandIndex] != NO_INPUT) {
            printf("This brand is not valid.\n");
            missingBrandsPrint(brandsInputted);
            numOfInputs = scanf(" %d %d %d %d %d",&brandIndex , &dailySum[SUV_INDEX] , &dailySum[SEDAN_INDEX] , &dailySum[COUPE_INDEX] , &dailySum[GT_INDEX]);
        }
        brandsInputted[brandIndex] = INPUTTED;
        insertDBTValue(brandIndex, dailySum,dbtArray,brandDayCounter);
    }
    while(brandsInputted[TOYOGA_INDEX] == NO_INPUT ||
        brandsInputted[HYUNNIGHT_INDEX] == NO_INPUT ||
        brandsInputted[MAZDUH_INDEX] == NO_INPUT ||
        brandsInputted[FOLKSVEGAN_INDEX] == NO_INPUT ||
        brandsInputted[KEYYUH_INDEX] == NO_INPUT);
        return brandDayCounter + 1;
}
void printStats(int dbtArray[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int brandDayCounter) {
    int day = 0;
    int salesTotal = 0;
    int maxBrandSales = 0;
    int maxBrandSalesIndex = -1;
    int maxTypeSales = 0;
    int maxTypeSalesIndex = 0;
    int typeSales[NUM_OF_TYPES] = {0};
    int temp = 0;
    int i = 0;
    printf("What day would you like to analyze?\n");
    scanf(" %d", &day);
    day--;
    while(day >= brandDayCounter || day < 0 || day >= DAYS_IN_YEAR) {
        printf("Please enter a valid day.\n");
        scanf("%d", &day);
        day--;
    }
    for(i = 0;i<NUM_OF_BRANDS;i++) {
        temp = 0;
        for(int j = 0;j<NUM_OF_TYPES;j++) {
            temp += dbtArray[day][i][j];
            typeSales[j] += temp;
        }
        salesTotal += temp;
        if(temp > maxBrandSales) {
            maxBrandSales = temp;
            maxBrandSalesIndex = i;
        }
    }
    getBestValue(NUM_OF_TYPES, typeSales);
    maxTypeSales = typeSales[0];
    maxTypeSalesIndex = typeSales[1];
    day++;
    printf("In day number %d ",day);
    printf("the sales total was %d\n",salesTotal);
    printf("The best sold brand with %d sales was ",maxBrandSales);
    printString(brands[maxBrandSalesIndex]);
    printf("\nThe best sold type with %d sales was ",maxTypeSales);
    printString(types[maxTypeSalesIndex]);
    printf("\n");
}
void printDataSet(int dbtArray[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int brandDayCounter) {
    printf("*****************************************\n\n");
    for(int brand = 0;brand<NUM_OF_BRANDS;brand++) {
        printf("Sales of ");
        printString(brands[brand]);
        printf(":\n");
        for(int day = 0;day<brandDayCounter;day++) {
            printf("Day %d-",day + 1);
            for(int type = 0;type<NUM_OF_TYPES;type++) {
                printf(" ");
                printString(types[type]);
                printf(": %d",dbtArray[day][brand][type]);
            }
            printf("\n");
        }
    }
    printf("\n\n*****************************************\n");
}
void printInsights(int bestDaySum,int bestDayIndex,int brandSales[NUM_OF_BRANDS],int typeSales[NUM_OF_TYPES]) {
    getBestValue(NUM_OF_BRANDS,brandSales);
    int bestBrandSum = brandSales[0];
    int bestBrandIndex = brandSales[1];
    getBestValue(NUM_OF_TYPES,typeSales);
    int bestTypeSum = typeSales[0];
    int bestTypeIndex = typeSales[1];
    printf("The best-selling brand overall is ");
    printString(brands[bestBrandIndex]);
    printf(":%d$\n",bestBrandSum);
    printf("The best-selling type of car is ");
    printString(types[bestTypeIndex]);
    printf(":%d$\n",bestTypeSum);
    printf("The most profitable day was day number %d:%d$\n",bestDayIndex + 1,bestDaySum);//our 0 day is the users 1 day
}
void insightsFunc(int dbtArray[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int brandDayCounter) {
    int bestDayBrandSum = 0;
    int bestDayBrandIndex = 0;
    int brandSales[NUM_OF_BRANDS] = {0};
    int typeSales[NUM_OF_TYPES] = {0};
    int tempBrandDaySum = 0;
    for(int day = 0;day < brandDayCounter;day++) {
        for(int brand = 0;brand < NUM_OF_BRANDS;brand++) {
            tempBrandDaySum = sumArray(dbtArray[day][brand],NUM_OF_TYPES);
            brandSales[brand] += tempBrandDaySum;
            for(int type = 0;type < NUM_OF_TYPES;type++) {
                typeSales[type] += dbtArray[day][brand][type];
            }
        }
        if(tempBrandDaySum > bestDayBrandSum) {
            bestDayBrandSum = tempBrandDaySum;
            bestDayBrandIndex = day;
        }
    }
    printInsights(bestDayBrandSum,bestDayBrandIndex,brandSales,typeSales);
}
void deltasFunc(int dbtArray[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES],int brandDayCounter) {
    int lastDaySales = 0;
    int delta = 0;
    int currentDaySales = 0;
    float averageDelta = 0;
    for(int brand = 0; brand < NUM_OF_BRANDS;brand++) {
        lastDaySales = sumArray(dbtArray[0][brand],NUM_OF_TYPES);
        for(int day = 1; day < brandDayCounter; day++) {
            currentDaySales = sumArray(dbtArray[day][brand],NUM_OF_TYPES);
            delta += currentDaySales - lastDaySales;
            lastDaySales = currentDaySales;
        }
        averageDelta = (float)delta / (float)(brandDayCounter+ 1);
        printf("Brand: ");
        printString(brands[brand]);
        printf(", Average Delta: %f\n",averageDelta);
    }

}
int main() {
    int dbtArray[DAYS_IN_YEAR][NUM_OF_BRANDS][NUM_OF_TYPES];
    int brandDayCounter = 0;
    initdbtArray(dbtArray);
    int choice;
    printMenu();
    scanf("%d", &choice);
    while(choice != DONE){
        switch(choice){
            case ADD_ONE:
                addOneFunc(dbtArray,brandDayCounter);
                break;
            case ADD_ALL:
                brandDayCounter = addAllFunc(dbtArray,brandDayCounter);
                break;
            case STATS:
                printStats(dbtArray,brandDayCounter);
                break;
            case PRINT_DATA_SET:
                printDataSet(dbtArray,brandDayCounter);
                break;
            case INSIGHTS:
                insightsFunc(dbtArray,brandDayCounter);
                break;
            case DELTAS:
                deltasFunc(dbtArray,brandDayCounter);
                break;
            default:
                printf("Invalid input\n");
        }
        printMenu();
        scanf("%d", &choice);
    }
    printf("Goodbye!\n");
    return 0;
}