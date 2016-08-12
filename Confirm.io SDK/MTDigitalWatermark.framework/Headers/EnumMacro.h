#ifndef EnumMacro_h
#define EnumMacro_h

#pragma mark - Enum Macros
// expansion macro for enum value definition
#define ENUM_VALUE(name,assign) name assign,

// expansion macro for enum to string conversion
#define ENUM_CASE(name,assign) case name: return @#name;

// expansion macro for string to enum conversion
#define ENUM_STRCMP(name,assign) if ([string isEqualToString:@#name]) return name;

/// declare the access function and define enum values
#define DECLARE_ENUM(EnumType,ENUM_DEF) \
    typedef enum EnumType { \
    ENUM_DEF(ENUM_VALUE) \
}EnumType; \
NSString *NSStringFrom##EnumType(EnumType value); \
EnumType EnumType##FromNSString(NSString *string);

// Define Functions
#define DEFINE_ENUM(EnumType, ENUM_DEF) \
    NSString *NSStringFrom##EnumType(EnumType value) \
    { \
        switch(value) \
        { \
            ENUM_DEF(ENUM_CASE) \
            default: return @""; \
        } \
    } \
EnumType EnumType##FromNSString(NSString *string) \
    { \
        ENUM_DEF(ENUM_STRCMP) \
        return (EnumType)0; \
    }

#endif


// ** Sample Use ********************************************
//      // Declare enums like so:
//
//  #define IMAGE_STATUS(XX)  \
//  XX(kDOImageStatusOK, = 0) \
//  XX(kDOImageStatusCached, )\
//  XX(kDOImageStatusRetry, )
//  DECLARE_ENUM(DOImageStatus, IMAGE_STATUS)
//
//      // Define Enum-To-NSString functions like so:
//  DEFINE_ENUM(DOImageStatus, IMAGE_STATUS)
//
//      //use them like this:
//  NSString *imageStatus = NSStringFromDOImageStatus(kDOImageStatusOK);
//  DOImageStatus statusFromString = DOImageStatusFromNSString(@"kDOImageStatusCached");