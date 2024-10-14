#include <stdio.h>
#include "battery_check.h"

// Initializing flags for enabling/disabling warnings
int enable_temp_warning = 1;
int enable_soc_warning = 1;
int enable_charge_rate_warning = 1;

int is_within_range(float value, float lower, float upper, const char* error_message) {
    if (value < lower || value > upper) {
        printf("%s out of range!\n", error_message);
        return 0;
    }
    return 1;
}

void check_warning(float value, float upper_limit, float tolerance, int enable_warning, const char* warning_message) {
    // Calculate if warning condition is met as a boolean-like (1 or 0) value
    int should_warn = enable_warning * (value >= upper_limit - tolerance) * (value <= upper_limit);
    
    // Use multiplication to ensure printf only gets called when should_warn is 1
    should_warn && printf("Warning: %s\n", warning_message);
}
int check_temperature(float temperature) {
    if (!is_within_range(temperature, 0, TEMP_UPPER_LIMIT, "Temperature")) {
        return 0;
    }
    check_warning(temperature, TEMP_UPPER_LIMIT, TEMP_WARNING_TOLERANCE, enable_temp_warning, "Approaching temperature peak!");
    return 1;
}

int check_soc(float soc) {
    if (!is_within_range(soc, 20, SOC_UPPER_LIMIT, "State of Charge")) {
        return 0;
    }
    check_warning(soc, 20, SOC_WARNING_TOLERANCE, enable_soc_warning, "Approaching discharge!");
    check_warning(soc, SOC_UPPER_LIMIT, SOC_WARNING_TOLERANCE, enable_soc_warning, "Approaching charge-peak!");
    return 1;
}

int check_chargeRate(float chargeRate) {
    if (!is_within_range(chargeRate, 0, CHARGE_RATE_UPPER_LIMIT, "Charge Rate")) {
        return 0;
    }
    check_warning(chargeRate, CHARGE_RATE_UPPER_LIMIT, CHARGE_RATE_WARNING_TOLERANCE, enable_charge_rate_warning, "Approaching charge rate peak!");
    return 1;
}

int batteryIsOk(float temperature, float soc, float chargeRate) {
    return check_temperature(temperature) && check_soc(soc) && check_chargeRate(chargeRate);
}
