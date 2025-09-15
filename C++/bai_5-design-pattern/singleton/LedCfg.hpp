#ifndef LEDCFG_HPP
#define LEDCFG_HPP
typedef enum
{
    PORTA,
    PORTB,
    PORTC,
    PORTD
} GPIO_PORT;

typedef enum
{
    InputMode,
    OutputMode
} GPIO_Mode;

typedef enum
{
    Speed_LOW,
    Speed_HIGH,
} GPIO_Speed;

typedef enum
{
    Pin_LOW,
    Pin_HIGH,
    NOT_SET
} pinState;

typedef enum
{
    GPIO_PIN_0,
    GPIO_PIN_1,
    GPIO_PIN_2,
    GPIO_PIN_3,
    GPIO_PIN_4,
    GPIO_PIN_5
} GPIO_Pin;

typedef struct GPIO_StructInitTypedef
{
    GPIO_PORT Port;
    GPIO_Mode Mode;
    GPIO_Speed Speed;
} GPIO_StructInitTypedef;

typedef struct GPIOpin_StructConfig
{
    GPIO_Pin pin;
    pinState state;
} GPIOpin_StructConfig;
#endif
