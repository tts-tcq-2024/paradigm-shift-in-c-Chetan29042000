#ifndef BATTERY_CHECK_H
#define BATTERY_CHECK_H

// Early warning tolerance for all parameters (5% of upper limits)
#define TEMP_UPPER_LIMIT 45.0
#define TEMP_WARNING_TOLERANCE (TEMP_UPPER_LIMIT * 0.05)
#define SOC_UPPER_LIMIT 80.0
#define SOC_WARNING_TOLERANCE (SOC_UPPER_LIMIT * 0.05)
#define CHARGE_RATE_UPPER_LIMIT 0.8
#define CHARGE_RATE_WARNING_TOLERANCE (CHARGE_RATE_UPPER_LIMIT * 0.05)

// Flags for enabling/disabling warnings for specific parameters
extern int enable_temp_warning;
extern int enable_soc_warning;
extern int enable_charge_rate_warning;

// Function prototypes
int check_temperature(float temperature);
int check_soc(float soc);
int check_chargeRate(float chargeRate);
int batteryIsOk(float temperature, float soc, float chargeRate);

#endif
