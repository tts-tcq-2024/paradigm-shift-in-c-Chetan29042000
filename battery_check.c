#include <stdio.h>
#include "battery_check.h"

// Initializing flags for enabling/disabling warnings
int enable_temp_warning = 1;
int enable_soc_warning = 1;
int enable_charge_rate_warning = 1;

int check_temperature(float temperature){
    if(temperature < 0 || temperature > TEMP_UPPER_LIMIT) {
        printf("Temperature out of range!\n");
        return 0;
    } 
    if (enable_temp_warning) {
        if (temperature >= TEMP_UPPER_LIMIT - TEMP_WARNING_TOLERANCE && temperature <= TEMP_UPPER_LIMIT) {
            printf("Warning: Approaching temperature peak!\n");
        }
    }
    return 1;  
}

int check_soc(float soc){
    if(soc < 20 || soc > SOC_UPPER_LIMIT) {
        printf("State of Charge out of range!\n");
        return 0;
    } 
    if (enable_soc_warning) {
        if (soc >= 20 && soc <= 20 + SOC_WARNING_TOLERANCE) {
            printf("Warning: Approaching discharge!\n");
        } else if (soc >= SOC_UPPER_LIMIT - SOC_WARNING_TOLERANCE && soc <= SOC_UPPER_LIMIT) {
            printf("Warning: Approaching charge-peak!\n");
        }
    }
    return 1;  
}

int check_chargeRate(float chargeRate){
    if(chargeRate > CHARGE_RATE_UPPER_LIMIT) {
        printf("Charge Rate out of range!\n");
        return 0;
    } 
    if (enable_charge_rate_warning) {
        if (chargeRate >= CHARGE_RATE_UPPER_LIMIT - CHARGE_RATE_WARNING_TOLERANCE && chargeRate <= CHARGE_RATE_UPPER_LIMIT) {
            printf("Warning: Approaching charge rate peak!\n");
        }
    }
    return 1;  
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
  return check_temperature(temperature) && check_soc(soc) && check_chargeRate(chargeRate);
}
